#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cstdlib>

class BillItem {
private:
    std::string itemName;
    int rate;
    int quantity;
public:
    BillItem() : itemName(""), rate(0), quantity(0) {}

    BillItem(std::string name, int r, int q) : itemName(name), rate(r), quantity(q) {}

    std::string getItemName() const {
        return itemName;
    }

    void setItemName(const std::string &name) {
        itemName = name;
    }

    int getRate() const {
        return rate;
    }

    void setRate(int r) {
        rate = r;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int q) {
        quantity = q;
    }
};

class Bill {
private:
    std::vector<BillItem> items;
    std::string customerName;
    std::string contactNumber;
    bool firstTimeCustomer;

public:
    void setCustomerInfo(const std::string &name, const std::string &number, bool firstTime) {
        customerName = name;
        contactNumber = number;
        firstTimeCustomer = firstTime;
    }

    void addItem(const BillItem &item) {
        items.push_back(item);
    }

    void removeItem(const std::string &itemName) {
        items.erase(std::remove_if(items.begin(), items.end(), [&](const BillItem &item) {
            return item.getItemName() == itemName;
        }), items.end());
    }

    int getTotal() const {
        int total = 0;
        for (const auto &item : items) {
            total += item.getRate() * item.getQuantity();
        }
        if (firstTimeCustomer) {
            // Apply 20% discount for first-time customers
            total -= total * 0.20;
        } else {
            // Apply 10% discount for returning customers
            total -= total * 0.10;
        }
        return total;
    }

    int getTotalItems() const {
        return items.size();
    }

    void printBill() const {
        std::cout << "\n\n\t\t***** Super Market Billing System *****\n\n";
        std::cout << "Customer Name: " << customerName << std::endl;
        std::cout << "Contact Number: " << contactNumber << std::endl;
        std::cout << std::setw(20) << std::left << "Item Name"
                  << std::setw(10) << std::left << "Rate"
                  << std::setw(10) << std::left << "Quantity"
                  << std::setw(10) << std::left << "Amount" << std::endl;
        for (const auto &item : items) {
            std::cout << std::setw(20) << std::left << item.getItemName()
                      << std::setw(10) << std::left << item.getRate()
                      << std::setw(10) << std::left << item.getQuantity()
                      << std::setw(10) << std::left << (item.getRate() * item.getQuantity()) << std::endl;
        }
        std::cout << "\n\t\tTotal Number of Items: " << getTotalItems() << std::endl;
        std::cout << "\n\t\tTotal Bill: " << getTotal() << std::endl;
        std::cout << "\n\t\tThanks For Shopping!\n\n";
    }

    void clearBill() {
        items.clear();
    }
};

void addItem(Bill &bill) {
    std::string itemName;
    int rate, quantity;
    std::cout << "\tEnter Item Name: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, itemName);
    std::cout << "\tEnter Rate Of Item: ";
    std::cin >> rate;
    std::cout << "\tEnter Quantity Of Item: ";
    std::cin >> quantity;

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    BillItem item(itemName, rate, quantity);
    bill.addItem(item);

    std::ofstream out("Bill.txt", std::ios::app);
    if (out.is_open()) {
        out << itemName << " : " << rate << " : " << quantity << std::endl;
        out.close();
    } else {
        std::cerr << "\tError: File Can't Open!" << std::endl;
    }
    std::cout << "\tItem Added Successfully" << std::endl;
}



void modifyBill(Bill &bill) {
    std::cout << "\n\tModify Bill Menu:" << std::endl;
    std::cout << "\t1. Add Item." << std::endl;
    std::cout << "\t2. Remove Item." << std::endl;
    std::cout << "\t3. Exit." << std::endl;
    std::cout << "\tEnter Choice: ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Clear input buffer
    
    switch (choice) {
        case 1:
            addItem(bill);
            break;
        case 2: {
            std::string itemName;
            std::cout << "\tEnter Item Name to remove: ";
            std::cin >> itemName;
            bill.removeItem(itemName);
            std::cout << "\tItem Removed Successfully" << std::endl;
            break;
        }
        case 3:
            std::cout << "\tExiting from Modify Bill menu." << std::endl;
            break;
        default:
            std::cout << "\tInvalid Choice! No modifications made." << std::endl;
    }
}

void printMainMenu() {
    std::cout << "\tWelcome To Super Market Billing System" << std::endl;
    std::cout << "\t**************************************" << std::endl;
    std::cout << "\t\t1. Add Item." << std::endl;
    std::cout << "\t\t2. Print Bill." << std::endl;
    std::cout << "\t\t3. Modify Bill." << std::endl;
    std::cout << "\t\t4. Exit." << std::endl;
    std::cout << "\t\tEnter Choice: ";
}

int main() {
    bool continueShopping = true;

    while (continueShopping) {
        Bill bill;
        std::string customerName, contactNumber;
        bool firstTimeCustomer;

        std::cout << "Are you shopping for the first time? (yes/no): ";
        std::string firstTimeResponse;
        std::cin >> firstTimeResponse;
        if (firstTimeResponse == "yes") {
            firstTimeCustomer = true;
        } else {
            firstTimeCustomer = false;
        }

        std::cout << "Enter Customer Name: ";
        std::cin.ignore(); // Clear input buffer
        std::getline(std::cin, customerName);

        std::cout << "Enter Contact Number: ";
        std::getline(std::cin, contactNumber);

        bill.setCustomerInfo(customerName, contactNumber, firstTimeCustomer);

        bool exit = false;
        while (!exit) {
            printMainMenu();
            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Clear input buffer

            switch (choice) {
                case 1:
                    addItem(bill);
                    break;
                case 2:
                    bill.printBill();
                    break;
                case 3:
                    modifyBill(bill);
                    break;
                case 4:
                    exit = true;
                    std::cout << "\tGood Luck!" << std::endl;
                    break;
                default:
                    std::cout << "\tInvalid Choice! Please choose again." << std::endl;
            }
        }

        std::string response;
        std::cout << "Do you want to continue Billing? (yes/no): ";
        std::cin >> response;
        if (response != "yes")
            continueShopping = false;
    }

    return 0;
}

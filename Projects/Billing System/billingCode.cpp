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
        std::cout << "\n\n\t\t***** Sammy's Super Market *****\n\n";
        std::cout << "\t\t ***Invoice***\n\n "<< std::endl;
        std::cout << "Customer Name: " << customerName << std::endl;
        std::cout << "Contact Number: \n" << contactNumber << std::endl;
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

    // Writing item details to file (if needed)...
    std::cout << "\tItem Added Successfully" << std::endl;
}

// Function to modify the bill
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
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, itemName);
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

// Function to print the main menu
    void printMainMenu() {
        std::cout << "\tWelcome To Sammy's Super Market " << std::endl;
        std::cout << "\t**************************************" << std::endl;
        std::cout << "\t\t1. Add Item." << std::endl;
        std::cout << "\t\t2. Print Bill." << std::endl;
        std::cout << "\t\t3. Modify Bill." << std::endl;
        std::cout << "\t\t4. Exit." << std::endl;
        std::cout << "\t\tEnter Choice: ";
}


class SalesManager {
private:
    std::string name;
    int id;
    std::vector<std::pair<std::string, int>> storeItems; // {item name, quantity}

public:
    SalesManager(const std::string& n, int i) : name(n), id(i) {}

    void addItemToStore() {
        std::string itemName;
        int quantity;
        std::cout << "\tEnter Item Name: ";
        std::cin.ignore(); // Clear input buffer
        std::getline(std::cin, itemName);
        std::cout << "\tEnter Quantity Of Item: ";
        std::cin >> quantity;

        storeItems.push_back(std::make_pair(itemName, quantity));
        std::cout << "\tItem Added to Store Successfully" << std::endl;
    }

    void removeItemFromStore() {
        std::string itemName;
        std::cout << "\tEnter Item Name to remove: ";
        std::cin.ignore(); // Clear input buffer
        std::getline(std::cin, itemName);

        auto it = std::find_if(storeItems.begin(), storeItems.end(), [&](const std::pair<std::string, int>& item) {
            return item.first == itemName;
        });

        if (it != storeItems.end()) {
            storeItems.erase(it);
            std::cout << "\tItem Removed from Store Successfully" << std::endl;
        } else {
            std::cout << "\tItem not found in Store" << std::endl;
        }
    }

    void displayAllItems() {
        std::cout << "\n\t\t***** Items in Store *****\n\n";
        for (const auto& item : storeItems) {
            std::cout << "\tItem Name: " << item.first << ", Quantity: " << item.second << std::endl;
        }
        std::cout << "\n\t\tEnd of Store Items\n\n";
    }

    void searchItemInStore() {
        std::string itemName;
        std::cout << "\tEnter Item Name to search: ";
        std::cin.ignore(); // Clear input buffer
        std::getline(std::cin, itemName);

        auto it = std::find_if(storeItems.begin(), storeItems.end(), [&](const std::pair<std::string, int>& item) {
            return item.first == itemName;
        });

        if (it != storeItems.end()) {
            std::cout << "\tItem Found in Store, Quantity: " << it->second << std::endl;
        } else {
            std::cout << "\tItem not found in Store" << std::endl;
        }
    }

    void printManagerInfo() const {
        std::cout << "\tSales Manager Name: " << name << std::endl;
        std::cout << "\tSales Manager ID: " << id << std::endl;
    }
};

int main() {
    std::string managerType;
    bool continueProgram = true;

    while (continueProgram) {
        std::cout << "Are you a Billing Manager or Sales Manager? (billing/sales): ";
        std::cin >> managerType;

        if (managerType == "billing") {
            // Billing Manager
            std::cout << "Enter Billing Manager Name: ";
            std::string billingManagerName;
            std::cin >> billingManagerName;

            std::cout << "Enter Billing Manager ID: ";
            int billingManagerID;
            std::cin >> billingManagerID;

            std::cout << "Billing Manager Name: " << billingManagerName << std::endl;
            std::cout << "Billing Manager ID: " << billingManagerID << std::endl;

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

        } else if (managerType == "sales") {
            // Sales Manager
            std::cout << "Enter Sales Manager Name: ";
            std::string salesManagerName;
            std::cin >> salesManagerName;

            std::cout << "Enter Sales Manager ID: ";
            int salesManagerID;
            std::cin >> salesManagerID;

            SalesManager salesManager(salesManagerName, salesManagerID);

            bool continueSales = true;
            while (continueSales) {
                std::cout << "\nSammy's Store : Sales Manager Menu:" << std::endl;
                std::cout << "1. Add Item to Store." << std::endl;
                std::cout << "2. Remove Item from Store." << std::endl;
                std::cout << "3. Display all Items in Store." << std::endl;
                std::cout << "4. Search an Item in Store." << std::endl;
                std::cout << "5. Exit." << std::endl;
                std::cout << "Enter Choice: ";

                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1:
                        salesManager.addItemToStore();
                        break;
                    case 2:
                        salesManager.removeItemFromStore();
                        break;
                    case 3:
                        salesManager.displayAllItems();
                        break;
                    case 4:
                        salesManager.searchItemInStore();
                        break;
                    case 5:
                        continueSales = false;
                        break;
                    default:
                        std::cout << "Invalid Choice! Please choose again." << std::endl;
                }
            }
        } else {
            std::cout << "Invalid Choice!" << std::endl;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Ask if the user wants to continue
        std::cout << "Do you want to continue? (yes/no): ";
        std::string response;
        std::cin >> response;
        if (response != "yes")
            continueProgram = false;
    }

    return 0;
}

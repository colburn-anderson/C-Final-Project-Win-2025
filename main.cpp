#include "Inventory.h"
#include "Tobacco.h"
#include "LotteryTickets.h"
#include "GroceryItem.h"
#include <iostream>
#include <limits>
#include <memory>
#include <iomanip>

using namespace std;

// Color codes
const string RESET   = "\033[0m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string BLUE    = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN    = "\033[36m";
const string BOLD    = "\033[1m";

// Function to clear input buffer and handle invalid input
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to get valid float input
float getValidFloat(const string& prompt) {
    float value;
    while (true) {
        cout << CYAN << prompt << RESET;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        cout << RED << "Invalid input. Please enter a number.\n" << RESET;
        clearInputBuffer();
    }
}

// Function to get valid integer input
int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << CYAN << prompt << RESET;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        cout << RED << "Invalid input. Please enter a whole number.\n" << RESET;
        clearInputBuffer();
    }
}

// Function to display menu and get choice
int displayMenu() {
    cout << BOLD << BLUE << "\n=== POS System Menu ===" << RESET << "\n";
    cout << YELLOW << "1. Search Inventory\n";
    cout << GREEN << "2. Sales & Revenue\n";
    cout << MAGENTA << "3. Add New Inventory\n";
    cout << CYAN << "4. Remove Inventory\n";
    cout << RED << "5. Exit\n" << RESET;
    cout << BOLD << "Enter your choice (1-5): " << RESET;
    
    int choice;
    cin >> choice;
    clearInputBuffer();
    return choice;
}

// Function to handle search menu
void handleSearch(const Inventory& inventory) {
    cout << BOLD << BLUE << "\n=== Search Options ===" << RESET << "\n";
    cout << YELLOW << "1. Search by Category\n";
    cout << "2. Search by Name\n";
    cout << "3. Search by Price Range\n";
    cout << "4. Display All Products\n" << RESET;
    cout << BOLD << "Enter your choice (1-4): " << RESET;
    
    int choice;
    cin >> choice;
    clearInputBuffer();
    
    switch (choice) {
        case 1: {
            string category;
            cout << CYAN << "Enter category: " << RESET;
            getline(cin, category);
            auto results = inventory.searchByCategory(category);
            if (results.empty()) {
                cout << RED << "No products found in category: " << category << RESET << endl;
            } else {
                for (const auto& product : results) {
                    cout << GREEN;
                    product->displayInfo();
                    cout << BLUE << "------------------------\n" << RESET;
                }
            }
            break;
        }
        case 2: {
            string name;
            cout << CYAN << "Enter product name: " << RESET;
            getline(cin, name);
            auto results = inventory.searchByName(name);
            if (results.empty()) {
                cout << RED << "No products found with name: " << name << RESET << endl;
            } else {
                for (const auto& product : results) {
                    cout << GREEN;
                    product->displayInfo();
                    cout << BLUE << "------------------------\n" << RESET;
                }
            }
            break;
        }
        case 3: {
            float min = getValidFloat("Enter minimum price: ");
            float max = getValidFloat("Enter maximum price: ");
            auto results = inventory.searchByPriceRange(min, max);
            if (results.empty()) {
                cout << RED << "No products found in price range: $" << min << " - $" << max << RESET << endl;
            } else {
                for (const auto& product : results) {
                    cout << GREEN;
                    product->displayInfo();
                    cout << BLUE << "------------------------\n" << RESET;
                }
            }
            break;
        }
        case 4:
            inventory.displayAllProducts();
            break;
        default:
            cout << RED << "Invalid choice.\n" << RESET;
    }
}

// Function to handle selling products
void handleSell(Inventory& inventory) {
    cout << BOLD << BLUE << "\n=== Sell Product ===" << RESET << "\n";
    cout << CYAN << "Enter product ID to sell: " << RESET;
    string id;
    getline(cin, id);
    
    auto product = inventory.getProductById(id);
    if (product) {
        cout << GREEN << "Product found:\n" << RESET;
        product->displayInfo();
        
        int availableQuantity = product->getQuantity();
        if (availableQuantity <= 0) {
            cout << RED << "This product is out of stock.\n" << RESET;
            return;
        }
        
        cout << YELLOW << "\nAvailable quantity: " << availableQuantity << RESET << endl;
        int sellQuantity = getValidInt("Enter quantity to sell: ");
        
        if (sellQuantity <= 0) {
            cout << RED << "Invalid quantity.\n" << RESET;
            return;
        }
        
        if (sellQuantity > availableQuantity) {
            cout << RED << "Not enough stock available. Only " << availableQuantity << " available.\n" << RESET;
            return;
        }
        
        cout << YELLOW << "\nConfirm sale of " << sellQuantity << " items? (y/n): " << RESET;
        char confirm;
        cin >> confirm;
        clearInputBuffer();
        
        if (confirm == 'y' || confirm == 'Y') {
            float salePrice = product->computePrice() * sellQuantity;
            inventory.addToSales(salePrice);  // Track the sale
            inventory.updateProductQuantity(id, -sellQuantity);  // Decrease quantity
            cout << GREEN << "Product sold successfully for $" << fixed << setprecision(2) << salePrice << "\n" << RESET;
        } else {
            cout << YELLOW << "Sale cancelled.\n" << RESET;
        }
    } else {
        cout << RED << "Product not found.\n" << RESET;
    }
}

// Function to display total sales
void displayTotalSales(const Inventory& inventory) {
    cout << BOLD << BLUE << "\n=== Total Sales ===" << RESET << "\n";
    cout << GREEN << "Total Gross Revenue: $" << fixed << setprecision(2) << inventory.getTotalSales() << "\n" << RESET;
}

// Function to handle adding new inventory
void handleAdd(Inventory& inventory) {
    cout << "\n=== Add New Product ===" << endl;
    cout << "1. Add Tobacco Product" << endl;
    cout << "2. Add Lottery Ticket" << endl;
    cout << "3. Add Grocery Item" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "Enter your choice (1-4): ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    string id, name, expDate;
    float price;
    int quantity;
    
    switch(choice) {
        case 1: {
            cout << "Enter Tobacco Product ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Expiration Date (YYYY-MM-DD): ";
            getline(cin, expDate);
            cout << "Enter Base Price: $";
            cin >> price;
            cout << "Enter Special Tax: $";
            float specialTax;
            cin >> specialTax;
            cout << "Enter Quantity: ";
            cin >> quantity;
            
            auto tobacco = make_shared<Tobacco>(id, name, expDate, price, specialTax, quantity);
            inventory.addProduct(tobacco);
            cout << "\nTobacco product added successfully!" << endl;
            break;
        }
        case 2: {
            cout << "Enter Lottery Ticket ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Base Price: $";
            cin >> price;
            cout << "Enter Quantity: ";
            cin >> quantity;
            
            auto lottery = make_shared<LotteryTickets>(id, name, price, quantity);
            inventory.addProduct(lottery);
            cout << "\nLottery ticket added successfully!" << endl;
            cout << "Note: City Tax (7%) and County Tax (3%) are automatically applied." << endl;
            break;
        }
        case 3: {
            cout << "Enter Grocery Item ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Expiration Date (YYYY-MM-DD): ";
            getline(cin, expDate);
            cout << "Enter Base Price: $";
            cin >> price;
            cout << "Enter Sales Tax: $";
            float salesTax;
            cin >> salesTax;
            cout << "Is Perishable? (1 for Yes, 0 for No): ";
            bool isPerishable;
            cin >> isPerishable;
            cout << "Enter Quantity: ";
            cin >> quantity;
            
            auto grocery = make_shared<GroceryItem>(id, name, expDate, price, salesTax, isPerishable, quantity);
            inventory.addProduct(grocery);
            cout << "\nGrocery item added successfully!" << endl;
            break;
        }
        case 4:
            return;
        default:
            cout << "Invalid choice!" << endl;
    }
}

// Function to handle removing inventory
void handleRemove(Inventory& inventory) {
    string id;
    cout << CYAN << "Enter product ID to remove: " << RESET;
    getline(cin, id);
    
    if (inventory.removeProduct(id)) {
        cout << GREEN << "Product removed successfully.\n" << RESET;
    } else {
        cout << RED << "Product not found with ID: " << id << RESET << endl;
    }
}

// Function to handle sales and revenue menu
void handleSalesAndRevenue(Inventory& inventory) {
    cout << BOLD << BLUE << "\n=== Sales & Revenue ===" << RESET << "\n";
    cout << YELLOW << "1. Sell Product\n";
    cout << "2. View Total Revenue\n" << RESET;
    cout << BOLD << "Enter your choice (1-2): " << RESET;
    
    int choice;
    cin >> choice;
    clearInputBuffer();
    
    switch (choice) {
        case 1:
            handleSell(inventory);
            break;
        case 2:
            displayTotalSales(inventory);
            break;
        default:
            cout << RED << "Invalid choice.\n" << RESET;
    }
}

int main() {
    Inventory inventory;  // Loads products from JSON file
    
    cout << BOLD << GREEN << "Welcome to the POS System\n" << RESET;
    
    while (true) {
        int choice = displayMenu();
        
        switch (choice) {
            case 1:
                handleSearch(inventory);
                break;
            case 2:
                handleSalesAndRevenue(inventory);
                break;
            case 3:
                handleAdd(inventory);
                break;
            case 4:
                handleRemove(inventory);
                break;
            case 5:
                cout << BOLD << RED << "Thank you for using the POS System!\n" << RESET;
                return 0;
            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
        }
    }
    
    return 0;
} 
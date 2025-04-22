#include "DatabaseManager.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor initializes the database file path
DatabaseManager::DatabaseManager(const string& file) : filename(file) {}

// Load all products from the JSON file
vector<shared_ptr<Product>> DatabaseManager::loadProducts() {
    vector<shared_ptr<Product>> products;
    
    try {
        // Open the JSON file
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No existing database file found. Starting with empty inventory." << endl;
            return products;
        }
        
        // Parse the JSON file
        json j;
        file >> j;
        
        // Check if the JSON has a "products" array
        if (!j.contains("products") || !j["products"].is_array()) {
            cout << "Invalid database format. Starting with empty inventory." << endl;
            return products;
        }
        
        // Convert each JSON object to a Product
        for (const auto& productJson : j["products"]) {
            try {
                shared_ptr<Product> product = jsonToProduct(productJson);
                if (product) {
                    products.push_back(product);
                }
            } catch (const exception& e) {
                cout << "Error loading product: " << e.what() << endl;
            }
        }
        
    } catch (const exception& e) {
        cout << "Error reading database: " << e.what() << endl;
    }
    
    return products;
}

// Save all products to the JSON file
bool DatabaseManager::saveProducts(const vector<shared_ptr<Product>>& products) {
    try {
        // Create a JSON array to store all products
        json j;
        j["products"] = json::array();
        
        // Convert each product to JSON and add to the array
        for (const auto& product : products) {
            j["products"].push_back(productToJson(product));
        }
        
        // Write the JSON to the file
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open database file for writing." << endl;
            return false;
        }
        
        file << j.dump(4);  // Pretty print with 4 spaces indentation
        return true;
        
    } catch (const exception& e) {
        cout << "Error saving to database: " << e.what() << endl;
        return false;
    }
}

// Convert a JSON object to a Product
shared_ptr<Product> DatabaseManager::jsonToProduct(const json& j) {
    // Extract common product fields
    string type = j["type"].get<string>();
    string id = j["id"].get<string>();
    string name = j["name"].get<string>();
    double price = j["price"].get<double>();
    int quantity = j["quantity"].get<int>();
    
    // Create the appropriate product type
    if (type == "Tobacco") {
        double specialTax = j["specialTax"].get<double>();
        string expDate = j["expDate"].get<string>();
        return make_shared<Tobacco>(id, name, expDate, price, specialTax, quantity);
    }
    else if (type == "Lottery") {
        return make_shared<LotteryTickets>(id, name, price, quantity);
    }
    else if (type == "Grocery") {
        double salesTax = j["salesTax"].get<double>();
        bool isPerishable = j["isPerishable"].get<bool>();
        string expDate = j["expDate"].get<string>();
        return make_shared<GroceryItem>(id, name, expDate, price, salesTax, isPerishable, quantity);
    }
    
    return nullptr;
}

// Convert a Product to a JSON object
json DatabaseManager::productToJson(const shared_ptr<Product>& product) {
    json j;
    
    // Set common product fields
    j["id"] = product->getId();
    j["name"] = product->getName();
    j["category"] = product->getCategory();
    j["price"] = product->getBasePrice();
    j["quantity"] = product->getQuantity();
    
    // Set type-specific fields
    if (auto tobacco = dynamic_pointer_cast<Tobacco>(product)) {
        j["type"] = "Tobacco";
        j["specialTax"] = tobacco->getSpecialTax();
        j["expDate"] = tobacco->getExpDate();
    }
    else if (auto lottery = dynamic_pointer_cast<LotteryTickets>(product)) {
        j["type"] = "Lottery";
    }
    else if (auto grocery = dynamic_pointer_cast<GroceryItem>(product)) {
        j["type"] = "Grocery";
        j["salesTax"] = grocery->getSalesTax();
        j["isPerishable"] = grocery->getIsPerishable();
        j["expDate"] = grocery->getExpDate();
    }
    
    return j;
} 
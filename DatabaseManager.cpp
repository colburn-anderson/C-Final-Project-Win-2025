#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const string& file) : filename(file) {}

vector<shared_ptr<Product>> DatabaseManager::loadProducts() {
    vector<shared_ptr<Product>> products;
    try {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Warning: Could not open database file. Starting with empty inventory." << endl;
            return products;
        }
        
        json j;
        file >> j;
        
        for (const auto& product_json : j["products"]) {
            try {
                auto product = jsonToProduct(product_json);
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

bool DatabaseManager::saveProducts(const vector<shared_ptr<Product>>& products) {
    try {
        json j;
        j["products"] = json::array();
        
        for (const auto& product : products) {
            j["products"].push_back(productToJson(product));
        }
        
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open database file for writing." << endl;
            return false;
        }
        
        file << setw(4) << j << endl;
        return true;
        
    } catch (const exception& e) {
        cout << "Error saving to database: " << e.what() << endl;
        return false;
    }
}

shared_ptr<Product> DatabaseManager::jsonToProduct(const json& j) {
    string type = j["type"];
    string id = j["id"];
    string name = j["name"];
    string category = j["category"];
    string expDate = j["expDate"];
    float price = j["price"];
    
    if (type == "Tobacco") {
        float specialTax = j["specialTax"];
        return make_shared<Tobacco>(id, name, expDate, price, specialTax);
    }
    else if (type == "LotteryTickets") {
        float cityTax = j["cityTax"];
        float countyTax = j["countyTax"];
        return make_shared<LotteryTickets>(id, name, expDate, price, cityTax, countyTax);
    }
    else if (type == "Grocery") {
        float salesTax = j["salesTax"];
        bool isPerishable = j["isPerishable"];
        return make_shared<GroceryItem>(id, name, expDate, price, salesTax, isPerishable);
    }
    
    throw runtime_error("Unknown product type: " + type);
}

json DatabaseManager::productToJson(const shared_ptr<Product>& product) {
    json j;
    j["id"] = product->getId();
    j["name"] = product->getName();
    j["category"] = product->getCategory();
    j["expDate"] = product->getExpDate();
    j["price"] = product->getBasePrice();
    
    // Check product type and add specific fields
    if (auto tobacco = dynamic_pointer_cast<Tobacco>(product)) {
        j["type"] = "Tobacco";
        j["specialTax"] = tobacco->getSpecialTax();
    }
    else if (auto lottery = dynamic_pointer_cast<LotteryTickets>(product)) {
        j["type"] = "LotteryTickets";
        j["cityTax"] = lottery->getCityTax();
        j["countyTax"] = lottery->getCountyTax();
    }
    else if (auto grocery = dynamic_pointer_cast<GroceryItem>(product)) {
        j["type"] = "Grocery";
        j["salesTax"] = grocery->getSalesTax();
        j["isPerishable"] = grocery->getIsPerishable();
    }
    
    return j;
} 
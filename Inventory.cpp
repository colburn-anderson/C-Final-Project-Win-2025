#include "Inventory.h"
#include "Tobacco.h"
#include "LotteryTickets.h"
#include "GroceryItem.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// Helper function to round to 3 decimal places
float roundTo3Decimals(float value) {
    return round(value * 1000) / 1000;
}

// Constructor loads from database
Inventory::Inventory() {
    loadFromDatabase();
}

// Destructor saves to database
Inventory::~Inventory() {
    saveToDatabase();
}

// Add a product to inventory
void Inventory::addProduct(shared_ptr<Product> product) {
    products.push_back(product);
    saveToDatabase();
}

// Remove a product by ID
bool Inventory::removeProduct(const string& id) {
    auto it = find_if(products.begin(), products.end(),
        [&id](const shared_ptr<Product>& p) { return p->getId() == id; });
    
    if (it != products.end()) {
        products.erase(it);
        saveToDatabase();
        return true;
    }
    return false;
}

// Search by category
vector<shared_ptr<Product>> Inventory::searchByCategory(const string& category) const {
    vector<shared_ptr<Product>> results;
    for (const auto& product : products) {
        if (product->getCategory() == category) {
            results.push_back(product);
        }
    }
    return results;
}

// Search by name
vector<shared_ptr<Product>> Inventory::searchByName(const string& name) const {
    vector<shared_ptr<Product>> results;
    for (const auto& product : products) {
        if (product->getName() == name) {
            results.push_back(product);
        }
    }
    return results;
}

// Search by price range
vector<shared_ptr<Product>> Inventory::searchByPriceRange(float min, float max) const {
    vector<shared_ptr<Product>> results;
    for (const auto& product : products) {
        float price = product->computePrice();
        if (price >= min && price <= max) {
            results.push_back(product);
        }
    }
    return results;
}

// Get product by ID
shared_ptr<Product> Inventory::getProductById(const string& id) const {
    for (const auto& product : products) {
        if (product->getId() == id) {
            return product;
        }
    }
    return nullptr;
}

// Display all products making sure the categories are displayed together
void Inventory::displayAllProducts() const {
    if (products.empty()) {
        cout << "No products in inventory." << endl;
        return;
    }
    
    cout << "\n=== Current Inventory ===" << endl;
    
    // Display Tobacco products
    cout << "\n=== Tobacco Products ===" << endl;
    for (const auto& product : products) {
        if (product->getCategory() == "Tobacco") {
            product->displayInfo();
            cout << "------------------------" << endl;
        }
    }
    
    // Display Lottery products
    cout << "\n=== Lottery Products ===" << endl;
    for (const auto& product : products) {
        if (product->getCategory() == "Lottery") {
            product->displayInfo();
            cout << "------------------------" << endl;
        }
    }
    
    // Display Grocery products
    cout << "\n=== Grocery Products ===" << endl;
    for (const auto& product : products) {
        if (product->getCategory() == "Grocery") {
            product->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

// Get total number of products
size_t Inventory::getProductCount() const {
    return products.size();
}

// Save current state to database
void Inventory::saveToDatabase() {
    json productsJson = json::array();
    for (const auto& product : products) {
        json productJson;
        productJson["id"] = product->getId();
        productJson["name"] = product->getName();
        productJson["category"] = product->getCategory();
        productJson["basePrice"] = roundTo3Decimals(product->getBasePrice());
        productJson["quantity"] = product->getQuantity();
        
        if (auto tobacco = dynamic_pointer_cast<Tobacco>(product)) {
            productJson["type"] = "tobacco";
            productJson["expDate"] = product->getExpDate();
            productJson["specialTax"] = roundTo3Decimals(tobacco->getSpecialTax());
        }
        else if (auto lottery = dynamic_pointer_cast<LotteryTickets>(product)) {
            productJson["type"] = "lottery";
            
        }
        else if (auto grocery = dynamic_pointer_cast<GroceryItem>(product)) {
            productJson["type"] = "grocery";
            productJson["expDate"] = product->getExpDate();
            productJson["salesTax"] = roundTo3Decimals(grocery->getSalesTax());
            productJson["isPerishable"] = grocery->getIsPerishable();
        }
        
        productsJson.push_back(productJson);
    }
    
    json mainJson;
    mainJson["products"] = productsJson;
    mainJson["totalSales"] = roundTo3Decimals(totalSales);
    
    ofstream file("products.json");
    file << setw(4) << mainJson << endl;
}

void Inventory::loadFromDatabase() {
    products.clear();
    
    ifstream file("products.json");
    if (!file.is_open()) {
        return;
    }
    
    json mainJson;
    file >> mainJson;
    
    if (mainJson.contains("totalSales")) {
        totalSales = mainJson["totalSales"];
    }
    
    if (mainJson.contains("products")) {
        for (const auto& productJson : mainJson["products"]) {
            string type = productJson["type"];
            string id = productJson["id"];
            string name = productJson["name"];
            float basePrice = productJson["basePrice"];
            int quantity = productJson["quantity"];
            
            if (type == "tobacco") {
                string expDate = productJson["expDate"];
                float specialTax = productJson["specialTax"];
                products.push_back(make_shared<Tobacco>(id, name, expDate, basePrice, specialTax, quantity));
            }
            else if (type == "lottery") {
                products.push_back(make_shared<LotteryTickets>(id, name, basePrice, quantity));
            }
            else if (type == "grocery") {
                string expDate = productJson["expDate"];
                float salesTax = productJson["salesTax"];
                bool isPerishable = productJson["isPerishable"];
                products.push_back(make_shared<GroceryItem>(id, name, expDate, basePrice, salesTax, isPerishable, quantity));
            }
        }
    }
}

bool Inventory::updateProductQuantity(const string& id, int quantityChange) {
    auto product = getProductById(id);
    if (product) {
        int newQuantity = product->getQuantity() + quantityChange;
        if (newQuantity < 0) {
            return false;  // Can't have negative quantity
        }
        product->setQuantity(newQuantity);
        saveToDatabase();  // Save changes to database
        return true;
    }
    return false;
} 
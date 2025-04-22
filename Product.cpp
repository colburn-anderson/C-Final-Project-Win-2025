#include "Product.h"
#include <iostream>

using namespace std;

// Color codes for product display
const string RESET   = "\033[0m";
const string CYAN    = "\033[36m";
const string YELLOW  = "\033[33m";

// Constructor implementation
Product::Product(const string& id, const string& name, const string& category, 
                const string& expDate, double basePrice, int quantity)
    : id(id), name(name), category(category), expDate(expDate), 
      basePrice(basePrice), quantity(quantity) {}

// Getter implementations
string Product::getId() const {
    return id;
}

string Product::getCategory() const {
    return category;
}

string Product::getName() const {
    return name;
}

string Product::getExpDate() const {
    return expDate;
}

double Product::getBasePrice() const {
    return basePrice;
}

int Product::getQuantity() const {
    return quantity;
}

// Setter implementation
void Product::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

// Display product information
void Product::displayInfo() const {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Category: " << category << endl;
    cout << "Expiration Date: " << expDate << endl;
    cout << "Base Price: $" << basePrice << endl;
    cout << "Quantity: " << quantity << endl;
} 
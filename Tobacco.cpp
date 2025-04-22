#include "Tobacco.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor implementation
Tobacco::Tobacco(const string& id, const string& name, const string& expDate, double basePrice, double specialTax, int quantity)
    : Product(id, name, "Tobacco", expDate, basePrice, quantity), specialTax(specialTax) {}

// Compute final price including special tax
double Tobacco::computePrice() const {
    return roundTo3Decimals(getBasePrice() + specialTax);
}

// Display tobacco product information including tax
void Tobacco::displayInfo() const {
    cout << "ID: " << getId() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Category: " << getCategory() << endl;
    cout << "Expiration Date: " << getExpDate() << endl;
    cout << "Base Price: $" << fixed << setprecision(3) << getBasePrice() << endl;
    cout << "Special Tax: $" << fixed << setprecision(3) << specialTax << endl;
    cout << "Total Price: $" << fixed << setprecision(3) << computePrice() << endl;
    cout << "Quantity: " << getQuantity() << endl;
}

// Getter for special tax
double Tobacco::getSpecialTax() const {
    return specialTax;
} 
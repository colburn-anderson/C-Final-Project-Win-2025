#include "GroceryItem.h"
#include <iomanip>
#include <iostream>

using namespace std;

// Constructor implementation
GroceryItem::GroceryItem(const string& id, const string& name, const string& expDate, 
                        double basePrice, double salesTax, bool isPerishable, int quantity)
    : Product(id, name, "Grocery", expDate, basePrice, quantity),
      salesTax(salesTax), isPerishable(isPerishable) {}

// Compute final price including sales tax
double GroceryItem::computePrice() const {
    return getBasePrice() * (1.0 + salesTax);
}

// Display grocery item information
void GroceryItem::displayInfo() const {
    cout << "Grocery Item: " << getName() << endl;
    cout << "ID: " << getId() << endl;
    cout << "Expiration Date: " << getExpDate() << endl;
    cout << "Base Price: $" << fixed << setprecision(2) << getBasePrice() << endl;
    cout << "Sales Tax: " << fixed << setprecision(2) << (salesTax * 100) << "%" << endl;
    cout << "Final Price: $" << fixed << setprecision(2) << computePrice() << endl;
    cout << "Perishable: " << (isPerishable ? "Yes" : "No") << endl;
    cout << "Quantity: " << getQuantity() << endl;
    cout << "------------------------" << endl;
}

// Getters implementation
double GroceryItem::getSalesTax() const {
    return salesTax;
}

bool GroceryItem::getIsPerishable() const {
    return isPerishable;
} 
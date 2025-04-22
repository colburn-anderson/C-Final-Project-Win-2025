#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include "Product.h"
#include <string>

using namespace std;

// GroceryItem class that inherits from Product
class GroceryItem : public Product {
private:
    double salesTax;    // Sales tax for grocery items
    bool isPerishable;  // Whether the item is perishable

public:
    // Constructor
    GroceryItem(const string& id, const string& name, const string& expDate, 
               double basePrice, double salesTax, bool isPerishable, int quantity = 0);
    
    // Override the computePrice method to include sales tax
    double computePrice() const override;
    
    // Override the display method to show grocery-specific information
    void displayInfo() const override;
    
    // Getters
    double getSalesTax() const;
    bool getIsPerishable() const;
};

#endif // GROCERYITEM_H 
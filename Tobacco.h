#ifndef TOBACCO_H
#define TOBACCO_H

#include "Product.h"
#include <string>

using namespace std;

// Tobacco class that inherits from Product
class Tobacco : public Product {
private:
    double specialTax;  // Special tax for tobacco products

public:
    // Constructor
    Tobacco(const string& id, const string& name, const string& expDate, 
           double basePrice, double specialTax, int quantity = 0);
    
    // Override the computePrice method to include special tax
    double computePrice() const override;
    
    // Override the display method to show tobacco-specific information
    void displayInfo() const override;
    
    // Getter for special tax
    double getSpecialTax() const;
};

#endif // TOBACCO_H 
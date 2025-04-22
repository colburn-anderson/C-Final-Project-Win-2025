#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <memory>

using namespace std;

// Helper function to round to 3 decimal places
inline double roundTo3Decimals(double value) {
    return round(value * 1000) / 1000;
}

// Base Product class that defines common attributes and behaviors for all products
class Product {
protected:
    // Protected member variables accessible by derived classes
    string id;
    string category;
    string name;
    string expDate;
    double basePrice;  // Changed from float to double
    int quantity;  // Add quantity field

public:
    // Constructor
    Product(const string& id, const string& name, const string& category, const string& expDate, double basePrice, int quantity = 0);
    
    // Virtual destructor for proper cleanup of derived classes
    virtual ~Product() = default;

    // Getter methods
    string getId() const;
    string getCategory() const;
    string getName() const;
    string getExpDate() const;
    double getBasePrice() const;
    int getQuantity() const;  // Getter for quantity

    // Setter methods
    void setQuantity(int newQuantity);  // Add setter for quantity

    // Pure virtual function that derived classes must implement
    virtual double computePrice() const = 0;

    // Virtual function for displaying product information
    virtual void displayInfo() const = 0;
};

#endif 
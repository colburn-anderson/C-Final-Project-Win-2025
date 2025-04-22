#ifndef INVENTORY_H
#define INVENTORY_H
#include "Product.h"
#include "Tobacco.h"
#include "LotteryTickets.h"
#include "GroceryItem.h"
#include <vector>
#include <memory>
#include <string>

using namespace std;

// Inventory class to manage the collection of products
class Inventory {
private:
    // Using smart pointers to manage product objects
    vector<shared_ptr<Product> > products;
    float totalSales = 0.0;  // Track total sales revenue

    void saveToDatabase();
    void loadFromDatabase();

public:
    // Constructor now loads from database
    Inventory();
    
    // Destructor saves to database
    ~Inventory();
    
    // Add a product to inventory
    void addProduct(shared_ptr<Product> product);
    
    // Remove a product by ID
    bool removeProduct(const string& id);
    
    // Search functions
    vector<shared_ptr<Product> > searchByCategory(const string& category) const;
    vector<shared_ptr<Product> > searchByName(const string& name) const;
    vector<shared_ptr<Product> > searchByPriceRange(float minPrice, float maxPrice) const;
    
    // Get product by ID
    shared_ptr<Product> getProductById(const string& id) const;
    
    // Display all products
    void displayAllProducts() const;
    
    // Get total number of products
    size_t getProductCount() const;
    
    // Get total sales
    float getTotalSales() const { return totalSales; }
    
    // Add to sales
    void addToSales(float amount) { totalSales += amount; }
    
    // Update product quantity
    bool updateProductQuantity(const string& id, int quantityChange);
    
    // Add method to update total sales
    void addToTotalSales(float amount) {
        totalSales += amount;
    }
};

#endif 
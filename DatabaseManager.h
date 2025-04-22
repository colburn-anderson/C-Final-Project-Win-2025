#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Product.h"
#include "Tobacco.h"
#include "LotteryTickets.h"
#include "GroceryItem.h"
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include "json.hpp" // We'll download this

using json = nlohmann::json;
using namespace std;

class DatabaseManager {
private:
    string filename;
    
    // Helper methods to convert between JSON and Product objects
    shared_ptr<Product> jsonToProduct(const json& j);
    json productToJson(const shared_ptr<Product>& product);
    
public:
    DatabaseManager(const string& file = "products.json");
    
    // Load all products from JSON file
    vector<shared_ptr<Product>> loadProducts();
    
    // Save all products to JSON file
    bool saveProducts(const vector<shared_ptr<Product>>& products);
    
};

#endif 
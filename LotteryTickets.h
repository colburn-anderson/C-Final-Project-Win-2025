#ifndef LOTTERYTICKETS_H
#define LOTTERYTICKETS_H

#include "Product.h"
#include <string>

using namespace std;

// LotteryTickets class that inherits from Product
class LotteryTickets : public Product {
private:
    static constexpr double CITY_TAX = 0.07;    // Fixed 7% city tax
    static constexpr double COUNTY_TAX = 0.03;  // Fixed 3% county tax

public:
    // Constructor
    LotteryTickets(const string& id, const string& name, double basePrice, int quantity = 0);
    
    // Override the computePrice method to include both taxes
    double computePrice() const override;
    
    // Override the display method to show lottery-specific information
    void displayInfo() const override;
    
    // Getters for tax rates
    static double getCityTax() { return CITY_TAX; }
    static double getCountyTax() { return COUNTY_TAX; }
};

#endif // LOTTERYTICKETS_H 
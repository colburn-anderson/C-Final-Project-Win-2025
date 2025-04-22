#ifndef LOTTERYTICKET_H
#define LOTTERYTICKET_H

#include "Product.h"
#include <string>

class LotteryTicket : public Product {
private:
    static const double CITY_TAX;    // 7% city tax
    static const double COUNTY_TAX;  // 3% county tax

public:
    LotteryTicket(const string& id, const string& name, double basePrice, int quantity = 0);
    
    double computePrice() const override;
    void displayInfo() const override;
};

#endif 
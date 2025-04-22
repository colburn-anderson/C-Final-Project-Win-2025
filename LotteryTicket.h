#ifndef LOTTERYTICKET_H
#define LOTTERYTICKET_H

#include "Product.h"
#include <string>

class LotteryTicket : public Product {
private:
    float cityTax;
    float countyTax;

public:
    LotteryTicket(const string& id, const string& name, const string& expDate, 
                 float basePrice, float cityTax, float countyTax, int quantity = 0);
    
    float getCityTax() const;
    float getCountyTax() const;
    float computePrice() const override;
    void displayInfo() const override;
};

#endif 
#include "LotteryTicket.h"
#include <iomanip>
#include <iostream>

LotteryTicket::LotteryTicket(const string& id, const string& name, const string& expDate, 
                           float basePrice, float cityTax, float countyTax, int quantity)
    : Product(id, name, "Lottery", expDate, basePrice, quantity),
      cityTax(cityTax), countyTax(countyTax) {}

float LotteryTicket::getCityTax() const {
    return cityTax;
}

float LotteryTicket::getCountyTax() const {
    return countyTax;
}

float LotteryTicket::computePrice() const {
    return getBasePrice() + cityTax + countyTax;
}

void LotteryTicket::displayInfo() const {
    cout << "ID: " << getId() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Category: " << getCategory() << endl;
    cout << "Expiration Date: " << getExpDate() << endl;
    cout << "Base Price: $" << fixed << setprecision(2) << getBasePrice() << endl;
    cout << "City Tax: $" << fixed << setprecision(2) << cityTax << endl;
    cout << "County Tax: $" << fixed << setprecision(2) << countyTax << endl;
    cout << "Total Price: $" << fixed << setprecision(2) << computePrice() << endl;
    cout << "Quantity: " << getQuantity() << endl;
} 
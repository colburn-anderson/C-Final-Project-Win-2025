#include "LotteryTicket.h"
#include <iomanip>
#include <iostream>

using namespace std;

// These rates are applied to the base price of lottery tickets
const double LotteryTicket::CITY_TAX = 0.07;    // 7% city tax
const double LotteryTicket::COUNTY_TAX = 0.03;  // 3% county tax

// Creates a new lottery ticket with the given parameters, sets category to "Lottery" and expiration date to "N/A"
LotteryTicket::LotteryTicket(const string& id, const string& name, double basePrice, int quantity)
    : Product(id, name, "Lottery", "N/A", basePrice, quantity) {}


// Calculates the final price
double LotteryTicket::computePrice() const {
    double totalTax = getBasePrice() * (CITY_TAX + COUNTY_TAX);
    return roundTo3Decimals(getBasePrice() + totalTax);
}

// Shows all relevant information about the lottery ticket:
void LotteryTicket::displayInfo() const {
    cout << "ID: " << getId() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Category: " << getCategory() << endl;
    cout << "Base Price: $" << fixed << setprecision(3) << getBasePrice() << endl;
    cout << "City Tax: $" << fixed << setprecision(3) << getBasePrice() * CITY_TAX << endl;
    cout << "County Tax: $" << fixed << setprecision(3) << getBasePrice() * COUNTY_TAX << endl;
    cout << "Total Price: $" << fixed << setprecision(3) << computePrice() << endl;
    cout << "Quantity: " << getQuantity() << endl;
} 
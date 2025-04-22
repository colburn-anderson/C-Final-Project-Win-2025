#include "LotteryTickets.h"
#include <iomanip>
#include <iostream>

using namespace std;

// Constructor implementation
LotteryTickets::LotteryTickets(const string& id, const string& name, double basePrice, int quantity)
    : Product(id, name, "Lottery", "N/A", basePrice, quantity) {}

// Compute final price including both city and county taxes
double LotteryTickets::computePrice() const {
    double totalTax = getBasePrice() * (CITY_TAX + COUNTY_TAX);
    return roundTo3Decimals(getBasePrice() + totalTax);
}

// Display lottery ticket information including both taxes
void LotteryTickets::displayInfo() const {
    cout << "ID: " << getId() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Category: " << getCategory() << endl;
    cout << "Base Price: $" << fixed << setprecision(3) << getBasePrice() << endl;
    cout << "City Tax: $" << fixed << setprecision(3) << getBasePrice() * CITY_TAX << endl;
    cout << "County Tax: $" << fixed << setprecision(3) << getBasePrice() * COUNTY_TAX << endl;
    cout << "Total Price: $" << fixed << setprecision(3) << computePrice() << endl;
    cout << "Quantity: " << getQuantity() << endl;
} 
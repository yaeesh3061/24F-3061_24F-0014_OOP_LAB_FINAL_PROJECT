// Economy.cpp
#include "Stronghold.h"

Economy::Economy(float tax) : taxRate(tax), inflation(0.0f), publicSpending(0.0f) {}

void Economy::adjustTax(float delta) {
    taxRate += delta;
    if (taxRate < 0) taxRate = 0;
    else if (taxRate > 50) taxRate = 50;
    cout << "\nTax are adjusted to " << taxRate;
}

void Economy::applyInflation() {
    inflation += 0.5f;
    if (inflation > 10) inflation = 10;
    cout << "\nInflation applied.\nInflation rate: " << inflation;
}

float Economy::collectTaxes(int populationSize) {
    float collected = populationSize * (taxRate / 100.0f);
    cout << "\nTax collected of amount: $" << collected;
    return collected;
}

void Economy::increasePublicSpending(float amount) {
    publicSpending += amount;
    cout << "\nPublic spending increased by $" << amount;
    cout << "\nTotal public spending: $" << publicSpending;
}

void Economy::printStatus() const {
    cout << "\nTax Rate: " << taxRate << "% | Inflation: " << inflation << "%\n";
}

void Economy::saveToFile(ofstream& out) const {
    out << taxRate << "\n";
    out << inflation << "\n";
    out << publicSpending << "\n";
}

void Economy::loadFromFile(ifstream& in) {
    string line;
    getline(in, line); taxRate = stof(line);
    getline(in, line); inflation = stof(line);
    getline(in, line); publicSpending = stof(line);
}
float Economy::getTaxRate() const {
    return taxRate;
}

float Economy::getInflation() const {
    return inflation;
}
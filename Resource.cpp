// Resource.cpp
#include "Stronghold.h"

Resource::Resource(){}
Resource::Resource(const string& n, float initial) : name(n), stockpile(initial), consumptionRate(5.0f) {}

void Resource::gather(float amount) {
    stockpile += amount;
    cout << "\nGathered " << amount << " units of " << name << "\nTotal: " << stockpile << endl;
}

bool Resource::consume(float amount) {
    if (stockpile >= amount) {
        stockpile -= amount;
        cout << "Consumed " << amount << " units of " << name << ". Remaining: " << stockpile << endl;
        return true;
    }
    cout << "Not enough " << name << " to consume " << amount << ". Available: " << stockpile << endl;
    return false;
}

void Resource::setConsumption(float rate) {
    consumptionRate = rate;
}

float Resource::getStockpile() const {
    return stockpile;
}

void Resource::printStatus() const {
    cout << name << ": " << stockpile << " units" << endl;
}

void Resource::saveToFile(ofstream& out) const {
    out << name << "\n";
    out << stockpile << "\n";
    out << consumptionRate << "\n";
}

void Resource::loadFromFile(ifstream& in) {
    string line;
    getline(in, name);
    getline(in, line); stockpile = stof(line);
    getline(in, line); consumptionRate = stof(line);
}

string Resource::getName() const {
    return name;
}
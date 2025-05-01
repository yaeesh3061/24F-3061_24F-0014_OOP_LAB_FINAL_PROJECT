// Population.cpp
#include "Stronghold.h"

Population::Population(int initial) : total(initial), employed(0), healthy(initial) {}

void Population::grow() {
    total += 5;
    cout << "\nPopulation grew.";
    cout << "\nTotal Population: " << total << endl;
}

void Population::shrink(int amount) {
    if (total - amount > 0){
        total -= amount;
        cout << "\nPopulation reduced by " << amount;
        cout << "\nTotal pouplation: " << total;
    }
    else {
        total = 0;
        cout << "\nPopulation cannot be reduced.";
    }
        

}

void Population::fallIll(int count) {
    if (healthy - count > 0) {
        healthy -= count;
        cout << "\n" << count << " people fell ill.";
    }
    else {
        healthy = 0;
        cout << "\nNo people fell ill.";
    }
}

void Population::updateEmployment(int workers) {
    employed = (workers < total) ? workers : total;
    cout << "\n" << employed << " people are employed out of " << total;
}

int Population::getTotal() const {
    return total;
}

int Population::getUnemployed() const {
    return (total - employed > 0) ? total - employed : 0;
}

void Population::printStatus() const {
    cout << "\nPopulation: " << total << " | Healthy: " << healthy
        << " | Employed: " << employed << endl;
}

void Population::saveToFile(ofstream& out) const {
    out << total << "\n";
    out << employed << "\n";
    out << healthy << "\n";
}

void Population::loadFromFile(ifstream& in) {
    string line;
    getline(in, line); total = stoi(line);
    getline(in, line); employed = stoi(line);
    getline(in, line); healthy = stoi(line);
}
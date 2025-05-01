// Army.cpp
#include "Stronghold.h"

Army::Army(int size) : soldiers(size), morale(50.0f), payArrears(0.0f) {}

void Army::recruit(int count, const Population& pop) {
    int unemployed = pop.getUnemployed();
    if (count > unemployed) count = unemployed;
    soldiers += count;
    cout << "\n" << count << " soldiers recruited.";
    cout << "\nTotal army size: " << soldiers;
}

void Army::dismiss(int count) {
    if (count > soldiers) count = soldiers;
    soldiers -= count;
    cout << "\n" << count << " soldiers dismissed from army.";
    cout << "\nTotal army size: " << soldiers;
}

void Army::train() {
    if (rand() % 2 == 0)
        morale += 5.0f;
    else
        morale -= 2.0f;
    if (morale > 100) morale = 100;
    cout << "\nArmy trained.";
    cout << "\nMorale: " << morale;
}

void Army::paySoldiers(float treasury) {
    float needed = soldiers * 0.5f;
    if (treasury >= needed) {
        payArrears = 0;
        morale += 2;
        cout << "\nSoldiers paid. Morale increased";
    }
    else {
        payArrears += needed - treasury;
        morale -= 3;
        cout << "\nSoldiers unpaid. Morale dropped.";
    }
    if (morale < 0) morale = 0;
}

float Army::getPayOwed() const {
    return soldiers * 0.5f;
}

int Army::getSize() const {
    return soldiers;
}

void Army::updateMorale(float change) {
    morale += change;
    if (morale > 100) morale = 100;
    if (morale < 0) morale = 0;
    cout << "\nMorale updated by " << change << "%.\nNew Morale: " << morale << "%";
}

void Army::printStatus() const {
    cout << "\nArmy Size: " << soldiers << " | Morale: " << morale << "%"
        << " | Pay Arrears: $" << payArrears << endl;
}

void Army::saveToFile(ofstream& out) const {
    out << soldiers << "\n";
    out << morale << "\n";
    out << payArrears << "\n";
}

void Army::loadFromFile(ifstream& in) {
    string line;
    getline(in, line); soldiers = stoi(line);
    getline(in, line); morale = stof(line);
    getline(in, line); payArrears = stof(line);
}
float Army::getMorale() const {
    return morale;
}

void Army::shrink(int count) {
    if (count > soldiers) count = soldiers;
    soldiers -= count;
    cout << "\nArmy shrinked.";
}
// Leader.cpp
#include "Stronghold.h"

Leader::Leader(const string& name, LeadershipStyle s)
    : name(name), style(s), popularity(70) {}

void Leader::influenceEconomy(Economy& economy) const {
    switch (style) {
    case AUTHORITARIAN:
        economy.adjustTax(2.0f);
        cout << "\n" << name << " rise taxes to tighten control.";
        break;
    case DEMOCRATIC:
        economy.adjustTax(-1.0f);
        economy.increasePublicSpending(50.0f);
        cout << "\n" << name << " lowered taxes and increased public services.";
        break;
    case LAISSEZ_FAIRE:
        economy.applyInflation(); // No control----inflation rises
        cout << "\n" << name << " did nothing. Inflation rises naturally.";
        break;
    }
}

void Leader::handleRevolt() {
    cout <<"\n"<< name << " is handling a revolt!\n";
    popularity -= 5;
}

void Leader::coupAttempt() {
    cout << "\nA coup attempt on " << name << "!\n";
    if (rand() % 2 == 0)
        cout <<"\n"<< name << " survives.\n";
    else
        cout <<"\n"<< name << " has been overthrown!\n";
}

void Leader::printStatus() const {
    cout << "\nLeader: " << name << " | Popularity: " << popularity << "%" << endl;
}

void Leader::saveToFile(ofstream& out) const {
    out << name << "\n";
    out << style << "\n";
    out << popularity << "\n";
}

void Leader::loadFromFile(ifstream& in) {
    string line;
    getline(in, name);
    getline(in, line); style = static_cast<LeadershipStyle>(stoi(line));
    getline(in, line); popularity = stoi(line);
}
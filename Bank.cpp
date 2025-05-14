// Bank.cpp
#include "Stronghold.h"

Bank::Bank(float initial) : treasury(initial), loansGiven(0.0f) {}

void Bank::deposit(float amount) {
    treasury += amount;
    cout << "\nAmount deposited: $" << amount;    
    cout << "\nTreasure: " << treasury;
}

bool Bank::withdraw(float amount) {
    if (amount <= treasury) {
        treasury -= amount;
        cout << "\n" << amount << " withdrawn from .";
        cout << "\nTreasure: " << treasury;
        return true;
    }
    else {
        cout << "\nFailed. Not enough funds.";
        return false;
    }
}

void Bank::giveLoan(float amount) {
    if (amount < treasury) {
        treasury -= amount;
        loansGiven += amount;
        cout << "\nIssued loan of amount " << amount;
        cout << "\nLoans outstanding: " << loansGiven;
    }
    else {
        cout << "\nFailed.Not enough funds to give loan.";
    }
}

void Bank::collectInterest(float rate) {
    float interest = loansGiven * rate;
    treasury += interest;
    cout << "Collected $" << interest << " in interest.\nTreasury: $" << treasury << endl;
}

void Bank::audit() {
    cout << "Audit Report.\nTreasury = $" << treasury << "\nLoans Outstanding = $" << loansGiven << endl;
}

float Bank::getTreasury() const {
    return treasury;
}   

void Bank::printStatus() const {
    cout << "\nTreasury: $" << treasury << " | Loans Outstanding: $" << loansGiven << endl;
}

void Bank::saveToFile(ofstream& out) const {
    out << treasury << "\n";
    out << loansGiven << "\n";
}

void Bank::loadFromFile(ifstream& in) {
    string line;
    getline(in, line); treasury = stof(line);
    getline(in, line); loansGiven = stof(line);
}


#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Population;
class Army;
class Economy;
class Leader;
class Bank;
class Resource;
class EventSystem;

void logGameState(const string& filename);

class Population {
private:
    int total;
    int employed;
    int healthy;
public:
    Population(int initial = 100);
    void grow();
    void shrink(int amount);
    void fallIll(int count);
    void updateEmployment(int workers);
    int getUnemployed() const;
    int getTotal() const;
    void printStatus() const;
    void saveToFile(ofstream& out) const;
    void loadFromFile(ifstream& in);
};

class Army {
private:
    int soldiers;
    float morale;
    float payArrears; 
public:
    Army(int size = 50);
    void recruit(int count, const Population& pop);
    void dismiss(int count);
    void train();
    void paySoldiers(float treasury);
    float getPayOwed() const;
    int getSize() const;
    void updateMorale(float change);
    void printStatus() const;
    void saveToFile(ofstream& out) const;
    void loadFromFile(ifstream& in);
    float getMorale() const;
    void shrink(int count);
};

class Economy {
private:
    float taxRate; 
    float inflation;
    float publicSpending;
public:
    Economy(float tax = 20.0f);
    void adjustTax(float delta);
    void applyInflation();
    float collectTaxes(int populationSize);
    void increasePublicSpending(float amount);
    void printStatus() const;
    void saveToFile(ofstream& out) const;
    void loadFromFile(ifstream& in);
    float getTaxRate() const;
    float getInflation() const;
};

enum LeadershipStyle { AUTHORITARIAN, DEMOCRATIC, LAISSEZ_FAIRE };

class Leader {
private:
    string name;
    LeadershipStyle style;
    int popularity;
public:
    Leader(const string& name = "King", LeadershipStyle s = AUTHORITARIAN);
    void influenceEconomy(Economy& economy) const;
    void handleRevolt();
    void coupAttempt();
    void printStatus() const;
    void saveToFile(ofstream& out) const;
    void loadFromFile(ifstream& in);
};

class Bank {
private:
    float treasury;
    float loansGiven;
public:
    Bank(float initialFunds = 1000.0f);
    void deposit(float amount);
    bool withdraw(float amount);
    void giveLoan(float amount);
    void collectInterest(float rate);
    void audit();
    float getTreasury() const;
    void printStatus() const;
    void saveToFile(ofstream& out) const;
    void loadFromFile(ifstream& in);
};

class Resource {
private:
    string name;
    float stockpile;
    float consumptionRate;
public:
    Resource();
    Resource(const string& name, float initial = 100.0f);
    void gather(float amount);
    bool consume(float amount);
    void setConsumption(float rate);
    float getStockpile() const;
    void printStatus() const;
    void saveToFile(ofstream& out) const;
    void loadFromFile(ifstream& in);
    string getName() const;
};

class EventSystem {
private:
    int seed;
public:
    EventSystem(int seed);
    void triggerRandomEvent(Population& pop, Army& army, Bank& bank, Resource* resources, int resCount);
};

#endif 

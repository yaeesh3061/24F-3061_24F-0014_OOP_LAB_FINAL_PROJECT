// EventSystem.cpp
#include "Stronghold.h"

EventSystem::EventSystem(int seed)
    : seed(seed) {
    srand(seed);
}

void EventSystem::triggerRandomEvent(Population& pop, Army& army, Bank& bank, Resource* resources, int resCount) {
    int event = rand() % 5;
    cout << "\nRandom Event triggered.";
    switch (event) {
    case 0: // Disease
        pop.fallIll(10);
        cout << "[EVENT] A disease outbreak occurred!\n";
        break;
    case 1: // Famine
        if (resources[0].consume(30))
            cout << "[EVENT] Food shortage caused famine!\n";
        else
            cout << "[EVENT] Not enough food to cause famine this time.\n";
        break;
    case 2: // War
        army.shrink(10); 
        cout << "[EVENT] Minor skirmish resulted in losses.\n";
        break;
    case 3: // Loan
        bank.giveLoan(200);
        cout << "[EVENT] Government took a new loan.\n";
        break;
    case 4: // Revolt
        pop.shrink(5);
        army.updateMorale(-5);
        cout << "[EVENT] Peasants revolted!\n";
        break;
    }
}
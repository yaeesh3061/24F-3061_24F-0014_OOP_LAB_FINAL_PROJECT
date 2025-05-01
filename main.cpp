// main.cpp
#include "Stronghold.h"

void displayMenu();
void handlePopulation(Population&);
void handleArmy(Army&, const Population&);
void handleEconomy(Economy&, int populationSize);
void handleLeader(Leader&, Economy&);
void handleBank(Bank&);
void handleResources(Resource*, int);
void handleEvents(EventSystem&, Population&, Army&, Bank&, Resource*, int);
void logGameStateToFile(const string&, const Population&, const Army&, const Economy&, const Leader&, const Bank&, const Resource*, int);
void viewAllStatus(const Population&, const Army&, const Economy&, const Leader&, const Bank&, const Resource*, int);
// saveGame function
void saveGame(const Population& pop, const Army& army, const Economy& econ,
    const Leader& leader, const Bank& bank, const Resource* resources, int resCount) {
    ofstream out("game_save.txt");
    if (!out.is_open()) {
        cout << "Failed to open save file.\n";
        return;
    }

    pop.saveToFile(out);
    army.saveToFile(out);
    econ.saveToFile(out);
    leader.saveToFile(out);
    bank.saveToFile(out);

    out << resCount << "\n";
    for (int i = 0; i < resCount; ++i) {
        resources[i].saveToFile(out);
    }

    cout << "Game saved successfully.\n";
    out.close();
}


// loadGame function
void loadGame(Population& pop, Army& army, Economy& econ,
    Leader& leader, Bank& bank, Resource*& resources, int& resCount) {
    ifstream in("game_save.txt");
    if (!in.is_open()) {
        cerr << "Failed to open save file.\n";
        return;
    }

    pop.loadFromFile(in);
    army.loadFromFile(in);
    econ.loadFromFile(in);
    leader.loadFromFile(in);
    bank.loadFromFile(in);

    string line;
    getline(in, line); resCount = stoi(line);

    delete[] resources; // Avoid memory leak
    resources = new Resource[resCount];

    for (int i = 0; i < resCount; ++i) {
        resources[i].loadFromFile(in);
    }

    cout << "Game loaded successfully.\n";
    in.close();
}
int main() {

    Population pop;
    Army army;
    Economy econ;
    Leader leader("Lord Aragon", DEMOCRATIC);
    Bank treasury;
    Resource food("Food", 200);
    Resource wood("Wood", 150);
    Resource stone("Stone", 100);
    Resource* resources = new Resource[3]{ food, wood, stone };
    int resCount = 3;

    // Instantiate EventSystem with a seed
    EventSystem events(rand()); // Pass an integer seed

    char choice;
    bool running = true;

    while (running) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case '1':
            handlePopulation(pop);
            break;
        case '2':
            handleArmy(army, pop);
            break;
        case '3':
            handleEconomy(econ, pop.getTotal());
            break;
        case '4':
            handleLeader(leader, econ);
            break;
        case '5':
            handleBank(treasury);
            break;
        case '6':
            handleResources(resources, resCount);
            break;
        case '7':
            handleEvents(events, pop, army, treasury, resources, resCount);
            break;
        case 'V':
        case 'v':
            viewAllStatus(pop, army, econ, leader, treasury, resources, resCount);
            break;
        case 'S':
        case 's':
            saveGame(pop, army, econ, leader, treasury, resources, resCount);
            break;
        case 'L':
        case 'l': {
            delete[] resources;
            Resource* loadedResources = nullptr;
            int loadedResCount = 0;
            loadGame(pop, army, econ, leader, treasury, loadedResources, loadedResCount);
            resources = loadedResources;
            resCount = loadedResCount;
            break;
        }
        case 'Q':
        case 'q':
            running = false;
            cout << "Exiting Stronghold. May your kingdom endure.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        // Log current state after each action
        logGameStateToFile("score.txt", pop, army, econ, leader, treasury, resources, resCount);
    }

    delete[] resources;
    return 0;
}

void displayMenu() {
    cout << "\n===== STRONGHOLD KINGDOM ENGINE =====\n"
        << "[1] Manage Population\n"
        << "[2] Manage Army\n"
        << "[3] Manage Economy\n"
        << "[4] Manage Leader\n"
        << "[5] Manage Treasury & Banking\n"
        << "[6] Manage Resources\n"
        << "[7] Trigger Random Event\n"
        << "[V] View overall Kingdom Status\n"
        << "[S] Save Game\n"
        << "[L] Load Game\n"
        << "[Q] Quit\n"
        << "=====================================\n";
}

void viewAllStatus(const Population& pop, const Army& army, const Economy& econ,
    const Leader& leader, const Bank& bank, const Resource* resources, int resCount) {
    cout << "\n=== CURRENT KINGDOM STATUS ===\n";
    pop.printStatus();
    army.printStatus();
    econ.printStatus();
    leader.printStatus();
    bank.printStatus();
    for (int i = 0; i < resCount; ++i) {
        resources[i].printStatus();
    }
    cout << "==============================\n";
}

void handlePopulation(Population& pop) {
    cout << "\n=== Population Management ===\n"
        << "[1] Grow population\n"
        << "[2] Shrink population\n"
        << "[3] Cause illness\n"
        << "[4] Update employment\n"
        << "[5] View status\n"
        << "Choose an action: ";

    int choice;
    cin >> choice;

    int amount;

    switch (choice) {
    case 1:
        pop.grow();
        break;
    case 2:
        cout << "Enter number to reduce population: ";
        cin >> amount;
        pop.shrink(amount);
        break;
    case 3:
        cout << "Enter number of people falling ill: ";
        cin >> amount;
        pop.fallIll(amount);
        break;
    case 4:
        cout << "Enter employed workers: ";
        cin >> amount;
        pop.updateEmployment(amount);
        break;
    case 5:
        pop.printStatus();
        break;
    default:
        cout << "Invalid option.\n";
    }
}

void handleArmy(Army& army, const Population& pop) {
    cout << "\n=== Army Management ===\n"
        << "[1] Recruit soldiers\n"
        << "[2] Dismiss soldiers\n"
        << "[3] Train army\n"
        << "[4] Pay soldiers\n"
        << "[5] View status\n"
        << "Choose an action: ";

    int choice;
    cin >> choice;

    int count;

    switch (choice) {
    case 1:
        cout << "How many soldiers to recruit? ";
        cin >> count;
        army.recruit(count, pop);
        break;
    case 2:
        cout << "How many soldiers to dismiss? ";
        cin >> count;
        army.dismiss(count);
        break;
    case 3:
        army.train();
        cout << "Army trained!\n";
        break;
    case 4:
        army.paySoldiers(1000); // Simulated treasury input
        cout << "Soldiers paid.\n";
        break;
    case 5:
        army.printStatus();
        break;
    default:
        cout << "Invalid option.\n";
    }
}

void handleEconomy(Economy& econ, int populationSize) {
    cout << "\n=== Economy Management ===\n"
        << "[1] Adjust tax rate\n"
        << "[2] Apply inflation\n"
        << "[3] Collect taxes\n"
        << "[4] Increase public spending\n"
        << "[5] View status\n"
        << "Choose an action: ";

    int choice;
    cin >> choice;

    float delta;
    switch (choice) {
    case 1:
        cout << "Enter change in tax rate (+/-): ";
        cin >> delta;
        econ.adjustTax(delta);
        break;
    case 2:
        econ.applyInflation();
        break;
    case 3:
        econ.collectTaxes(populationSize);
        break;
    case 4:
        cout << "Enter public spending increase: ";
        cin >> delta;
        econ.increasePublicSpending(delta);
        break;
    case 5:
        econ.printStatus();
        break;
    default:
        cout << "Invalid option.\n";
    }
}

void handleLeader(Leader& leader, Economy& econ) {
    cout << "\n=== Leader Management ===\n"
        << "[1] Influence economy\n"
        << "[2] Handle revolt\n"
        << "[3] Coup attempt\n"
        << "[4] View status\n"
        << "Choose an action: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        leader.influenceEconomy(econ);
        cout << "Leader influenced economy.\n";
        break;
    case 2:
        leader.handleRevolt();
        break;
    case 3:
        leader.coupAttempt();
        break;
    case 4:
        leader.printStatus();
        break;
    default:
        cout << "Invalid option.\n";
    }
}

void handleBank(Bank& bank) {
    cout << "\n=== Treasury / Bank Management ===\n"
        << "[1] Deposit funds\n"
        << "[2] Withdraw funds\n"
        << "[3] Give loan\n"
        << "[4] Collect interest\n"
        << "[5] Audit\n"
        << "[6] View status\n"
        << "Choose an action: ";

    int choice;
    cin >> choice;

    float amount;
    switch (choice) {
    case 1:
        cout << "Enter amount to deposit: ";
        cin >> amount;
        bank.deposit(amount);
        break;
    case 2:
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        bank.withdraw(amount);
        break;
    case 3:
        cout << "Enter loan amount: ";
        cin >> amount;
        bank.giveLoan(amount);
        break;
    case 4:
        bank.collectInterest(0.05f); // 5% interest
        break;
    case 5:
        bank.audit();
        break;
    case 6:
        bank.printStatus();
        break;
    default:
        cout << "Invalid option.\n";
    }
}

void handleResources(Resource* resources, int resCount) {
    cout << "\n=== Resource Management ===\n"
        << "Available Resources:\n";
    for (int i = 0; i < resCount; ++i) {
        cout << "[" << i + 1 << "] " << resources[i].getName() << endl;
    }

    int choice;
    cout << "Select resource number: ";
    cin >> choice;

    if (choice < 1 || choice > resCount) {
        cout << "Invalid selection.\n";
        return;
    }

    Resource& res = resources[choice - 1];

    cout << "\n[1] Gather " << res.getName() << "\n"
        << "[2] Consume " << res.getName() << "\n"
        << "[3] View status\n"
        << "Choose an action: ";
    cin >> choice;

    float amount;

    switch (choice) {
    case 1:
        cout << "Amount to gather: ";
        cin >> amount;
        res.gather(amount);
        break;
    case 2:
        cout << "Amount to consume: ";
        cin >> amount;
        if (!res.consume(amount))
            cout << "Not enough stockpile.\n";
        break;
    case 3:
        res.printStatus();
        break;
    default:
        cout << "Invalid action.\n";
    }
}

void handleEvents(EventSystem& events, Population& pop, Army& army, Bank& bank, Resource* resources, int resCount) {
    cout << "\n=== Triggering Random Event ===\n";
    events.triggerRandomEvent(pop, army, bank, resources, resCount);
}

void logGameStateToFile(const string& filename, const Population& pop, const Army& army,
    const Economy& econ, const Leader& leader, const Bank& bank,
    const Resource* resources, int resCount) {
    ofstream out(filename, ios::app); // Append mode
    if (!out.is_open()) {
        cerr << "Failed to open log file.\n";
        return;
    }

    out << "=== Game State Log - " << " === \n";
    out << "Population: " << pop.getTotal() << " | Healthy: " << resources[0].getStockpile() << endl;
    out << "Army Size: " << army.getSize() << " | Morale: " << army.getMorale() << "%" << endl;
    out << "Tax Rate: " << econ.getTaxRate() << "% | Inflation: " << econ.getInflation() << "%" << endl;
    out << "Treasury: $" << bank.getTreasury() << endl;
    out << "Resources:\n";
    for (int i = 0; i < resCount; ++i) {
        out << "- " << resources[i].getName() << ": " << resources[i].getStockpile() << endl;
    }
    out << "---------------------------------------------\n";

    out.close();
}
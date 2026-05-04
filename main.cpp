#include "TriageSystem.h"
#include <iostream>
using namespace std;

int main() {
    TriageSystem system;
    int choice = 0;

    while (true) {
        TriageSystem::printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        std::cin.ignore(1000, '\n');

        if (choice == 1) system.admitPatient();
        else if (choice == 2) system.callNextPatient();
        else if (choice == 3) system.peekNextPatient();
        else if (choice == 4) system.viewWaitlist();
        else if (choice == 5) {
            cout << "Exiting system. Ingat!\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}

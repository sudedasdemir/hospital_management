\
#include "../Header/Staff.h"
#include <iostream>
#include <algorithm>
using namespace std;

int Staff::staffCounter = 1000;

Staff::Staff() {
    id = ++staffCounter;
}

void Staff::addStaff(vector<Staff>& staffList) {
    Staff s;
    cout << "\nEnter Staff Name: ";
    cin >> s.name;
    cout << "Enter Age: ";
    cin >> s.age;
    cout << "Enter Gender: ";
    cin >> s.gender;
    cout << "Enter Position: ";
    cin >> s.position;

    staffList.push_back(s);
    cout << "\nStaff added successfully! [ID: " << s.id << "]\n";
}

void Staff::searchStaffByName(const vector<Staff>& staffList) const {
    string q;
    cout << "\nEnter Staff Name to Search: ";
    cin >> q;
    bool found = false;

    for (const auto& s : staffList) {
        if (s.name == q) {
            s.displayStaffInfo();
            found = true;
        }
    }
    if (!found) cout << "Staff not found!\n";
}

void Staff::deleteStaff(vector<Staff>& staffList) {
    int deleteID;
    cout << "\nEnter Staff ID to delete: ";
    cin >> deleteID;

    auto it = remove_if(staffList.begin(), staffList.end(),
        [deleteID](Staff& s) { return s.id == deleteID; });

    if (it != staffList.end()) {
        staffList.erase(it, staffList.end());
        cout << "Staff deleted successfully.\n";
    } else {
        cout << "Staff not found.\n";
    }
}

void Staff::displayStaffInfo() const {
    cout << "\n----- Staff Info -----\n";
    displayInfo();
    cout << "Position: " << position << endl;
    cout << "----------------------\n";
}

void Staff::showAllStaff(const vector<Staff>& staffList) {
    cout << "\n===== All Registered Staff =====\n";
    if (staffList.empty()) {
        cout << "No staff registered.\n";
    } else {
        for (const auto& s : staffList)
            s.displayStaffInfo();
    }
    cout << "================================\n";
}

void Staff::staffMenu(vector<Staff>& staffList) {
    int choice;
    do {
        cout << "\n------ Staff Management ------\n";
        cout << "1. Add Staff\n";
        cout << "2. Search Staff by Name\n";
        cout << "3. Delete Staff\n";
        cout << "4. Show All Staff\n";
        cout << "0. Back to Main Menu\n";
        cout << "------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStaff(staffList); break;
            case 2: searchStaffByName(staffList); break;
            case 3: deleteStaff(staffList); break;
            case 4: showAllStaff(staffList); break;
            case 0: cout << "Returning...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

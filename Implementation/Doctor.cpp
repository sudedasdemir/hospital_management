\
#include "../Header/Doctor.h"
#include <iostream>
#include <algorithm>
using namespace std;

int Doctor::doctorCounter = 2000;

Doctor::Doctor() {
    id = ++doctorCounter;
}

void Doctor::addDoctor(vector<Doctor>& doctors) {
    Doctor d;
    cout << "\nEnter Doctor Name: ";
    cin >> d.name;
    cout << "Enter Age: ";
    cin >> d.age;
    cout << "Enter Gender: ";
    cin >> d.gender;
    cout << "Enter Specialty: ";
    cin >> d.specialty;

    doctors.push_back(d);
    cout << "\nDoctor added successfully! [ID: " << d.id << "]\n";
}

void Doctor::searchDoctorByName(const vector<Doctor>& doctors) const {
    string q;
    cout << "\nEnter Doctor Name to Search: ";
    cin >> q;
    bool found = false;

    for (const auto& d : doctors) {
        if (d.name == q) {
            d.displayDoctorInfo();
            found = true;
        }
    }
    if (!found) cout << "Doctor not found!\n";
}

void Doctor::deleteDoctor(vector<Doctor>& doctors) {
    int deleteID;
    cout << "\nEnter Doctor ID to delete: ";
    cin >> deleteID;

    auto it = remove_if(doctors.begin(), doctors.end(),
        [deleteID](Doctor& d) { return d.id == deleteID; });

    if (it != doctors.end()) {
        doctors.erase(it, doctors.end());
        cout << "Doctor deleted successfully.\n";
    } else {
        cout << "Doctor not found.\n";
    }
}

void Doctor::displayDoctorInfo() const {
    cout << "\n----- Doctor Info -----\n";
    displayInfo();
    cout << "Specialty: " << specialty << endl;
    cout << "-----------------------\n";
}

void Doctor::showAllDoctors(const vector<Doctor>& doctors) {
    cout << "\n===== All Registered Doctors =====\n";
    if (doctors.empty()) {
        cout << "No doctors registered.\n";
    } else {
        for (const auto& d : doctors)
            d.displayDoctorInfo();
    }
    cout << "=================================\n";
}

void Doctor::doctorMenu(vector<Doctor>& doctors) {
    int choice;
    do {
        cout << "\n------ Doctor Management ------\n";
        cout << "1. Add Doctor\n";
        cout << "2. Search Doctor by Name\n";
        cout << "3. Delete Doctor\n";
        cout << "4. Show All Doctors\n";
        cout << "0. Back to Main Menu\n";
        cout << "-------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addDoctor(doctors); break;
            case 2: searchDoctorByName(doctors); break;
            case 3: deleteDoctor(doctors); break;
            case 4: showAllDoctors(doctors); break;
            case 0: cout << "Returning...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

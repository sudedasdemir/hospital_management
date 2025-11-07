\
#include "../Header/Patient.h"
#include <iostream>
#include <algorithm>
using namespace std;

int Patient::patientCounter = 3000;

// Constructor
Patient::Patient() {
    id = ++patientCounter;
}

// Add patient
void Patient::addPatient(vector<Patient>& patients) {
    Patient p;
    cout << "\nEnter Patient Name: ";
    cin >> p.name;
    cout << "Enter Age: ";
    cin >> p.age;
    cout << "Enter Gender: ";
    cin >> p.gender;
    cout << "Enter Disease: ";
    cin >> p.disease;

    patients.push_back(p);
    cout << "\nPatient added successfully! [ID: " << p.id << "]\n";
}

// Search patient
void Patient::searchPatientByName(const vector<Patient>& patients) const {
    string name;
    cout << "\nEnter Patient Name to Search: ";
    cin >> name;
    bool found = false;

    for (const auto& p : patients) {
        if (p.name == name) {
            p.displayPatientInfo();
            found = true;
        }
    }
    if (!found)
        cout << "Patient not found!\n";
}

// Delete patient
void Patient::deletePatient(vector<Patient>& patients) {
    int deleteID;
    cout << "\nEnter Patient ID to delete: ";
    cin >> deleteID;

    auto it = remove_if(patients.begin(), patients.end(),
        [deleteID](Patient& p) { return p.id == deleteID; });

    if (it != patients.end()) {
        patients.erase(it, patients.end());
        cout << "Patient deleted successfully.\n";
    } else {
        cout << "Patient not found.\n";
    }
}

// Display info
void Patient::displayPatientInfo() const {
    cout << "\n----- Patient Info -----\n";
    displayInfo();
    cout << "Disease: " << disease << endl;
    cout << "------------------------\n";
}

// Show all patients
void Patient::showAllPatients(const vector<Patient>& patients) {
    cout << "\n===== All Registered Patients =====\n";
    if (patients.empty()) {
        cout << "No patients registered.\n";
    } else {
        for (const auto& p : patients)
            p.displayPatientInfo();
    }
    cout << "==================================\n";
}

// Menu
void Patient::patientMenu(vector<Patient>& patients) {
    int choice;
    do {
        cout << "\n------ Patient Management ------\n";
        cout << "1. Add Patient\n";
        cout << "2. Search Patient by Name\n";
        cout << "3. Delete Patient\n";
        cout << "4. Show All Patients\n";
        cout << "0. Back to Main Menu\n";
        cout << "-------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(patients); break;
            case 2: searchPatientByName(patients); break;
            case 3: deletePatient(patients); break;
            case 4: showAllPatients(patients); break;
            case 0: cout << "Returning...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

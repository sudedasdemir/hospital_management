#include "../Header/Patient.h"
#include <iostream>
#include <stdexcept> 
#include <algorithm> // all_of ve isdigit için
#include <limits>    // numeric_limits için

using namespace std;

// Requirement: Static variable initialization for Phase 2
int Patient::patientCounter = 3000;

// Default Constructor
Patient::Patient() {
    id = ++patientCounter;
}

// Function to add a patient
void Patient::addPatient(vector<Patient>& patients) {
    Patient p;
    // GÜNCELLEME: İsim ve Soyisim ayrıldı
    cout << "\nEnter Patient First Name: "; cin >> p.firstName;
    cout << "Enter Patient Last Name: "; cin >> p.lastName;

    // --- SMART VALIDATION: Sayısal giriş doğrulaması ---
    while (cout << "Enter Age: " && (!(cin >> p.age) || p.age < 0 || p.age > 120)) {
        cout << "Invalid input! Please enter a valid number between 0-120.\n";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // GÜNCELLEME: Cinsiyet kısıtlaması (male/female)
    do {
        cout << "Enter Gender (male/female): "; cin >> p.gender;
        if (p.gender != "male" && p.gender != "female") {
            cout << "Invalid choice! Please type 'male' or 'female'.\n";
        }
    } while (p.gender != "male" && p.gender != "female");

    // (TR: Kritik hastaliklar puanlamayi etkileyecegi icin buyuk/kucuk harf duyarliligina dikkat.)
    cout << "Enter Disease (e.g., Critical, Heart, Flu): "; cin >> p.disease;

    patients.push_back(p);
    cout << "\nPatient registered successfully! [ID: " << p.id << "]\n";
}

// ======================================================================
// --- COMPLEX ALGORITHM 2: WEIGHTED TRIAGE SCORE SORTING ---
// (TR: Karmasik Algoritma: Agirlikli Triyaj Puani Siralamasi)
// ======================================================================
void Patient::sortWithPriority(vector<Patient>& patients) {
    if (patients.empty()) return;

    for (size_t i = 0; i < patients.size() - 1; i++) {
        for (size_t j = i + 1; j < patients.size(); j++) {
            
            int scoreI = (patients[i].age >= 65) ? 50 : 0; 
            if (patients[i].disease == "Critical" || patients[i].disease == "Heart") 
                scoreI += 40; 

            int scoreJ = (patients[j].age >= 65) ? 50 : 0;
            if (patients[j].disease == "Critical" || patients[j].disease == "Heart") 
                scoreJ += 40;

            if (scoreJ > scoreI) {
                Patient temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
            else if (scoreJ == scoreI) {
                if (patients[j].age > patients[i].age) {
                    Patient temp = patients[i];
                    patients[i] = patients[j];
                    patients[j] = temp;
                }
            }
        }
    }
    cout << "\n[COMPLEX ALGORITHM] Triage sorting complete based on Age and Severity.\n";
}

// Manual search function
void Patient::searchPatientByName(const vector<Patient>& patients) const {
    string q;
    cout << "\nEnter Patient Name, Surname or ID to filter: ";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, q); 

    if (q.empty()) return;

    // Girilen değerin ID mi yoksa isim mi olduğunu tespit eder
    bool isDigit = all_of(q.begin(), q.end(), ::isdigit);

    vector<const Patient*> matches;
    for (const auto& p : patients) {
        if (isDigit) {
            // ID araması
            if (to_string(p.getID()) == q) {
                matches.push_back(&p);
            }
        } else {
            // İsim ve Soyisim kombinasyonunda arama
            string fullName = p.firstName + " " + p.lastName;
            if (fullName.find(q) != string::npos) {
                matches.push_back(&p);
            }
        }
    }

    if (matches.empty()) {
        cout << "No patient record found matching: " << q << endl;
        return;
    }

    cout << "\nFound " << matches.size() << " match(es):" << endl;
    for (const auto* p : matches) {
        // HATA DÜZELTME: .name yerine firstName ve lastName
        cout << "[ID: " << p->getID() << "] Name: " << p->firstName << " " << p->lastName 
             << " | Age: " << p->getAge() << endl;
    }
}

// Requirement: Manual delete algorithm
void Patient::deletePatient(vector<Patient>& patients) {
    int deleteID;
    while (cout << "\nEnter Patient ID to delete: " && !(cin >> deleteID)) {
        cout << "Invalid ID format! Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool found = false;
    for (size_t i = 0; i < patients.size(); i++) {
        if (patients[i].id == deleteID) {
            patients.erase(patients.begin() + i);
            found = true;
            cout << "Patient deleted successfully.\n";
            break; 
        }
    }
    if (!found) cout << "Patient not found.\n";
}

// Requirement: Function Overriding
void Patient::displayInfo() const {
    cout << "\n----- Patient Info -----\n";
    if (age >= 65 || disease == "Critical") cout << "[HIGH PRIORITY] "; 
    Person::displayInfo(); 
    cout << "Disease: " << disease << endl;
    cout << "------------------------\n";
}

// Static function to display all records
void Patient::showAllPatients(const vector<Patient>& patients) {
    cout << "\n===== All Registered Patients =====\n";
    if (patients.empty()) {
        cout << "No patients registered.\n";
    } else {
        for (size_t i = 0; i < patients.size(); i++) {
            patients[i].displayInfo();
        }
    }
    cout << "==================================\n";
}

// Menu for managing patients
void Patient::patientMenu(vector<Patient>& patients) {
    int choice;
    do {
        cout << "\n------ Patient Management ------\n";
        cout << "1. Add Patient\n";
        cout << "2. Search Patient by Name/ID\n";
        cout << "3. Delete Patient\n";
        cout << "4. Show All Patients\n";
        cout << "5. Apply Triage Priority Sorting\n"; 
        cout << "0. Back to Main Menu\n";
        cout << "-------------------------------\n";
        cout << "Enter your choice: ";
        
        // GÜNCELLEME: Menü giriş doğrulaması
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addPatient(patients); break;
            case 2: searchPatientByName(patients); break;
            case 3: deletePatient(patients); break;
            case 4: showAllPatients(patients); break;
            case 5: sortWithPriority(patients); showAllPatients(patients); break;
            case 0: cout << "Returning...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}
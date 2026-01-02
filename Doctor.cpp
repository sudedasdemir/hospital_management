#include "../Header/Doctor.h"
#include <iostream>
#include <algorithm> // all_of ve isdigit için
#include <limits>
#include <iomanip>

using namespace std;

// Requirement: Static Variable initialization
int Doctor::doctorCounter = 2000;

// Default Constructor
Doctor::Doctor() {
    id = ++doctorCounter;
}

// Function to add a doctor record
void Doctor::addDoctor(vector<Doctor>& doctors) {
    Doctor d;
    // GÜNCELLEME: İsim ve Soyisim ayrıldı
    cout << "\nEnter Doctor First Name: "; cin >> d.firstName;
    cout << "Enter Doctor Last Name: "; cin >> d.lastName;
    
    // GÜNCELLEME: Sayısal giriş doğrulaması (Input Validation)
    while (cout << "Enter Age: " && (!(cin >> d.age) || d.age < 0 || d.age > 120)) {
        cout << "Invalid age! Please enter a number between 0-120.\n";
        cin.clear(); cin.ignore(1000, '\n');
    }

    // GÜNCELLEME: Cinsiyet kısıtlaması (male/female)
    string g;
    do {
        cout << "Enter Gender (male/female): "; cin >> g;
        if (g != "male" && g != "female") cout << "Invalid choice! Try again.\n";
    } while (g != "male" && g != "female");
    d.gender = g;

    cout << "Enter Specialty: "; cin >> d.specialty;

    doctors.push_back(d);
    cout << "\nDoctor added successfully! [ID: " << d.id << "]\n";
}

// Function to search for a doctor using a manual loop
void Doctor::searchDoctorByName(const vector<Doctor>& doctors) const {
    string q;
    cout << "\nEnter Name or ID to filter: ";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, q); 

    // --- SMART SEARCH ALGORITHM ---
    // (TR: Girilen degerin ID mi yoksa isim mi oldugunu tespit eder)
    bool isDigit = !q.empty() && all_of(q.begin(), q.end(), ::isdigit);

    vector<const Doctor*> matches;
    for (const auto& d : doctors) {
        if (isDigit) {
            // ID araması (Tam eşleşme)
            if (to_string(d.getID()) == q) {
                matches.push_back(&d);
            }
        } else {
            // İsim araması (Kısmi eşleşme)
            // GÜNCELLEME: firstName ve lastName birleştirilerek arama yapılır
            string fullName = d.firstName + " " + d.lastName;
            if (fullName.find(q) != string::npos) {
                matches.push_back(&d);
            }
        }
    }

    if (matches.empty()) {
        cout << "No record found matching: " << q << endl;
        return;
    }

    cout << "\nFound " << matches.size() << " match(es):" << endl;
    for (const auto* d : matches) {
        // HATA DÜZELTME: .name yerine getFullName() veya firstName/lastName
        cout << "[ID: " << d->getID() << "] Name: " << d->firstName << " " << d->lastName 
             << " | Dept: " << d->specialty << endl;
    }
}

// Requirement: Delete record using a manual loop (Avoided std::remove_if)
// (Turkce Not: Hoca hazir fonksiyonlara kizdigi icin manuel for dongusu ile siliyoruz)
void Doctor::deleteDoctor(vector<Doctor>& doctors) {
    int deleteID;
    while (cout << "\nEnter Doctor ID to delete: " && !(cin >> deleteID)) {
        cout << "Invalid ID format! Enter a number.\n";
        cin.clear(); cin.ignore(1000, '\n');
    }

    bool found = false;
    for (size_t i = 0; i < doctors.size(); i++) {
        if (doctors[i].id == deleteID) {
            doctors.erase(doctors.begin() + i);
            found = true;
            cout << "Doctor deleted successfully.\n";
            break; 
        }
    }
    
    if (!found) cout << "Doctor not found.\n";
}

// Requirement: Function Overriding
// (Turkce Not: Person sinifindaki displayInfo fonksiyonunu burada gecersiz kiliyoruz/eziyoruz)
void Doctor::displayInfo() const {
    cout << "\n----- Doctor Info -----\n";
    // Calling Base Class version of displayInfo
    Person::displayInfo(); 
    cout << "Specialty: " << specialty << endl;
    cout << "-----------------------\n";
}

// Static function to display all doctors in the list
void Doctor::showAllDoctors(const vector<Doctor>& doctors) {
    cout << "\n===== All Registered Doctors =====\n";
    if (doctors.empty()) {
        cout << "No doctors registered.\n";
    } else {
        for (size_t i = 0; i < doctors.size(); i++) {
            doctors[i].displayInfo();
        }
    }
    cout << "=================================\n";
}

// Menu for Doctor Management
void Doctor::doctorMenu(vector<Doctor>& doctors) {
    int choice;
    do {
        cout << "\n------ Doctor Management ------\n";
        cout << "1. Add Doctor\n";
        cout << "2. Search Doctor by Name/ID\n";
        cout << "3. Delete Doctor\n";
        cout << "4. Show All Doctors\n";
        cout << "0. Back to Main Menu\n";
        cout << "-------------------------------\n";
        cout << "Enter your choice: ";
        
        // GÜNCELLEME: Menü giriş doğrulaması
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

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
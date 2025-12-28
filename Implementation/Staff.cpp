#include "../Header/Staff.h"
#include "../Header/Doctor.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

using namespace std;

// Requirement: Static variables for Phase 2
int Staff::staffCounter = 4000;

Staff::Staff() {
    id = ++staffCounter;
    role = "Nurse";
    baseSalary = 5000.0;
    joinYear = 2025;
}

// ======================================================================
// --- GÜNCELLENMİŞ: NOBET VE IZIN ALGORITMASI (2 Hemsire + 1 Doktor) ---
// ======================================================================
void generateHospitalSchedule(const vector<Staff>& staffList, const vector<Doctor>& doctorList) {
    if (staffList.size() < 2 || doctorList.empty()) {
        cout << "\n[!] Insufficient personnel for the duty cycle (Need at least 2 nurses & 1 doctor).\n";
        return;
    }

    cout << "\n" << string(95, '=') << endl;
    cout << "   PROFESSIONAL 10-DAY HOSPITAL DUTY & REST CHART (Dynamic Scaling)   " << endl;
    cout << string(95, '=') << endl;
    cout << left << setw(10) << "Day" << setw(25) << "Doctor on Duty" << setw(40) << "Nurses on Duty" << setw(20) << "Status" << endl;
    cout << string(95, '-') << endl;

    string days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "Mon", "Tue", "Wed"};

    for (int i = 0; i < 10; i++) {
        // --- DYNAMIC ROUND ROBIN ALGORITHM ---
        int docIdx = i % doctorList.size();
        int n1Idx = (i * 2) % staffList.size();
        int n2Idx = (i * 2 + 1) % staffList.size();

        string dayType = (days[i] == "Sat" || days[i] == "Sun") ? "[EMERGENCY ONLY]" : "[NORMAL OPS]";

        // HATA DÜZELTME: Artık .name yerine firstName ve lastName kullanıyoruz
        cout << left << setw(10) << days[i] 
             << setw(25) << (doctorList[docIdx].firstName + " " + doctorList[docIdx].lastName)
             << (staffList[n1Idx].firstName + " " + staffList[n1Idx].lastName) << " & " 
             << (staffList[n2Idx].firstName + " " + staffList[n2Idx].lastName)
             << setw(20) << dayType << endl;

        // --- NOBET ERTESI IZIN BILGISI ---
        if (i < 9) {
            cout << "       -> REST NEXT DAY (" << days[i+1] << "): " << doctorList[docIdx].lastName 
                 << ", " << staffList[n1Idx].lastName << ", " << staffList[n2Idx].lastName << " (OFF DAY)" << endl;
        }
    }
    cout << string(95, '=') << endl;
}

// GÜNCELLEME: Personel ve Doktor Maaş Raporu
void Staff::calculatePayroll(const vector<Staff>& staffMembers, const vector<Doctor>& doctors) {
    cout << "\n" << string(70, '=') << endl;
    cout << "   HOSPITAL PAYROLL & PERFORMANCE REPORT (JANUARY 2025)   " << endl;
    cout << string(70, '=') << endl;

    cout << "\n[ DOCTOR PAYROLL ]" << endl;
    for (const auto& d : doctors) {
        double doctorBase = 10000.0;
        double specialtyBonus = (d.specialty == "Surgery") ? 2500.0 : 1000.0;
        double total = doctorBase + specialtyBonus;
        cout << ">>> Dr. " << left << setw(20) << (d.firstName + " " + d.lastName)
             << " | Salary: $" << total << " (Inc. Bonus)" << endl;
    }

    cout << "\n[ NURSING & TECH STAFF PAYROLL ]" << endl;
    for (const auto& s : staffMembers) {
        int seniority = 2025 - s.joinYear;
        double roleBonus = (s.role == "Nurse") ? 1.25 : 1.10;
        double finalSalary = (s.baseSalary * roleBonus) + (seniority * 200.0);
        cout << ">>> Staff: " << left << setw(18) << (s.firstName + " " + s.lastName)
             << " | Salary: $" << finalSalary << endl;
    }
}

// GÜNCELLEME: Veri Giriş Doğrulamalı Ekleme (Input Validation)
void Staff::addStaff(vector<Staff>& staffMembers) {
    Staff s;
    cout << "\nEnter First Name: "; cin >> s.firstName;
    cout << "Enter Last Name: "; cin >> s.lastName;
    
    // Sayı girişi doğrulaması (Age)
    while (cout << "Enter Age (18-70): " && (!(cin >> s.age) || s.age < 18 || s.age > 70)) {
        cout << "Invalid input! Please enter a valid number between 18 and 70.\n";
        cin.clear(); cin.ignore(1000, '\n');
    }

    // Cinsiyet Kısıtlaması (male/female)
    do {
        cout << "Enter Gender (male/female): "; cin >> s.gender;
    } while (s.gender != "male" && s.gender != "female");

    cout << "Enter Role (Doctor/Nurse/Tech): "; cin >> s.role;
    cout << "Enter Base Salary: "; cin >> s.baseSalary;
    cout << "Enter Employment Year (YYYY): "; cin >> s.joinYear;

    staffMembers.push_back(s);
    cout << "\nStaff registered successfully! [ID: " << s.id << "]\n";
}

void Staff::searchStaffByName(const vector<Staff>& staffList) const {
    string q;
    cout << "\nEnter Staff Name or ID to filter: ";
    cin.ignore();
    getline(cin, q);

    if (q.empty()) return;
    bool isDigit = all_of(q.begin(), q.end(), ::isdigit);

    bool found = false;
    for (const auto& s : staffList) {
        if (isDigit) {
            if (to_string(s.getID()) == q) { s.displayInfo(); found = true; break; }
        } else {
            // Hem isim hem soyisim içinde arama yapar
            if (s.firstName.find(q) != string::npos || s.lastName.find(q) != string::npos) { 
                s.displayInfo(); found = true; 
            }
        }
    }
    if (!found) cout << "No staff record found matching: " << q << endl;
}

void Staff::displayInfo() const {
    cout << "\n----- Staff Member -----\n";
    Person::displayInfo();
    cout << "Role: " << role << " | Joined: " << joinYear << endl;
    cout << "------------------------\n";
}

void Staff::showAllStaff(const vector<Staff>& staffMembers) {
    cout << "\n===== Hospital Staff Directory =====\n";
    for (size_t i = 0; i < staffMembers.size(); i++) {
        staffMembers[i].displayInfo();
    }
}

void Staff::staffMenu(vector<Staff>& staffMembers, const vector<Doctor>& doctorList) {
    int choice;
    do {
        cout << "\n--- Staff Management System ---" << endl;
        cout << "1. Register New Staff\n2. Search Staff (Name/ID)\n3. Resign Staff\n4. List All\n";
        cout << "5. RUN FULL HOSPITAL PAYROLL\n6. GENERATE 10-DAY DUTY SCHEDULE\n0. Back\nChoice: "; 
        
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1: addStaff(staffMembers); break;
            case 2: searchStaffByName(staffMembers); break;
            case 3: /* deleteStaff çağrısı */ break;
            case 4: showAllStaff(staffMembers); break;
            case 5: calculatePayroll(staffMembers, doctorList); break;
            case 6: generateHospitalSchedule(staffMembers, doctorList); break;
        }
    } while (choice != 0);
}
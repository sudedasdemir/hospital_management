#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <limits> // numeric_limits için
#include "../Header/Appointment.h"
#include "../Header/Staff.h" 

using namespace std;

int Appointment::appointmentCounter = 5000;

string minutesToTime(int totalMinutes) {
    int h = totalMinutes / 60;
    int m = totalMinutes % 60;
    string hStr = (h < 10 ? "0" : "") + to_string(h);
    string mStr = (m < 10 ? "0" : "") + to_string(m);
    return hStr + ":" + mStr;
}

Appointment::Appointment() : id(0), doctorName(""), patientName(""), date(""), time("") {}

Appointment::Appointment(string dName, string pName, string dt, string tm) 
    : doctorName(dName), patientName(pName), date(dt), time(tm) {
    id = ++appointmentCounter;
}

// GÜNCELLEME: Esnek Arama (Partial Match) - Linda yazınca Linda Chen'i bulur
bool Appointment::doctorExists(const vector<Doctor>& doctors, const string& name) const {
    if (name.empty()) return false;
    for (const auto& d : doctors) {
        string fullName = d.getFullName();
        // Kısmi eşleşme kontrolü: Girilen metin tam ismin içinde geçiyor mu?
        if (fullName.find(name) != string::npos || name.find(d.firstName) != string::npos) {
            return true; 
        }
    }
    return false;
}

void Appointment::bookAppointment(vector<Appointment>& appointments,
                                  const vector<Doctor>& doctors,
                                  const vector<Patient>& patients) {
    if (doctors.empty() || patients.empty()) {
        cout << "\nError: System data missing. Register doctors and patients first.\n";
        return;
    }

    cout << "\n--- Select Appointment Type ---" << endl;
    cout << "1. General Consultation\n2. Surgery\n3. Radiology\nChoice: ";
    int typeChoice; cin >> typeChoice;
    string typeStr = (typeChoice == 1) ? "Consultation" : (typeChoice == 2 ? "Surgery" : "Radiology");

    cout << "\n--- Select Department ---" << endl;
    cout << "1. Cardiology\n2. Ophthalmology\n3. Internal Medicine\nChoice: ";
    int dept; cin >> dept;

    string dName, pName, dStr;
    cout << "\nEnter Doctor Name (e.g. Linda): "; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Tampon temizliği
    getline(cin, dName); // Boşluklu isim girişi desteği
    
    cout << "Enter Patient Name (e.g. Sude): "; 
    getline(cin, pName);

    const Patient* targetPat = nullptr;
    for (const auto& p : patients) {
        string pFullName = p.getFullName();
        // GÜNCELLEME: Hastayı bulurken de esnek davranıyoruz
        if (pFullName.find(pName) != string::npos || pName.find(p.firstName) != string::npos) {
            targetPat = &p;
            break;
        }
    }

    // MANTIKSAL DÜZELTME: Esnek arama sayesinde "Rejected" hatası azalır
    if (!doctorExists(doctors, dName) || targetPat == nullptr) {
        cout << "\n[!] Rejected: Name mismatch. Make sure Doctor and Patient are registered.\n";
        return;
    }

    if (targetPat->getAge() >= 65) {
        cout << "\n***************************************************";
        cout << "\n>>> PRIORITY ALERT: Patient is 65+ years old.   <<<";
        cout << "\n***************************************************\n";
    }

    cout << "Enter Day of Week (e.g., Monday): "; cin >> dStr;

    if (typeChoice == 1 && dStr == "Wednesday") { 
         cout << "\n[!] Dr. " << dName << " is in SURGERY on this day. Consultation blocked.\n";
         return;
    }

    cout << "\n--- Available Slots for Dr. " << dName << " ---" << endl;
    vector<string> freeSlots;
    for (int current = 9 * 60; current < 17 * 60; current += 15) {
        string slot = minutesToTime(current);
        bool taken = false;
        for (const auto& app : appointments) {
            if (app.doctorName == dName && app.date == dStr && app.time == slot) {
                taken = true; break;
            }
        }
        if (!taken) {
            freeSlots.push_back(slot);
            cout << "[" << slot << "] ";
        }
    }

    string tStr;
    cout << "\n\nSelect a slot (HH:MM): "; cin >> tStr;

    bool isValid = false;
    for (const string& s : freeSlots) { if (s == tStr) isValid = true; }

    if (!isValid) {
        cout << "\n!!! ERROR: Slot busy or invalid. !!!\n";
    } else {
        appointments.push_back(Appointment(dName, pName, dStr, tStr));
        cout << "\n[" << typeStr << "] Booked Successfully! ID: " << appointments.back().id << "\n";
    }
}

void Appointment::searchAppointmentById(const vector<Appointment>& appointments) const {
    if (appointments.empty()) { cout << "\nNo appointments found.\n"; return; }
    int qid; cout << "\nEnter ID: "; cin >> qid;
    for (size_t i = 0; i < appointments.size(); i++) {
        if (appointments[i].id == qid) {
            cout << "\nID: " << appointments[i].id << " | Dr: " << appointments[i].doctorName 
                 << " | Pat: " << appointments[i].patientName << " | Time: " << appointments[i].time << endl;
            return;
        }
    }
    cout << "Not found.\n";
}

void Appointment::deleteAppointment(vector<Appointment>& appointments) {
    int qid; cout << "\nEnter ID to delete: "; cin >> qid;
    for (size_t i = 0; i < appointments.size(); i++) {
        if (appointments[i].id == qid) {
            appointments.erase(appointments.begin() + i);
            cout << "Deleted.\n"; return;
        }
    }
    cout << "Not found.\n";
}

void Appointment::showAllAppointments(const vector<Appointment>& appointments) const {
    cout << "\n===== All Appointments =====\n";
    for (size_t i = 0; i < appointments.size(); i++) {
        cout << "ID: " << appointments[i].id << " | Dr: " << appointments[i].doctorName 
             << " | Pat: " << appointments[i].patientName << " | Day: " << appointments[i].date << " | Time: " << appointments[i].time << endl;
    }
}

void Appointment::appointmentMenu(vector<Appointment>& appointments,
                                  const vector<Doctor>& doctors,
                                  const vector<Patient>& patients) {
    int choice;
    do {
        cout << "\n--- Appointment Menu ---" << endl;
        cout << "1. Book Appointment\n2. Search\n3. Delete\n4. Show All\n0. Back\nChoice: "; cin >> choice;
        
        // GÜNCELLEME: Menü giriş koruması
        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: bookAppointment(appointments, doctors, patients); break;
            case 2: searchAppointmentById(appointments); break;
            case 3: deleteAppointment(appointments); break;
            case 4: showAllAppointments(appointments); break;
        }
    } while (choice != 0);
}
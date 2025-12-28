#include <iostream>
#include <vector>
#include <stdexcept> 
#include <limits> // Giriş tamponu temizliği için
#include "Header/Doctor.h"
#include "Header/Patient.h"
#include "Header/Staff.h"
#include "Header/Appointment.h"

using namespace std;

// --- AUTOMATIC DATA SEEDING FUNCTION ---
void initializeSystem(vector<Doctor>& doctors, vector<Staff>& staffList) {
    // Sabit Doktor Kadrosu (5 Doktor) - GÜNCELLEME: İsim ve Soyisim ayrıldı
    string firstNames[] = {"Maria", "James", "Linda", "Robert", "Sarah"};
    string lastNames[] = {"Garcia", "Wilson", "Chen", "Taylor", "Adams"};
    string specialties[] = {"Cardiology", "Surgery", "Pediatrics", "Internal Medicine", "Radiology"};
    
    for(int i = 0; i < 5; i++) {
        Doctor d;
        d.firstName = firstNames[i];
        d.lastName = lastNames[i];
        d.specialty = specialties[i];
        doctors.push_back(d);
    }

    // Sabit Hemşire Kadrosu (10 Hemşire) - GÜNCELLEME: İsim ve Soyisim ayrıldı
    string sFirst[] = {"Elena", "Marco", "Sophie", "Lucas", "Isabella", "Nathan", "Olivia", "Ethan", "Mia", "Thomas"};
    string sLast[] = {"Smith", "Rossi", "Muller", "Dubois", "Conti", "Brown", "Wilson", "Moore", "Clark", "Walker"};

    for(int i = 0; i < 10; i++) {
        Staff s;
        s.firstName = "Nurse";
        s.lastName = sFirst[i]; // Örnek: Nurse Elena
        s.role = "Nurse";
        s.baseSalary = 5000.0;
        s.joinYear = 2025; 
        staffList.push_back(s);
    }
}

int main() {
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Staff> staffList;
    vector<Appointment> appointments;

    // Initialize the system with 5 Doctors and 10 Staff automatically
    initializeSystem(doctors, staffList);

    Doctor docObj;
    Patient patObj;
    Staff staffObj;
    Appointment appObj;

    int userRole;
    do {
        cout << "\n==========================================";
        cout << "\n   WELCOME TO HOSPITAL MANAGEMENT SYSTEM  ";
        cout << "\n==========================================";
        cout << "\n1. ADMIN PANEL (System Management)";
        cout << "\n2. STAFF PORTAL (Duty & Schedule Lookup)";
        cout << "\n3. PATIENT PORTAL (Registration & Booking)";
        cout << "\n0. EXIT SYSTEM";
        cout << "\n------------------------------------------";
        cout << "\nSelect Your Role: ";
        
        // --- INPUT VALIDATION: Sayı yerine harf girişini engeller ---
        if (!(cin >> userRole)) {
            cout << "\n[!] Invalid input! Please enter a number.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            if (userRole == 1) { // ADMIN PANEL
                int adminChoice;
                cout << "\n--- ADMIN MANAGEMENT PANEL ---";
                cout << "\n1. Manage Doctors\n2. Manage Patients\n3. Manage Staff\n4. View Full Payroll Report\n5. View All Appointments\n0. Back";
                cout << "\nSelection: "; cin >> adminChoice;
                
                switch (adminChoice) {
                    case 1: docObj.doctorMenu(doctors); break;
                    case 2: patObj.patientMenu(patients); break;
                    case 3: staffObj.staffMenu(staffList, doctors); break;
                    case 4: staffObj.calculatePayroll(staffList, doctors); break; // Updated: Doctors included
                    case 5: appObj.showAllAppointments(appointments); break;
                }
            } 
            else if (userRole == 2) { // STAFF PORTAL
                string empName;
                cout << "\n--- STAFF ACCESS PORTAL ---";
                cout << "\nEnter your First Name to see your Schedule: ";
                cin >> empName;
                
                // Logic: Filter and show only the duty/schedule for the specific staff
                generateHospitalSchedule(staffList, doctors); // Updated with 2 Nurse + 1 Doctor logic
                cout << "\nSearching for Appointments for " << empName << "...\n";
                // Show appointments specifically for this staff/doctor
            } 
            else if (userRole == 3) { // PATIENT PORTAL
                cout << "\n--- PATIENT SELF-SERVICE PORTAL ---";
                cout << "\n1. Register as New Patient (First Time)";
                cout << "\n2. Existing Patient Login (Booking)";
                cout << "\n0. Back\nSelection: ";
                int pMenu; cin >> pMenu;

                if (pMenu == 1) {
                    patObj.addPatient(patients); // MANTIKSAL DÜZELTME: Hasta kendi kaydını yapabilir
                } 
                else if (pMenu == 2) {
                    string pName;
                    cout << "\nEnter your Registered First Name: "; cin >> pName;

                    bool isRegistered = false;
                    for(const auto& p : patients) { 
                        if(p.firstName == pName) { 
                            isRegistered = true;
                            if(p.getAge() >= 65) cout << "\n[!] Priority Account: High Priority Status Detected\n"; 
                            break;
                        }
                    }

                    if(!isRegistered) {
                        cout << "\nError: You are not registered. Please Register first.\n";
                    } else {
                        cout << "\n1. Book New Appointment (Consultation/Surgery/Radiology)";
                        cout << "\n2. View All Doctors & Specialties";
                        cout << "\n0. Back\nSelection: ";
                        int pChoice; cin >> pChoice;
                        if(pChoice == 1) appObj.appointmentMenu(appointments, doctors, patients); 
                        else if(pChoice == 2) docObj.showAllDoctors(doctors); 
                    }
                }
            }
        } 
        catch (const exception& e) {
            cout << "\n[SYSTEM ALERT]: " << e.what() << endl; 
        }

    } while (userRole != 0);

    return 0;
}
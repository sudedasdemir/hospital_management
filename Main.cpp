\
#include <iostream>
#include <vector>
#include "Header/Doctor.h"
#include "Header/Patient.h"
#include "Header/Staff.h"
#include "Header/Appointment.h"
using namespace std;

int main() {
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Staff> staffList;
    vector<Appointment> appointments;

    Doctor docObj;
    Patient patObj;
    Staff staffObj;
    Appointment appObj;

    int choice;
    do {
        cout << "\n======= Hospital Management System =======\n";
        cout << "1. Doctor Management\n";
        cout << "2. Patient Management\n";
        cout << "3. Staff Management\n";
        cout << "4. Appointments Management\n";
        cout << "0. Exit\n";
        cout << "------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: docObj.doctorMenu(doctors); break;
            case 2: patObj.patientMenu(patients); break;
            case 3: staffObj.staffMenu(staffList); break;
            case 4: appObj.appointmentMenu(appointments, doctors, patients); break;
            case 0: cout << "Exiting the system... Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

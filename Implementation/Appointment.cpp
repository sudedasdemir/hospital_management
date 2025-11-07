
#include "../Header/Appointment.h"
#include <iostream>
#include <algorithm>
using namespace std;

int Appointment::appointmentCounter = 5000;

bool Appointment::doctorExists(const vector<Doctor>& doctors, const string& name) const {
    for (const auto& d : doctors) {
        if (d.getName() == name) return true; // Person::getName()
    }
    return false;
}

bool Appointment::patientExists(const vector<Patient>& patients, const string& name) const {
    for (const auto& p : patients) {
        if (p.getName() == name) return true; // Person::getName()
    }
    return false;
}

void Appointment::bookAppointment(vector<Appointment>& appointments,
                                  const vector<Doctor>& doctors,
                                  const vector<Patient>& patients) {
    if (doctors.empty() || patients.empty()) {
        cout << "\nCannot create appointment. You must have at least one registered doctor and patient.\n";
        return;
    }

    Appointment a;
    cout << "\nEnter Doctor Name: ";
    cin >> a.doctorName;
    cout << "Enter Patient Name: ";
    cin >> a.patientName;

    // Validate names
    if (!doctorExists(doctors, a.doctorName) || !patientExists(patients, a.patientName)) {
        cout << "\n Cannot book appointment without a valid Doctor and Patient (names must exist).\n";
        return;
    }

    cout << "Enter Date (DD/MM/YYYY): ";
    cin >> a.date;
    cout << "Enter Time (HH:MM): ";
    cin >> a.time;

    a.id = ++appointmentCounter;
    appointments.push_back(a);
    cout << "\n Appointment booked successfully! [ID: " << a.id << "]\n";
}

void Appointment::searchAppointmentById(const vector<Appointment>& appointments) const {
    if (appointments.empty()) {
        cout << "\nNo appointments found.\n";
        return;
    }
    int qid;
    cout << "\nEnter Appointment ID to search: ";
    cin >> qid;

    bool found = false;
    for (const auto& a : appointments) {
        if (a.id == qid) {
            cout << "\n----- Appointment -----\n";
            cout << "ID: " << a.id << endl;
            cout << "Doctor: " << a.doctorName << endl;
            cout << "Patient: " << a.patientName << endl;
            cout << "Date: " << a.date << endl;
            cout << "Time: " << a.time << endl;
            cout << "-----------------------\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Appointment not found.\n";
}

void Appointment::editAppointment(vector<Appointment>& appointments,
                                  const vector<Doctor>& doctors,
                                  const vector<Patient>& patients) {
    if (appointments.empty()) {
        cout << "\nNo appointments to edit.\n";
        return;
    }
    int qid;
    cout << "\nEnter Appointment ID to edit: ";
    cin >> qid;

    for (auto& a : appointments) {
        if (a.id == qid) {
            cout << "Editing appointment [ID: " << a.id << "]\n";

            string newDoctor, newPatient, newDate, newTime;

            cout << "Enter New Doctor Name (current: " << a.doctorName << "): ";
            cin >> newDoctor;
            cout << "Enter New Patient Name (current: " << a.patientName << "): ";
            cin >> newPatient;

            if (!doctorExists(doctors, newDoctor) || !patientExists(patients, newPatient)) {
                cout << "\n Cannot update. Doctor and Patient must exist.\n";
                return;
            }

            cout << "Enter New Date (DD/MM/YYYY) (current: " << a.date << "): ";
            cin >> newDate;
            cout << "Enter New Time (HH:MM) (current: " << a.time << "): ";
            cin >> newTime;

            a.doctorName  = newDoctor;
            a.patientName = newPatient;
            a.date        = newDate;
            a.time        = newTime;

            cout << "\n Appointment updated successfully.\n";
            return;
        }
    }
    cout << "Appointment not found.\n";
}

void Appointment::deleteAppointment(vector<Appointment>& appointments) {
    if (appointments.empty()) {
        cout << "\nNo appointments to delete.\n";
        return;
    }
    int qid;
    cout << "\nEnter Appointment ID to delete: ";
    cin >> qid;

    auto it = remove_if(appointments.begin(), appointments.end(),
                        [qid](const Appointment& a){ return a.id == qid; });

    if (it != appointments.end()) {
        appointments.erase(it, appointments.end());
        cout << " Appointment deleted successfully.\n";
    } else {
        cout << "Appointment not found.\n";
    }
}

void Appointment::showAllAppointments(const vector<Appointment>& appointments) const {
    cout << "\n===== All Appointments =====\n";
    if (appointments.empty()) {
        cout << "No appointments found.\n";
    } else {
        for (const auto& a : appointments) {
            cout << "ID: " << a.id
                 << " | Doctor: " << a.doctorName
                 << " | Patient: " << a.patientName
                 << " | Date: " << a.date
                 << " | Time: " << a.time << endl;
        }
    }
    cout << "=============================\n";
}

void Appointment::appointmentMenu(vector<Appointment>& appointments,
                                  const vector<Doctor>& doctors,
                                  const vector<Patient>& patients) {
    int choice;
    do {
        cout << "\n------ Appointments ------\n";
        cout << "1. Book New Appointment\n";
        cout << "2. Search by Appointment ID\n";
        cout << "3. Edit Appointment\n";
        cout << "4. Delete Appointment\n";
        cout << "0. Back to Main Menu\n";
        cout << "--------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookAppointment(appointments, doctors, patients); break;
            case 2: searchAppointmentById(appointments); break;
            case 3: editAppointment(appointments, doctors, patients); break;
            case 4: deleteAppointment(appointments); break;
            case 0: cout << "Returning...\n"; break;
            default: cout << "Invalid choice.\n";
        }

        if (choice != 0) {
            cout << "\nCurrent Appointments:\n";
            showAllAppointments(appointments);
        }

    } while (choice!=0);
}

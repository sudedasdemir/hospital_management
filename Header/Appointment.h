#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <vector>
#include "Doctor.h"
#include "Patient.h"

using namespace std;

class Appointment {
private:
    int id;
    // (Turkce Not: Hocanin 'fundamental' dedigi Composition budur. Nesneleri direkt tuttuk)
    string doctorName;
    string patientName;
    string date;
    string time;

    // (Turkce Not: Phase 2 icin gereken static degisken)
    static int appointmentCounter; 

    // Helper functions for validation
    bool doctorExists(const vector<Doctor>& doctors, const string& name) const;
    bool patientExists(const vector<Patient>& patients, const string& name) const;

public:

    // 1. Default Constructor
    Appointment();

    // 2. Overloaded Constructor with Default Arguments
    // (Turkce Not: Hoca 'default argument value assignment' istediği için buraya ekledik)
    Appointment(string dName, string pName, string dt = "01/01/2025", string tm = "09:00"); 

    // Core Management Functions (Requirement: en az 5 fonksiyon)
    void bookAppointment(vector<Appointment>& appointments,
                         const vector<Doctor>& doctors,
                         const vector<Patient>& patients); 

    void searchAppointmentById(const vector<Appointment>& appointments) const;

    void editAppointment(vector<Appointment>& appointments,
                         const vector<Doctor>& doctors,
                         const vector<Patient>& patients);

    void deleteAppointment(vector<Appointment>& appointments);

    void showAllAppointments(const vector<Appointment>& appointments) const;

    void appointmentMenu(vector<Appointment>& appointments,
                         const vector<Doctor>& doctors,
                         const vector<Patient>& patients);
};

#endif
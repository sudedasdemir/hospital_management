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
    string doctorName;
    string patientName;
    string date;
    string time;

    static int appointmentCounter;

    bool doctorExists(const vector<Doctor>& doctors, const string& name) const;
    bool patientExists(const vector<Patient>& patients, const string& name) const;

public:
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
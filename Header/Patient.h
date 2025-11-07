\
#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <vector>
using namespace std;

class Patient : public Person {
private:
    string disease;
    static int patientCounter;

public:
    Patient();

    void addPatient(vector<Patient>& patients);
    void searchPatientByName(const vector<Patient>& patients) const;
    void deletePatient(vector<Patient>& patients);
    void displayPatientInfo() const;
    static void showAllPatients(const vector<Patient>& patients);
    void patientMenu(vector<Patient>& patients);
};

#endif

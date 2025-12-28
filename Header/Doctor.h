#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <vector>
#include <string>

using namespace std;

// Requirement: Inheritance (Kalıtım) - Doctor is a Person
class Doctor : public Person {
public:
    string specialty; // Public for automatic seeding in main

private:
    static int doctorCounter; 
    
public:
    Doctor();
    void displayInfo() const override; // Requirement: Overriding
    void addDoctor(vector<Doctor>& doctors);
    void searchDoctorByName(const vector<Doctor>& doctors) const;
    void deleteDoctor(vector<Doctor>& doctors);
    static void showAllDoctors(const vector<Doctor>& doctors);
    void doctorMenu(vector<Doctor>& doctors);
};

#endif
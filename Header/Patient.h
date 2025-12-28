#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <vector>
#include <string>

using namespace std;

// Requirement: Inheritance - Patient is a Person [cite: 32, 44]
// (Turkce Not: Patient sinifi Person'dan turedigi icin kalitim kurali saglandi)
class Patient : public Person {
private:
    string disease;
    // Requirement: Static Variable for unique IDs 
    static int patientCounter;

public:
    // Default Constructor 
    Patient();

    // Requirement: Overriding 
    // (Turkce Not: displayInfo ismini Person ile ayni yaparak override ediyoruz)
    void displayInfo() const override;

    // Member Functions (Requirement: At least 5 functions) 
    void addPatient(vector<Patient>& patients);
    void searchPatientByName(const vector<Patient>& patients) const;
    void deletePatient(vector<Patient>& patients);
    void sortWithPriority(vector<Patient>& patients);

    // Static function to display all patient records
    static void showAllPatients(const vector<Patient>& patients);
    
    void patientMenu(vector<Patient>& patients);

    // Getter for disease (Algoritma kurarken lazim olabilir)
    string getDisease() const { return disease; }

    int getAge() const { return age; } // Yas bilgisini dondurur
    
};

#endif
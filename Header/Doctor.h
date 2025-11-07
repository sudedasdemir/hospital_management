\
#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <vector>
using namespace std;

class Doctor : public Person {
private:
    string specialty;
    static int doctorCounter;

public:
    Doctor();

    void addDoctor(vector<Doctor>& doctors);
    void searchDoctorByName(const vector<Doctor>& doctors) const;
    void deleteDoctor(vector<Doctor>& doctors);
    void displayDoctorInfo() const;
    static void showAllDoctors(const vector<Doctor>& doctors);

    void doctorMenu(vector<Doctor>& doctors);
};

#endif

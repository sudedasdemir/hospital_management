#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include <vector>
#include <string>

using namespace std;

class Doctor;

// Requirement: Inheritance - Staff is a Person
class Staff : public Person {
private:
    // Requirement: Static Variable for unique IDs
    static int staffCounter;
    // (TR: Ameliyat gununu merkezden yonetmek icin static tanimladik)
    static string globalSurgeryDay; 
    string position;

public: 
    // --- Variables for Algorithms (Public for Initial Seeding) ---
    string role;
    double baseSalary; 
    int joinYear;      

    Staff();
    void displayInfo() const override;
    void addStaff(vector<Staff>& staffList);
    void searchStaffByName(const vector<Staff>& staffList) const;
    void deleteStaff(vector<Staff>& staffList);

    void showPersonalSchedule(string empName, const vector<Staff>& staffList, const vector<Doctor>& doctorList);
    
    // --- COMPLEX ALGORITHM 1: Payroll Calculation ---
    void calculatePayroll(const vector<Staff>& staffMembers, const vector<Doctor>& doctors);

    // --- HOCANIN ISTEDIGI: FRIEND FUNCTION (ALGORITMA 2) ---
    friend void generateHospitalSchedule(const vector<Staff>& staffList, const vector<Doctor>& doctorList);
    
    static void showAllStaff(const vector<Staff>& staffList);
    // Düzeltme: staffMenu artık doctor listesini de alıyor
    void staffMenu(vector<Staff>& staffList, const vector<Doctor>& doctorList);

    static string getSurgeryDay() { return globalSurgeryDay; }
};

#endif
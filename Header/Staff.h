\
#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include <vector>
using namespace std;

class Staff : public Person {
private:
    string position;
    static int staffCounter;

public:
    Staff();

    void addStaff(vector<Staff>& staffList);
    void searchStaffByName(const vector<Staff>& staffList) const;
    void deleteStaff(vector<Staff>& staffList);
    void displayStaffInfo() const;
    static void showAllStaff(const vector<Staff>& staffList);
    void staffMenu(vector<Staff>& staffList);
};

#endif

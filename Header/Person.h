\
#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

// -----------------------------------------------------------
// Base Class: Person
// -----------------------------------------------------------
// This class provides basic information that is shared
// between Doctor, Patient, and Staff classes.
// Demonstrates inheritance and encapsulation.
// -----------------------------------------------------------
class Person {
protected:
    string name;     // Person's full name
    int age;         // Person's age
    string gender;   // Gender of the person
    int id;          // Unique ID (auto-generated in subclasses)

public:
    // Constructors
    Person();
    Person(string n, int a, string g);

    // Core functions
    void setInfo(string n, int a, string g);
    void updateInfo(string n, int a, string g);
    void displayInfo() const;

    // Getters
    string getName() const;
    int getID() const;
};

#endif

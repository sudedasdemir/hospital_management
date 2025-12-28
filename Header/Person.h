#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using namespace std;

// Base Class for all individuals in the system
// (Turkce Not: Kalitim kurali icin gereken temel ata sinif)
class Person {
public: 
    // Requirement: Public access for Initial Seeding in main.cpp
    string firstName;
    string lastName;
    int age;
    string gender;
    int id;

    // Requirement: Default Argument Value Assignment
    Person(string fn = "Unknown", string ln = "Unknown", int a = 0, string g = "N/A");

    // Requirement: Virtual Function for Overriding
    virtual void displayInfo() const;

    // Requirement: Function Overloading
    void updateInfo(string fn, string ln);
    void updateInfo(string fn, string ln, int a, string g);

    // Getters
    // Basic getters
    string getFullName() const { return firstName + " " + lastName; }
    int getID() const { return id; }
};

#endif
\
#include "../Header/Person.h"
#include <iostream>
using namespace std;

// Default constructor
Person::Person() : name(""), age(0), gender(""), id(0) {}

// Parameterized constructor
Person::Person(string n, int a, string g)
    : name(n), age(a), gender(g), id(0) {}

// Set information
void Person::setInfo(string n, int a, string g) {
    name = n;
    age = a;
    gender = g;
}

// Display information
void Person::displayInfo() const {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "ID: " << id << endl;
}

// Getters
string Person::getName() const { return name; }
int Person::getID() const { return id; }

// Update info
void Person::updateInfo(string n, int a, string g) {
    name = n;
    age = a;
    gender = g;
}

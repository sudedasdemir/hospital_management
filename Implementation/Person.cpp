#include "../Header/Person.h"
#include <iostream>

using namespace std;

// Parameterized Constructor
// (Turkce Not: Bu constructor, Person nesnesi ilk olusturuldugunda calisir)
Person::Person(string fn, string ln, int a, string g) 
    : firstName(fn), lastName(ln), age(a), gender(g), id(0) {}

// Function Overloading - Version 1: Updates only the name
// (Turkce Not: Ismi ayni ama parametresi farkli oldugu icin Overloading kuralina uyar)
void Person::updateInfo(string fn, string ln) { 
    firstName = fn; 
    lastName = ln;
}

// Function Overloading - Version 2: Updates all personal info
void Person::updateInfo(string fn, string ln, int a, string g) {
    firstName = fn; 
    lastName = ln;
    age = a; 
    gender = g;
}

// Display basic info - This is a virtual function in the header
// (Turkce Not: Bu fonksiyonu Doctor ve Patient siniflarinda 'override' ediyoruz)
void Person::displayInfo() const {
    cout << "ID: " << id << " | Name: " << firstName << " " << lastName 
         << " | Age: " << age << " | Gender: " << gender << endl;
}

ostream& operator<<(ostream& os, const Person& p) {
    os << "---------------------------------" << endl;
    os << "ID: " << p.id << endl;
    os << "Name: " << p.firstName << " " << p.lastName << endl;
    os << "Age: " << p.age << " | Gender: " << p.gender << endl;
    os << "---------------------------------";
    return os;
}
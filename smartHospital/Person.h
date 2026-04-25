// ============================================================
//  Person.h  —  Base class for Patient and Doctor
//  Concepts: Encapsulation, Inheritance, Virtual Functions
// ============================================================
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int    age;
    string contact;

public:
    // Default constructor
    Person();
    // Parameterized constructor
    Person(string name, int age, string contact);
    // Virtual destructor (important for proper cleanup in inheritance)
    virtual ~Person() {}

    // --- Getters (Encapsulation) ---
    string getName()    const { return name;    }
    int    getAge()     const { return age;     }
    string getContact() const { return contact; }

    // --- Setters ---
    void setName(string n)    { name    = n; }
    void setAge(int a)        { age     = a; }
    void setContact(string c) { contact = c; }

    // Pure virtual display — every derived class MUST implement it
    virtual void display() const = 0;
};

#endif

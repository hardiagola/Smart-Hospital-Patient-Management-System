// ============================================================
//  Doctor.h  —  Derived from Person
//  Concepts: Inheritance, Encapsulation, File I/O
// ============================================================
#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <fstream>

class Doctor : public Person {
private:
    int    doctorID;
    string specialization;
    string availability;   // "Morning" or "Evening"

public:
    // --- Constructors ---
    Doctor();
    Doctor(int id, string name, int age, string contact,
           string spec, string avail);

    // --- Getters ---
    int    getID()             const { return doctorID;       }
    string getSpecialization() const { return specialization; }
    string getAvailability()   const { return availability;   }

    // --- Display (override of pure virtual) ---
    void display() const override;

    // --- File I/O ---
    void saveToFile(ofstream& file) const;
    bool loadFromFile(ifstream& file);
};

#endif

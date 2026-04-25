// ============================================================
//  Patient.h  —  Derived from Person
//  Concepts: Inheritance, Static Member, File I/O, Encapsulation
// ============================================================
#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <fstream>

class Patient : public Person {
private:
    int    patientID;
    string disease;
    string bloodGroup;
    string admissionDate;
    bool   isAdmitted;

    // Static member — tracks total patients ever registered
    static int totalPatients;

public:
    // --- Constructors ---
    Patient();
    Patient(int id, string name, int age, string contact,
            string disease, string bloodGroup, string date);

    // --- Getters ---
    int    getID()              const { return patientID;    }
    string getDisease()         const { return disease;      }
    string getBloodGroup()      const { return bloodGroup;   }
    string getAdmissionDate()   const { return admissionDate;}
    bool   getAdmissionStatus() const { return isAdmitted;   }

    // --- Operations ---
    void discharge();
    void display() const override;   // Polymorphism

    // --- File I/O ---
    void saveToFile(ofstream& file) const;
    bool loadFromFile(ifstream& file);

    // --- Static function ---
    static int getTotalPatients() { return totalPatients; }
    static void setTotalPatients(int t) { totalPatients = t; }
};

#endif

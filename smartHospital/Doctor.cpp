// ============================================================
//  Doctor.cpp  —  Implementation of Doctor class
// ============================================================
#include "Doctor.h"
#include <iomanip>

// Default constructor
Doctor::Doctor()
    : Person(), doctorID(0), specialization("N/A"), availability("N/A") {}

// Parameterized constructor
Doctor::Doctor(int id, string n, int a, string c, string spec, string avail)
    : Person(n, a, c),
      doctorID(id), specialization(spec), availability(avail) {}

// Display doctor details
void Doctor::display() const {
    cout << left;
    cout << "  ┌─────────────────────────────────────┐\n";
    cout << "  │          DOCTOR RECORD               │\n";
    cout << "  ├─────────────────────────────────────┤\n";
    cout << "  │ Doctor ID      : " << setw(19) << doctorID       << "│\n";
    cout << "  │ Name           : " << setw(19) << name           << "│\n";
    cout << "  │ Age            : " << setw(19) << age            << "│\n";
    cout << "  │ Contact        : " << setw(19) << contact        << "│\n";
    cout << "  │ Specialization : " << setw(19) << specialization << "│\n";
    cout << "  │ Availability   : " << setw(19) << availability   << "│\n";
    cout << "  └─────────────────────────────────────┘\n";
}

// Save doctor to file
void Doctor::saveToFile(ofstream& file) const {
    file << doctorID       << "\n"
         << name           << "\n"
         << age            << "\n"
         << contact        << "\n"
         << specialization << "\n"
         << availability   << "\n";
}

// Load doctor from file
bool Doctor::loadFromFile(ifstream& file) {
    if (!(file >> doctorID)) return false;
    file.ignore();
    getline(file, name);
    file >> age;
    file.ignore();
    getline(file, contact);
    getline(file, specialization);
    getline(file, availability);
    return true;
}

// ============================================================
//  Patient.cpp  —  Implementation of Patient class
// ============================================================
#include "Patient.h"
#include <iomanip>

// Initialize static member
int Patient::totalPatients = 0;

// Default constructor
Patient::Patient()
    : Person(), patientID(0), disease("N/A"),
      bloodGroup("N/A"), admissionDate("N/A"), isAdmitted(false) {}

// Parameterized constructor — calls base class constructor (constructor chaining)
Patient::Patient(int id, string n, int a, string c,
                 string dis, string bg, string date)
    : Person(n, a, c),
      patientID(id), disease(dis), bloodGroup(bg),
      admissionDate(date), isAdmitted(true)
{
    totalPatients++;
}

// Discharge the patient
void Patient::discharge() {
    isAdmitted = false;
    cout << "\n  [✓] Patient \"" << name << "\" has been discharged.\n";
}

// Display patient details (override of pure virtual)
void Patient::display() const {
    cout << left;
    cout << "  ┌─────────────────────────────────────┐\n";
    cout << "  │         PATIENT RECORD               │\n";
    cout << "  ├─────────────────────────────────────┤\n";
    cout << "  │ Patient ID   : " << setw(21) << patientID    << "│\n";
    cout << "  │ Name         : " << setw(21) << name         << "│\n";
    cout << "  │ Age          : " << setw(21) << age          << "│\n";
    cout << "  │ Contact      : " << setw(21) << contact      << "│\n";
    cout << "  │ Disease      : " << setw(21) << disease      << "│\n";
    cout << "  │ Blood Group  : " << setw(21) << bloodGroup   << "│\n";
    cout << "  │ Admitted On  : " << setw(21) << admissionDate<< "│\n";
    cout << "  │ Status       : " << setw(21) << (isAdmitted ? "Admitted" : "Discharged") << "│\n";
    cout << "  └─────────────────────────────────────┘\n";
}

// Save patient data to file
void Patient::saveToFile(ofstream& file) const {
    file << patientID    << "\n"
         << name         << "\n"
         << age          << "\n"
         << contact      << "\n"
         << disease      << "\n"
         << bloodGroup   << "\n"
         << admissionDate<< "\n"
         << isAdmitted   << "\n";
}

// Load patient data from file
bool Patient::loadFromFile(ifstream& file) {
    if (!(file >> patientID)) return false;
    file.ignore();
    getline(file, name);
    file >> age;
    file.ignore();
    getline(file, contact);
    getline(file, disease);
    getline(file, bloodGroup);
    getline(file, admissionDate);
    file >> isAdmitted;
    file.ignore();
    return true;
}

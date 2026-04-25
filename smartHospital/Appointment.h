// ============================================================
//  Appointment.h  —  Appointment record
//  Concepts: Class Design, File I/O, Encapsulation
// ============================================================
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Appointment {
private:
    int    appointmentID;
    int    patientID;
    int    doctorID;
    string patientName;
    string doctorName;
    string date;
    string status;  // "Scheduled" / "Completed" / "Cancelled"

public:
    // --- Constructors ---
    Appointment();
    Appointment(int apID, int pID, int dID,
                string pName, string dName,
                string date);

    // --- Getters ---
    int    getAppointmentID() const { return appointmentID; }
    int    getPatientID()     const { return patientID;     }
    int    getDoctorID()      const { return doctorID;      }
    string getStatus()        const { return status;        }
    string getDate()          const { return date;          }

    // --- Operations ---
    void markCompleted()  { status = "Completed";  }
    void markCancelled()  { status = "Cancelled";  }

    // --- Display ---
    void display() const;

    // --- File I/O ---
    void saveToFile(ofstream& file) const;
    bool loadFromFile(ifstream& file);
};

// ============================================================
//  Appointment.cpp  —  (inline implementation for simplicity)
// ============================================================

inline Appointment::Appointment()
    : appointmentID(0), patientID(0), doctorID(0),
      patientName("N/A"), doctorName("N/A"), date("N/A"), status("Scheduled") {}

inline Appointment::Appointment(int apID, int pID, int dID,
                                 string pName, string dName, string d)
    : appointmentID(apID), patientID(pID), doctorID(dID),
      patientName(pName), doctorName(dName), date(d), status("Scheduled") {}

inline void Appointment::display() const {
    cout << left;
    cout << "  ┌─────────────────────────────────────┐\n";
    cout << "  │        APPOINTMENT RECORD            │\n";
    cout << "  ├─────────────────────────────────────┤\n";
    cout << "  │ Appt. ID     : " << setw(21) << appointmentID << "│\n";
    cout << "  │ Patient ID   : " << setw(21) << patientID     << "│\n";
    cout << "  │ Patient Name : " << setw(21) << patientName   << "│\n";
    cout << "  │ Doctor ID    : " << setw(21) << doctorID      << "│\n";
    cout << "  │ Doctor Name  : " << setw(21) << doctorName    << "│\n";
    cout << "  │ Date         : " << setw(21) << date          << "│\n";
    cout << "  │ Status       : " << setw(21) << status        << "│\n";
    cout << "  └─────────────────────────────────────┘\n";
}

inline void Appointment::saveToFile(ofstream& file) const {
    file << appointmentID << "\n"
         << patientID     << "\n"
         << doctorID      << "\n"
         << patientName   << "\n"
         << doctorName    << "\n"
         << date          << "\n"
         << status        << "\n";
}

inline bool Appointment::loadFromFile(ifstream& file) {
    if (!(file >> appointmentID)) return false;
    file >> patientID >> doctorID;
    file.ignore();
    getline(file, patientName);
    getline(file, doctorName);
    getline(file, date);
    getline(file, status);
    return true;
}

#endif

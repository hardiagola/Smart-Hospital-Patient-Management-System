// ============================================================
//  Bill.h  —  Billing for patients
//  Concepts: Class, Encapsulation, File I/O, Calculation
// ============================================================
#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Bill {
private:
    int    billID;
    int    patientID;
    string patientName;
    double consultationFee;
    double medicineCost;
    double roomCharge;
    bool   isPaid;

public:
    Bill();
    Bill(int bID, int pID, string pName,
         double consult, double medicine, double room);

    // --- Getters ---
    int    getBillID()     const { return billID;     }
    int    getPatientID()  const { return patientID;  }
    bool   getIsPaid()     const { return isPaid;     }

    // Total amount (inline function — from syllabus topic)
    inline double getTotalAmount() const {
        return consultationFee + medicineCost + roomCharge;
    }

    void markPaid() { isPaid = true; }

    // --- Display ---
    void display() const;

    // --- File I/O ---
    void saveToFile(ofstream& file) const;
    bool loadFromFile(ifstream& file);
};

// ============================================================
//  Inline implementation
// ============================================================

inline Bill::Bill()
    : billID(0), patientID(0), patientName("N/A"),
      consultationFee(0), medicineCost(0), roomCharge(0), isPaid(false) {}

inline Bill::Bill(int bID, int pID, string pName,
                  double consult, double medicine, double room)
    : billID(bID), patientID(pID), patientName(pName),
      consultationFee(consult), medicineCost(medicine),
      roomCharge(room), isPaid(false) {}

inline void Bill::display() const {
    cout << fixed << setprecision(2);
    cout << "\n  ============================================\n";
    cout << "       SMART HOSPITAL - BILLING RECEIPT\n";
    cout << "  ============================================\n";
    cout << "  Bill ID         : " << billID                << "\n";
    cout << "  Patient ID      : " << patientID             << "\n";
    cout << "  Patient Name    : " << patientName           << "\n";
    cout << "  --------------------------------------------\n";
    cout << "  Consultation Fee: Rs. " << setw(10) << consultationFee << "\n";
    cout << "  Medicine Cost   : Rs. " << setw(10) << medicineCost    << "\n";
    cout << "  Room Charges    : Rs. " << setw(10) << roomCharge      << "\n";
    cout << "  --------------------------------------------\n";
    cout << "  TOTAL AMOUNT    : Rs. " << setw(10) << getTotalAmount() << "\n";
    cout << "  Payment Status  : " << (isPaid ? "PAID" : "PENDING")   << "\n";
    cout << "  ============================================\n";
}

inline void Bill::saveToFile(ofstream& file) const {
    file << billID           << "\n"
         << patientID        << "\n"
         << patientName      << "\n"
         << consultationFee  << "\n"
         << medicineCost     << "\n"
         << roomCharge       << "\n"
         << isPaid           << "\n";
}

inline bool Bill::loadFromFile(ifstream& file) {
    if (!(file >> billID)) return false;
    file >> patientID;
    file.ignore();
    getline(file, patientName);
    file >> consultationFee >> medicineCost >> roomCharge >> isPaid;
    file.ignore();
    return true;
}

#endif

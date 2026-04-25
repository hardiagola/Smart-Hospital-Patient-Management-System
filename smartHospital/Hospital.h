// ============================================================
//  Hospital.h  —  Central Management Class
//  Concepts: STL vector, STL map, Polymorphism, File I/O
// ============================================================
#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Bill.h"
#include "Exceptions.h"
#include <vector>
#include <map>

class Hospital {
private:
    string hospitalName;

    // STL containers to store records
    vector<Patient>     patients;
    vector<Doctor>      doctors;
    vector<Appointment> appointments;
    vector<Bill>        bills;

    // STL map for fast patient lookup by ID
    map<int, int> patientIndexMap;  // patientID -> index in patients vector
    map<int, int> doctorIndexMap;   // doctorID  -> index in doctors vector

    // ID counters
    int nextPatientID;
    int nextDoctorID;
    int nextAppointmentID;
    int nextBillID;

    // File paths
    const string PATIENT_FILE     = "patients.dat";
    const string DOCTOR_FILE      = "doctors.dat";
    const string APPOINTMENT_FILE = "appointments.dat";
    const string BILL_FILE        = "bills.dat";

public:
    Hospital(string name);

    // --- Patient Operations ---
    void registerPatient();
    void viewAllPatients();
    void searchPatientByID();
    void searchPatientByName();
    void dischargePatient();

    // --- Doctor Operations ---
    void addDoctor();
    void viewAllDoctors();
    void searchDoctorBySpecialization();

    // --- Appointment Operations ---
    void bookAppointment();
    void viewAllAppointments();
    void updateAppointmentStatus();

    // --- Billing Operations ---
    void generateBill();
    void viewBill();
    void markBillPaid();

    // --- File Operations (Practical 5) ---
    void saveAllData();
    void loadAllData();

    // --- Statistics ---
    void showStatistics();

    // --- Helper (uses polymorphism via Person*) ---
    void displayPersonInfo(Person* p);
};

#endif

// ============================================================
//  Hospital.cpp  —  Implementation of Hospital class
//  All syllabus concepts are used here together
// ============================================================
#include "Hospital.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

// ─── Constructor ─────────────────────────────────────────────
Hospital::Hospital(string name)
    : hospitalName(name),
      nextPatientID(1001), nextDoctorID(201),
      nextAppointmentID(3001), nextBillID(5001)
{
    loadAllData();
}

// ─── Helper: Clear input buffer ──────────────────────────────
static void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ─── Helper: Display info using polymorphism ─────────────────
void Hospital::displayPersonInfo(Person* p) {
    p->display();   // virtual function call — runtime polymorphism
}

// ═════════════════════════════════════════════════════════════
//  PATIENT OPERATIONS
// ═════════════════════════════════════════════════════════════

void Hospital::registerPatient() {
    cout << "\n  ── Register New Patient ──\n";
    try {
        string name, contact, disease, bloodGroup, date;
        int age;

        cout << "  Enter Name      : "; clearBuffer();
        getline(cin, name);
        if (name.empty()) throw InvalidInputException("Name cannot be empty.");

        cout << "  Enter Age       : ";
        cin >> age;
        if (cin.fail() || age <= 0 || age > 150)
            throw InvalidInputException("Age must be between 1 and 150.");

        cout << "  Enter Contact   : "; clearBuffer();
        getline(cin, contact);
        if (contact.empty()) throw InvalidInputException("Contact cannot be empty.");

        cout << "  Enter Disease   : ";
        getline(cin, disease);
        if (disease.empty()) throw InvalidInputException("Disease cannot be empty.");

        cout << "  Enter Blood Grp : ";
        getline(cin, bloodGroup);

        cout << "  Admission Date  : ";
        getline(cin, date);

        // Check duplicate ID (already guaranteed by auto-increment, but good practice)
        if (patientIndexMap.count(nextPatientID))
            throw DuplicateIDException("Patient ID already exists.");

        Patient p(nextPatientID, name, age, contact, disease, bloodGroup, date);
        patientIndexMap[nextPatientID] = (int)patients.size();
        patients.push_back(p);
        nextPatientID++;

        cout << "\n  [✓] Patient registered. ID = " << (nextPatientID - 1) << "\n";
    }
    catch (InvalidInputException& e) {
        cout << "\n  [!] Input Error: " << e.what() << "\n";
    }
    catch (DuplicateIDException& e) {
        cout << "\n  [!] Duplicate: " << e.what() << "\n";
    }
}

void Hospital::viewAllPatients() {
    if (patients.empty()) {
        cout << "\n  [i] No patients registered yet.\n";
        return;
    }
    cout << "\n  ── All Patients (" << patients.size() << " records) ──\n";
    // Polymorphism: using Person* to call derived class display()
    for (auto& p : patients) {
        Person* ptr = &p;
        displayPersonInfo(ptr);
    }
}

void Hospital::searchPatientByID() {
    cout << "\n  Enter Patient ID to search: ";
    int id; cin >> id;
    try {
        if (!patientIndexMap.count(id))
            throw RecordNotFoundException("Patient ID " + to_string(id) + " not found.");
        int idx = patientIndexMap[id];
        patients[idx].display();
    }
    catch (RecordNotFoundException& e) {
        cout << "\n  [!] " << e.what() << "\n";
    }
}

void Hospital::searchPatientByName() {
    cout << "\n  Enter Patient Name (partial): ";
    clearBuffer();
    string keyword;
    getline(cin, keyword);

    // Convert keyword to lowercase for case-insensitive search
    string kLower = keyword;
    transform(kLower.begin(), kLower.end(), kLower.begin(), ::tolower);

    bool found = false;
    for (auto& p : patients) {
        string nameLower = p.getName();
        transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
        if (nameLower.find(kLower) != string::npos) {
            p.display();
            found = true;
        }
    }
    if (!found) cout << "\n  [i] No patients found with name containing \"" << keyword << "\".\n";
}

void Hospital::dischargePatient() {
    cout << "\n  Enter Patient ID to discharge: ";
    int id; cin >> id;
    try {
        if (!patientIndexMap.count(id))
            throw RecordNotFoundException("Patient ID " + to_string(id) + " not found.");
        int idx = patientIndexMap[id];
        if (!patients[idx].getAdmissionStatus())
            throw InvalidInputException("Patient is already discharged.");
        patients[idx].discharge();
    }
    catch (RecordNotFoundException& e) { cout << "\n  [!] " << e.what() << "\n"; }
    catch (InvalidInputException& e)   { cout << "\n  [!] " << e.what() << "\n"; }
}

// ═════════════════════════════════════════════════════════════
//  DOCTOR OPERATIONS
// ═════════════════════════════════════════════════════════════

void Hospital::addDoctor() {
    cout << "\n  ── Add New Doctor ──\n";
    try {
        string name, contact, spec, avail;
        int age;

        cout << "  Enter Name           : "; clearBuffer();
        getline(cin, name);
        if (name.empty()) throw InvalidInputException("Name cannot be empty.");

        cout << "  Enter Age            : ";
        cin >> age;
        if (cin.fail() || age <= 0 || age > 100)
            throw InvalidInputException("Invalid age.");

        cout << "  Enter Contact        : "; clearBuffer();
        getline(cin, contact);

        cout << "  Enter Specialization : ";
        getline(cin, spec);
        if (spec.empty()) throw InvalidInputException("Specialization cannot be empty.");

        cout << "  Availability (Morning/Evening): ";
        getline(cin, avail);

        Doctor d(nextDoctorID, name, age, contact, spec, avail);
        doctorIndexMap[nextDoctorID] = (int)doctors.size();
        doctors.push_back(d);
        nextDoctorID++;

        cout << "\n  [✓] Doctor added. ID = " << (nextDoctorID - 1) << "\n";
    }
    catch (InvalidInputException& e) {
        cout << "\n  [!] Input Error: " << e.what() << "\n";
    }
}

void Hospital::viewAllDoctors() {
    if (doctors.empty()) {
        cout << "\n  [i] No doctors added yet.\n";
        return;
    }
    cout << "\n  ── All Doctors (" << doctors.size() << " records) ──\n";
    for (auto& d : doctors) {
        Person* ptr = &d;
        displayPersonInfo(ptr);   // polymorphism
    }
}

void Hospital::searchDoctorBySpecialization() {
    cout << "\n  Enter Specialization to search: ";
    clearBuffer();
    string keyword;
    getline(cin, keyword);

    string kLower = keyword;
    transform(kLower.begin(), kLower.end(), kLower.begin(), ::tolower);

    bool found = false;
    for (auto& d : doctors) {
        string specLower = d.getSpecialization();
        transform(specLower.begin(), specLower.end(), specLower.begin(), ::tolower);
        if (specLower.find(kLower) != string::npos) {
            d.display();
            found = true;
        }
    }
    if (!found) cout << "\n  [i] No doctors found for specialization \"" << keyword << "\".\n";
}

// ═════════════════════════════════════════════════════════════
//  APPOINTMENT OPERATIONS
// ═════════════════════════════════════════════════════════════

void Hospital::bookAppointment() {
    cout << "\n  ── Book Appointment ──\n";
    try {
        int pID, dID;
        string date;

        cout << "  Enter Patient ID : "; cin >> pID;
        if (!patientIndexMap.count(pID))
            throw RecordNotFoundException("Patient ID " + to_string(pID) + " not found.");
        if (!patients[patientIndexMap[pID]].getAdmissionStatus())
            throw InvalidInputException("Patient is already discharged.");

        cout << "  Enter Doctor ID  : "; cin >> dID;
        if (!doctorIndexMap.count(dID))
            throw RecordNotFoundException("Doctor ID " + to_string(dID) + " not found.");

        cout << "  Enter Date (DD/MM/YYYY): "; clearBuffer();
        getline(cin, date);
        if (date.empty()) throw InvalidInputException("Date cannot be empty.");

        string pName = patients[patientIndexMap[pID]].getName();
        string dName = doctors[doctorIndexMap[dID]].getName();

        Appointment ap(nextAppointmentID, pID, dID, pName, dName, date);
        appointments.push_back(ap);
        nextAppointmentID++;

        cout << "\n  [✓] Appointment booked. ID = " << (nextAppointmentID - 1) << "\n";
    }
    catch (RecordNotFoundException& e) { cout << "\n  [!] " << e.what() << "\n"; }
    catch (InvalidInputException& e)   { cout << "\n  [!] " << e.what() << "\n"; }
}

void Hospital::viewAllAppointments() {
    if (appointments.empty()) {
        cout << "\n  [i] No appointments booked yet.\n";
        return;
    }
    cout << "\n  ── All Appointments (" << appointments.size() << " records) ──\n";
    for (auto& ap : appointments) ap.display();
}

void Hospital::updateAppointmentStatus() {
    cout << "\n  Enter Appointment ID: ";
    int id; cin >> id;
    bool found = false;
    for (auto& ap : appointments) {
        if (ap.getAppointmentID() == id) {
            cout << "  1. Mark Completed\n  2. Mark Cancelled\n  Choice: ";
            int ch; cin >> ch;
            if (ch == 1) ap.markCompleted();
            else if (ch == 2) ap.markCancelled();
            else cout << "  [!] Invalid choice.\n";
            found = true;
            cout << "  [✓] Status updated.\n";
            break;
        }
    }
    if (!found) cout << "\n  [!] Appointment ID not found.\n";
}

// ═════════════════════════════════════════════════════════════
//  BILLING OPERATIONS
// ═════════════════════════════════════════════════════════════

void Hospital::generateBill() {
    cout << "\n  ── Generate Bill ──\n";
    try {
        int pID;
        double consult, medicine, room;

        cout << "  Enter Patient ID         : "; cin >> pID;
        if (!patientIndexMap.count(pID))
            throw RecordNotFoundException("Patient ID " + to_string(pID) + " not found.");

        cout << "  Consultation Fee (Rs.)   : "; cin >> consult;
        cout << "  Medicine Cost (Rs.)      : "; cin >> medicine;
        cout << "  Room Charges (Rs./day)   : "; cin >> room;

        if (cin.fail() || consult < 0 || medicine < 0 || room < 0)
            throw InvalidInputException("Amounts cannot be negative.");

        string pName = patients[patientIndexMap[pID]].getName();
        Bill b(nextBillID, pID, pName, consult, medicine, room);
        bills.push_back(b);
        nextBillID++;

        b.display();
        cout << "  [✓] Bill generated. Bill ID = " << (nextBillID - 1) << "\n";
    }
    catch (RecordNotFoundException& e) { cout << "\n  [!] " << e.what() << "\n"; }
    catch (InvalidInputException& e)   { cout << "\n  [!] " << e.what() << "\n"; }
}

void Hospital::viewBill() {
    cout << "\n  Enter Patient ID to view bill: ";
    int pID; cin >> pID;
    bool found = false;
    for (auto& b : bills) {
        if (b.getPatientID() == pID) {
            b.display();
            found = true;
        }
    }
    if (!found) cout << "\n  [i] No bill found for Patient ID " << pID << ".\n";
}

void Hospital::markBillPaid() {
    cout << "\n  Enter Bill ID to mark as paid: ";
    int bID; cin >> bID;
    bool found = false;
    for (auto& b : bills) {
        if (b.getBillID() == bID) {
            if (b.getIsPaid()) cout << "\n  [i] Bill already paid.\n";
            else { b.markPaid(); cout << "\n  [✓] Bill marked as PAID.\n"; }
            found = true;
            break;
        }
    }
    if (!found) cout << "\n  [!] Bill ID not found.\n";
}

// ═════════════════════════════════════════════════════════════
//  FILE OPERATIONS (Practical 5 — File Processing)
// ═════════════════════════════════════════════════════════════

void Hospital::saveAllData() {
    // Save patients
    {
        ofstream file(PATIENT_FILE);
        if (!file) { cout << "\n  [!] Error saving patient data.\n"; return; }
        file << nextPatientID << "\n" << patients.size() << "\n";
        for (auto& p : patients) p.saveToFile(file);
        file.close();
    }
    // Save doctors
    {
        ofstream file(DOCTOR_FILE);
        if (!file) { cout << "\n  [!] Error saving doctor data.\n"; return; }
        file << nextDoctorID << "\n" << doctors.size() << "\n";
        for (auto& d : doctors) d.saveToFile(file);
        file.close();
    }
    // Save appointments
    {
        ofstream file(APPOINTMENT_FILE);
        if (!file) return;
        file << nextAppointmentID << "\n" << appointments.size() << "\n";
        for (auto& ap : appointments) ap.saveToFile(file);
        file.close();
    }
    // Save bills
    {
        ofstream file(BILL_FILE);
        if (!file) return;
        file << nextBillID << "\n" << bills.size() << "\n";
        for (auto& b : bills) b.saveToFile(file);
        file.close();
    }
    cout << "\n  [✓] All data saved to files.\n";
}

void Hospital::loadAllData() {
    // Load patients
    {
        ifstream file(PATIENT_FILE);
        if (!file) return;
        int count;
        file >> nextPatientID >> count;
        file.ignore();
        for (int i = 0; i < count; i++) {
            Patient p;
            if (p.loadFromFile(file)) {
                patientIndexMap[p.getID()] = (int)patients.size();
                patients.push_back(p);
            }
        }
        file.close();
    }
    // Load doctors
    {
        ifstream file(DOCTOR_FILE);
        if (!file) return;
        int count;
        file >> nextDoctorID >> count;
        file.ignore();
        for (int i = 0; i < count; i++) {
            Doctor d;
            if (d.loadFromFile(file)) {
                doctorIndexMap[d.getID()] = (int)doctors.size();
                doctors.push_back(d);
            }
        }
        file.close();
    }
    // Load appointments
    {
        ifstream file(APPOINTMENT_FILE);
        if (!file) return;
        int count;
        file >> nextAppointmentID >> count;
        file.ignore();
        for (int i = 0; i < count; i++) {
            Appointment ap;
            if (ap.loadFromFile(file)) appointments.push_back(ap);
        }
        file.close();
    }
    // Load bills
    {
        ifstream file(BILL_FILE);
        if (!file) return;
        int count;
        file >> nextBillID >> count;
        file.ignore();
        for (int i = 0; i < count; i++) {
            Bill b;
            if (b.loadFromFile(file)) bills.push_back(b);
        }
        file.close();
    }
}

// ═════════════════════════════════════════════════════════════
//  STATISTICS
// ═════════════════════════════════════════════════════════════

void Hospital::showStatistics() {
    int admitted = 0, discharged = 0;
    for (auto& p : patients) {
        if (p.getAdmissionStatus()) admitted++;
        else discharged++;
    }

    int scheduled = 0, completed = 0, cancelled = 0;
    for (auto& ap : appointments) {
        if (ap.getStatus() == "Scheduled")  scheduled++;
        else if (ap.getStatus() == "Completed") completed++;
        else cancelled++;
    }

    double totalRevenue = 0;
    for (auto& b : bills) totalRevenue += b.getTotalAmount();

    cout << fixed << setprecision(2);
    cout << "\n  ╔═══════════════════════════════════════╗\n";
    cout << "  ║         HOSPITAL STATISTICS           ║\n";
    cout << "  ╠═══════════════════════════════════════╣\n";
    cout << "  ║  Total Patients   : " << setw(17) << patients.size()     << " ║\n";
    cout << "  ║  Currently Admitted: " << setw(16) << admitted           << " ║\n";
    cout << "  ║  Discharged       : " << setw(17) << discharged          << " ║\n";
    cout << "  ║  Total Doctors    : " << setw(17) << doctors.size()      << " ║\n";
    cout << "  ║  Appointments     : " << setw(17) << appointments.size() << " ║\n";
    cout << "  ║    - Scheduled    : " << setw(17) << scheduled           << " ║\n";
    cout << "  ║    - Completed    : " << setw(17) << completed           << " ║\n";
    cout << "  ║    - Cancelled    : " << setw(17) << cancelled           << " ║\n";
    cout << "  ║  Total Revenue    : Rs. " << setw(14) << totalRevenue    << " ║\n";
    cout << "  ╚═══════════════════════════════════════╝\n";
}

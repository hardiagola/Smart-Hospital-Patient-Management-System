// ============================================================
//  main.cpp  —  Smart Hospital Patient Management System
//  CEUC102 — Programming with C++  |  Semester 2
//  Faculty of Technology & Engineering, CHARUSAT
//
//  Concepts Covered:
//   ✓ Classes & Objects         (Practical 2)
//   ✓ Inheritance               (Practical 6)
//   ✓ Polymorphism + Virtual    (Practical 7)
//   ✓ Abstract Class            (Practical 7.5)
//   ✓ File I/O                  (Practical 5)
//   ✓ Exception Handling        (Practical 8)
//   ✓ STL vector & map          (Practical 9)
//   ✓ Static Members            (Practical 3.3)
//   ✓ Constructor Chaining      (Practical 6.2)
//   ✓ Encapsulation             (Practical 1)
// ============================================================

#include <iostream>
#include <string>
#include <limits>
#include "Hospital.h"
using namespace std;


// ── Helper: Print the main menu ──────────────────────────────
void printMainMenu() {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════╗\n";
    cout << "  ║    SMART HOSPITAL MANAGEMENT SYSTEM      ║\n";
    cout << "  ╠══════════════════════════════════════════╣\n";
    cout << "  ║  PATIENT MANAGEMENT                      ║\n";
    cout << "  ║   1. Register New Patient                ║\n";
    cout << "  ║   2. View All Patients                   ║\n";
    cout << "  ║   3. Search Patient by ID                ║\n";
    cout << "  ║   4. Search Patient by Name              ║\n";
    cout << "  ║   5. Discharge Patient                   ║\n";
    cout << "  ╠══════════════════════════════════════════╣\n";
    cout << "  ║  DOCTOR MANAGEMENT                       ║\n";
    cout << "  ║   6. Add New Doctor                      ║\n";
    cout << "  ║   7. View All Doctors                    ║\n";
    cout << "  ║   8. Search Doctor by Specialization     ║\n";
    cout << "  ╠══════════════════════════════════════════╣\n";
    cout << "  ║  APPOINTMENT MANAGEMENT                  ║\n";
    cout << "  ║   9. Book Appointment                    ║\n";
    cout << "  ║  10. View All Appointments               ║\n";
    cout << "  ║  11. Update Appointment Status           ║\n";
    cout << "  ╠══════════════════════════════════════════╣\n";
    cout << "  ║  BILLING                                 ║\n";
    cout << "  ║  12. Generate Patient Bill               ║\n";
    cout << "  ║  13. View Patient Bill                   ║\n";
    cout << "  ║  14. Mark Bill as Paid                   ║\n";
    cout << "  ╠══════════════════════════════════════════╣\n";
    cout << "  ║  15. Hospital Statistics                 ║\n";
    cout << "  ║  16. Save All Data                       ║\n";
    cout << "  ║   0. Exit                                ║\n";
    cout << "  ╚══════════════════════════════════════════╝\n";
    cout << "  Enter your choice: ";
}

// ── Main Function ─────────────────────────────────────────────
int main() {
    system("chcp 65001");
    // Create Hospital object — loads saved data automatically
    Hospital hospital("City Care Hospital");

    cout << "\n  ╔══════════════════════════════════════════╗\n";
    cout << "  ║   Welcome to Smart Hospital System       ║\n";
    cout << "  ║   City Care Hospital — Est. 2025         ║\n";
    cout << "  ╚══════════════════════════════════════════╝\n";
    cout << "  [i] Previous data loaded from files.\n";

    int choice;
    do {
        printMainMenu();
        cin >> choice;

        // Handle non-integer input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n  [!] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            // ── Patient ──
            case 1:  hospital.registerPatient();           break;
            case 2:  hospital.viewAllPatients();           break;
            case 3:  hospital.searchPatientByID();         break;
            case 4:  hospital.searchPatientByName();       break;
            case 5:  hospital.dischargePatient();          break;
            // ── Doctor ──
            case 6:  hospital.addDoctor();                 break;
            case 7:  hospital.viewAllDoctors();            break;
            case 8:  hospital.searchDoctorBySpecialization(); break;
            // ── Appointment ──
            case 9:  hospital.bookAppointment();           break;
            case 10: hospital.viewAllAppointments();       break;
            case 11: hospital.updateAppointmentStatus();   break;
            // ── Billing ──
            case 12: hospital.generateBill();              break;
            case 13: hospital.viewBill();                  break;
            case 14: hospital.markBillPaid();              break;
            // ── Misc ──
            case 15: hospital.showStatistics();            break;
            case 16: hospital.saveAllData();               break;
            case 0:
                hospital.saveAllData();   // auto-save on exit
                cout << "\n  [✓] Data saved. Goodbye!\n\n";
                break;
            default:
                cout << "\n  [!] Invalid choice. Please enter 0–16.\n";
        }

    } while (choice != 0);

    cout<<"\n25CE001-25CE002-25CE003\n";

    return 0;
}

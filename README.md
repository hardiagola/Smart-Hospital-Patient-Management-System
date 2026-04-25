# Smart-Hospital-Patient-Management-System
A console-based Hospital Management System built in C++ demonstrating OOP, Inheritance, Polymorphism, STL, File I/O, and Exception Handling.

#  Smart Hospital Patient Management System

> A console-based C++ project developed as part of **CEUC102 — Programming with C++**  
> Semester 2 | Faculty of Technology & Engineering | CSPIT, CHARUSAT (2025–2026)

---

##  About the Project

The **Smart Hospital Patient Management System** simulates the core operations of a real-world hospital using Object-Oriented Programming in C++. It allows hospital staff to manage patients, doctors, appointments, and billing — with all data saved persistently to files so nothing is lost between sessions.

This project was built to demonstrate practical application of C++ concepts learned throughout the semester, including inheritance, polymorphism, STL containers, file handling, and exception handling.

---

##  Features

-  **Patient Management** — Register, search, view, and discharge patients
-  **Doctor Management** — Add doctors with specialization and availability
-  **Appointment Booking** — Book, view, and update appointment status
-  **Billing System** — Auto-calculate bills with consultation, medicine, and room charges
-  **Smart Search** — Search patients by ID or partial name (case-insensitive)
-  **Statistics Dashboard** — View total patients, revenue, and appointment summary
- **File Persistence** — All records saved to `.dat` files and reloaded on startup
- **Exception Handling** — Custom exceptions for invalid input and missing records

---

##  C++ Concepts Used

| Concept | Implementation |
|---|---|
| Abstract Class & Pure Virtual | `Person::display()` forces override in derived classes |
| Hierarchical Inheritance | `Patient` and `Doctor` both inherit from `Person` |
| Runtime Polymorphism | `Person*` pointer calls correct `display()` at runtime |
| Constructor Chaining | Derived constructors call base `Person()` via initializer list |
| Static Data Member | `Patient::totalPatients` tracks registrations across all objects |
| Inline Function | `Bill::getTotalAmount()` for fast fee calculation |
| File I/O | `ofstream`/`ifstream` used to save and load all records |
| Custom Exception Handling | `RecordNotFoundException`, `InvalidInputException`, `DuplicateIDException` |
| STL `vector` | Stores dynamic lists of patients, doctors, appointments, bills |
| STL `map` | Fast O(1) lookup of patient/doctor by ID |
| String Manipulation | Case-insensitive search using `std::transform` and `tolower` |

---

## Academic Info

| Field | Details |
|---|---|
| Course | CEUC102 — Programming with C++ |
| Semester | 2nd Semester (2025–2026) |
| University | CHARUSAT — Charotar University of Science & Technology |
| Institute | CSPIT — Chandubhai S. Patel Institute of Technology |
| Tools Used | C++17, VS Code, Code::Blocks, g++ |

---

##  Author

**Hardi Agola**  
Enrollment No: 25CE002  
B.Tech — CE  
CSPIT, CHARUSAT

---

##  License

This project is submitted for academic evaluation purposes.

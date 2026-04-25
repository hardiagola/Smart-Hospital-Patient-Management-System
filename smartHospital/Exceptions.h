// ============================================================
//  Exceptions.h  —  Custom Exception Classes
//  Concepts: Exception Handling, Custom Exception (Practical 8.2)
// ============================================================
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
using namespace std;

// Exception: Record not found
class RecordNotFoundException : public exception {
private:
    string message;
public:
    RecordNotFoundException(string msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Exception: Invalid input
class InvalidInputException : public exception {
private:
    string message;
public:
    InvalidInputException(string msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Exception: Duplicate ID
class DuplicateIDException : public exception {
private:
    string message;
public:
    DuplicateIDException(string msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif

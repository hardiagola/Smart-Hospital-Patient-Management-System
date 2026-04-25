// ============================================================
//  Person.cpp  —  Implementation of Person base class
// ============================================================
#include "Person.h"

// Default constructor
Person::Person() : name("Unknown"), age(0), contact("N/A") {}

// Parameterized constructor
Person::Person(string n, int a, string c)
    : name(n), age(a), contact(c) {}

#ifndef PATIENT_H
#define PATIENT_H

#include <string>
// =====================
//  Patient.h
//  Defines the core data structure representing a single
//  patient in the triage system.
//
//  Severity levels (1 = highest priority, treated first):
//    1 - Critical   (highest priority, treated first)
//    2 - Serious
//    3 - Moderate
//    4 - Minor
//    5 - Routine    (lowest priority)
//
//  Routing rule:
//    Severity 1-2  =  Emergency Priority Queue
//    Severity 3-5  =  Standard FIFO Queue
//  Author  :Kent Rowen Reyes
//  Group   : Team 1
//  Course  : CC 103
// =====================

struct Patient {
    int         id;         // Unique auto-incremented patient ID
    std::string name;       // Full name of the patient
    std::string ailment;    // Reported ailment / chief complaint
    int         severity;   // Priority level: 1 (Critical) … 5 (Routine)

    // Default constructor
    Patient()
        : id(0), name(""), ailment(""), severity(0) {}

    // Parameterised constructor
    Patient(int id, const std::string& name,
            const std::string& ailment, int severity)
        : id(id), name(name), ailment(ailment), severity(severity) {}
};

#endif // PATIENT_H

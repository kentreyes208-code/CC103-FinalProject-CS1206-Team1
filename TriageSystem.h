// writes class declaration


#ifndef TRIAGESYSTEM_H
#define TRIAGESYSTEM_H

#include "PriorityQueue.h"
#include <string>
#include <deque>    // deque used for the FIFO standard queue
#include <vector>   // vector used for the LIFO activity stack

// =====================
//  TriageSystem.h
//  Declares the TriageSystem class — the high-level manager
//  that bridges the raw data structures with the hospital-
//  specific business logic and console UI.
//
//  Data structures (REVISED):
//    stack_         — LIFO activity log of recent registrations
//    emergencyPQ_   — Priority Queue for severity 1-2 patients
//    standardQueue_ — FIFO Queue    for severity 3-5 patients
//
//  Routing rule:
//    Severity 1-2  → emergencyPQ_   (called first)
//    Severity 3-5  → standardQueue_ (called after emergencyPQ_)
//    All patients  → stack_         (always pushed on register)
//
//  Responsibilities:
//    • Maintaining all three patient structures
//    • Auto-incrementing unique patient IDs
//    • Providing user-friendly operations (admit, call, view)
//    • Printing formatted output / status banners
//  Author  :Trixie Feigh Sanchez
//  Group   : Team 1
//  Course  : CC 103
// =====================

class TriageSystem {
public:
    TriageSystem();     // Constructor — seeds the ID counter

    // ── Patient management ──────────────────────────────────

    // Collect patient details interactively and add to queue
    void admitPatient();

    // Remove & display the next (highest-priority) patient
    void callNextPatient();

    // Show the top patient without removing them
    void peekNextPatient() const;

    // Print the full sorted waitlist
    void viewWaitlist()   const;

    // Return total number of waiting patients (both queues)
    int  getPatientCount() const;

    // ── CUI helpers ──────────────────────────────────────────

    // Print the main menu banner
    static void printMenu();

    // Print a styled section divider with a title
    static void printBanner(const string& title);

    // Print a success / error message with a prefix tag
    static void printStatus(const string& tag,
                             const string& message);

private:
    // ── Data structures ─────────────────────────────────────

    // Emergency triage — Priority Queue (severity 1-2, lowest number = highest urgency)
    PriorityQueue           emergencyPQ_;

    // Standard waiting list — FIFO Queue (severity 3-5, arrival order)
    std::deque<Patient>     standardQueue_;

    // Recent registration log — LIFO Stack (most recent registration on top)
    std::vector<Patient>    stack_;

    // ── Internal helpers ────────────────────────────────────

    int nextId_;      // Auto-increment counter for patient IDs

    // Prompt the user for a severity level (1-5) and validate input
    static int  promptSeverity();

    // Prompt for a non-empty string field (name / ailment)
    static std::string promptString(const std::string& fieldName);

    // Display the standard FIFO queue as a formatted table
    void displayStandardQueue() const;

    // Display the LIFO activity stack (most recent first)
    void displayActivityStack() const;
};

#endif 

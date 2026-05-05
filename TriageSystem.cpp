// =====================
//  TriageSystem.cpp
//  Implements the TriageSystem class declared in TriageSystem.h.
//  Contains all hospital-specific features and console UI logic.
//
//  KEY LOGIC CHANGES (vs. original):
//    • Severity scale is now 1-5  (1 = Critical, 5 = Routine)
//    • admitPatient()  pushes every patient onto stack_ (log),
//      then routes: sev 1-2 → emergencyPQ_, sev 3-5 → standardQueue_
//    • callNextPatient() drains emergencyPQ_ first; only when
//      it is empty does it pull from standardQueue_
//    • peekNextPatient() previews emergencyPQ_ if non-empty,
//      else peeks the front of standardQueue_
//    • viewWaitlist() prints all three structures separately
//    • getPatientCount() returns the sum of both queues
// =====================

#include "TriageSystem.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <string>
using namespace std;

// ANSI colour helpers (degrades gracefully on Windows CMD) 
namespace Color {
    const string RESET   = "\033[0m";
    const string RED     = "\033[1;31m";
    const string GREEN   = "\033[1;32m";
    const string YELLOW  = "\033[1;33m";
    const string CYAN    = "\033[1;36m";
    const string WHITE   = "\033[1;37m";
    const string MAGENTA = "\033[1;35m";
}

//  Constructor 
TriageSystem::TriageSystem() : nextId_(1001) {}

// printBanner 
void TriageSystem::printBanner(const string& title) {
    const int width = 54;
    cout << "\n" << Color::CYAN;
    const string hLine(width, '=');
    cout << "  +" << hLine << "+\n";
    // Centre the title inside the box
    int padding = (width - static_cast<int>(title.size())) / 2;
    cout << "  |" << string(padding, ' ')
              << title
              << string(width - padding - static_cast<int>(title.size()), ' ')
              << "|\n";
    std::cout << "  +" << hLine << "+"
              << Color::RESET << "\n\n";
}

// printMenu 
void TriageSystem::printMenu() {
    cout << Color::WHITE;
    cout << "\n+---------------------------------------+\n";
    cout << "|          TRIAGE SYSTEM MENU           |\n";
    cout << "+---------------------------------------+\n";
    cout << "|  1.  Register New Patient             |\n";
    cout << "|  2.  Call Next Patient (Dequeue)      |\n";
    cout << "|  3.  Peek at Next Patient             |\n";
    cout << "|  4.  View Full Waitlist               |\n";
    cout << "|  5.  Exit                             |\n";
    cout << "+---------------------------------------+\n";
    cout << Color::RESET;
    cout << "  Choice: ";
}

//  printStatus 
void TriageSystem::printStatus(const string& tag,
                                const string& message) {
    string color;
    if      (tag == "OK")   color = Color::GREEN;
    else if (tag == "ERR")  color = Color::RED;
    else if (tag == "INFO") color = Color::YELLOW;
    else                    color = Color::WHITE;

    cout << "\n  " << color << "[ " << tag << " ]"
              << Color::RESET << "  " << message << "\n";
}

//  promptString 
string TriageSystem::promptString(const string& fieldName) {
    string value;
    while (true) {
        cout << "  " << fieldName << ": ";
        getline(cin, value);
        if (!value.empty()) return value;
        cout << Color::RED
                  << "  [ERR] Field cannot be empty. Try again.\n"
                  << Color::RESET;
    }
}

// promptSeverity
//  Updated to accept 1-5.  1 = Critical (highest), 5 = Routine.
int TriageSystem::promptSeverity() {
    int level = 0;
    while (true) {
        cout << "  Severity  [1=Critical | 2=Serious | 3=Moderate | 4=Minor | 5=Routine]: ";
        if (cin >> level && level >= 1 && level <= 5) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return level;
        }
        // Bad input — clear the stream and try again
        cin.clear();
        cin.ignore(numeric_limits< streamsize>::max(), '\n');
        cout << Color::RED
                  << "  [ERR] Please enter a number from 1 to 5.\n"
                  << Color::RESET;
    }
}

// ── Internal helper: severity number → coloured label string ─
static string sevLabel(int sev) {
    switch (sev) {
        case 1:  return Color::RED     + "1-CRITICAL" + Color::RESET;
        case 2:  return Color::RED     + "2-SERIOUS " + Color::RESET;
        case 3:  return Color::YELLOW  + "3-MODERATE" + Color::RESET;
        case 4:  return Color::GREEN   + "4-MINOR   " + Color::RESET;
        case 5:  return Color::GREEN   + "5-ROUTINE " + Color::RESET;
        default: return Color::WHITE   + "UNKNOWN   " + Color::RESET;
    }
}

// ── admitPatient ────────────────────────────────────────────
//  Collects patient data, pushes onto the activity stack,
//  then routes to the correct queue based on severity.
void TriageSystem::admitPatient() {
    printBanner("REGISTER NEW PATIENT");

    string name    = promptString("Full Name");
    string ailment = promptString("Chief Complaint / Ailment");
    int    sev     = promptSeverity();

    Patient p(nextId_++, name, ailment, sev);

    // ── Always push to the activity stack (LIFO log) ─
    stack_.push_back(p);

    //  Route by severity 
    //    Severity 1-2 → Emergency Priority Queue
    //    Severity 3-5 → Standard FIFO Queue
    string destination;
    if (sev <= 2) {
        emergencyPQ_.enqueue(p);
        destination = Color::RED + "[EMERGENCY PRIORITY QUEUE]" + Color::RESET;
    } else {
        standardQueue_.push_back(p);
        destination = Color::YELLOW + "[STANDARD WAITING QUEUE]" + Color::RESET;
    }

    cout << "\n  " << Color::GREEN << "Patient registered successfully."
              << Color::RESET << "\n";
    cout << "  =====================================\n";
    cout << "  Patient ID  : " << p.id                    << "\n";
    cout << "  Name        : " << p.name                  << "\n";
    cout << "  Ailment     : " << p.ailment               << "\n";
    cout << "  Severity    : " << sevLabel(sev)           << "\n";
    cout << "  Routed to   : " << destination             << "\n";
    cout << "  Stack log   : " << stack_.size()
                               << " recent registration(s) recorded\n";
    cout << "  Queue size  : " << getPatientCount()
                               << " patient(s) waiting total\n";
    cout << "  =====================================\n";
}

// ── callNextPatient ─────────────────────────────────────────
//  Dequeues from emergencyPQ_ first (severity 1-2).
//  Only pulls from standardQueue_ when emergencyPQ_ is empty.
//  This guarantees no Critical/Serious patient is ever skipped.
void TriageSystem::callNextPatient() {
    printBanner("CALL NEXT PATIENT");

    // Guard: both queues empty
    if (emergencyPQ_.isEmpty() && standardQueue_.empty()) {
        printStatus("ERR", "Both queues are empty — no patients to call.");
        return;
    }

    Patient p;
    string  sourceLabel;

    if (!emergencyPQ_.isEmpty()) {
        // Emergency queue takes absolute precedence
        p           = emergencyPQ_.dequeue();
        sourceLabel = Color::RED + "[EMERGENCY PRIORITY QUEUE]" + Color::RESET;
    } else {
        // Standard FIFO queue — pull from the front
        p           = standardQueue_.front();
        standardQueue_.pop_front();
        sourceLabel = Color::YELLOW + "[STANDARD WAITING QUEUE]" + Color::RESET;
    }

    cout << "  " << Color::MAGENTA
              << "  NOW CALLING TO CONSULTATION ROOM:"
              << Color::RESET << "\n\n";
    cout << "  Patient ID  : " << p.id           << "\n";
    cout << "  Name        : " << p.name         << "\n";
    cout << "  Ailment     : " << p.ailment      << "\n";
    cout << "  Severity    : " << sevLabel(p.severity) << "\n";
    cout << "  Source      : " << sourceLabel    << "\n";
    cout << "\n  " << getPatientCount()
              << " patient(s) still in the waitlist.\n";
}

// ── peekNextPatient ─────────────────────────────────────────
//  Previews the patient who would be called next without
//  removing them.  Mirrors the priority logic of callNextPatient.
void TriageSystem::peekNextPatient() const {
    printBanner("NEXT PATIENT PREVIEW");

    if (emergencyPQ_.isEmpty() && standardQueue_.empty()) {
        printStatus("ERR", "Both queues are empty — nothing to peek at.");
        return;
    }

    Patient p;
    string  sourceLabel;

    if (!emergencyPQ_.isEmpty()) {
        p           = emergencyPQ_.peek();
        sourceLabel = Color::RED + "[EMERGENCY PRIORITY QUEUE]" + Color::RESET;
    } else {
        p           = standardQueue_.front();
        sourceLabel = Color::YELLOW + "[STANDARD WAITING QUEUE]" + Color::RESET;
    }

    cout << "  The following patient will be called next:\n\n";
    cout << "  Patient ID  : " << p.id                  << "\n";
    cout << "  Name        : " << p.name                << "\n";
    cout << "  Ailment     : " << p.ailment             << "\n";
    cout << "  Severity    : " << sevLabel(p.severity)  << "\n";
    cout << "  Source      : " << sourceLabel           << "\n";
}

// ── displayStandardQueue ────────────────────────────────────
//  Prints the standard FIFO queue (arrival order).
void TriageSystem::displayStandardQueue() const {
    if (standardQueue_.empty()) {
        cout << "  [Standard queue is empty]\n";
        return;
    }

    cout << "\n";
    cout << "  " << string(63, '-') << "\n";
    cout << "  " << left
              << setw(5)  << "Pos"
              << setw(6)  << "ID"
              << setw(22) << "Name"
              << setw(20) << "Ailment"
              << setw(10) << "Severity"
              << "\n";
    cout << "  " << string(63, '-') << "\n";

    auto label = [](int s) -> string {
        switch (s) {
            case 3:  return "MODERATE ";
            case 4:  return "MINOR    ";
            case 5:  return "ROUTINE  ";
            default: return "UNKNOWN  ";
        }
    };

    int pos = 1;
    for (const Patient& p : standardQueue_) {
        cout << "  " << left
                  << setw(5)  << pos
                  << setw(6)  << p.id
                  << setw(22) << p.name
                  << setw(20) << p.ailment
                  << setw(10) << label(p.severity)
                  << "\n";
        ++pos;
    }
    cout << "  " << string(63, '-') << "\n";
}

// ── displayActivityStack ────────────────────────────────────
//  Prints the registration log (most recent on top = LIFO).
void TriageSystem::displayActivityStack() const {
    if (stack_.empty()) {
        cout << "  [Activity log is empty]\n";
        return;
    }

    cout << "\n";
    cout << "  " << string(63, '-') << "\n";
    cout << "  " << left
              << setw(5)  << "Rec"
              << setw(6)  << "ID"
              << setw(22) << "Name"
              << setw(20) << "Ailment"
              << setw(10) << "Severity"
              << "\n";
    cout << "  " << std::string(63, '-') << "\n";

    auto label = [](int s) -> string {
        switch (s) {
            case 1:  return "CRITICAL ";
            case 2:  return "SERIOUS  ";
            case 3:  return "MODERATE ";
            case 4:  return "MINOR    ";
            case 5:  return "ROUTINE  ";
            default: return "UNKNOWN  ";
        }
    };

    // Iterate in reverse — top of stack (most recent) printed first
    int rec = 1;
    for (int i = static_cast<int>(stack_.size()) - 1; i >= 0; --i) {
        const Patient& p = stack_[i];
        cout << "  " << std::left
                  << setw(5)  << rec
                  << setw(6)  << p.id
                  << setw(22) << p.name
                  << setw(20) << p.ailment
                  << setw(10) << label(p.severity)
                  << "\n";
        ++rec;
    }
    cout << "  " << std::string(63, '-') << "\n";
}

// ── viewWaitlist ────────────────────────────────────────────
//  Prints all three structures so staff can see the full picture.
void TriageSystem::viewWaitlist() const {
    printBanner("CURRENT WAITLIST");

    // Section 1 — Emergency Priority Queue
    cout << Color::RED << "  [1/3] EMERGENCY PRIORITY QUEUE"
              << "  (Severity 1-2 · highest urgency first)\n"
              << Color::RESET;
    emergencyPQ_.display();
    cout << "  Emergency patients waiting: " << emergencyPQ_.size() << "\n";

    cout << "\n";

    // Section 2 — Standard FIFO Queue
    cout << Color::YELLOW << "  [2/3] STANDARD WAITING QUEUE"
              << "  (Severity 3-5 · arrival order)\n"
              << Color::RESET;
    displayStandardQueue();
    cout << "  Standard patients waiting : " << standardQueue_.size() << "\n";

    cout << "\n";

    // Section 3 — Activity Stack (registration log)
    cout << Color::CYAN << "  [3/3] RECENT REGISTRATION LOG"
              << "  (Stack · most recent on top)\n"
              << Color::RESET;
    displayActivityStack();
    cout << "  Total log entries         : " << stack_.size() << "\n";

    cout << "\n  Total patients waiting    : " << getPatientCount() << "\n";
}

// ── getPatientCount ─────────────────────────────────────────
//  Returns the combined size of both active queues.
//  (The stack is a log — it does not shrink when patients are called.)
int TriageSystem::getPatientCount() const {
    return emergencyPQ_.size() + static_cast<int>(standardQueue_.size());
}

// ============================================================
//  PriorityQueue.cpp
//  Implements the linked-list priority queue declared in
//  PriorityQueue.h.
//
//  Insertion strategy (enqueue) — REVISED:
//    Walk the list until we find a node whose severity number
//    is STRICTLY GREATER THAN the incoming patient's severity,
//    then splice the new node in before it.
//    Because 1 = Critical (highest urgency), a lower number
//    means higher priority, so the front of the list always
//    holds the most urgent patient.
//    Ties preserve first-come-first-served order (stable).
//  Author  : Lianne Jade Magtaas
//  Group   : Team 1
//  Course  : CC 103
// ============================================================

#include "PriorityQueue.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

// ── Constructor ─────────────────────────────────────────────
PriorityQueue::PriorityQueue() : head(nullptr), count(0) {}

// ── Destructor ──────────────────────────────────────────────
PriorityQueue::~PriorityQueue() {
    // Walk the list and free every node to avoid memory leaks
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head  = nullptr;
    count = 0;
}

//  enqueue 
//  Inserts 'patient' so that the list remains sorted by
//  ascending severity number (lowest number - front).
//  Severity 1 (Critical) always precedes 2, 3, 4, 5.
void PriorityQueue::enqueue(const Patient& patient) {
    Node* newNode = new Node(patient);

    // Case 1: Empty list  OR  new patient is more urgent than head
    //         (smaller severity number = higher urgency)
    if (head == nullptr || patient.severity < head->data.severity) {
        newNode->next = head;
        head          = newNode;
        ++count;
        return;
    }

    // Case 2: Walk until we find the correct insertion point.
    //         Stop when the NEXT node has a strictly GREATER
    //         severity number (i.e. lower priority) so that
    //         ties are broken by arrival order (stable sort).
    Node* current = head;
    while (current->next != nullptr &&
           current->next->data.severity <= patient.severity) {
        current = current->next;
    }

    // Splice newNode between current and current->next
    newNode->next  = current->next;
    current->next  = newNode;
    ++count;
}

// ── dequeue ─────────────────────────────────────────────────
//  Removes and returns the patient at the front (highest priority).
//  Throws std::underflow_error if the queue is empty.
Patient PriorityQueue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty — no patients to call.");
    }

    Node*   frontNode = head;
    Patient frontData = frontNode->data;

    head = head->next;
    delete frontNode;
    --count;

    return frontData;
}

// peek
//  Returns (without removing) the highest-priority patient.
//  Throws std::underflow_error if the queue is empty.
Patient PriorityQueue::peek() const {
    if (isEmpty()) {
        throw underflow_error("Queue is empty — nothing to peek at.");
    }
    return head->data;
}

//  isEmpty 
bool PriorityQueue::isEmpty() const {
    return head == nullptr;
}

//  size 
int PriorityQueue::size() const {
    return count;
}

// display 
//  Prints the entire waitlist, in priority order, to stdout.
void PriorityQueue::display() const {
    if (isEmpty()) {
        std::cout << "  [Emergency queue is empty]\n";
        return;
    }

    // Helper lambda — maps severity 1-5 to a readable label
    auto severityLabel = [](int s) -> std::string {
        switch (s) {
            case 1:  return "CRITICAL ";
            case 2:  return "SERIOUS  ";
            case 3:  return "MODERATE ";
            case 4:  return "MINOR    ";
            case 5:  return "ROUTINE  ";
            default: return "UNKNOWN  ";
        }
    };

    // Table header
    cout << "\n";
    cout << "  " << std::string(63, '-') << "\n";
    cout << "  " << std::left
              << setw(5)  << "Pos"
              << setw(6)  << "ID"
              << setw(22) << "Name"
              << setw(20) << "Ailment"
              << setw(10) << "Severity"
              << "\n";
    cout << "  " << string(63, '-') << "\n";

    // Rows
    Node* current = head;
    int   pos     = 1;
    while (current != nullptr) {
        const Patient& p = current->data;
        cout << "  " << std::left
                  << setw(5)  << pos
                  << setw(6)  << p.id
                  << setw(22) << p.name
                  << setw(20) << p.ailment
                  << setw(10) << severityLabel(p.severity)
                  << "\n";
        current = current->next;
        ++pos;
    }
    cout << "  " << string(63, '-') << "\n";
}

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Patient.h"

//  PriorityQueue.h
//  Declares a singly-linked-list based priority queue.
//  Priority rule (REVISED):
//    Patients with LOWER severity numbers are positioned
//    closer to the front (head) of the list, so severity 1
//    (Critical) is always dequeued before 2, 3, 4, or 5.
//    Ties preserve first-come-first-served order (stable).
//  Author  : Lianne Jade Magtaas
//  Group   : Team 1
//  Course  : CC 103

//  Internal linked-list node
//  (Used only by PriorityQueue — not exposed to callers)
// -----------------
struct Node {
    Patient data;   // The patient stored in this node
    Node*   next;   // Pointer to the next node in the list

    explicit Node(const Patient& p) : data(p), next(nullptr) {}
};


//  PriorityQueue class

class PriorityQueue {
public:
    PriorityQueue();    // Constructor  — initialises an empty queue
    ~PriorityQueue();   // Destructor   — frees all heap-allocated nodes

    // Core queue operations
    void    enqueue(const Patient& patient);    // Insert patient in priority order
    Patient dequeue();                          // Remove & return the highest-priority patient
    Patient peek()    const;                    // Inspect highest-priority patient (no removal)

    // Utility
    bool    isEmpty() const;                    // Returns true when queue has no patients
    int     size()    const;                    // Returns the current number of patients
    void    display() const;                    // Prints the full waitlist to stdout

private:
    Node* head;         // Points to the lowest-severity-number node (front of queue)
    int   count;        // Tracks number of nodes currently in the list
};

#endif // PRIORITYQUEUE_H

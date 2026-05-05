# [Documentation Website of Hospital Triage and Patient Management (Read Here)](https://readme-team1-d4u5.vercel.app/)

▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃

## ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ 「 MARKDOWN VERSION 」
# ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎  Hospital Triage & Patient Management System

## ◢ Table of Contents

* [╰► Project Title](#-project-title)
* [╰► Problem Description](#-problem-description--what-problem-are-you-solving)
* [╰► Data Structures Used](#-data-structures-used--what-it-is-why-you-used-it)
* [╰► Algorithm Explanation](#️-algorithm-explanation--step-by-step-logic)
* [╰► Iterative vs Recursive Comparison](#-iterative-vs-recursive-comparison--which-is-faster-which-is-easier)
* [╰► Design Decisions](#-design-decisions--choices-and-trade-offs)
* [╰► Team Members](#-team-members)
* [╰► Acknowledgement](#-acknowledgement)
* [╰► Full Interactive Version](#-full-interactive-version)

═══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Project Title

**Hospital Triage & Patient Management System**

════════════════════════════════════════════════════════════════════════

## ◢ Problem Description

Many hospital patient management systems face challenges in efficiently handling patient flow, particularly when dealing with both emergency and non-emergency cases.

Common issues include:

* Lack of prioritization for critical patients
* Disorganized patient queues
* Absence of a reliable activity log for tracking recent registrations
* Inefficient display and traversal of patient records

Without a structured system, critical patients may experience delays, and hospital staff may struggle to maintain accountability and workflow clarity.

════════════════════════════════════════════════════════════════════════

### ◢ Proposed Solution

This project implements a **multi-level queuing system** that:

* Prioritizes emergency cases using a **Priority Queue**
* Maintains fairness for regular patients using a **FIFO Queue**
* Tracks all recent activities using a **Stack**
* Uses **recursion** for structured data traversal

════════════════════════════════════════════════════════════════════════

## ◢ Data Structures Used

### ╰► Stack (LIFO)

**What it is:**
A Last-In, First-Out (LIFO) data structure implemented using `std::vector`.

**Why it was used:**
To maintain a **recent activity log**, allowing quick access to the most recently registered patients for auditing and review.

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► FIFO Queue

**What it is:**
A First-In, First-Out (FIFO) data structure implemented using `std::deque`.

**Why it was used:**
To ensure **fair processing of non-critical patients**, maintaining the order in which they arrived.

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Priority Queue (Linked List Implementation)

**What it is:**
A custom-built singly linked list that maintains sorted order based on patient severity.

**Why it was used:**
To ensure that **patients with higher urgency (lower severity number)** are always treated first, regardless of arrival time.

════════════════════════════════════════════════════════════════════════

### ◢ Severity Classification

| Severity | Description | Queue          |
| -------- | ----------- | -------------- |
| 1        | Critical    | Priority Queue |
| 2        | Serious     | Priority Queue |
| 3        | Moderate    | FIFO Queue     |
| 4        | Minor       | FIFO Queue     |
| 5        | Routine     | FIFO Queue     |

════════════════════════════════════════════════════════════════════════

## ◢ Algorithm or Step-by-step logic

### ╰► Step 1: Patient Registration

* Input patient name, complaint, and severity
* Assign a unique ID starting from 1001

**Explanation:**
When a patient arrives, the system collects essential information such as their name, medical concern, and severity level. A unique identifier is automatically generated to ensure that each patient can be tracked individually. This step establishes the foundation for all subsequent operations in the system.

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Step 2: Stack Logging

* Every patient is pushed onto the stack
* Ensures a complete activity history

**Explanation:**
Immediately after registration, the patient is stored in a stack. Since a stack follows the Last-In, First-Out principle, the most recently registered patient is always on top. This allows hospital staff to quickly review or undo recent entries, making it useful for auditing and tracking recent activity.

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Step 3: Severity-Based Routing

```cpp
if (severity <= 2)
    emergencyPQ.enqueue(patient);
else
    standardQueue.push_back(patient);
```

**Explanation:**
The system evaluates the severity level of the patient to determine where they should be placed. Patients with severity levels 1 or 2 are considered urgent and are routed to the Priority Queue. Patients with severity levels 3 to 5 are placed in the standard FIFO queue. This separation ensures that critical patients are handled immediately without being delayed by less urgent cases.

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Step 4: Priority Queue Insertion

```cpp
while (current->next != nullptr &&
       current->next->data.severity <= patient.severity) {
    current = current->next;
}

newNode->next = current->next;
current->next = newNode;
```

**Explanation:**
When inserting into the Priority Queue, the system traverses the linked list to find the correct position based on severity. The loop continues until it finds a node with a lower priority (higher severity number). The new patient is then inserted at that position. This ensures that the list remains sorted at all times, with the most critical patient always at the front.

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Step 5: Calling the Next Patient

* Check **Priority Queue first**
* If empty, serve from FIFO queue

**Explanation:**
When the system needs to call the next patient, it always checks the Priority Queue first. If there are emergency patients waiting, the one with the highest priority is served immediately. Only when the Priority Queue is empty does the system proceed to serve patients from the FIFO queue. This guarantees that urgent cases are never delayed.

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Step 6: Recursive Display

```cpp
static void displayRecursive(Node* current, int pos) {
    if (current == nullptr) return;
    displayRecursive(current->next, pos + 1);
}
```

**Explanation:**
The system uses recursion to display the contents of the Priority Queue. The function processes one node at a time and then calls itself for the next node. The base case stops the recursion when there are no more nodes. This approach simplifies traversal logic and closely matches the structure of a linked list, making the code easier to understand.

════════════════════════════════════════════════════════════════════════

## ◢ Iterative vs Recursive Comparison 

| Aspect                | Iterative                  | Recursive                      |
| --------------------- | -------------------------- | ------------------------------ |
| Speed                 | Faster (no function calls) | Slightly slower                |
| Memory Usage          | O(1)                       | O(n) stack usage               |
| Ease of Understanding | Moderate                   | Easier for traversal logic     |
| Risk                  | No overflow risk           | Possible stack overflow (rare) |

### ╰► Conclusion

* **Iterative approach** is more efficient and suitable for production systems
* **Recursive approach** is easier to understand and aligns with linked list structure

════════════════════════════════════════════════════════════════════════

## ◢ Design Decisions

### ╰► Custom Priority Queue

* Built using a linked list instead of `std::priority_queue`
* ✔ Allows full control over sorting and stability
* ❌ Slower insertion (O(n))

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Dual Queue System

* Separate queues for emergency and standard patients
* ✔ Ensures critical patients are always prioritized
* ❌ Adds slight complexity in routing logic

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Use of STL Containers

* `vector` used for stack
* `deque` used for queue
* ✔ Reduces implementation complexity
* ✔ Improves reliability

 ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °

### ╰► Recursive Traversal

* Used for displaying patient records
* ✔ Cleaner and more intuitive
* ❌ Uses additional memory

════════════════════════════════════════════════════════════════════════

## ◢ Team Members

| Name                 | Role                                               |
| -------------------- | -------------------------------------------------- |
| Lianne Jade Magtaas  | Documenter · Test Programmer · Analyst · Presenter |
| Kent Rowen L. Reyes  | Data Structures & Algorithm Specialist             |
| Trixie Feigh Sanchez | Main Programmer · System Architect                 |
| Andrea L. Valenzuela | Designer · Research Coordinator                    |

════════════════════════════════════════════════════════════════════════

## ◢ Acknowledgement

**Ms. Fatima Marie Agdon**
Professor, CC 103 — Data Structures and Algorithms
> We sincerely thank our professor for her guidance, support, and encouragement throughout the development of this project.

**Batangas State University — Alangilan Campus**
*"The National Engineering University"*


**College of Informatics and Computing Sciences (CICS)**
For providing the academic environment and resources necessary for this project.

════════════════════════════════════════════════════════════════════════

## ◢ Full Interactive Version

For the complete visual and interactive version, visit:
https://readme-team1-d4u5.vercel.app/


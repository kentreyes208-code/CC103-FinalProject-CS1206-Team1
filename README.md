# [Documentation Website of Hospital Triage and Patient Management (Read Here)](https://readme-team1-d4u5.vercel.app/)

▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃

## ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ 「 MARKDOWN VERSION 」
# ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎  Hospital Triage & Patient Management System


## ◢ Table of Contents

* [╰► Project Title](#-project-title)
* [╰► Problem Description](#-problem-description)
* [╰► Data Structures Used](#-data-structures-used)
* [╰► Algorithm Explanation](#-algorithm-explanation)
* [╰► Iterative vs Recursive Comparison](#-iterative-vs-recursive-comparison)
* [╰► Design Decisions](#-design-decisions)
* [╰► Team Members](#-team-members)
* [╰► Acknowledgement](#-acknowledgement)
* [╰► Full Interactive Version](#-full-interactive-version)

══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Project Title

**Hospital Triage & Patient Management System**

### ╰► Overview

The Hospital Triage and Patient Management System is a console-based application designed to streamline patient registration and queue management in hospital settings. It organizes patients based on arrival time and medical urgency, ensuring both efficiency and fairness in patient handling using core data structures.

══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Problem Description

Many hospital patient registration systems lack efficient tracking of recently registered patients while simultaneously managing both standard and emergency queues. This often leads to:

* **Disorganized patient workflows** — without proper queuing, the order and prioritization of patients become unclear
* **Delays in critical patient care** — non-emergency patients may inadvertently be served before critical cases
* **Lack of accountability in registration logs** — there is no reliable record of who was admitted and when

### ╰► Proposed Solution

This project implements a **multi-level queuing system** that:

* **Prioritizes emergency cases** using a **Priority Queue (Linked List-Based)** for severity levels 1–2
* **Maintains fairness for regular patients** using a **FIFO Queue (Deque)** for severity levels 3–5
* **Tracks all recent activities** using a **Stack (Vector)** to maintain a complete registration history
* **Uses Recursion** for structured and elegant data traversal of the priority queue

The system addresses these issues by implementing a structured, multi-level queuing mechanism with triage-based categorization, ensuring critical patients are never delayed and staff can audit recent registrations instantly.

══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Data Structures Used

### ╰► 1. Priority Queue (Linked List-Based)

**File:** `PriorityQueue.h` / `PriorityQueue.cpp`

**What it is:**
A Priority Queue is a special queue where elements are not served in simple arrival order — instead, each element has a priority level, and the highest-priority element is always served first. In this system, it is built using a **singly linked list** of Node objects, where each node holds a Patient and a pointer to the next node.

**Why it was used:**
Emergency patients (severity 1–2) cannot wait in line like regular patients. A Critical patient must always be treated before a Serious one, regardless of who arrived first. The linked list allows efficient sorted insertion — every new emergency patient is placed exactly where they belong based on severity, so the front always holds the most urgent case.

**Key Features:**
- **Sorted Insertion:** Maintains sorted order automatically during insertion
- **O(n) insertion time:** Must traverse to find correct position, but no element shifting needed
- **O(1) deletion time:** Removing the front (highest priority) patient is constant time
- **Dynamic memory:** Grows and shrinks as patients are admitted and treated

**Recursion in this structure:**
The `display()` function uses a recursive helper called `displayRecursive()` to traverse the linked list. Instead of a while loop, it calls itself on each successive node until it reaches `nullptr` (the base case). This replaces the original iterative traversal with an elegant recursive approach.

····························································································································································································································································································································································

### ╰► 2. Deque (FIFO Standard Queue)

**File:** `TriageSystem.h` / `TriageSystem.cpp`

**Variable:** `std::deque<Patient> standardQueue_;`

**What it is:**
A deque (double-ended queue) from the C++ Standard Library. In this system it is used strictly as a FIFO (First-In, First-Out) queue — patients are added at the back (`push_back`) and removed from the front (`pop_front`).

**Why it was used:**
Standard patients (severity 3–5) have no urgency difference that requires reordering — whoever arrived first gets seen first. A deque efficiently supports both front removal and back insertion in O(1) time, making it a natural fit for a simple waiting line.

**Performance Characteristics:**
- **Time Complexity:** O(1) for both `push_back()` and `pop_front()` operations
- **Space Complexity:** O(n) where n is the number of patients in the queue
- **Memory Structure:** Contiguous blocks of memory with pointers to front and back, allowing efficient two-ended access

**Advantages:**
- Fair treatment of non-urgent patients
- Simple and straightforward FIFO logic
- Efficient for both insertion and removal operations

····························································································································································································································································································································································

### ╰► 3. Vector (LIFO Activity Stack)

**File:** `TriageSystem.h` / `TriageSystem.cpp`

**Variable:** `std::vector<Patient> stack_;`

**What it is:**
A vector from the C++ Standard Library, used here to simulate a stack (Last-In, First-Out). New registrations are added to the back (`push_back`) and the log is read in reverse order, so the most recent registration always appears on top.

**Why it was used:**
The stack serves as a **registration activity log** — it records every patient admitted regardless of which queue they went to. Since staff typically want to review the most recent registrations first (e.g., "who just came in?"), the LIFO behavior of a stack is the natural fit. It is never dequeued from, so it grows as a permanent log throughout the session.

**Why vector instead of std::stack:**
The vector is used instead of `std::stack` because it allows full iteration and display of all entries. The `std::stack` adapter only exposes the top element, making it impossible to display the full history. Since the goal is a viewable registration history, a vector reversed during display gives the same LIFO behavior while remaining fully traversable.

**Characteristics:**
- Grows continuously as new patients are registered
- Provides complete audit trail of all admissions
- Staff can review registration history in reverse chronological order
- Never removes entries (serves as permanent log)

════════════════════════════════════════════════════════════════════════════════════════════

### ◢ Severity Classification

| Severity | Description | Queue          | Explanation                      |
| -------- | ----------- | -------------- | -------------------------------- |
| 1        | Critical    | Priority Queue | Life-threatening conditions      |
| 2        | Serious     | Priority Queue | Urgent medical issues            |
| 3        | Moderate    | FIFO Queue     | Standard medical conditions      |
| 4        | Minor       | FIFO Queue     | Minor injuries or complaints     |
| 5        | Routine     | FIFO Queue     | Check-ups and routine visits     |

**Severity Scale Design:**
Lower numbers indicate higher urgency. This intuitive scale ensures medical staff naturally understand that "Level 1" is the most severe and critical priority.

══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Algorithm Explanation

### ╰► admitPatient() — Patient Registration Process

**Step-by-Step Logic:**

1. **Input Collection**
   - Prompt user for patient name
   - Prompt user for medical ailment/complaint
   - Prompt user for severity level (1–5)

2. **Unique ID Assignment**
   - Assign a unique auto-incremented ID (starts at 1001)
   - Each patient receives a distinct identifier for tracking

3. **Patient Object Creation**
   - Create a Patient object with collected data (name, ailment, severity, ID)

4. **Always Log to Stack**
   - Push the patient onto `stack_` (registration log)
   - This ensures complete audit trail regardless of routing

5. **Severity-Based Routing**
   - **If severity ≤ 2:** Call `emergencyPQ_.enqueue(patient)` — send to priority queue
   - **If severity ≥ 3:** Call `standardQueue_.push_back(patient)` — send to FIFO queue

6. **Confirmation Display**
   - Display confirmation message with patient details
   - Show routing destination (Emergency Queue or Standard Queue)

**Pseudocode:**
```
function admitPatient():
    name ← getUserInput("Enter patient name")
    ailment ← getUserInput("Enter ailment")
    severity ← getUserInput("Enter severity (1-5)")
    
    id ← generateUniqueID()  // Auto-incremented from 1001
    patient ← createPatient(id, name, ailment, severity)
    
    stack_.push_back(patient)  // Always log
    
    if (severity <= 2):
        emergencyPQ_.enqueue(patient)
    else:
        standardQueue_.push_back(patient)
    
    displayConfirmation(patient)
```

····························································································································································································································································································································································

### ╰► enqueue() — Priority Queue Insertion

**Detailed Logic:**

1. **Create New Node**
   - Wrap the incoming patient in a new Node object
   - Initialize next pointer to nullptr

2. **Handle Empty List or Front Insertion**
   - **Case 1:** Check if the list is empty OR if the new patient is more urgent (lower severity number) than the head
   - **If true:** Insert at the front
   - New node becomes the new head
   - Update head pointer

3. **Find Correct Position**
   - **Case 2:** Walk the list forward using a while loop
   - Continue while: `current->next != nullptr AND current->next->severity ≤ new_patient->severity`
   - This preserves **arrival order on severity ties** — patients with the same severity are treated in FIFO order
   - Stop when finding the correct insertion point

4. **Splice the New Node**
   - Once the correct position is found: `newNode->next = current->next`
   - Then: `current->next = newNode`
   - This re-links pointers without moving any data

5. **Update Count**
   - Increment the patient count for the priority queue

**Pseudocode:**
```
function enqueue(patient):
    newNode ← createNode(patient)
    
    // Case 1: Empty or most urgent
    if (head == nullptr OR patient.severity < head.severity):
        newNode.next ← head
        head ← newNode
    else:
        // Case 2: Find correct position
        current ← head
        while (current.next != nullptr AND 
               current.next.severity ≤ patient.severity):
            current ← current.next
        
        // Splice in
        newNode.next ← current.next
        current.next ← newNode
    
    count++
```

**Example Walk-Through:**
- Queue: [Severity 1] → [Severity 3] → [Severity 4] → nullptr
- Inserting: Severity 2 patient
- Result: [Severity 1] → [Severity 2] → [Severity 3] → [Severity 4] → nullptr

····························································································································································································································································································································································

### ╰► displayRecursive() — Recursive Linked List Traversal

**Function Signature:**
```cpp
static void displayRecursive(Node* current, int pos)
```

**Base Case:**
```cpp
if (current == nullptr) return;
```
When the pointer reaches nullptr, it means the entire list has been traversed — the function stops here. Without this base case, the recursion would run forever and crash the program.

**Recursive Case:**
```cpp
displayRecursive(current->next, pos + 1);
```
After printing the current patient's row, the function calls itself with the next node and an incremented position number. Each call handles exactly one node, then delegates the rest to the next call.

**How It Works:**
1. Print the current patient's information as a table row
2. Increment the position counter
3. Call `displayRecursive()` with the next node
4. When reaching nullptr, all nodes have been printed

**Example Execution:**
```
displayRecursive(Node_A, 1)
  ├─ Print Node_A data at position 1
  └─ Call displayRecursive(Node_B, 2)
      ├─ Print Node_B data at position 2
      └─ Call displayRecursive(Node_C, 3)
          ├─ Print Node_C data at position 3
          └─ Call displayRecursive(nullptr, 4)
              └─ Base case: return
```

····························································································································································································································································································································································

### ╰► display() — Public Display Wrapper

**Step-by-Step Logic:**

1. **Check if Empty**
   - Check if queue is empty → print empty message and return

2. **Print Table Header**
   - Print column labels (Position, Patient ID, Name, Ailment, Severity)
   - Print separator lines for formatting

3. **Delegate to Recursive Helper**
   - Call `displayRecursive(head, 1)` 
   - This triggers the recursive traversal starting from position 1

4. **Print Table Footer**
   - Print closing separator lines

**Note:** The `display()` function itself is **not recursive**. It simply sets up the table and delegates the row-printing work to `displayRecursive()`. This is a common design pattern called the **recursive helper pattern**.

····························································································································································································································································································································································

### ╰► callNextPatient() — Service Priority Logic

**Step-by-Step Logic:**

1. **Check Both Queues**
   - Check if both `emergencyPQ_` and `standardQueue_` are empty
   - If both empty → show error message and return
   - No patients available to serve

2. **Emergency Queue Priority**
   - **If emergencyPQ_ is NOT empty:** Call `dequeue()` from it
   - Emergency patients take **absolute precedence** — served before all standard patients
   - Highest priority patient in emergency queue is always served first

3. **Standard Queue Fallback**
   - **If emergencyPQ_ is empty:** Pull from the front of `standardQueue_` using `pop_front()`
   - FIFO order ensures fairness — first patient to arrive is served first

4. **Display Called Patient**
   - Display the called patient's complete details
   - Show remaining count in their respective queue
   - Indicate which queue they came from

**Pseudocode:**
```
function callNextPatient():
    if (emergencyPQ_.isEmpty() AND standardQueue_.isEmpty()):
        print("No patients available")
        return
    
    if (emergencyPQ_.isNotEmpty()):
        patient ← emergencyPQ_.dequeue()
    else:
        patient ← standardQueue_.pop_front()
    
    displayPatientDetails(patient)
    displayRemainingCounts()
```

····························································································································································································································································································································································

### ╰► dequeue() — Priority Queue Removal

**Step-by-Step Logic:**

1. **Check for Underflow**
   - Check if queue is empty
   - If empty → throw `underflow_error` exception
   - Prevent operation on empty queue

2. **Save Head Data**
   - Save the head node and its patient data in a temporary variable
   - This preserves the data before the node is deleted

3. **Move Head Pointer**
   - Move the head pointer to `head->next`
   - The next node becomes the new head

4. **Free Memory**
   - Delete the old front node using `delete`
   - Free the memory allocated for the node (memory management)

5. **Update Count**
   - Decrement the patient count
   - Maintain accurate count of patients in queue

6. **Return Patient Data**
   - Return the saved patient data to the caller

**Pseudocode:**
```
function dequeue() → Patient:
    if (head == nullptr):
        throw underflow_error("Queue is empty")
    
    savedPatient ← head.data
    temp ← head
    head ← head.next
    
    delete temp  // Free memory
    count--
    
    return savedPatient
```

····················································································································································································································································································································································

### ╰► peekNextPatient() — View Without Removing

**Step-by-Step Logic:**

1. **Check Both Queues**
   - Check if both `emergencyPQ_` and `standardQueue_` are empty
   - If both empty → show error message and return
   - No patients available to peek

2. **Emergency Queue Priority**
   - **If emergencyPQ_ is NOT empty:** Return `emergencyPQ_.peek()`
   - Read head patient without removing them
   - Shows who will be served next

3. **Standard Queue Fallback**
   - **If emergencyPQ_ is empty:** Return `standardQueue_.front()`
   - Read front patient without removing them

4. **Display Patient Info**
   - Display patient information on screen
   - **No data is modified** — pure read operation

**Key Difference from callNextPatient():**
- `peekNextPatient()` shows who's next WITHOUT removing them
- `callNextPatient()` actually removes them from the queue
- Useful for staff to plan ahead without officially calling the patient

══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Iterative vs Recursive Comparison

### ╰► Overview

This system uses **BOTH approaches** — each in the context where it fits best:

- **Iterative:** `enqueue()` uses a while loop to find the correct insertion position in the linked list
- **Recursive:** `displayRecursive()` uses recursion to traverse and print the entire linked list

### ╰► Detailed Comparison Table

| Factor           | Iterative (enqueue)                | Recursive (displayRecursive)        |
| ---------------- | ---------------------------------- | ----------------------------------- |
| **Speed**        | Faster — no function call overhead | Slower — each call adds a stack frame |
| **Memory Usage** | Constant extra memory (O(1))       | Uses O(n) call stack memory         |
| **Risk**         | No stack overflow risk             | Can crash on very long lists        |
| **Readability**  | Slightly more verbose but predictable | Elegant and concise for traversal |
| **Debugging**    | Easier to trace with print statements | Harder to follow call chains |
| **Best for**     | Linear structures; list modification | Linear traversal without modification |

### ╰► Why Iterative for enqueue()?

In `enqueue()`, the goal is to **find and insert at a specific position**. A while loop is straightforward:
- Move a pointer forward
- Check the condition at each step
- Splice in the new node once the correct position is found
- No recursion is needed because we are not just visiting every node; we are also **modifying the list structure**

**Iterative is safer and more efficient here** because:
- ✔ No function call overhead
- ✔ O(1) extra memory
- ✔ Efficient modification of list structure
- ✔ No risk of stack overflow

### ╰► Why Recursive for displayRecursive()?

In `displayRecursive()`, the goal is to **visit every node in order and print its data** — a pure traversal with **no structural modification**. This is the ideal scenario for recursion because:

- ✔ Each call handles exactly one node — clean and self-contained
- ✔ The base case (`nullptr`) naturally marks the end of the list
- ✔ The recursive call (`current->next`) elegantly moves forward
- ✔ No index or extra variable is needed to track position — `pos` is passed as a parameter
- ✔ Code reads naturally and closely mirrors the linked list structure

**Recursion is more elegant here** because:
- ✔ Mirrors the recursive structure of a linked list
- ✔ Self-documenting code that clearly shows traversal
- ✔ Clean base case handling

### ╰► Output Comparison

Both approaches produce **identical output** when displaying the priority queue. The difference is stylistic:
- **Recursion** reads more naturally for traversal problems
- **Iteration** is preferred for modification tasks

### ╰► Conclusion

The choice between iterative and recursive approaches should depend on the **task nature**:
- **Use Iterative for:** Finding positions, inserting, modifying, any structural change
- **Use Recursive for:** Traversing, displaying, searching without modification
- **Trade-off:** Speed and memory vs readability and elegance

In this system, combining both approaches provides **optimal efficiency and clean, maintainable code**.

══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Design Decisions

### ╰► Decision 1: Linked List for the Priority Queue (not an array)

**Comparison:**

| Aspect | Linked List | Array / Vector |
| ------ | ----------- | -------------- |
| **Insertion in middle** | O(n) — just re-link pointers | O(n) — must shift elements |
| **Memory Usage** | Dynamic — grows as needed | May need resizing/copying |
| **Access by index** | Not supported | O(1) random access |
| **Best for** | Frequent insertions at arbitrary positions | Frequent reads by index |

**Why Chosen: Linked List**

The priority queue needs to insert patients at specific sorted positions **frequently**. With a linked list:
- ✔ Inserting between two nodes only requires re-pointing two pointers
- ✔ No elements need to be physically moved in memory
- ✔ Dynamic memory allocation — no resizing needed
- ✔ Natural fit for maintaining sorted order

With an array:
- ❌ Would require shifting all lower-priority patients one slot to make room
- ❌ May trigger expensive resize operations when capacity exceeded
- ❌ Memory allocation overhead for moving all elements

**Trade-offs:**
- ✔ Better insertion performance for sorted data
- ❌ Cannot access arbitrary positions by index
- ❌ Slightly more memory overhead per node (for pointers)

····························································································································································································································································································································································

### ╰► Decision 2: Recursive displayRecursive() instead of a while loop

**Alternative Approaches:**

| Approach | Code Style | Memory | Speed |
| -------- | ---------- | ------ | ----- |
| **Recursive** | Elegant, concise | O(n) call stack | Slower |
| **Iterative** | Verbose, predictable | O(1) extra space | Faster |

**Why Chosen: Recursive**

- ✔ Recursion naturally models the traversal of a linked list — each node delegates to the next
- ✔ The base case (`nullptr`) clearly marks termination — equivalent to the while condition
- ✔ Passing `pos` as a parameter avoids a separate counter variable
- ✔ Code is more elegant and easier to understand

**Trade-off:**
- ⚠️ O(n) call stack memory vs O(1) for iterative
- ✔ Acceptable given typical patient list sizes (hospital queues rarely exceed thousands)

**Why Not Iterative:**
- Less elegant for pure traversal
- Requires explicit loop condition management
- Doesn't mirror the recursive structure of a linked list

····························································································································································································································································································································································

### ╰► Decision 3: Two Separate Queues instead of One

**Alternative: Single Priority Queue with all 5 severity levels**

The system uses `emergencyPQ_` and `standardQueue_` separately rather than putting all patients into one priority queue.

**Comparison:**

| Aspect | Separate Queues | Single Priority Queue |
| ------ | --------------- | --------------------- |
| **Code Clarity** | Clear separation of concerns | Everything in one structure |
| **FIFO Fairness** | Ensured for standard patients | Must be enforced in code |
| **Processing Logic** | Simple emergency-first check | Complex mixed-priority logic |
| **Display** | Separate reports per queue | Requires filtering |
| **Performance** | Check two structures | Check only one structure |

**Why Chosen: Separate Queues**

- ✔ **Cleaner separation of concerns** — emergency logic stays isolated
- ✔ **Standard patients can be managed simply with FIFO** — no sorting needed
- ✔ **Easier to display and report each group separately**
- ✔ **Reflects real hospital workflow** — emergency rooms and waiting rooms are physically separate
- ✔ **Psychological clarity** — staff understand the dual-queue system intuitively

**Trade-off:**
- ⚠️ **Requires checking two structures** every time a patient is called
- ✔ Negligible performance impact given typical queue sizes

**Why Not Single Priority Queue:**
- ❌ Mixing all 5 severity levels into one priority queue would work, but unnecessarily
- ❌ Would require sorting mild patients who just need simple FIFO ordering
- ❌ Staff must mentally track multiple severity levels
- ❌ Less intuitive from hospital workflow perspective

····························································································································································································································································································································································

### ╰► Decision 4: Vector as a Stack (not std::stack)

The registration log uses `std::vector` iterated in reverse instead of `std::stack`.

**Comparison:**

| Feature | Vector-as-Stack | std::stack |
| ------- | --------------- | ---------- |
| **Full Iteration** | ✔ Supported | ❌ Not supported |
| **Random Access** | ✔ Supported | ❌ Not supported |
| **Display History** | ✔ Can display entire log | ❌ Can only access top |
| **Semantic Purity** | ⚠️ Not a true stack | ✔ Pure stack semantics |
| **Enforce Discipline** | ⚠️ Allows any operation | ✔ Enforces push/pop only |

**Why Chosen: Vector**

- ✔ **Allows iteration and display of all entries** — `std::stack` does not
- ✔ **Can check size, loop through history, display most-recent-first**
- ✔ **Provides full audit trail** without modification
- ✔ **More useful for hospital staff** — can review who was admitted during the session

**Trade-off:**
- ⚠️ **Slightly less semantically pure** than a true stack
- ⚠️ **Doesn't enforce strict push/pop discipline** — other operations are possible
- ✔ Acceptable because stack is only internal data structure, not public API

**Why Not std::stack:**
- ❌ `std::stack` only exposes the top element
- ❌ Cannot loop through to display the full log
- ❌ Cannot implement reverse iteration for LIFO display
- ❌ No way to audit complete registration history

····················································································································································································································································································································································

### ╰► Decision 5: Severity 1 = Highest Priority (Lower = More Urgent)

The scale runs 1 (Critical) to 5 (Routine) — a **lower number means higher urgency**.

**Alternative Scales:**

| Scale | Pros | Cons |
| ----- | ---- | ---- |
| **1 = Critical, 5 = Routine (CHOSEN)** | Intuitive for medical staff | Counterintuitive for programmers |
| **5 = Critical, 1 = Routine** | Natural for programmers | Confusing for medical staff |
| **10 = Critical, 1 = Routine** | More granular | More complex |

**Why Chosen: 1 = Highest Priority**

- ✔ **Intuitive for medical staff** — "Level 1" naturally sounds most severe
- ✔ **Aligns with medical terminology** — Common in hospitals and emergency departments
- ✔ **Sorting is straightforward** — Always move lower numbers to the front
- ✔ **Visual clarity** — Staff immediately understand severity hierarchy
- ✔ **Industry standard** — Most hospitals use similar scales

**Trade-off:**
- ⚠️ **Slightly counterintuitive for programmers** used to "higher number = higher priority"
- ✔ Easily overcome with clear documentation and code comments

**Sorting Logic:**
```cpp
// With 1 = Highest Priority
if (patient.severity < existing.severity) {
    // New patient is more urgent → goes first
}
// Intuitive: lower numbers are checked for being "less than"
```

════════════════════════════════════════════════════════════════════════════════════════════

## ◢ Team Members

| Name                 | Role                                               |
| -------------------- | -------------------------------------------------- |
| Lianne Jade Magtaas  | Documenter · Test Programmer · Analyst · Presenter |
| Kent Rowen L. Reyes  | Data Structures & Algorithm Specialist             |
| Trixie Feigh Sanchez | Main Programmer · System Architect                 |
| Andrea L. Valenzuela | Designer · Research Coordinator                    |

══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Acknowledgement

╰► **Ms. Fatima Marie Agdon**
Professor, CC 103 — Data Structures and Algorithms
> **We sincerely thank our professor for her guidance, support, and encouragement throughout the development of this project.**

╰► **College of Informatics and Computing Sciences (CICS)**
**Batangas State University — Alangilan Campus**
*"The National Engineering University"*
> **For providing the academic environment and resources necessary for this project.**

══════════════════════════════════════════════════════════════════════════════════════════

## ◢ Full Interactive Version

For the complete visual and interactive version, visit:
https://readme-team1-d4u5.vercel.app/

▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃
▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃


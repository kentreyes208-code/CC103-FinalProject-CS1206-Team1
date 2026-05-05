# 🏥 Hospital Triage and Patient Management System

> **CC 103 – Data Structures and Algorithms**
> Batangas State University · College of Informatics and Computing Sciences
> 2nd Semester, AY 2025–2026

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Problem Statement](#-problem-statement)
- [Features](#-features)
- [Data Structures Used](#-data-structures-used)
- [System Architecture](#-system-architecture)
- [Process Flow](#-process-flow)
- [Team](#-team)
- [References](#-references)

---

## 🔍 Overview

The **Hospital Triage and Patient Management System** is a console-based application designed to streamline patient registration and queue management in hospital settings. It organizes patients based on **arrival time** and **medical urgency**, ensuring both efficiency and fairness in patient handling through the use of core data structures.

---

## ⚠️ Problem Statement

Many hospital patient registration systems lack efficient tracking of recently registered patients while simultaneously managing both standard and emergency queues. This often leads to:

- 🔴 Disorganized patient workflows
- 🔴 Delays in critical patient care
- 🔴 Lack of accountability in registration logs

This system addresses these issues by implementing a structured, multi-level queuing mechanism with triage-based categorization.

---

## ✨ Features

| Feature | Description |
|---|---|
| 📝 **Recent Activity Log** | Stack-based log with timestamps and notes for accountability |
| 🚨 **Triage-Based Categorization** | Severity levels (1–5) assigned to each incoming patient |
| 🔄 **Real-Time Queue Processing** | Iterative loops keep the interface responsive at all times |

---

## 🗃️ Data Structures Used

| Data Structure | Purpose | Behavior |
|---|---|---|
| 🧱 **Stack** | Recent Registration Log | LIFO — quick review/correction of latest patient entries |
| 📋 **Queue** | Standard Waiting List | FIFO — fair processing for non-emergency cases by arrival time |
| ⚡ **Priority Queue** | Emergency Triage | Severity-based — critical cases (Level 1) handled first regardless of arrival |

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────┐
│         PATIENT REGISTRATION            │
└────────────────┬────────────────────────┘
                 │
        ┌────────▼────────┐
        │  Centralized    │
        │ Patient Record  │
        └────────┬────────┘
                 │
        ┌────────▼────────┐
        │  Stack Logging  │  ◄── Recent Activity History
        └────────┬────────┘
                 │
         ┌───────▼────────┐
         │ Severity Check │
         └────────────────┘
            
   ┌────────▼──────┐    ┌────────▼─────────┐
   │ Standard Queue│    │  Priority Queue  │
   │  (Low Severity│    │ (High Severity,  │
   │   FIFO order) │    │  Level 1–5)      │
   └───────────────┘    └──────────────────┘
```

---

## 🔄 Process Flow

1. **📥 Patient Registration** — Patient details are entered via the console interface.
2. **💾 Data Storage** — Information is saved to the centralized patient record.
3. **📚 Stack Logging** — Patient is pushed onto the stack for activity history and monitoring.
4. **🔀 Queue Assignment** — Based on severity level, patient is routed to the appropriate queue:
   - `Severity 3–5` → **Standard Queue** (low urgency)
   - `Severity 1–2` → **Priority Queue** (high urgency)
5. **⚙️ Continuous Processing** — The system runs iterative loops to keep all records and queues updated in real-time.


---

## 👨‍💻 Team

**Team 1 — Queue the Healing**
Batangas State University, Computer Science Department

| SR-Code | Name | Role |
|---|---|---|
| 25-07829 | Magtaas, Lianne Jade | Documenter · Test Programmer · Requirements Analyst · Presentation Lead |
| 25-01395 | Reyes, Kent Rowen L. | Documenter · Data Structure & Algorithm Specialist · Assistant Developer |
| 25-06254 | Sanchez, Trixie Feigh | Documenter · Main Programmer · System Architect |
| 25-09041 | Valenzuela, Andrea L. | Documenter · Console Designer · Research & References Coordinator |

---

## 📚 References

- Abarnakumar28. (2025). *Clinical Management System using Priority Queue – C*. GitHub. https://github.com/Abarnakumar28/clinical-Management-system

- Alipour-Vaezi, M., Aghsami, A., & Jolai, F. (2022). Prioritizing and queueing emergency department patients using a novel data-driven decision-making methodology. *Expert Systems with Applications, 195*, 116568. https://doi.org/10.1016/j.eswa.2022.116568

- Sai, T., Singh, T., & Malik, V. M. (2025). *Hospital Management System Using Priority Queue for Emergency and Appointment Scheduling*. ResearchGate. https://www.researchgate.net/publication/398142858

- srushti1006. (2025). *Hospital Management Priority Queue*. GitHub. https://github.com/srushti1006/Hospital_Management_Priority_Queue

- World Health Organization. (2012). *Triage and emergency assessment*. NIH.gov. https://www.ncbi.nlm.nih.gov/books/NBK143755/

---

<div align="center">

**Batangas State University — The National Engineering University**
*Leading Innovations, Transforming Lives, Building the Nation*

</div>

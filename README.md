# 🅿️ Digital Parking Management System (DPMS)

This repository contains the source code for a command-line application developed in **C** to simulate and manage the operations of a digital parking lot. It provides a robust, menu-driven interface with persistent data storage.

---

## 🚀 Project Context

This system was completed as a part of **Emertxe Embedded System Course**. The goal was to demonstrate proficiency in:

* **Core C Programming:** Mastery of functions, loops, and control structures.
* **Data Structures:** Effective use of the `struct` keyword for organizing complex data (slot and vehicle details).
* **File I/O:** Implementing persistent data storage using text files (`parking_db.txt`), ensuring the parking state survives program execution.
* **Time Management:** Utilizing the `<time.h>` library for precise recording of entry times and calculating fees based on duration.
* **Input Handling:** Implementing robust input techniques to prevent common C I/O issues (like skipped prompts).

---

## ✨ Features and Menu Options

The application presents a main menu loop with the following functionalities:

| Option | Function | Description |
| :---: | :--- | :--- |
| **1** | **Display Status** | Shows the occupancy status, plate number, and entry time for all configured slots. |
| **2** | **Park Vehicle** | Records the vehicle's details and registers the current time stamp (`time_t`). |
| **3** | **Remove Vehicle** | Calculates the total parking time, computes the fee (`RATE_PER_HOUR = 10`), and clears the slot. |
| **4** | **Search Vehicle** | Locates a vehicle by its license plate and displays its slot and details. |
| **5** | **Change Total Slots**| Dynamically adjusts the lot size (up to `MAX_SLOTS = 50`), ensuring existing data is preserved on expansion and checking for occupied slots on reduction. |
| **6** | **Exit** | Saves the current state to the database file and safely terminates the program. |

---

## 🛠️ Build and Execution

### Prerequisites

* A C compiler (GCC recommended).

### Compilation

Navigate to the directory containing `main.c`, `utility.c`, and `utility.h`, and compile all source files together:

```bash
gcc main.c utility.c -o parking_manager
```
### Execution
```bash
./parking_manager
```

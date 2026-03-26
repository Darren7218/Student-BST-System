# 🌳 Student-BST-System

![C++](https://img.shields.io/badge/Language-C++-00599C?style=flat-square&logo=c%2B%2B)
![Status](https://img.shields.io/badge/Status-Completed-success?style=flat-square)
![Course](https://img.shields.io/badge/Course-Data_Structures-blue?style=flat-square)

**Year 1 Semester 3 Data Structure Assignment 2** A C++ application designed to manage student records efficiently using a **Binary Search Tree (BST)**. This system allows users to load student data, execute various complex tree traversals, clone specific subtrees, and export organized data.

---

## ✨ Features

* **📥 Read Data:** Automatically loads and parses multi-line student records from `student.txt`. Prevents the insertion of duplicate Student IDs.
* **🎯 Deepest Nodes:** Identifies and outputs the Student IDs of the nodes located at the absolute deepest level of the BST.
* **🗂️ Display / Export Data:**
  * Sorts records in **Ascending** (In-order traversal) and **Descending** (Reverse In-order traversal) order based on Student ID.
  * Outputs data directly to the console or saves it externally to `student-info.txt`.
* **🧬 Clone Subtree:** Generates a complete deep copy of a subtree starting from any user-specified Student ID.
* **📶 Print Level Nodes:** Utilizes a Breadth-First Search (BFS) algorithm to print Student IDs level by level.
* **🛤️ Print Paths:** Displays all external pathways from the root node down to every individual leaf node.

---

## 📂 Project Structure

The repository is modularized into application logic, data structures, and data files.

### ⚙️ Application Logic
* `app.cpp`: The main entry point. Handles the interactive menu loop, file reading logic (`readFile`), and user input processing.

### 🏗️ Data Structures
* `BST.cpp` / `BST.h`: The core Binary Search Tree implementation. Contains methods for insertion, deletion, and specialized assignment features (deepest nodes, cloning, path printing).
* `Student.cpp` / `Student.h`: Defines the `Student` structure (ID, Name, Address, DOB, etc.) and handles object comparison logic.
* `BTNode.cpp` / `BTNode.h`: Represents a single node within the Binary Search Tree.
* `Queue.cpp` / `Queue.h`: A custom Linked-List based Queue implementation used strictly for level-order traversals (BFS).
* `Node.cpp` / `Node.h`: Represents a node specifically within the Queue structure.

### 📄 Data Files
* `student.txt`: The raw input file containing the initial student records.
* `student-info.txt`: The formatted output file generated upon selecting the "Write into file" export option.

---

## 🚀 Getting Started

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/Darren7218/Student-BST-System.git](https://github.com/Darren7218/Student-BST-System.git)

2. **Compile the program:**
   ```bash
   g++ *.cpp -o bst_system

3. **Run the executable:**
   ```bash
   ./bst_system

## Group Members
Universiti Tunku Abdul Rahman (UTAR) - Computer Science

* Heled Kong Sheng En

* Ooh Rui Hang

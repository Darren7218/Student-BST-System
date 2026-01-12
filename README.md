# Student-BST-System
**Y1S3 Data Structure Assignment 2**

A C++ program that manages student records using a Binary Search Tree (BST). This application allows users to read student data from a file, perform various tree traversals, clone subtrees, and export data in specific orders.


📋 **Features**
Read Data: Loads student records from student.txt. It automatically handles parsing of multi-line records and prevents inserting duplicate Student IDs.

Deepest Nodes: Identifies and prints the Student IDs of nodes located at the deepest level of the BST.

Display / Export:

Supports Ascending (In-order) and Descending (Reverse In-order) sorting based on Student ID.

Output can be directed to the Console or saved to a file named student-info.txt.

Clone Subtree: Creates a deep copy of a subtree starting from a specific Student ID provided by the user.

Print Level Nodes: Performs a Breadth-First Search (BFS) to print Student IDs level by level.

Print Paths: Displays all external paths from the root to every leaf node.


📂 **Project Structure**

This project consists of the following C++ source files and headers:

Application Logic

app.cpp: The main entry point. Handles the menu loop, file reading logic (readFile), and user input processing.

Data Structures

BST.cpp / BST.h: implementation of the Binary Search Tree. Includes methods for insertion, deletion, and the specific assignment features (deepest nodes, cloning, printing paths).

Student.cpp / Student.h: Defines the Student structure (ID, Name, Address, DOB, etc.) and comparison logic.

BTNode.cpp / BTNode.h: Represent a node within the Binary Search Tree.

Queue.cpp / Queue.h: A Linked-List based Queue implementation used for level-order traversals (BFS).

Node.cpp / Node.h: Represents a node within the Queue.

Data Files

student.txt: The input file containing raw student records.

student-info.txt: The output file generated when the user selects the "Write into file" option.


👥 Group Members

Heled Kong Sheng En 

Ooh Rui Hang 


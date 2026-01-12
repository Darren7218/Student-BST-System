#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
bool duplicate(BST* tree, Student& stu, BTNode* cur);
const char* STUDENTRECORD_FILE = "student.txt";
int menu(),success; //success counter
int main() {
	BST	t1,t2;
	int theMenu = 0;
   
    Student student;
	while (theMenu != 7) {
		theMenu = menu();
		switch (theMenu) {
		case 1:
			cout << "\nREAD FILE\n";
			if (readFile(STUDENTRECORD_FILE, &t1))
				cout << success << " records were read successfully." << endl;
			else
				cout << STUDENTRECORD_FILE << " not found." << endl;
			break;
		case 2:
			cout << "\nPrint deepest nodes\n";
			if (!t1.deepestNodes())
				cout << "\nEmpty Tree." << endl;
			break;
		case 3:
			cout << "\nDisplay student\n";
			int order, source;
			cout << "\nEnter order [1 (Ascending) OR 2 (Descending]:\n";
			cin >> order;
			cout << "\nEnter source [1 (Display to screen), 2 (Write into file]:";
			cin >> source;
			t1.display(order, source);
			break;
		case 4:
			cout << "\nClone Subtree\nEnter Student ID for cloned subtree root:";
            cin >> student.id;
            if (!t1.CloneSubtree(t1, student)) {
                cout << "\nError cloning subtree\n" << endl;
            }
			break;
		case 5:
            cout << "\nPrint Level Nodes\n";
            if (!t1.printLevelNodes()) {
                cout<<"\nCannot print\n" << endl;
            }
			break;
		case 6:
            cout << "\nPrint Path\n";
            if (!t1.printPath()) {
                cout << "\nFailed to print path\n";
            }
			break;
        case 7:
            cout << "\nExiting Program\n";

            break;
		}
	}
	system("pause");
	return 0;
}


int menu() {
	bool valid = 0;
	int option = 0;
	while (valid == 0) {//valid is used to check if the number entered is between 1-7
		valid = 1; //if input is valid it will stay 1
		cout << "\n\tMenu\n\n";
		cout << "(1) Read data to BST\n";
		cout << "(2) Print deepest nodes\n";
		cout << "(3) Display student\n";
		cout << "(4) Clone Subtree\n";
		cout << "(5) Print Level Nodes\n";
		cout << "(6) Print Path\n";
		cout << "(7) Exit.\n";
		cout << "Enter your choice: ";

		cin >> option;
		if (option > 7 || option < 1) {//turns valid to 0 to show it is invalid and loops
			cout << "\n\nThe number is out of range\nPick another valid number\n " << endl;
			valid = 0;
		}
	}
	return option;
}

bool readFile(const char* filename, BST* t1)
{
    success = 0;
    ifstream in(filename);
    char dump[256];  // Buffer for unwanted/unprocessed characters
    Student stu;
    int k, j;

    if (!in) {
        cout << "\n\nCannot open file " << filename << "\n\n";
        return false;
    }

    while (in) {  // Loop as long as the stream is valid

        j = 0;  // Reset `j` before processing each student

        // Skip first two unneeded values
        for (int i = 0; i < 3; i++) in >> dump;

        // Read student ID
        if (!(in >> stu.id)) {
            break;  // Exit if reading student ID fails
        }
        cout << "ID: " << stu.id << endl;

        in.ignore();  // Ignore the newline after ID

        // Read and process the name from `dump`
        in.getline(dump, 256);
        if (strlen(dump) >= 7) {  // Ensure dump has at least 7 characters
            k = 7;  // First character of the name is at index 7
            while (dump[k] != '\0') {
                stu.name[j++] = dump[k++];
            }
            stu.name[j] = '\0';  // Null-terminate the name
        }
        cout << "Name: " << stu.name << endl;

        j = 0;  // Reset `j` for the address

        // Read and process the address
        in.getline(dump, 256);
        if (strlen(dump) >= 10) {  // Ensure dump has at least 10 characters
            k = 10;  // First character of the address is at index 10
            while (dump[k] != '\0') {
                stu.address[j++] = dump[k++];
            }
            stu.address[j] = '\0';  // Null-terminate the address
        }
        cout << "Address: " << stu.address << endl;

        // Skip unneeded values and read DOB
        for (int i = 0; i < 2; i++) in >> dump;
        if (!(in >> stu.DOB)) break;
        cout << "DOB: " << stu.DOB << endl;
        in.ignore();

        // Skip unneeded values and read phone number
        for (int i = 0; i < 3; i++) in >> dump;
        if (!(in >> stu.phone_no)) break;
        cout << "Phone: " << stu.phone_no << endl;
        in.ignore();

        // Skip unneeded values and read course
        for (int i = 0; i < 2; i++) in >> dump;
        if (!(in >> stu.course)) break;
        cout << "Course: " << stu.course << endl;
        in.ignore();

        // Skip unneeded values and read CGPA
        for (int i = 0; i < 2; i++) in >> dump;
        if (!(in >> stu.cgpa)) break;
        cout << "CGPA: " << stu.cgpa << endl << endl;
        in.ignore();
        in.ignore();  // Skip any additional newlines

        //check for duplicate
        if (!duplicate(t1, stu, t1->root)) {
            t1->insert(stu);
            success++;
        }

    }

    in.close();
    return true;
}

bool duplicate(BST* tree, Student& stu, BTNode* cur)
{
    // Base case: if the current node is NULL, no duplicate is found.
    if (cur == NULL)
        return false;

    // If the current node has the same ID, it's a duplicate.
    if (cur->item.id == stu.id) {
        return true;
    }

    // Recursively search in the left or right subtree based on the ID comparison.
    if (stu.id < cur->item.id)
        return duplicate(tree, stu, cur->left);  // Search the left subtree
    else
        return duplicate(tree, stu, cur->right);  // Search the right subtree
}



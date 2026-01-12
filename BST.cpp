#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);
			
			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


//***************PART (B)****************************************************
bool BST::deepestNodes() {
	if (root == NULL) {
		cout << "The BST is empty." << endl;
		return false;
	}

	// Find the height of the tree
	int height = getHeight(root);

	// Print nodes that are at the deepest level
	cout << "Deepest nodes are: ";
	printDeepestNodes(root, height);
	cout << endl;

	return true;
}


void BST::printDeepestNodes(BTNode* cur, int level) {
	if (cur == NULL)
		return;

	// If we reach the required level, print the student ID
	if (level == 1) {
		cout << cur->item.id << " ";
	}
	else {
		// Recurse to the left and right children, decreasing the level
		printDeepestNodes(cur->left, level - 1);
		printDeepestNodes(cur->right, level - 1);
	}
}


int BST::getHeight(BTNode* cur) {  //find the max height of tree
	if (cur == NULL) return 0;

	//Recursively find height of the left and right subtrees
	int leftHeight = getHeight(cur->left);
	int rightHeight = getHeight(cur->right);

	// The height of the tree is the maximum of the two subtree heights + 1 (for the current node)
	return max(leftHeight, rightHeight) + 1;
}


//***************PART (C)****************************************************
bool BST::display(int order, int source) {
	if (root == NULL) {
		cout << "The BST is empty." << endl;
		return false;
	}

	// Validate input for `order`
	if (order != 1 && order != 2) {
		cout << "Invalid order option. Use 1 for ascending or 2 for descending." << endl;
		return false;
	}

	// Validate input for `source`
	if (source != 1 && source != 2) {
		cout << "Invalid source option. Use 1 to print to screen or 2 to print to file." << endl;
		return false;
	}

	ofstream out;
	if (source == 2) {
		out.open("student-info.txt");
		if (!out.is_open()) {
			cout << "Unable to open the output file." << endl;
			return false;
		}
	}
	// Use the ternary operator to determine the output stream
	ostream& output = (source == 1) ? cout : out;
	// if source = 1, output  = cout, else output = out

	// Traverse the tree according to the order
	if (order == 1) {
		displayAscending(root, output); // Ascending order
	}
	else {
		displayDescending(root, output); // Descending order
	}

	// If file output, inform user and close file
	if (source == 2) {
		cout << "BST printed to file." << endl;
		out.close();
	}

	return true; // If we reach here, everything succeeded
}


void BST::displayAscending(BTNode* cur, ostream& out) {
	if (cur != NULL) {
		displayAscending(cur->left, out);
		cur->item.print(out);
		displayAscending(cur->right, out);
	}
}

void BST::displayDescending(BTNode* cur, ostream& out) {
	if (cur != NULL) {
		displayDescending(cur->right, out);
		cur->item.print(out);
		displayDescending(cur->left, out);
	}
}

//d
bool BST::CloneSubtree(BST t1, type item) {
	BTNode* cur = t1.root; //one cursor for original and other for cloned
	BTNode* cur1 = NULL;
	BST t0;//cloned subtree
	t0.root = NULL;
	if (t1.root == NULL) {
		cout <<"t1 is empty tree\n";
		return false;
	}
	while (cur) { // search loop
		if (cur->item.id == item.id) {
			CloneSubtree2(t0, cur); //insert root
			break;
		}
		cur = (item.id < cur->item.id) ? cur->left : cur->right; //if item less than cursor then move left
		//if item more than cursor then move right
	}

	if (t0.root == NULL) {
		cout <<"\nCannot find student ID\n";
		return false;
	}
	cout <<"\nStudents in t1:\n";
	t1.preOrderPrint(); //preorder from q
	cout << "\nStudents in cloned t2 from " << item.id <<endl;
	t0.preOrderPrint();
	return true;
}

void BST::CloneSubtree2(BST& t0, BTNode* cur) {
	if (cur==NULL) {
		return;
	}
	BTNode* cur1 = new BTNode(cur->item); //initialize new btnode with cur->item value
	if (cur1) {
		t0.insert(cur1->item);
	}
	CloneSubtree2(t0, cur->left);//recursion to insert left and right
	CloneSubtree2(t0, cur->right);
}



//e
bool BST::printLevelNodes() {
	if (root == NULL) {
		cout<<"\nEmpty tree\n";
		return false;
	}
	BTNode* cur;
	Queue q;
	int nodesNextLevel = 0;
	int nodesCurrentLevel = 1;
	int level = 1;
	q.enqueue(root);
	while (!q.empty()) {
		cout << "Level " << level << ": ";

		for (int i = 0; i < nodesCurrentLevel; i++) {//loops to number of nodes

			q.dequeue(cur);// dequeue and give value to cur

			cout << cur->item.id << " ";//prints cur

			if (cur->left) {
				q.enqueue(cur->left);//queue left of cur
				nodesNextLevel++;
			}

			if (cur->right) {
				q.enqueue(cur->right);//queue right of cur
				nodesNextLevel++;
			}
		}

		cout << endl; //new line for new level
		level++;
		nodesCurrentLevel = nodesNextLevel; //assign counter for for loop
		nodesNextLevel = 0; //reset count for next level
	}
	return true;
}



//f
bool BST::printPath() {
	if (root == NULL) {
		cout << "Empty tree" << endl;
		return false;
	}
	cout << "External paths of tree:" << endl;
	printExternal(root, "");
	return true;
}
void BST::printExternal(BTNode* cur, string ids) {//ids accumulates the id of nodes in current path
	if (cur == NULL) {
		return;
	}

	// Add current node ID to ids
	ids += to_string(cur->item.id) + "   ";

	// Print path when reach leaf
	if (cur->right == NULL && cur->left == NULL) {
		cout << ids << endl;
		return;
	}
	//recursion
	printExternal(cur->left, ids);//go left
	printExternal(cur->right, ids);//go right
}



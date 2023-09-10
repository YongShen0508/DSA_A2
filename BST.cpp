#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"
#pragma warning(disable:4996)


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
		if (cur != NULL) {
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
// Task B
bool BST::deepestNodes()
{
	// Handle the case where the tree is empty
	if (empty()) {
		return false;
	}
	else
	{
		int treeHeight = calculateTreeHeight(root); // Calculate the height of the tree
		printDeepestNodes(root, treeHeight); // Print the nodes at the deepest level
		cout << "\n";
		return true;
	}
}

void BST::printDeepestNodes(BTNode* node, int height)
{
	if (!node) return;

	if (height == 1)
	{
		// Print the student ID
		cout << "||\t\t\t" << node->item.id << "\t\t\t||";
	}
	else if (height > 1)
	{
		// Recursively traverse to the deepest level
		printDeepestNodes(node->left, height - 1);
		printDeepestNodes(node->right, height - 1);
	}
}

int BST::calculateTreeHeight(BTNode* node)
{
	if (!node) return 0;
	else
	{
		int leftHeight = calculateTreeHeight(node->left);
		int rightHeight = calculateTreeHeight(node->right);
		// The height of the current node is the maximum height of its left and right subtrees, plus 1
		return max(leftHeight, rightHeight) + 1;
	}
}
// Task C
bool BST::display(int order, int source) {
	ofstream writeFile;

	if (root == NULL) return false;
	if (source == 1) {
		display2(order, cout);
	}
	else {
		writeFile.open("student-info.txt");
		if (!writeFile.is_open())
			return false;
		display2(order, writeFile);
		cout << "The nodes have been recorded into \"student-info.txt\"." << endl;
		writeFile.close();
	}
	return true;
}

// Helper function to handle the display logic based on order
void BST::display2(int order, ostream& out) {
	if (order == 1)
		ascPrint(root, out);
	else
		descPrint(root, out);
}

void BST::ascPrint(BTNode* cur, ostream& out) {   //left to right
	if (cur == NULL) return;      //Base Case
	ascPrint(cur->left, out);
	cur->item.print(out);
	ascPrint(cur->right, out);
}

void BST::descPrint(BTNode* cur, ostream& out) {   //right to left
	if (cur == NULL) return;      //Base Case
	descPrint(cur->right, out);
	cur->item.print(out);
	descPrint(cur->left, out);
}



bool BST::printLevelNodes() {
		if (root == NULL) return false; // Empty tree
		Queue q;
		BTNode* cur=NULL;
		q.enqueue(root);	//take out root
		int Level = 0;
		while (!q.empty()) {	//loop until queue is empty
			int Size = q.size();	//get size of queue
			cout << "\t\033[1;34m Level " << Level+1 << " nodes: ";
			for (int i = 0; i < Size; i++) {	//loop through queue
				q.dequeue(cur);	//take out out node fron queue
				cout << cur->item.id << " ";
				if (cur->left!=NULL)		//if left child exists, enqueue
					q.enqueue(cur->left);																								
				if (cur->right!=NULL)		//if right child exists, enqueue
					q.enqueue(cur->right);
			}
			cout <<"\033[0m"<< endl;
			Level ++;	
		}
		return true;
}

bool BST::CloneSubtree(BST t1, type item) {
	if(t1.empty()) return false;// special case 1: tree is empty

	BTNode *t1Ptr = t1.root;
	if (CloneSubTree2(t1Ptr, item)) {
		cout <<"\n\n"<< string(66, '=') << endl;
		cout << "\t\t\033[1;32m ALL STUDENT INFORMATION LIST(S) \033[0m" << endl;
		cout << string(66, '=') << endl;
		t1.preOrderPrint();   //all student info
		return true;
	}

	return false;
}

bool BST::CloneSubTree2(BTNode* cur, type item) {
	if (cur->item.compare3(item.id)) {
		CloneSubTree3(cur);
		return true;
	}//manage to find the item

	else if (item.id < cur->item.id){	//if item is smaller than current node
		if (cur->left != NULL)					//if left child exists
			return CloneSubTree2(cur->left, item);			
	}
	else{		//if item is larger than current node
		if (cur->right != NULL)					//if right child exists
			return CloneSubTree2(cur->right, item);
	}

	return false;
}

void BST::CloneSubTree3(BTNode* cur) {	//insert all related nodes in t2 subtree
	if (cur == NULL) return ; 	

	insert(cur->item);
	CloneSubTree3(cur->left);
	CloneSubTree3(cur->right);
}

bool BST::PrintPath() {
	if (root == NULL)	return false;
	int completed[30];
	int count = 0;
	PrintExternalPath(root,completed,count);
	return true;
}


void BST::PrintExternalPath(BTNode* cur, int completed[], int count) {		//print external path
	completed[count] = cur->item.id;
	if (cur->left==NULL && cur->right==NULL) {	  		//both side is null
		cout << "\t";
		for (int i = 0; i <= count; i++)  		//print all item in list
			cout << "\033[1;34m"<< completed[i] << " \033[0m";
		cout << endl;
		return;
	}
	count++;
	if (cur->left!=NULL)
		PrintExternalPath(cur->left, completed, count);
	if (cur->right!=NULL)
		PrintExternalPath(cur->right, completed, count);
	count--;
}
#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"
#include<string>
#include <windows.h>
#pragma warning(disable:4996)
using namespace std;

bool ReadFile(const char *, BST *);
int menu();
bool IsRedundant(int, BTNode*);


int main() {
	bool decision = true;
	BST *StudentRecord= new BST();
	do {
		switch (menu()) {
		case(1): {
			system("cls");
			cout << "\n\n\n" << endl;
			cout << string(50, '=') << endl;
			cout << "||\t\tRead Data to BST\t\t||" << endl;
			cout << string(50, '=') << endl;
			const char* Filename = "student.txt";
			ReadFile(Filename, StudentRecord);
			system("pause");
			break;
		}
		case(2):
		{
			system("cls");
			cout << string(50, '=') << endl;
			cout << "||\t\tDeepest Node(s)\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			if (!StudentRecord->deepestNodes()) {
				cout << "||\t" << "\033[1;31m The BST is empty \033[0m" << "\t\t\t||" << endl;
				cout << "||\t" << "\033[1;31m No node will be presented \033[0m" << "\t\t||" << endl;
			}
			cout << string(50, '=') << endl;
			system("pause");
			break;

		}
		case(3):
		{
			int order, source;
			system("cls");
			cout << string(50, '=') << endl;
			cout << "||\t\tDisplay Nodes\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			cout << "||\tOrder:       \t\t\t\t||" << endl;
			cout << "||\t1.	Ascending Order\t\t\t||" << endl;
			cout << "||\t2.	Descending Order\t\t||" << endl;
			cout << string(50, '=') << endl;
			cout << "||\tDisplay Destination:\t\t\t||" << endl;
			cout << "||\t1.	Console Screen\t\t\t||" << endl;
			cout << "||\t2.	File\t\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			cout << "Order: ";
			cin >> order;
			cout << endl;
			cout << "Display to: ";
			cin >> source;
			system("cls");
			cout << string(50, '=') << endl;
			cout << "||\t\tDisplay Nodes\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			if (!StudentRecord->display(order, source)) {
				cout << "||\t" << "\033[1;31m The BST is empty \033[0m" << "\t\t\t||" << endl;
				cout << "||\t" << "\033[1;31m No node will be presented \033[0m" << "\t\t||" << endl;
				cout << string(50, '=') << endl;
			}
			system("pause");
			cin.ignore();
			break;
		}
		case(4)://clone subtree
		{
			system("cls");
			cout << string(66, '=') << endl;
			cout << "||\t\t\tClone Subtree\t\t\t\t||" << endl;
			cout << string(66, '=') << endl;
			bool leave = true;
			int id;
			BST t2;
			cout << "Please input the student id >>>";
			cin >> id;
			Student student;
			student.id = id;
			if (t2.CloneSubtree(*StudentRecord, student))
			{
				cout << string(66, '=') << endl;
				cout << "\033[1;32m \t\tt2 Clone Subtree\033[0m" << endl;
				cout << string(66, '=') << endl;
				t2.preOrderPrint();
			}
			else{
				cout << "\033[1;31m Cannot create a clone subtree\033[0m" << endl;
				leave = false;
			}
			cout << string(66, '=') << endl;
			cin.ignore();
			system("pause");
			break;
		}
		case(5)://Print level node
		{
			system("cls");
			cout << string(50, '=') << endl;
			cout << "||\t\tPrint Level Nodes\t\t||" << endl;
			cout << string(50, '=') << endl;
			if (!StudentRecord->printLevelNodes())
			{
				cout << "\033[1;31m The tree is empty...\033[0m" << endl;
				Sleep(1000);
			}
			cout << string(50, '=') << endl;
			system("pause");
			break;
		}
		case(6):
		{
			system("cls");
			cout << string(50, '=') << endl;
			cout << "||\t\tPrint Path\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			if(!StudentRecord->PrintPath())
				cout<<"\033[1;31m The tree is empty...\033[0m"<<endl;
			cout << string(50, '=') << endl;
			system("pause");
			break;
		}
		case(7):
		{
			decision = false;
			break;
		}
		default:
		{
			cout << "\033[1;31m Invalid input found in the system...\033[0m" << endl;
			Sleep(1000);
			break;
		}
		}
	} while (decision);
	
	system("pause");
	return 0;
}

int menu() {
	system("cls");
	string selection, decision;
	int record=0;
	cout << "\n\n\n" << string(50, '=') << endl;
	cout << "||\t\t\t\t\t\t||" << endl;
	cout << "||\t\t   MAIN MENU        \t\t||" << endl;
	cout << "||\t\t\t\t\t\t||" << endl;
	cout << string(50, '=') << endl;
	cout << "||\t\t\t\t\t\t||" << endl;
	cout << "||\t\033[1;36m1. Read Data to BST\033[0m\t\t\t||" << endl;
	cout << "||\t\033[1;36m2. Print Deepest Nodes.\033[0m\t\t\t||" << endl;
	cout << "||\t\033[1;36m3. Display Student.\033[0m\t\t\t||" << endl;
	cout << "||\t\033[1;36m4. Clone Subtree.\033[0m\t\t\t||" << endl;
	cout << "||\t\033[1;36m5. Print Level Nodes.\033[0m\t\t\t||" << endl;
	cout << "||\t\033[1;36m6. Print Path\033[0m\t\t\t\t||" << endl;
	cout << "||\t\033[1;36m7. Exit.\033[0m\t\t\t\t||" << endl;
	cout << "||\t\t\t\t\t\t||" << endl;
	cout << string(50, '=') << endl;
	cin.clear();
	cout << "\033[0;34mEnter your choice : ";
	getline(cin, selection);
	cout << "\033[0m";
	for (int i = 0; i < selection.size(); i++) {
		if (isdigit(selection[i]))
			record++;
	}
	if (record == selection.size())
		return stoi(selection);
	return NULL;
}


bool ReadFile(const char* filename, BST* t1)
{
	ifstream readFile;
	readFile.open(filename);
	if (readFile.fail())
	{
		cout << "student.txt file is not found.\n";
		return false;
	}
	struct Student studInfo;
	string line;
	int count = 0;   //represent how many student record has inserted
	int index = 0;   //the value of index indicate which info of student to store
	while (!readFile.eof())
	{
		readFile >> line;
		if (line == "=")
		{
			if (index == 0)
			{
				readFile >> studInfo.id;
			}
			else if (index == 1)
			{
				readFile.ignore();
				readFile.getline(studInfo.name, 30);
			}
			else if (index == 2)
			{
				readFile.ignore();
				readFile.getline(studInfo.address, 100);
			}
			else if (index == 3)
			{
				readFile >> studInfo.DOB;
			}
			else if (index == 4)
			{
				readFile >> studInfo.phone_no;
			}
			else if (index == 5)
			{
				readFile >> studInfo.course;
			}
			else
			{
				readFile >> studInfo.cgpa;
				index = -1;
				if (t1->empty())
				{
					t1->insert(studInfo);
					count++;
				}
				else if (!IsRedundant(studInfo.id, t1->root))
				{
					t1->insert(studInfo);
					count++;
				}
			}
			index++;
		}
	}
	readFile.close();
	cout << count << " student(s) record has been successfully read.\n";
	return true;
}

//avoid duplication record
bool IsRedundant(int id, BTNode* BTptr)
{
	if (id == BTptr->item.id)  //student id = student id in BST
		return true;
	if (id > BTptr->item.id && BTptr->right != NULL)
		return IsRedundant(id, BTptr->right);
	else if (id < BTptr->item.id && BTptr->left != NULL)
		return IsRedundant(id, BTptr->left);
	return false;
}


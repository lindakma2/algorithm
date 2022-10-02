// C++ code
#include <iostream>
#include <vector>
#include <string>
#include <math.h>       // floor()
#include <fstream>	  //�}���ɸ�Ƭy
#include <cctype>     //�Ω�R��token�����Ÿ�
#include <algorithm>  //�Ω�R��token�����Ÿ�
#include <iomanip>	  //�Ψ�����X�r�ꪺsetw()
#include <sstream>	  //�Ω�Ū�ɮɪ�stringstream
#include <ctime>	  //�Ω��H������priority����
#include <Windows.h>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using namespace std;

struct Node {
    int key;                    // number 
    string value;               // genre
    Node* next;                 // pointer to remember memory address of next node

    Node() :key(0), value(""), next(0) {};
    Node(int Key, string Value) :key(Key), value(Value), next(0) {};
    Node(Node const& data) :key(data.key), value(data.value), next(data.next) {};
};

class HashChainNode {
private:
    int size,                 // size: size of table, count: number of data
        count;                // count/size = load factor
    Node** table;             // pointer to pointer, hash table  

    int HashFunction(int key);      // Multiplication method
    void TableDoubling();
    void TableShrinking();
    void Rehashing(int size_orig);

public:
    HashChainNode() {};
    HashChainNode(int m) :size(m), count(0) {
        table = new Node * [size];           // allocate the first demension of table
        for (int i = 0; i < size; i++) {    // initialization
            table[i] = 0;                   // ensure every slot points to NULL
        }
    }
    ~HashChainNode();

    void Insert(Node data);         // consider TableDoubling()
    void Delete(int key);           // consider TableShrinking()
    string Search(int key);
    void DisplayTable();
};

void HashChainNode::Insert(Node data) {

    count++;
    if (count > size) {         // consider load factor
        TableDoubling();        // if n/m > 1, then double the size of table
    }

    int index = HashFunction(data.key);   // get index of slot
    Node* newNode = new Node(data);       // create new node to store data

    // push_front()
    if (table[index] == NULL) {           // eg: list: (empty), add4
        table[index] = newNode;           // eg: list: 4->NULL
    }
    else {                                // eg: list: 5->9->NULL  , add 4
        Node* next = table[index]->next;  //     list: 5->4->9->NULL
        table[index]->next = newNode;
        newNode->next = next;
    }
}

void HashChainNode::Delete(int key) {

    int index = HashFunction(key);        // get index of slot
    Node* current = table[index],         // use two pointer for traversal in list
        * previous = NULL;

    while (current != NULL && current->key != key) {
        previous = current;               // traversal in list, 3 cases:
        current = current->next;          // 1. data not found
    }                                     // 2. data found at first node in list
                                          // 3. data found at other position in list

    if (current == NULL) {                    // eg: list:5->2->9->NULL, want to delete 3
        cout << "data not found.\n\n";
        return;
    }
    else {
        if (previous == NULL) {               // eg: list:5->2->9->NULL, want to delete 5
            table[index] = current->next;     // after deleting 5, list:2->9->NULL
        }                                     // current points to 5     

        else {                                // eg: list:5->2->9->NULL, want to delete 2
            previous->next = current->next;   // after deleting 2, list:5->9->NULL
        }                                     // current points to 2
        delete current;
        current = 0;
    }

    count--;
    if (count < size / 4) {      // consider load factor
        TableShrinking();      // if n/m < 4, then shrink the table
    }
}

string HashChainNode::Search(int key) {

    int index = HashFunction(key);      // get index of slot
    Node* current = table[index];       // current points to the first node in list

    while (current != NULL) {           // traversal in list
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return "no such data";
}

int HashChainNode::HashFunction(int key) {
    // Multiplication method
    double A = 0.6180339887,
        frac = key * A - floor(key * A);
    return floor(this->size * frac);
}

void HashChainNode::TableDoubling() {

    int size_orig = size;    // size_orig represents the original size of table
    size *= 2;               // double the size of table
    Rehashing(size_orig);;   // create new table with new larger size
}

void HashChainNode::TableShrinking() {

    int size_orig = size;    // size_orig represents the original size of table
    size /= 2;               // shrink the size of table
    Rehashing(size_orig);    // create new table with new smaller size
}

void HashChainNode::Rehashing(int size_orig) {

    Node** newtable = new Node * [size];    // allocate memory for new table
    for (int i = 0; i < size; i++) {       // initializetion 
        newtable[i] = 0;                   // ensure every node in slot points to NULL
    }

    for (int i = 0; i < size_orig; i++) {  // visit every node in the original table

        Node* curr_orig = table[i],        // curr_orig: current node in original table
            * prev_orig = NULL;            // prev_orig: following curr_orig 

        while (curr_orig != NULL) {      // traversal in list of each slot in original table

            prev_orig = curr_orig->next; // curr_orig will be directly move to new table
                                         // need prev_orig to keep pointer in original table

            int index = HashFunction(curr_orig->key);    // get index of slot in new table

            // push_front(), do not allocate new memory space for data
            // directly move node in original table to new table
            if (newtable[index] == NULL) {       // means newtable[index] is empty
                newtable[index] = curr_orig;
                newtable[index]->next = 0;       // equivalent to curr_orig->next = 0;
            }
            // if there is no initialization for newtable, segmentation faults might happen
            // because newtable[index] might not point to NULL 
            // but newtable[index] is empty
            else {                                   // if newtable[index] is not empty
                Node* next = newtable[index]->next;  // push_front()
                newtable[index]->next = curr_orig;
                curr_orig->next = next;
            }
            curr_orig = prev_orig;          // visit the next node in list in original table
        }
    }
    delete[] table;               // release memory of original table
    this->table = newtable;        // point table of object to new table
}

HashChainNode::~HashChainNode() {

    for (int i = 0; i < size; i++) {    // visit every node in table 
                                        // and release the memory of each node 
        Node* current = table[i];       // point *current to first node in list
        while (current != NULL) {       // traversal in list
            Node* previous = current;
            current = current->next;
            delete previous;
            previous = 0;
        }
    }
    delete[] table;
}

void HashChainNode::DisplayTable() {

    for (int i = 0; i < size; i++) {    // visit every node in table 
        cout << "#slot#" << i << ": ";
        Node* current = table[i];
        while (current != NULL) {
            cout << "(" << current->key << "," << current->value << ") ";
            current = current->next;
        }
        cout << endl;
    }
    cout << endl;
}



int PreHashing2(string key_str) {

	int exp = 9,        // choose randomly 
		key_int = 0,
		p = 1;

	for (int i = (int)key_str.size() - 1; i >= 0; i--) {
		key_int += key_str[i];
	}
	return key_int%2000;
}


int main()
{
	
	HashChainNode hash(2);

	ifstream TestFile1, TestFile11, TestFile12, TestFile13;
	string data; //read a sentence will be cut into token
	TestFile1.open("TestFile3.txt");
	TestFile11.open("TestFile11.txt");
	TestFile12.open("TestFile12.txt");
	TestFile13.open("TestFile13.txt");

	int tokennum = 0; //token amount
	int dicnodenum = 0; //dictionrary token amount
	string token[1000];
	string token_test1[1000];
	string token_test2[1000];	//�qTestFile12.txt��J��token
	string token_test3[1000];
	string user_token;//input string by user for insert,delete,search
	clock_t start, end;
	

	//distionary
	int count = 0;
	while (getline(TestFile1, data))
	{
		stringstream temp(data);				//�NŪ�J������Ʃ�btemp
		while (getline(temp, token[tokennum], ' '))	//�N�Ӧ��Ƥ��Ψ�token��
		{
			transform(token[tokennum].begin(), token[tokennum].end(), token[tokennum].begin(), tolower); //all change to little write
			tokennum++;
		}
		count++;
	}

	cout << "�q�ɮפ�Ū���쪺token �G\n";
	start = clock();
	for (int j = 0; j < tokennum; j++)
	{
		//�R��token�������I�Ÿ�
		//token[j].erase(remove_if(token[j].begin(), token[j].end(), static_cast<int(*)(int)>(&ispunct)),token[j].end());

		int hashingnum = PreHashing2(token[j]);
		string find=hash.Search(hashingnum);			// ���d�ߦ�key�ȬO�_�w�s�bBST��
		if (find == "no such data")								//���JBST
		{
			hash.Insert(Node(hashingnum, token[j]));
			dicnodenum++;
		}
		cout << token[j] << " ";
	}
	end = clock();
	cout << "\n���Jhashing�᪺�ɶ�: " << end - start << endl;
	cout << "\n�q�ɮפ�Ū���쪺token�ƶq" << tokennum << endl;
	cout << "\n�h�����ƪ���r��Adictionary����token�ƶq" << dicnodenum << endl;

	cout << "\n==========hashing��inorder trasversal==========" << endl;
	hash.DisplayTable();
	cout << end;

	//teatfile1
	tokennum = 0;
	while (getline(TestFile11, data))
	{
		stringstream temp(data);	//�NŪ�J������Ʃ�btemp
		while (getline(temp, token_test1[tokennum], ' '))
		{
			transform(token_test1[tokennum].begin(), token_test1[tokennum].end(), token_test1[tokennum].begin(), tolower);
			tokennum++;
		}
	}

	//�Ψӭp�⦨�\��쪺token��
	int countBST = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//�R��token�������I�Ÿ�
		token_test1[j].erase(
			remove_if(token_test1[j].begin(), token_test1[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test1[j].end());

		//�]�w���token�ɦL�X�T��
		int hashingnum = PreHashing2(token_test1[j]);
		string find = hash.Search(hashingnum);

		if (find != "no such data")
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> �i�H�bhashing�����";
			countBST++;
		}
		else
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> �bhashing���䤣��";
		}
	}
	double successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n�bhashing���token�����\�v�G" << successBST << " %" << endl;

	//teatfile2
	tokennum = 0;
	while (getline(TestFile12, data))
	{
		stringstream temp(data);	//�NŪ�J������Ʃ�btemp
		while (getline(temp, token_test2[tokennum], ' '))
		{
			transform(token_test2[tokennum].begin(), token_test2[tokennum].end(), token_test2[tokennum].begin(), tolower);
			tokennum++;
		}
	}

	//�Ψӭp�⦨�\��쪺token��
	countBST = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//�R��token�������I�Ÿ�
		token_test2[j].erase(
			remove_if(token_test2[j].begin(), token_test2[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test2[j].end());

		//�]�w���token�ɦL�X�T��
		int hashingnum = PreHashing2(token_test2[j]);
		string find = hash.Search(hashingnum);

		if (find != "no such data")
		{
			cout << setw(13) << token_test2[j] << setw(20) << "-> �i�H�bhashing�����";
			countBST++;
		}
		else
		{
			cout << setw(13) << token_test2[j] << setw(20) << "-> �bhashing���䤣��";
		}
	}
	successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n�bhashing���token�����\�v�G" << successBST << " %" << endl;

	//teatfile3
	tokennum = 0;
	while (getline(TestFile13, data))
	{
		stringstream temp(data);	//�NŪ�J������Ʃ�btemp
		while (getline(temp, token_test3[tokennum], ' '))
		{
			transform(token_test3[tokennum].begin(), token_test3[tokennum].end(), token_test3[tokennum].begin(), tolower);
			tokennum++;
		}
	}

	//�Ψӭp�⦨�\��쪺token��
	countBST = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//�R��token�������I�Ÿ�
		token_test3[j].erase(
			remove_if(token_test3[j].begin(), token_test3[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test3[j].end());

		//�]�w���token�ɦL�X�T��
		int hashingnum = PreHashing2(token_test1[j]);
		string find = hash.Search(hashingnum);

		if (find != "no such data")
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> �i�H�bhashing�����";
			countBST++;
		}
		else
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> �bhashing���䤣��";
		}
	}
	successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n�bhashing���token�����\�v�G" << successBST << " %" << endl;
	
	_LARGE_INTEGER Timestart, Timeend, Pintime;
	QueryPerformanceFrequency(&Pintime);

	//�H�U�B�z�ϥΪ̿�J������
	int selection = 0;      //�إߤ@���ܼƦs���ϥΪ̿�J��
	do
	{
		cout << "\n=======================" << endl;        //�i���ϥΥ\��
		cout << "\n�п�ܻݭn���檺�ʧ@(�ѿ�J�D���Ʀr����)" << endl;
		cout << "\n(1)���J���(Insert the token)" << endl
			<< "(2)�R�����(Delete the token)" << endl
			<< "(3)��X�Y�����(Find the token)" << endl
			<< "(4)����(Exit)" << endl;

		cout << ">>";
		cin >> selection;
		if (cin.fail())		//����ϥΪ̿�J���Ʀr�A�_�h�����{��
		{
			cout << "�z��J�����O�Ʀr" << endl;
			break;
		}

		//����ϥΪ̿�J�ȥ�������1��4����
		while (selection > 4 || selection < 1)
		{
			cout << "�D�d��� �Э��s��J(1~4)" << endl;
			cin >> selection;
		}

		
		//��ϥΪ̿�J���Ȱ��P�_
		if (selection == 1)     //���Jkey��
		{
			cout << "\n�п�J���s�W��token��: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//�ন�p�g
			QueryPerformanceCounter(&Timestart);
			int hashingnum = PreHashing2(user_token);
			string find = hash.Search(hashingnum);			// ���d�ߦ�key�ȬO�_�w�s�bBST��
			if (find != "no such data")                            //�Y�w�s�b�A�h��X�T��
				cout << "��token�Ȥw�s�b��hashing�� ";
			else
			{
				cout << "���\�s�W��hashing" << endl;
				hash.Insert(Node(hashingnum, user_token));
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�s�W��hashing��O���ɶ��G " << time << "ms" << endl;        
            hash.DisplayTable();
			
		}
		else if (selection == 2)  //�R��key
		{
			cout << "\n��J���R����token��: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//�ন�p�g
			QueryPerformanceCounter(&Timestart);
			int hashingnum = PreHashing2(user_token);
			string find = hash.Search(hashingnum);			// ���d�ߦ�key�ȬO�_�w�s�bBST
			if (find == "no such data")                            //�Y�w�s�b�A�h��X�T��
				cout << "\n��token�Ȥ��s�b��hashing�� ";
			else
			{
                hash.Delete(hashingnum);
				cout << "\n�qhashing�R�����\" << endl;
				cout << "\n�R��" << user_token << "�᪺hashing���ǵ��G�G\n" << endl;                  //��X���Ǫ�ܦ�           
                hash.DisplayTable();
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�qhashing�R���ηj�M��O���ɶ��G " << time << "ms" << endl;

		}
		else if (selection == 3)   //�d��key
		{
			cout << "�п�J���d�䪺���: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//�ন�p�g

			QueryPerformanceCounter(&Timestart);
			
            int hashingnum = PreHashing2(user_token);
            string find = hash.Search(hashingnum);
			
			if (find == "no such data")                            //�Y�w�s�b�A�h��X�T��
				cout << "\n" << user_token << "���s�b��hashing��" << endl;
			else
				cout << "\n" << user_token << "�s�b��hashing��" << endl;
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�bhashing�j�M��O���ɶ��G " << time << "ms" << endl;

		}


	} while (selection != 4);   //��J4�H�����j��

	TestFile1.close();
	TestFile11.close();
	system("PAUSE");
	return (0);
}
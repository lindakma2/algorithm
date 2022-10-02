#include <iostream>
#include <string>
#include <fstream>	  //�}���ɸ�Ƭy
#include <cctype>     //�Ω�R��token�����Ÿ�
#include <algorithm>  //�Ω�R��token�����Ÿ�
#include <iomanip>	  //�Ψ�����X�r�ꪺsetw()
#include <sstream>	  //�Ω�Ū�ɮɪ�stringstream
#include <ctime>	  //�Ω��H������priority����
#include <Windows.h>

using namespace std;


//�U���class�GtreeNode�BBST �A�w�q�F�G���j�M��һݪ��禡�H���ܼ� 
class treeNode {
public:
	treeNode* leftchild;	//���l��
	treeNode* rightchild;	//�k�l��
	treeNode* parent;		//���`�I
	string element;			//��node�����e �]���O�r��A��string���O
	//int key;

	treeNode() :leftchild(0), rightchild(0), parent(0), element("") {};
	treeNode(string b) :leftchild(0), rightchild(0), parent(0), element(b) {};

	//int GetKey() { return key; }              // ���F�bmain()�n����˵�node�O�_���T
	//string GetElement() { return element; }   // �~�ݭn�o���member functionŪ��private data

	// ��l���p, �]��class BST�Oclass TreeNode��friend class
	// �bclass BST��member function��, �i�H�����s��class TreeNode��private data
	friend class BST;   // ��b private �� public ���i�H 
};

class BST {
public:
	BST() :root(0) {};

	treeNode* Search(string element);
	void InsertBST(string element);
	void InorderPrint();        // �i�H�ΨӽT�{BST�O�_�إߦ��\
	void DeleteBST(string element);
private:
	treeNode* root;
	treeNode* Leftmost(treeNode* current);
	treeNode* Successor(treeNode* current);
};

//�U���class�GsplayNode�BSPT �A�w�q�Fsplay tree�һݪ��禡�H���ܼ�
class splayNode {
public:
	splayNode* leftchild;
	splayNode* rightchild;
	string element;

	friend class SPT;
};

class SPT {
public:
	SPT() {};

	splayNode* Search(splayNode* root, string element);
	splayNode* InsertSPT(splayNode* root, string element);
	splayNode* DeleteSPT(splayNode* root, string element);
	void Inorder(splayNode* root);

	splayNode* leftRotate(splayNode* x);
	splayNode* rightRotate(splayNode* x);
	splayNode* splay(splayNode* root, string element);
	splayNode* newElement(string element);
};

//�U���class�GtreapNode�BTREAP �A�w�q�Ftreap�һݪ��禡�H���ܼ�
class treapNode {
public:
	int priority;			//�Ω�إ�minheap���з�
	string element;			//�r��
	treapNode* leftchild;
	treapNode* rightchild;
	friend class TREAP;
};

class TREAP {
public:
	//TREAP() {};
	treapNode* Search(treapNode* root, string element);
	treapNode* InsertTREAP(treapNode* root, string element);
	treapNode* DeleteTREAP(treapNode* root, string element);
	void Inorder(treapNode* root);

	treapNode* leftRotate(treapNode* x);
	treapNode* rightRotate(treapNode* x);
	treapNode* newElement(string element);

};

//�G���j�M��search
treeNode* BST::Search(string element) {

	treeNode* current = root;               // �Ncurent���Vroot�@��traversal�_�I

	while (current != NULL && element != current->element) {  // ��ر��p���X�j��G
													  // 1.�S��� 2.�����
		if (element < current->element)
		{
			current = current->leftchild;   // �V����
		}
		else
		{
			current = current->rightchild;  // �V�k��
		}
	}
	return current;
}

//�G���j�M�𪺴��J
void BST::InsertBST(string element) {

	treeNode* y = 0;        // �Ƿs�⪨��
	treeNode* x = 0;        // ��L
	treeNode* insert_node = new treeNode(element);   // insert_node���N�n�s�W��node

	x = root;
	while (x != NULL) {                 // �bwhile��, �H�p�PSearch()���覡�M��A����m       
		y = x;                          // y����s����x����m
		/*
		if (insert_node->key < x->key) { // �P�_x�O�n��left- �٬Oright- �e�i
			x = x->leftchild;
		}
		else {
			x = x->rightchild;
		}
		*/
		//////////////////////////////////////////////////////////////////
		/*
		int i = 0;
		do
		{
			if (insert_node->element < x->element )
			{
				x = x->leftchild;
			}
			else if (strcmp(&insert_node->element[i], &x->element[i]) > 0)
			{
				x = x->rightchild;
			}
			i++;
		} while (strcmp(&insert_node->element[i - 1], &x->element[i - 1]) == 0 && i < insert_node->element.size());
		*/
		////////////////////////////////////////////////////////////////////
		if (insert_node->element < x->element)
		{ // �P�_x�O�n��left- �٬Oright- �e�i
			x = x->leftchild;
		}
		else if (insert_node->element > x->element)
		{
			x = x->rightchild;
		}

	}                        // ���X�j���, x�Y��NULL


										// y�Y��insert_node��parent
	insert_node->parent = y;            // �Ninsert_node��parent pointer���Vy

	if (y == NULL) {                     // �U���@��if-else, ��insert_node���WBST
		this->root = insert_node;
	}
	else
	{
		/*
		int j = 0;
		do
		{
			if (strcmp(&insert_node->element[j], &y->element[j]) < 0)
			{
				y->leftchild = insert_node;
			}
			else if (strcmp(&insert_node->element[j], &y->element[j]) > 0)
			{
				y->rightchild = insert_node;
			}
			j++;
		} while (strcmp(&insert_node->element[j - 1], &y->element[j - 1]) == 0 && j < insert_node->element.size());
	*/
		if (insert_node->element < y->element)
		{
			y->leftchild = insert_node;
		}
		else if (insert_node->element > y->element)
		{
			y->rightchild = insert_node;
		}
		else if (insert_node->element == y->element)
		{
			//y = insert_node;
		}
	}
}

//�ϥ�inorder��X
void BST::InorderPrint() {
	treeNode* current = new treeNode;
	current = Leftmost(root);
	int count = 0;
	while (current) {
		cout << current->element << " ";
		current = Successor(current);
		count++;
		if (count % 10 == 0)
			cout << "\n";
	}
}

treeNode* BST::Leftmost(treeNode* current) {
	while (current->leftchild != NULL) {
		current = current->leftchild;
	}
	return current;
}

treeNode* BST::Successor(treeNode* current) {
	if (current->rightchild != NULL) {
		return Leftmost(current->rightchild);
	}

	// �Q�Ψ��pointer: successor�Pcurrent��traversal 

	treeNode* successor = current->parent;
	while (successor != NULL && current == successor->rightchild) {
		current = successor;
		successor = successor->parent;
	}
	return successor;
}

void BST::DeleteBST(string element) {               // �n�R���㦳KEY��node

	treeNode* delete_node = Search(element);    // ���T�{BST���O�_���㦳KEY��node
	if (delete_node == NULL) {
		std::cout << "data not found.\n";
		//return;
	}

	treeNode* y = 0;      // �u���n�Q�R��������O���骺node
	treeNode* x = 0;      // �n�Q�R����node��"child"

	if (delete_node->leftchild == NULL || delete_node->rightchild == NULL) {
		y = delete_node;
	}
	else {
		y = Successor(delete_node);        // �Ny�]��delete_node��Successor
	}                                      // �g�L�o��if-else, y�վ㦨�ܦh�u���@��child
										   // �����վ㦨case1��case2�ӳB�z
	if (y->leftchild != NULL) {
		x = y->leftchild;                  // �Nx�]��y��child, �i��O���İO����,
	}                                      // �]���i��ONULL
	else {
		x = y->rightchild;
	}

	if (x != NULL) {                        // �by�Q�R�����e, �o�ӨB�J��x���^BST
		x->parent = y->parent;             // ���Y���ϤG(c)��, ���ñ��^�t�P�H���B�J
	}
	// ���ۦA��n�Q����O���骺node��"parent"���V�s��child
	if (y->parent == NULL) {                // �Y�R�����O�����root, �N��x���s��root 
		this->root = x;
	}
	else if (y == y->parent->leftchild) {    // �Yy�쥻�O��parent��left child
		y->parent->leftchild = x;           // �K��x�Ҧby��parent��left child, ���Ny
	}
	else {                                   // �Yy�쥻�O��parent��right child
		y->parent->rightchild = x;          // �K��x�Ҧby��parent��right child, ���Ny
	}
	// �w��case3
	if (y != delete_node) {                 // �Yy�Odelete_node������, �̫�n�A�Ny�����
		//delete_node->key = y->key;          // ��^delete_node���O�����m, �ñNy���O�����m����
		delete_node->element = y->element;  // �ϤG(d), y�Y�O�F��, delete_node�Y�O��|
	}

	delete y;                               // �Ny���O�����m����
	y = 0;
}


//===
treapNode* TREAP::leftRotate(treapNode* x)
{
	treapNode* y = x->rightchild;
	treapNode* z = y->leftchild;
	y->leftchild = x;
	x->rightchild = z;
	return y;
}

treapNode* TREAP::rightRotate(treapNode* x)
{
	treapNode* y = x->leftchild;
	treapNode* z = y->rightchild;
	y->rightchild = x;
	x->leftchild = z;
	return y;
}

treapNode* TREAP::newElement(string element)
{
	treapNode* node = new treapNode;
	node->element = element;
	node->priority = rand() % 100;		//�h�@���H����Ȫ��u���v
	node->rightchild = NULL;
	node->leftchild = NULL;
	return (node);
}

treapNode* TREAP::Search(treapNode* root, string element)
{
	treapNode* current = root;
	while (current != NULL && element != current->element)
	{
		if (element < current->element)
		{
			current = current->leftchild;   // �V����
		}
		else
		{
			current = current->rightchild;  // �V�k��
		}
	}
	return current;
}

treapNode* TREAP::InsertTREAP(treapNode* root, string element)
{
	if (!root)	//��root�Onull�ɡAcreate�@�ӷs��node
	{
		return newElement(element);
	}

	if (element > root->element) //���J�Ȥj���e��root ���k�䨫
	{
		root->rightchild = InsertTREAP(root->rightchild, element);
		if (root->priority > root->rightchild->priority)
		{
			root = leftRotate(root);
		}
	}
	else if (element < root->element)
	{
		root->leftchild = InsertTREAP(root->leftchild, element);

		if (root->priority > root->leftchild->priority)	//�ݭn�ŦXmin
		{
			root = rightRotate(root);
		}
	}

	return root;
}

treapNode* TREAP::DeleteTREAP(treapNode* root, string element)
{
	if (root == NULL)
	{
		return root;
	}
	if (element > root->element)
	{
		root->rightchild = DeleteTREAP(root->rightchild, element);
	}
	else if (element < root->element)
	{
		root->leftchild = DeleteTREAP(root->leftchild, element);
	}
	else if (root->leftchild == NULL)
	{
		treapNode* node = root->rightchild;
		delete(root);
		root = node;
	}
	else if (root->rightchild == NULL)
	{
		treapNode* node = root->leftchild;
		delete(root);
		root = node;
	}
	else if (root->leftchild->priority < root->rightchild->priority)
	{
		root = leftRotate(root);
		root->leftchild = DeleteTREAP(root->leftchild, element);

	}
	else
	{
		root = rightRotate(root);
		root->rightchild = DeleteTREAP(root->rightchild, element);

	}
	return root;
}

void TREAP::Inorder(treapNode* root)
{
	if (root)
	{
		Inorder(root->leftchild);	//��
		cout << setw(5) << "token: " << setw(10) << root->element << " priority = " << setw(5) << root->priority;
		if (root->leftchild)
			cout << setw(20) << "\t -> left child: " << root->leftchild->element
			<< " priority = " << setw(5) << root->priority;
		if (root->rightchild)
			cout << setw(20) << "\t -> right child: " << root->rightchild->element
			<< " priority = " << setw(5) << root->priority;
		cout << "\n";
		Inorder(root->rightchild);	//�k
	}
}

int
main(void)
{
	srand((unsigned)time(NULL));	//
	BST B;
	
	TREAP T;
	string tokenSPT[1000];
	string tokenSPT_test1[1000];
	
	
	treapNode* rootTreap;
	rootTreap = NULL;			//���w�]treap��root�Onull �]���쥻�O�Ū�tree
	treapNode* find;

	ifstream TestFile1, TestFile11, TestFile12, TestFile13;	//�ɮ׫��w
	string data;								//�N�ɮ�Ū�쪺����ƼȮɩ�Jdata�r��
	TestFile1.open("TestFile3.txt");
	TestFile11.open("TestFile11.txt");
	TestFile12.open("TestFile12.txt");
	TestFile13.open("TestFile13.txt");

	if (!(TestFile1 || TestFile11 || TestFile12))//�ɮ׿��~�T��
		cout << "�ɮ׵L�k�}��" << endl;

	int i = 0;					//�p��q�ɮפ�Ū���쪺token�ƶq
	int nodeNum = 0;			//�p��r�媺token�ƶq
	string token[1000];			//�ǳƩ�JBST��token
	string token_test1[1000];	//�qTestFile11.txt��J��token
	string token_test2[1000];	//�qTestFile12.txt��J��token
	string token_test3[1000];	//�qTestFile13.txt��J��token
	string user_token;			//�qcommand line��J��token �i���j�M �R�� �s�W
	treeNode* node;
	clock_t start, end;							//�إ�clock_t�ܼ�(����ƧκA)�H�O���ɶ��A�H�@�����
	while (getline(TestFile1, data))
	{
		stringstream temp(data);				//�NŪ�J������Ʃ�btemp
		while (getline(temp, token[i], ' '))	//�N�Ӧ��Ƥ��Ψ�token��
		{
			transform(token[i].begin(), token[i].end(), token[i].begin(), tolower);
			i++;
		}
	}
	cout << "�q�ɮפ�Ū���쪺token �G\n";
	start = clock();
	for (int j = 0; j < i; j++)
	{
		//�R��token�������I�Ÿ�
		token[j].erase(
			remove_if(token[j].begin(), token[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token[j].end());

		cout << token[j];
		node = B.Search(token[j]);				// ���d�ߦ�key�ȬO�_�w�s�bBST��
		if (!node)								//���JBST
		{
			
			B.InsertBST(token[j]);
			nodeNum++;
		}
		//cout << token[j] << endl;
	}
	end = clock();
	cout << "\n���JBST�᪺�ɶ�: " << end - start << endl;
	//cout << "\n�q�ɮפ�Ū���쪺token�ƶq" << i << endl;
	//cout << "\n�h�����ƪ���r��Adictionary����token�ƶq" << nodeNum << endl;

	start = 0; end = 0;
	for (int j = 0; j < i; j++)
	{
		//�R��token�������I�Ÿ�
		token[j].erase(
			remove_if(token[j].begin(), token[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token[j].end());

		rootTreap = T.InsertTREAP(rootTreap, token[j]);//���JTREAP
	}
	end = clock();
	cout << "\n���JTREAP�᪺�ɶ� " << end - start << endl;


	//cout << "\n�q�ɮפ�Ū���쪺token�ƶq" << i << endl;
	//cout << "\n�h�����ƪ���r��Adictionary����token�ƶq" << nodeNum << endl;
	
	cout << "\n==========BST��inorder trasversal==========" << endl;
	B.InorderPrint();
	cout << "\n==========TREAP��inorder trasversal==========" << endl;
	T.Inorder(rootTreap);

	
	i = 0;
	while (getline(TestFile11, data))
	{
		stringstream temp(data);	//�NŪ�J������Ʃ�btemp
		while (getline(temp, token_test1[i], ' '))
		{
			transform(token_test1[i].begin(), token_test1[i].end(), token_test1[i].begin(), tolower);
			i++;
		}
	}
	int countBST = 0;	//�Ψӭp�⦨�\��쪺token��
	int countSPT = 0;
	int countTREAP = 0;
	for (int j = 0; j < i; j++)
	{
		//�R��token�������I�Ÿ�
		token_test1[j].erase(
			remove_if(token_test1[j].begin(), token_test1[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test1[j].end());

		//�]�w���token�ɦL�X�T��
		treeNode* nodeE = B.Search(token_test1[j]);

		if (nodeE != NULL)
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> �i�H�bBST�����";
			countBST++;
		}
		else
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> �bBST���䤣��";
		}

		
		

		find = T.Search(rootTreap, token_test1[j]);
		if (find == NULL)
		{
			cout << "\t�bTREAP���䤣��" << endl;
		}
		else if (find->element == token_test1[j] && find != NULL)
		{
			cout << "\t�i�H�bTREAP�����" << endl;
			countTREAP++;
		}
		else
			cout << "\t�bTREAP���䤣��" << endl;

	}
	cout << "\n\n==================================�H�UŪ�JTestFile11==================================" << endl;
	double successBST = 100.0 * (double(countBST) / double(i));
	
	double successTREAP = 100.0 * (double(countTREAP) / double(i));
	cout << "\n�bBST���token�����\�v�G" << successBST << " %" << endl;
	cout << "\n�bTREAP���token�����\�v�G" << successTREAP << " %" << endl;

	
	i = 0;
	while (getline(TestFile12, data))
	{
		stringstream temp(data);	//�NŪ�J������Ʃ�btemp
		while (getline(temp, token_test2[i], ' '))
		{
			transform(token_test2[i].begin(), token_test2[i].end(), token_test2[i].begin(), tolower);
			i++;
		}
	}
	int countBST2 = 0;	//�Ψӭp�⦨�\��쪺token��
	int countSPT2 = 0;
	int countTREAP2 = 0;
	for (int j = 0; j < i; j++)
	{
		//�R��token�������I�Ÿ�
		token_test2[j].erase(
			remove_if(token_test2[j].begin(), token_test2[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test2[j].end());

		//�]�w���token�ɦL�X�T��
		treeNode* nodeE = B.Search(token_test2[j]);
		if (nodeE != NULL)
		{
			cout << setw(13) << token_test2[j] << setw(20) << "-> �i�H�bBST�����";
			countBST2++;
		}
		else
			cout << setw(13) << token_test2[j] << setw(20) << "-> �bBST���䤣��";

		

		find = T.Search(rootTreap, token_test2[j]);
		if (find == NULL)
		{
			cout << "\t�bTREAP���䤣��" << endl;
		}
		else if (find->element == token_test2[j] && find != NULL)
		{
			cout << "\t�i�H�bTREAP�����" << endl;
			countTREAP2++;
		}
		else
			cout << "\t�bTREAP���䤣��" << endl;

	}
	cout << "\n==================================�H�UŪ�JTestFile12==================================" << endl;
	double successBST2 = 100 * (double(countBST2) / double(i));
	double successSPT2 = 100 * (double(countSPT2) / double(i));
	double successTREAP2 = 100.0 * (double(countTREAP2) / double(i));
	cout << "\n�bBST���token�����\�v�G" << successBST2 << " %" << endl;
	
	cout << "\n�bTREAP���token�����\�v�G" << successTREAP2 << " %" << endl;

	
	i = 0;
	while (getline(TestFile13, data))
	{
		stringstream temp(data);	//�NŪ�J������Ʃ�btemp
		while (getline(temp, token_test3[i], ' '))
		{
			transform(token_test3[i].begin(), token_test3[i].end(), token_test3[i].begin(), tolower);
			i++;
		}
	}
	int countBST3 = 0;	//�Ψӭp�⦨�\��쪺token��
	int countSPT3 = 0;
	int countTREAP3 = 0;
	for (int j = 0; j < i; j++)
	{
		//�R��token�������I�Ÿ�
		token_test3[j].erase(
			remove_if(token_test3[j].begin(), token_test3[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test3[j].end());

		//�ˬd���S�����ƪ�token �٨S��

		//�]�w���token�ɦL�X�T��
		treeNode* nodeE = B.Search(token_test3[j]);

		if (nodeE != NULL)
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> �i�H�bBST�����";
			countBST3++;
		}
		else
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> �bBST���䤣��";
		}

		

		find = T.Search(rootTreap, token_test3[j]);
		if (find == NULL)
		{
			cout << "\t�bTREAP���䤣��" << endl;
		}
		else if (find->element == token_test3[j] && find != NULL)
		{
			cout << "\t�i�H�bTREAP�����" << endl;
			countTREAP3++;
		}
		else
			cout << "\t�bTREAP���䤣��" << endl;
	}
	cout << "\n==================================�H�UŪ�JTestFile13==================================" << endl;
	double successBST3 = 100.0 * (double(countBST3) / double(i));
	double successSPT3 = 100.0 * (double(countSPT3) / double(i));
	double successTREAP3 = 100.0 * (double(countTREAP3) / double(i));
	cout << "\n�bBST���token�����\�v�G" << successBST3 << " %" << endl;
	cout << "\n�bTREAP���token�����\�v�G" << successTREAP3 << " %" << endl;


	_LARGE_INTEGER Timestart, Timeend, Pintime;
	QueryPerformanceFrequency(&Pintime);
	//�H�U�B�z�ϥΪ̿�J������
	int selection = 0;      //�إߤ@���ܼƦs���ϥΪ̿�J��
	do {
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
			node = B.Search(user_token);				 // ���d�ߦ�key�ȬO�_�w�s�bBST��	 
			if (node != NULL)                            //�Y�w�s�b�A�h��X�T��
				cout << "��token�Ȥw�s�b��BST�� ";
			else
			{
				cout << "���\�s�W��BST" << endl;
				B.InsertBST(user_token);
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�s�W��BST��O���ɶ��G " << time << "ms" << endl;
			

			QueryPerformanceCounter(&Timestart);
			find = T.Search(rootTreap, user_token);
			if (find == NULL)
			{
				cout << "���\�s�W��TREAP" << endl;
				rootTreap = T.InsertTREAP(rootTreap, user_token);
			}
			else if (find->element == user_token)
			{
				cout << user_token << "�w�s�b��TREAP��" << endl;
			}
			QueryPerformanceCounter(&Timeend);
			time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�s�W��TREAP��O���ɶ��G " << time << "ms" << endl;
			
			cout << "\n���ǵ��G: \n" << "===BST===" << endl;                   //��X���Ǫ�ܦ�           
			B.InorderPrint();
			
			cout << "\n===TREAP===" << endl;
			T.Inorder(rootTreap);
			cout << endl;
		}
		else if (selection == 2)  //�R��key
		{
			cout << "\n��J���R����token��: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//�ন�p�g

			QueryPerformanceCounter(&Timestart);
			node = B.Search(user_token);				 // ���d�ߦ�key�ȬO�_�w�s�bBST��
			if (node == NULL)                            //�Y�w�s�b�A�h��X�T��
				cout << "\n��token�Ȥ��s�b��BST�� ";
			else
			{
				B.DeleteBST(user_token);
				cout << "\n�qBST�R�����\" << endl;

				cout << "\n�R��" << user_token << "�᪺BST���ǵ��G�G\n" << endl;                  //��X���Ǫ�ܦ�           
				B.InorderPrint();
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�qBST�R���ηj�M��O���ɶ��G " << time << "ms" << endl;

			

			QueryPerformanceCounter(&Timestart);
			find = T.Search(rootTreap, user_token);
			if (find == NULL)
				cout << "\n��token�Ȥ��s�b��TREAP�� ";
			else if (find->element == user_token)
			{
				rootTreap = T.DeleteTREAP(rootTreap, user_token);
				cout << "\n�qTREAP�R�����\" << endl;

				cout << "\n�R��" << user_token << "�᪺TREAP���ǵ��G�G\n" << endl;
				T.Inorder(rootTreap);
			}
			QueryPerformanceCounter(&Timeend);
			time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�qTREAP�R���ηj�M��O���ɶ��G " << time << "ms" << endl;
		}
		else if (selection == 3)   //�d��key
		{
			cout << "�п�J���d�䪺���: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//�ন�p�g

			QueryPerformanceCounter(&Timestart);
			node = B.Search(user_token);	// ���d�ߦ�key�ȬO�_�w�s�bBST��
			if (node == NULL)                            //�Y�w�s�b�A�h��X�T��
				cout << "\n" << user_token << "���s�b��BST��" << endl;
			else
				cout << "\n" << node->element << "�s�b��BST��" << endl;
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�bBST�j�M��O���ɶ��G " << time << "ms" << endl;
			

			

			QueryPerformanceCounter(&Timestart);
			find = T.Search(rootTreap, user_token);
			if (find == NULL)
			{
				cout << user_token << "���s�b��TREAP��" << endl;
			}
			else if (find->element == user_token && find != NULL)
			{
				cout << user_token << "�s�b��TREAP��" << endl;
			}
			else
				cout << user_token << "�bTREAP���䤣��" << endl;
			QueryPerformanceCounter(&Timeend);
			time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�bTREAP�j�M��O���ɶ��G " << time << "ms" << endl;
		}
	} while (selection != 4);   //��J4�H�����j��

	TestFile1.close();
	TestFile11.close();
	TestFile12.close();
	TestFile13.close();
	system("PAUSE");
	return (0);
}
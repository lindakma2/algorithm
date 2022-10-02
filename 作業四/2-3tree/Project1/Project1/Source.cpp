#include <iostream>
#include <stack>
#include <string>
#include <fstream>	  //�}���ɸ�Ƭy
#include <cctype>     //�Ω�R��token�����Ÿ�
#include <algorithm>  //�Ω�R��token�����Ÿ�
#include <iomanip>	  //�Ψ�����X�r�ꪺsetw()
#include <sstream>	  //�Ω�Ū�ɮɪ�stringstream
#include <ctime>	  //�Ω��H������priority����
#include <Windows.h>

using namespace std;

typedef struct Tree23Node* Tree23;

typedef struct Tree23Node {
	string datal;
	string datar;
	Tree23 lchild, mchild, rchild;
} Tree23Node;

#define  INT_MAX "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"
int dicnodenum = 1; //dictionrary token amount

stack<Tree23> s;

int compare(string x, Tree23 t)
{
	if (x < t->datal)
		return 1;
	else if (x > t->datar)
		return 3;
	else if (x < t->datar && x > t->datal)
		return 2;
	else
		return 4;
}

Tree23 createNode(string key)
{
	Tree23 t = new Tree23Node;
	t->datal = key;
	t->datar = INT_MAX;
	t->lchild = t->mchild = t->rchild = NULL;
	return t;
}
void newRoot(Tree23* root, string key, Tree23 midSub)
{
	Tree23 t = createNode(key);
	t->lchild = *root;
	t->mchild = midSub;
	*root = t;
}

bool isleaf(Tree23 root)
{
	if (root && root->datal < INT_MAX && root->lchild == NULL &&
		root->mchild == NULL && root->rchild == NULL)
		return true;
	return false;
}

Tree23 findNode(Tree23 root, string key)
{
	Tree23 t = NULL;
	while (root) {
		if (!isleaf(root))
			s.push(root);
		if (isleaf(root))
			t = root;
		switch (compare(key, root)) {
		case 1:	root = root->lchild;
			break;
		case 2:	root = root->mchild;
			break;
		case 3: root = root->rchild;
			break;
		case 4: return NULL;
			
		}
	}
	return t;
}

void put(Tree23* root, string key, Tree23 q)
{
	if (key < (*root)->datal) {
		(*root)->datar = (*root)->datal;
		(*root)->datal = key;
		(*root)->rchild = (*root)->mchild;
		(*root)->mchild = q;
	}
	else {
		(*root)->datar = key;
		(*root)->rchild = q;
	}
}

void split(Tree23 p, string* key, Tree23* q)
{
	Tree23 t = createNode(INT_MAX);

	if (*key < p->datal) {
		t->datal = p->datar;
		/*swap *key and p->datal */
		p->datar = *key;
		*key = p->datal;
		p->datal = p->datar;
		/* set p->datar to non sense */
		p->datar = INT_MAX;
	}
	else if (*key > p->datar) {
		t->datal = *key;
		*key = p->datar;
		p->datar = INT_MAX;
	}
	else {
		t->datal = p->datar;
		p->datar = INT_MAX;
	}
	t->lchild = p->rchild;
	p->rchild = NULL;
	t->mchild = *q;
	*q = t;
}

Tree23 del()
{
	if (!s.empty()) {
		Tree23 t = s.top();
		s.pop();
		return t;
	}
	return NULL;
}

void insert23(Tree23* root, string key)
{
	Tree23 p, q, temp;

	if (*root == NULL) {
		/* tree is empty */
		newRoot(root, key, NULL);
	}
	else {
		/* insert into an empty tree */
		p = findNode(*root, key);
		if (p == NULL) {
			//cout << "The key is currently in the tree." << endl;
			return;
		}
		else
		{
			dicnodenum++;
		}
		q = NULL;
		for (;;) {
			if (p->datar == INT_MAX) {
				/* two sub node */
				put(&p, key, q);
				break;
			}
			else {
				/* three sub node */
				split(p, &key, &q);
				if (p == *root) {
					/* split the root */
					newRoot(root, key, q);
					break;
				}
				else
					/* remove a node from stack */
					p = del();
			}
		}
	}
}

void visit(Tree23 T)
{
	if (T->datar < INT_MAX) {
		cout << "(" << T->datal << "," << T->datar << ") ";
	}
	else if (T->datal < INT_MAX) {
		cout << "(" << T->datal << ",) ";
	}
	else cout << "(,) ";
}
void inOrder(Tree23 T)
{
	if (T)
	{
		visit(T);
		//cout<<endl;
		if (T->lchild == NULL)
			return;
		cout << "(";
		inOrder(T->lchild);
		cout << ",";
		inOrder(T->mchild);
		cout << ",";
		inOrder(T->rchild);
		cout << ")";
	}

}

Tree23 search23(Tree23 root, string key)
{
	while (root) {
		s.push(root);
		switch (compare(key, root)) {
		case 1:	root = root->lchild;
			break;
		case 2: root = root->mchild;
			break;
		case 3: root = root->rchild;
			break;
		case 4: return root;
		}
	}
	return NULL;
}
Tree23 min23(Tree23 root)
{
	while (root->lchild) {
		s.push(root);
		root = root->lchild;
	}
	s.push(root);
	return root;
}

void deletex(Tree23 t, string key)
{
	/* delete key from node t */
	if (key == t->datal) {
		/* delete first key */
		if (t->datar < INT_MAX) {
			/* three sub node*/
			t->datal = t->datar;
			t->datar = INT_MAX;
		}
		else
			/* two sub node */
			t->datal = INT_MAX;
	}
	else
		/* delete second key */
		t->datar = INT_MAX;
}

void leftRotate(Tree23& p, Tree23& q, Tree23& r)
{
	p->datal = r->datal;
	r->datal = q->datal;
	q->datal = q->datar;
	q->datar = INT_MAX;

	p->mchild = q->lchild;
	q->lchild = q->mchild;
	q->mchild = q->rchild;
	q->rchild = NULL;
}

void leftCombine(Tree23& p, Tree23& q, Tree23& r)
{
	p->datal = r->datal;
	p->datar = q->datal;
	p->mchild = q->lchild;
	p->rchild = q->mchild;
	delete q;
	if (r->datar == INT_MAX) {
		/* r is two sub node*/
		r->datal = INT_MAX;
		r->mchild = NULL;
	}
	else {
		r->datal = r->datar;
		r->datar = INT_MAX;
		r->mchild = r->rchild;
		r->rchild = NULL;
	}
}


void middleRotate(Tree23& p, Tree23& q, Tree23& r)
{
	p->datal = r->datal;
	r->datal = q->datar;
	q->datar = INT_MAX;
	p->mchild = q->rchild;
	q->rchild = NULL;
}

void middleCombine(Tree23& p, Tree23& q, Tree23& r)
{
	q->datar = r->datal;
	q->rchild = p->lchild;
	delete p;
	if (r->datar < INT_MAX) {
		r->datal = r->datar;
		r->datar = INT_MAX;
		r->mchild = r->rchild;
		r->rchild = NULL;
	}
	else {
		r->datal = INT_MAX;
		r->mchild = NULL;
	}

}

void rightRotate(Tree23& p, Tree23& q, Tree23& r)
{
	p->datal = r->datar;
	r->datar = q->datar;
	q->datar = INT_MAX;
	p->mchild = q->rchild;
	q->rchild = NULL;
}

void rightCombine(Tree23& p, Tree23& q, Tree23& r)
{
	q->datar = r->datar;
	r->datar = INT_MAX;
	q->rchild = p->lchild;
	delete p;
	r->rchild = NULL;
}
bool delete23(Tree23* root, string key)
{
	Tree23 t = search23(*root, key);
	Tree23 p;
	Tree23 r;
	Tree23 q = NULL;
	if (t == NULL)
		return false;
	else {
		if (!isleaf(t)) {
			if (t->datal == key) {
				p = min23(t->mchild);
				t->datal = p->datal;
				key = p->datal;
			}
			else {
				p = min23(t->rchild);
				t->datar = p->datal;
				key = p->datal;
			}

		}
		else
			p = t;

		deletex(p, key);
		del();
		for (;;) {
			if (p->datal == INT_MAX && p->datar == INT_MAX) {
				r = del();
				if (r == NULL)
					break;
				if (r->lchild == p) {
					/* */
					q = r->mchild;
					if (q->datar < INT_MAX) {
						/* rotate when p is the left child of r */
						leftRotate(p, q, r);
					}
					else {
						/* combine when p is the left child of r*/
						leftCombine(p, q, r);
					}
				}
				else if (r->mchild == p) {
					q = r->lchild;
					if (q->datar < INT_MAX) {
						middleRotate(p, q, r);
					}
					else {
						middleCombine(p, q, r);
					}

				}
				else {
					q = r->mchild;
					if (q->datar < INT_MAX) {
						rightRotate(p, q, r);
					}
					else {
						rightCombine(p, q, r);
					}
				}
				p = r;
			}
			else
				break;

		}
		if (p->datal == INT_MAX) {
			*root = p->lchild;
			delete p;
		}

	}

}


int main()
{
	Tree23 tree=NULL;

	ifstream TestFile1, TestFile11, TestFile12, TestFile13;
	string data; //read a sentence will be cut into token
	TestFile1.open("TestFile3.txt");
	TestFile11.open("TestFile11.txt");
	TestFile12.open("TestFile12.txt");
	TestFile13.open("TestFile13.txt");

	int tokennum = 0; //token amount
	
	string token[1000];
	string token_test1[1000];
	string token_test2[1000];	//�qTestFile12.txt��J��token
	string token_test3[1000];
	string user_token;//input string by user for insert,delete,search
	Tree23 node;
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
		token[j].erase(remove_if(token[j].begin(), token[j].end(), static_cast<int(*)(int)>(&ispunct)),token[j].end());
		insert23(&tree, token[j]);
		cout << token[j] << " ";
	}
	end = clock();
	cout << "\n���J23tree�᪺�ɶ�: " << end - start << endl;
	//cout << "\n�q�ɮפ�Ū���쪺token�ƶq" << tokennum << endl;
	//cout << "\n�h�����ƪ���r��Adictionary����token�ƶq" << dicnodenum << endl;

	cout << "\n==========23tree��inorder trasversal==========" << endl;
	inOrder(tree);
	cout << endl;

	

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
	int counttree23 = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//�R��token�������I�Ÿ�
		token_test1[j].erase(
			remove_if(token_test1[j].begin(), token_test1[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test1[j].end());

		//�]�w���token�ɦL�X�T��
		
		Tree23 nodeE = search23(tree, token_test1[j]);


		if (nodeE != NULL)
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> �i�H�b23tree�����"<<endl;
			counttree23++;
		}
		else
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> �b23tree���䤣��"<<endl;
		}

	}
	double successtree23 = 100.0 * (double(counttree23) / double(tokennum));
	cout << "\n�b23tree���token�����\�v�G" << successtree23 << " %" << endl;

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
	counttree23 = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//�R��token�������I�Ÿ�
		token_test2[j].erase(
			remove_if(token_test2[j].begin(), token_test2[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test2[j].end());

		//�]�w���token�ɦL�X�T��

		Tree23 nodeE = search23(tree, token_test2[j]);


		if (nodeE != NULL)
		{
			cout << setw(13) << token_test2[j] << setw(20) << "-> �i�H�b23tree�����" << endl;
			counttree23++;
		}
		else
		{
			cout << setw(13) << token_test2[j] << setw(20) << "-> �b23tree���䤣��" << endl;
		}

	}
	successtree23 = 100.0 * (double(counttree23) / double(tokennum));
	cout << "\n�b23tree���token�����\�v�G" << successtree23 << " %" << endl;

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
	counttree23 = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//�R��token�������I�Ÿ�
		token_test3[j].erase(
			remove_if(token_test3[j].begin(), token_test3[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test3[j].end());

		//�]�w���token�ɦL�X�T��

		Tree23 nodeE = search23(tree, token_test3[j]);


		if (nodeE != NULL)
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> �i�H�b23tree�����" << endl;
			counttree23++;
		}
		else
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> �b23tree���䤣��" << endl;
		}

	}
	successtree23 = 100.0 * (double(counttree23) / double(tokennum));
	cout << "\n�b23tree���token�����\�v�G" << successtree23 << " %" << endl;
	//�H�U�B�z�ϥΪ̿�J������
	int selection = 0;      //�إߤ@���ܼƦs���ϥΪ̿�J��

	_LARGE_INTEGER Timestart, Timeend, Pintime;
	QueryPerformanceFrequency(&Pintime);
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
			
			node = search23(tree, user_token);			 // ���d�ߦ�key�ȬO�_�w�s�bBST��	 
			if (node != NULL)                            //�Y�w�s�b�A�h��X�T��
				cout << "��token�Ȥw�s�b��23tree�� ";
			else
			{
				cout << "���\�s�W��23tree" << endl;
				insert23(&tree, user_token);
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�s�W��23tree��O���ɶ��G " << time << "ms" << endl;



			cout << "\n���ǵ��G: \n" << "===23tree===" << endl;                   //��X���Ǫ�ܦ�           
			inOrder(tree);

		}
		else if (selection == 2)  //�R��key
		{
			cout << "\n��J���R����token��: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//�ন�p�g
			QueryPerformanceCounter(&Timestart);

			node = search23(tree, user_token);				 // ���d�ߦ�key�ȬO�_�w�s�bBST��
			if (node == NULL)                            //�Y�w�s�b�A�h��X�T��
				cout << "\n��token�Ȥ��s�b��23tree�� ";
			else
			{
				delete23(&tree, user_token);
				cout << "\n�q23tree�R�����\" << endl;

				cout << "\n�R��" << user_token << "�᪺23tree���ǵ��G�G\n" << endl;                  //��X���Ǫ�ܦ�           
				inOrder(tree);
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�q23tree�R���ηj�M��O���ɶ��G " << time << "ms" << endl;


		}
		else if (selection == 3)   //�d��key
		{
			cout << "�п�J���d�䪺���: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//�ন�p�g

			QueryPerformanceCounter(&Timestart);
			node = search23(tree, user_token);		// ���d�ߦ�key�ȬO�_�w�s�bBST��
			if (node == NULL)                            //�Y�w�s�b�A�h��X�T��
				cout << "\n" << user_token << "���s�b��23tree��" << endl;
			else
				cout << "\n" << user_token << "�s�b��23tree��" << endl;
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�b23tree�j�M��O���ɶ��G " << time << "ms" << endl;
		}
	} while (selection != 4);   //��J4�H�����j��

	TestFile1.close();
	TestFile11.close();
	system("PAUSE");
	return (0);
}

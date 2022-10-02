#include <iostream>
#include <stack>
#include <string>
#include <fstream>	  //開關檔資料流
#include <cctype>     //用於刪除token中的符號
#include <algorithm>  //用於刪除token中的符號
#include <iomanip>	  //用到對齊輸出字串的setw()
#include <sstream>	  //用於讀檔時的stringstream
#include <ctime>	  //用於隨機產生priority的值
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
	string token_test2[1000];	//從TestFile12.txt放入的token
	string token_test3[1000];
	string user_token;//input string by user for insert,delete,search
	Tree23 node;
	clock_t start, end;


	//distionary
	int count = 0;
	while (getline(TestFile1, data))
	{
		stringstream temp(data);				//將讀入的整行資料放在temp
		while (getline(temp, token[tokennum], ' '))	//將該行資料切割到token中
		{
			transform(token[tokennum].begin(), token[tokennum].end(), token[tokennum].begin(), tolower); //all change to little write
			tokennum++;
		}
		count++;
	}

	
	cout << "從檔案中讀取到的token ：\n";
	start = clock();

	for (int j = 0; j < tokennum; j++)
	{
		//刪除token中的標點符號
		token[j].erase(remove_if(token[j].begin(), token[j].end(), static_cast<int(*)(int)>(&ispunct)),token[j].end());
		insert23(&tree, token[j]);
		cout << token[j] << " ";
	}
	end = clock();
	cout << "\n插入23tree花的時間: " << end - start << endl;
	//cout << "\n從檔案中讀取到的token數量" << tokennum << endl;
	//cout << "\n去除重複的單字後，dictionary中的token數量" << dicnodenum << endl;

	cout << "\n==========23tree的inorder trasversal==========" << endl;
	inOrder(tree);
	cout << endl;

	

	//teatfile1
	tokennum = 0;
	while (getline(TestFile11, data))
	{
		stringstream temp(data);	//將讀入的整行資料放在temp
		while (getline(temp, token_test1[tokennum], ' '))
		{
			transform(token_test1[tokennum].begin(), token_test1[tokennum].end(), token_test1[tokennum].begin(), tolower);
			tokennum++;
		}
	}
	//用來計算成功找到的token數
	int counttree23 = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//刪除token中的標點符號
		token_test1[j].erase(
			remove_if(token_test1[j].begin(), token_test1[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test1[j].end());

		//設定找到token時印出訊息
		
		Tree23 nodeE = search23(tree, token_test1[j]);


		if (nodeE != NULL)
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> 可以在23tree中找到"<<endl;
			counttree23++;
		}
		else
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> 在23tree中找不到"<<endl;
		}

	}
	double successtree23 = 100.0 * (double(counttree23) / double(tokennum));
	cout << "\n在23tree找到token的成功率：" << successtree23 << " %" << endl;

	//teatfile2
	tokennum = 0;
	while (getline(TestFile12, data))
	{
		stringstream temp(data);	//將讀入的整行資料放在temp
		while (getline(temp, token_test2[tokennum], ' '))
		{
			transform(token_test2[tokennum].begin(), token_test2[tokennum].end(), token_test2[tokennum].begin(), tolower);
			tokennum++;
		}
	}
	//用來計算成功找到的token數
	counttree23 = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//刪除token中的標點符號
		token_test2[j].erase(
			remove_if(token_test2[j].begin(), token_test2[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test2[j].end());

		//設定找到token時印出訊息

		Tree23 nodeE = search23(tree, token_test2[j]);


		if (nodeE != NULL)
		{
			cout << setw(13) << token_test2[j] << setw(20) << "-> 可以在23tree中找到" << endl;
			counttree23++;
		}
		else
		{
			cout << setw(13) << token_test2[j] << setw(20) << "-> 在23tree中找不到" << endl;
		}

	}
	successtree23 = 100.0 * (double(counttree23) / double(tokennum));
	cout << "\n在23tree找到token的成功率：" << successtree23 << " %" << endl;

	//teatfile3
	tokennum = 0;
	while (getline(TestFile13, data))
	{
		stringstream temp(data);	//將讀入的整行資料放在temp
		while (getline(temp, token_test3[tokennum], ' '))
		{
			transform(token_test3[tokennum].begin(), token_test3[tokennum].end(), token_test3[tokennum].begin(), tolower);
			tokennum++;
		}
	}
	//用來計算成功找到的token數
	counttree23 = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//刪除token中的標點符號
		token_test3[j].erase(
			remove_if(token_test3[j].begin(), token_test3[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test3[j].end());

		//設定找到token時印出訊息

		Tree23 nodeE = search23(tree, token_test3[j]);


		if (nodeE != NULL)
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> 可以在23tree中找到" << endl;
			counttree23++;
		}
		else
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> 在23tree中找不到" << endl;
		}

	}
	successtree23 = 100.0 * (double(counttree23) / double(tokennum));
	cout << "\n在23tree找到token的成功率：" << successtree23 << " %" << endl;
	//以下處理使用者輸入的部分
	int selection = 0;      //建立一個變數存取使用者輸入值

	_LARGE_INTEGER Timestart, Timeend, Pintime;
	QueryPerformanceFrequency(&Pintime);
	do
	{
		cout << "\n=======================" << endl;        //告知使用功能
		cout << "\n請選擇需要執行的動作(由輸入題號數字執行)" << endl;
		cout << "\n(1)插入資料(Insert the token)" << endl
			<< "(2)刪除資料(Delete the token)" << endl
			<< "(3)找出某筆資料(Find the token)" << endl
			<< "(4)結束(Exit)" << endl;

		cout << ">>";
		cin >> selection;
		if (cin.fail())		//限制使用者輸入為數字，否則結束程式
		{
			cout << "您輸入的不是數字" << endl;
			break;
		}

		//限制使用者輸入值必須介於1到4之間
		while (selection > 4 || selection < 1)
		{
			cout << "非範圍值 請重新輸入(1~4)" << endl;
			cin >> selection;
		}

		//對使用者輸入的值做判斷
		if (selection == 1)     //插入key值
		{
			cout << "\n請輸入欲新增的token值: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//轉成小寫
			QueryPerformanceCounter(&Timestart);
			
			node = search23(tree, user_token);			 // 先查詢此key值是否已存在BST中	 
			if (node != NULL)                            //若已存在，則輸出訊息
				cout << "此token值已存在於23tree中 ";
			else
			{
				cout << "成功新增到23tree" << endl;
				insert23(&tree, user_token);
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n新增到23tree花費的時間： " << time << "ms" << endl;



			cout << "\n中序結果: \n" << "===23tree===" << endl;                   //輸出中序表示式           
			inOrder(tree);

		}
		else if (selection == 2)  //刪除key
		{
			cout << "\n輸入欲刪除的token值: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//轉成小寫
			QueryPerformanceCounter(&Timestart);

			node = search23(tree, user_token);				 // 先查詢此key值是否已存在BST中
			if (node == NULL)                            //若已存在，則輸出訊息
				cout << "\n此token值不存在於23tree中 ";
			else
			{
				delete23(&tree, user_token);
				cout << "\n從23tree刪除成功" << endl;

				cout << "\n刪除" << user_token << "後的23tree中序結果：\n" << endl;                  //輸出中序表示式           
				inOrder(tree);
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n從23tree刪除或搜尋花費的時間： " << time << "ms" << endl;


		}
		else if (selection == 3)   //查詢key
		{
			cout << "請輸入欲查找的資料: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//轉成小寫

			QueryPerformanceCounter(&Timestart);
			node = search23(tree, user_token);		// 先查詢此key值是否已存在BST中
			if (node == NULL)                            //若已存在，則輸出訊息
				cout << "\n" << user_token << "不存在於23tree中" << endl;
			else
				cout << "\n" << user_token << "存在於23tree中" << endl;
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n在23tree搜尋花費的時間： " << time << "ms" << endl;
		}
	} while (selection != 4);   //輸入4以結束迴圈

	TestFile1.close();
	TestFile11.close();
	system("PAUSE");
	return (0);
}

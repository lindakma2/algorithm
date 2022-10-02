#include <iostream>
#include <string>
#include <fstream>	  //開關檔資料流
#include <cctype>     //用於刪除token中的符號
#include <algorithm>  //用於刪除token中的符號
#include <iomanip>	  //用到對齊輸出字串的setw()
#include <sstream>	  //用於讀檔時的stringstream
#include <ctime>	  //用於隨機產生priority的值
#include <Windows.h>

using namespace std;


//下兩個class：treeNode、BST ，定義了二元搜尋樹所需的函式以及變數 
class treeNode {
public:
	treeNode* leftchild;	//左子樹
	treeNode* rightchild;	//右子樹
	treeNode* parent;		//父節點
	string element;			//該node的內容 因為是字串，用string型別
	//int key;

	treeNode() :leftchild(0), rightchild(0), parent(0), element("") {};
	treeNode(string b) :leftchild(0), rightchild(0), parent(0), element(b) {};

	//int GetKey() { return key; }              // 為了在main()要能夠檢視node是否正確
	//string GetElement() { return element; }   // 才需要這兩個member function讀取private data

	// 其餘情況, 因為class BST是class TreeNode的friend class
	// 在class BST的member function中, 可以直接存取class TreeNode的private data
	friend class BST;   // 放在 private 或 public 都可以 
};

class BST {
public:
	BST() :root(0) {};

	treeNode* Search(string element);
	void InsertBST(string element);
	void InorderPrint();        // 可以用來確認BST是否建立成功
	void DeleteBST(string element);
private:
	treeNode* root;
	treeNode* Leftmost(treeNode* current);
	treeNode* Successor(treeNode* current);
};

//下兩個class：splayNode、SPT ，定義了splay tree所需的函式以及變數
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

//下兩個class：treapNode、TREAP ，定義了treap所需的函式以及變數
class treapNode {
public:
	int priority;			//用於建立minheap的標準
	string element;			//字串
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

//二元搜尋樹的search
treeNode* BST::Search(string element) {

	treeNode* current = root;               // 將curent指向root作為traversal起點

	while (current != NULL && element != current->element) {  // 兩種情況跳出迴圈：
													  // 1.沒找到 2.有找到
		if (element < current->element)
		{
			current = current->leftchild;   // 向左走
		}
		else
		{
			current = current->rightchild;  // 向右走
		}
	}
	return current;
}

//二元搜尋樹的插入
void BST::InsertBST(string element) {

	treeNode* y = 0;        // 準新手爸媽
	treeNode* x = 0;        // 哨兵
	treeNode* insert_node = new treeNode(element);   // insert_node為將要新增的node

	x = root;
	while (x != NULL) {                 // 在while中, 以如同Search()的方式尋找適當的位置       
		y = x;                          // y先更新到原來x的位置
		/*
		if (insert_node->key < x->key) { // 判斷x是要往left- 還是right- 前進
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
		{ // 判斷x是要往left- 還是right- 前進
			x = x->leftchild;
		}
		else if (insert_node->element > x->element)
		{
			x = x->rightchild;
		}

	}                        // 跳出迴圈後, x即為NULL


										// y即為insert_node的parent
	insert_node->parent = y;            // 將insert_node的parent pointer指向y

	if (y == NULL) {                     // 下面一組if-else, 把insert_node接上BST
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

//使用inorder輸出
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

	// 利用兩個pointer: successor與current做traversal 

	treeNode* successor = current->parent;
	while (successor != NULL && current == successor->rightchild) {
		current = successor;
		successor = successor->parent;
	}
	return successor;
}

void BST::DeleteBST(string element) {               // 要刪除具有KEY的node

	treeNode* delete_node = Search(element);    // 先確認BST中是否有具有KEY的node
	if (delete_node == NULL) {
		std::cout << "data not found.\n";
		//return;
	}

	treeNode* y = 0;      // 真正要被刪除並釋放記憶體的node
	treeNode* x = 0;      // 要被刪除的node的"child"

	if (delete_node->leftchild == NULL || delete_node->rightchild == NULL) {
		y = delete_node;
	}
	else {
		y = Successor(delete_node);        // 將y設成delete_node的Successor
	}                                      // 經過這組if-else, y調整成至多只有一個child
										   // 全部調整成case1或case2來處理
	if (y->leftchild != NULL) {
		x = y->leftchild;                  // 將x設成y的child, 可能是有效記憶體,
	}                                      // 也有可能是NULL
	else {
		x = y->rightchild;
	}

	if (x != NULL) {                        // 在y被刪除之前, 這個步驟把x接回BST
		x->parent = y->parent;             // 此即為圖二(c)中, 把基紐接回龜仙人的步驟
	}
	// 接著再把要被釋放記憶體的node之"parent"指向新的child
	if (y->parent == NULL) {                // 若刪除的是原先的root, 就把x當成新的root 
		this->root = x;
	}
	else if (y == y->parent->leftchild) {    // 若y原本是其parent之left child
		y->parent->leftchild = x;           // 便把x皆在y的parent的left child, 取代y
	}
	else {                                   // 若y原本是其parent之right child
		y->parent->rightchild = x;          // 便把x皆在y的parent的right child, 取代y
	}
	// 針對case3
	if (y != delete_node) {                 // 若y是delete_node的替身, 最後要再將y的資料
		//delete_node->key = y->key;          // 放回delete_node的記憶體位置, 並將y的記憶體位置釋放
		delete_node->element = y->element;  // 圖二(d), y即是達爾, delete_node即是西魯
	}

	delete y;                               // 將y的記憶體位置釋放
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
	node->priority = rand() % 100;		//多一項隨機賦值的優先權
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
			current = current->leftchild;   // 向左走
		}
		else
		{
			current = current->rightchild;  // 向右走
		}
	}
	return current;
}

treapNode* TREAP::InsertTREAP(treapNode* root, string element)
{
	if (!root)	//當root是null時，create一個新的node
	{
		return newElement(element);
	}

	if (element > root->element) //插入值大於當前的root 往右邊走
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

		if (root->priority > root->leftchild->priority)	//需要符合min
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
		Inorder(root->leftchild);	//左
		cout << setw(5) << "token: " << setw(10) << root->element << " priority = " << setw(5) << root->priority;
		if (root->leftchild)
			cout << setw(20) << "\t -> left child: " << root->leftchild->element
			<< " priority = " << setw(5) << root->priority;
		if (root->rightchild)
			cout << setw(20) << "\t -> right child: " << root->rightchild->element
			<< " priority = " << setw(5) << root->priority;
		cout << "\n";
		Inorder(root->rightchild);	//右
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
	rootTreap = NULL;			//先預設treap的root是null 因為原本是空的tree
	treapNode* find;

	ifstream TestFile1, TestFile11, TestFile12, TestFile13;	//檔案指針
	string data;								//將檔案讀到的整行資料暫時放入data字串
	TestFile1.open("TestFile3.txt");
	TestFile11.open("TestFile11.txt");
	TestFile12.open("TestFile12.txt");
	TestFile13.open("TestFile13.txt");

	if (!(TestFile1 || TestFile11 || TestFile12))//檔案錯誤訊息
		cout << "檔案無法開啟" << endl;

	int i = 0;					//計算從檔案中讀取到的token數量
	int nodeNum = 0;			//計算字典的token數量
	string token[1000];			//準備放入BST的token
	string token_test1[1000];	//從TestFile11.txt放入的token
	string token_test2[1000];	//從TestFile12.txt放入的token
	string token_test3[1000];	//從TestFile13.txt放入的token
	string user_token;			//從command line輸入的token 可做搜尋 刪除 新增
	treeNode* node;
	clock_t start, end;							//建立clock_t變數(長整數形態)以記錄時間，以毫秒為單位
	while (getline(TestFile1, data))
	{
		stringstream temp(data);				//將讀入的整行資料放在temp
		while (getline(temp, token[i], ' '))	//將該行資料切割到token中
		{
			transform(token[i].begin(), token[i].end(), token[i].begin(), tolower);
			i++;
		}
	}
	cout << "從檔案中讀取到的token ：\n";
	start = clock();
	for (int j = 0; j < i; j++)
	{
		//刪除token中的標點符號
		token[j].erase(
			remove_if(token[j].begin(), token[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token[j].end());

		cout << token[j];
		node = B.Search(token[j]);				// 先查詢此key值是否已存在BST中
		if (!node)								//插入BST
		{
			
			B.InsertBST(token[j]);
			nodeNum++;
		}
		//cout << token[j] << endl;
	}
	end = clock();
	cout << "\n插入BST花的時間: " << end - start << endl;
	//cout << "\n從檔案中讀取到的token數量" << i << endl;
	//cout << "\n去除重複的單字後，dictionary中的token數量" << nodeNum << endl;

	start = 0; end = 0;
	for (int j = 0; j < i; j++)
	{
		//刪除token中的標點符號
		token[j].erase(
			remove_if(token[j].begin(), token[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token[j].end());

		rootTreap = T.InsertTREAP(rootTreap, token[j]);//插入TREAP
	}
	end = clock();
	cout << "\n插入TREAP花的時間 " << end - start << endl;


	//cout << "\n從檔案中讀取到的token數量" << i << endl;
	//cout << "\n去除重複的單字後，dictionary中的token數量" << nodeNum << endl;
	
	cout << "\n==========BST的inorder trasversal==========" << endl;
	B.InorderPrint();
	cout << "\n==========TREAP的inorder trasversal==========" << endl;
	T.Inorder(rootTreap);

	
	i = 0;
	while (getline(TestFile11, data))
	{
		stringstream temp(data);	//將讀入的整行資料放在temp
		while (getline(temp, token_test1[i], ' '))
		{
			transform(token_test1[i].begin(), token_test1[i].end(), token_test1[i].begin(), tolower);
			i++;
		}
	}
	int countBST = 0;	//用來計算成功找到的token數
	int countSPT = 0;
	int countTREAP = 0;
	for (int j = 0; j < i; j++)
	{
		//刪除token中的標點符號
		token_test1[j].erase(
			remove_if(token_test1[j].begin(), token_test1[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test1[j].end());

		//設定找到token時印出訊息
		treeNode* nodeE = B.Search(token_test1[j]);

		if (nodeE != NULL)
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> 可以在BST中找到";
			countBST++;
		}
		else
		{
			cout << setw(13) << token_test1[j] << setw(20) << "-> 在BST中找不到";
		}

		
		

		find = T.Search(rootTreap, token_test1[j]);
		if (find == NULL)
		{
			cout << "\t在TREAP中找不到" << endl;
		}
		else if (find->element == token_test1[j] && find != NULL)
		{
			cout << "\t可以在TREAP中找到" << endl;
			countTREAP++;
		}
		else
			cout << "\t在TREAP中找不到" << endl;

	}
	cout << "\n\n==================================以下讀入TestFile11==================================" << endl;
	double successBST = 100.0 * (double(countBST) / double(i));
	
	double successTREAP = 100.0 * (double(countTREAP) / double(i));
	cout << "\n在BST找到token的成功率：" << successBST << " %" << endl;
	cout << "\n在TREAP找到token的成功率：" << successTREAP << " %" << endl;

	
	i = 0;
	while (getline(TestFile12, data))
	{
		stringstream temp(data);	//將讀入的整行資料放在temp
		while (getline(temp, token_test2[i], ' '))
		{
			transform(token_test2[i].begin(), token_test2[i].end(), token_test2[i].begin(), tolower);
			i++;
		}
	}
	int countBST2 = 0;	//用來計算成功找到的token數
	int countSPT2 = 0;
	int countTREAP2 = 0;
	for (int j = 0; j < i; j++)
	{
		//刪除token中的標點符號
		token_test2[j].erase(
			remove_if(token_test2[j].begin(), token_test2[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test2[j].end());

		//設定找到token時印出訊息
		treeNode* nodeE = B.Search(token_test2[j]);
		if (nodeE != NULL)
		{
			cout << setw(13) << token_test2[j] << setw(20) << "-> 可以在BST中找到";
			countBST2++;
		}
		else
			cout << setw(13) << token_test2[j] << setw(20) << "-> 在BST中找不到";

		

		find = T.Search(rootTreap, token_test2[j]);
		if (find == NULL)
		{
			cout << "\t在TREAP中找不到" << endl;
		}
		else if (find->element == token_test2[j] && find != NULL)
		{
			cout << "\t可以在TREAP中找到" << endl;
			countTREAP2++;
		}
		else
			cout << "\t在TREAP中找不到" << endl;

	}
	cout << "\n==================================以下讀入TestFile12==================================" << endl;
	double successBST2 = 100 * (double(countBST2) / double(i));
	double successSPT2 = 100 * (double(countSPT2) / double(i));
	double successTREAP2 = 100.0 * (double(countTREAP2) / double(i));
	cout << "\n在BST找到token的成功率：" << successBST2 << " %" << endl;
	
	cout << "\n在TREAP找到token的成功率：" << successTREAP2 << " %" << endl;

	
	i = 0;
	while (getline(TestFile13, data))
	{
		stringstream temp(data);	//將讀入的整行資料放在temp
		while (getline(temp, token_test3[i], ' '))
		{
			transform(token_test3[i].begin(), token_test3[i].end(), token_test3[i].begin(), tolower);
			i++;
		}
	}
	int countBST3 = 0;	//用來計算成功找到的token數
	int countSPT3 = 0;
	int countTREAP3 = 0;
	for (int j = 0; j < i; j++)
	{
		//刪除token中的標點符號
		token_test3[j].erase(
			remove_if(token_test3[j].begin(), token_test3[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test3[j].end());

		//檢查有沒有重複的token 還沒做

		//設定找到token時印出訊息
		treeNode* nodeE = B.Search(token_test3[j]);

		if (nodeE != NULL)
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> 可以在BST中找到";
			countBST3++;
		}
		else
		{
			cout << setw(13) << token_test3[j] << setw(20) << "-> 在BST中找不到";
		}

		

		find = T.Search(rootTreap, token_test3[j]);
		if (find == NULL)
		{
			cout << "\t在TREAP中找不到" << endl;
		}
		else if (find->element == token_test3[j] && find != NULL)
		{
			cout << "\t可以在TREAP中找到" << endl;
			countTREAP3++;
		}
		else
			cout << "\t在TREAP中找不到" << endl;
	}
	cout << "\n==================================以下讀入TestFile13==================================" << endl;
	double successBST3 = 100.0 * (double(countBST3) / double(i));
	double successSPT3 = 100.0 * (double(countSPT3) / double(i));
	double successTREAP3 = 100.0 * (double(countTREAP3) / double(i));
	cout << "\n在BST找到token的成功率：" << successBST3 << " %" << endl;
	cout << "\n在TREAP找到token的成功率：" << successTREAP3 << " %" << endl;


	_LARGE_INTEGER Timestart, Timeend, Pintime;
	QueryPerformanceFrequency(&Pintime);
	//以下處理使用者輸入的部分
	int selection = 0;      //建立一個變數存取使用者輸入值
	do {
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
			node = B.Search(user_token);				 // 先查詢此key值是否已存在BST中	 
			if (node != NULL)                            //若已存在，則輸出訊息
				cout << "此token值已存在於BST中 ";
			else
			{
				cout << "成功新增到BST" << endl;
				B.InsertBST(user_token);
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n新增到BST花費的時間： " << time << "ms" << endl;
			

			QueryPerformanceCounter(&Timestart);
			find = T.Search(rootTreap, user_token);
			if (find == NULL)
			{
				cout << "成功新增到TREAP" << endl;
				rootTreap = T.InsertTREAP(rootTreap, user_token);
			}
			else if (find->element == user_token)
			{
				cout << user_token << "已存在於TREAP中" << endl;
			}
			QueryPerformanceCounter(&Timeend);
			time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n新增到TREAP花費的時間： " << time << "ms" << endl;
			
			cout << "\n中序結果: \n" << "===BST===" << endl;                   //輸出中序表示式           
			B.InorderPrint();
			
			cout << "\n===TREAP===" << endl;
			T.Inorder(rootTreap);
			cout << endl;
		}
		else if (selection == 2)  //刪除key
		{
			cout << "\n輸入欲刪除的token值: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//轉成小寫

			QueryPerformanceCounter(&Timestart);
			node = B.Search(user_token);				 // 先查詢此key值是否已存在BST中
			if (node == NULL)                            //若已存在，則輸出訊息
				cout << "\n此token值不存在於BST中 ";
			else
			{
				B.DeleteBST(user_token);
				cout << "\n從BST刪除成功" << endl;

				cout << "\n刪除" << user_token << "後的BST中序結果：\n" << endl;                  //輸出中序表示式           
				B.InorderPrint();
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n從BST刪除或搜尋花費的時間： " << time << "ms" << endl;

			

			QueryPerformanceCounter(&Timestart);
			find = T.Search(rootTreap, user_token);
			if (find == NULL)
				cout << "\n此token值不存在於TREAP中 ";
			else if (find->element == user_token)
			{
				rootTreap = T.DeleteTREAP(rootTreap, user_token);
				cout << "\n從TREAP刪除成功" << endl;

				cout << "\n刪除" << user_token << "後的TREAP中序結果：\n" << endl;
				T.Inorder(rootTreap);
			}
			QueryPerformanceCounter(&Timeend);
			time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n從TREAP刪除或搜尋花費的時間： " << time << "ms" << endl;
		}
		else if (selection == 3)   //查詢key
		{
			cout << "請輸入欲查找的資料: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//轉成小寫

			QueryPerformanceCounter(&Timestart);
			node = B.Search(user_token);	// 先查詢此key值是否已存在BST中
			if (node == NULL)                            //若已存在，則輸出訊息
				cout << "\n" << user_token << "不存在於BST中" << endl;
			else
				cout << "\n" << node->element << "存在於BST中" << endl;
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n在BST搜尋花費的時間： " << time << "ms" << endl;
			

			

			QueryPerformanceCounter(&Timestart);
			find = T.Search(rootTreap, user_token);
			if (find == NULL)
			{
				cout << user_token << "不存在於TREAP中" << endl;
			}
			else if (find->element == user_token && find != NULL)
			{
				cout << user_token << "存在於TREAP中" << endl;
			}
			else
				cout << user_token << "在TREAP中找不到" << endl;
			QueryPerformanceCounter(&Timeend);
			time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n在TREAP搜尋花費的時間： " << time << "ms" << endl;
		}
	} while (selection != 4);   //輸入4以結束迴圈

	TestFile1.close();
	TestFile11.close();
	TestFile12.close();
	TestFile13.close();
	system("PAUSE");
	return (0);
}
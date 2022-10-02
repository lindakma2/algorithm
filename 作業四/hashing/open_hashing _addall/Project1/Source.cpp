// C++ code
#include <iostream>
#include <string>
#include <vector>
#include <math.h>       // floor()
#include <fstream>	  //開關檔資料流
#include <cctype>     //用於刪除token中的符號
#include <algorithm>  //用於刪除token中的符號
#include <iomanip>	  //用到對齊輸出字串的setw()
#include <sstream>	  //用於讀檔時的stringstream
#include <ctime>	  //用於隨機產生priority的值
#include <Windows.h>

using std::string;
using std::cout;
using std::endl;
using namespace std;

struct dict {
    int key;
    string value;
    dict() :key(0), value("") {};
    dict(int k, string s) :key(k), value(s) {};
};

class HashOpenAddress {
private:
    int size, count;
    dict* table;

    int QuadraticProbing(int key, int i);

    // TableDoubling()
    // TableShrinking()
    // Rehashing()

public:
    HashOpenAddress() :size(0), count(0), table(0) {};
    HashOpenAddress(int m) :size(m), count(0) {
        table = new dict[size];
    }
    void Insert(int key, string value);
    void Delete(int key);
    string Search(int key);
    void Display();
};

string HashOpenAddress::Search(int key) {

    int i = 0;
    while (i != size) {
        int j = QuadraticProbing(key, i);
        if (table[j].key == key) {
            return table[j].value;
        }
        else {
            i++;
        }
    }
    return "no such data";
}

void HashOpenAddress::Delete(int key) {

    int i = 0;
    while (i != size) {
        int j = QuadraticProbing(key, i);
        if (table[j].key == key) {
            table[j].key = 0;
            table[j].value = "";
            count--;
            return;
        }
        else {
            i++;
        }
    }
    cout << "no such data";
}

void HashOpenAddress::Insert(int key, string value) {

    int i = 0;
    while (i != size) {
        int j = QuadraticProbing(key, i);
        if (table[j].value == "") {
            table[j].key = key;
            table[j].value = value;
            count++;
            return;
        }
        else {
            i++;
        }
    }
    cout << "Hash Table Overflow\n";
}

int HashOpenAddress::QuadraticProbing(int key, int i) {
    // c1 = c2 = 0.5
    return ((int)((key % size) + 0.5 * i + 0.5 * i * i) % size);
	//return key % size;
}

void HashOpenAddress::Display() {

    for (int i = 0; i < size; i++) {
        cout << "slot#" << i << ": (" << table[i].key
            << "," << table[i].value << ")" << endl;
    }
    cout << endl;
}



int PreHashing2(string key_str) {
	// if   key_str = Jordan, exp = 9
	// then key_int = ASCII(J)*9^5+ASCII(o)*9^4+ASCII(r)*9^3
	//               +ASCII(d)*9^2+ASCII(a)*9^1+ASCII(n)*9^0

	int exp = 9,        // choose randomly 
		key_int = 0,
		p = 1;

	for (int i = (int)key_str.size() - 1; i >= 0; i--) {
		key_int += key_str[i];
	}
	return key_int%350;
}


int main()
{

	HashOpenAddress hash(350);

	ifstream TestFile1, TestFile11, TestFile12, TestFile13;
	string data; //read a sentence will be cut into token
	TestFile1.open("TestFile1.txt");
	TestFile11.open("TestFile11.txt");
	TestFile12.open("TestFile12.txt");
	TestFile13.open("TestFile13.txt");

	int tokennum = 0; //token amount
	int dicnodenum = 0; //dictionrary token amount
	string token[1000];
	string token_test1[1000];
	string token_test2[1000];	//從TestFile12.txt放入的token
	string token_test3[1000];
	string user_token;//input string by user for insert,delete,search
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
		//token[j].erase(remove_if(token[j].begin(), token[j].end(), static_cast<int(*)(int)>(&ispunct)),token[j].end());

		int hashingnum = PreHashing2(token[j]);
		string find = hash.Search(hashingnum);			// 先查詢此key值是否已存在BST中
		if (find == "no such data")								//插入BST
		{
			hash.Insert(hashingnum, token[j]);
			dicnodenum++;
		}
		//cout << token[j] << " ";
	}
	end = clock();
	cout << "\n插入 open addressing hashing 花的時間: " << end - start << endl;
	cout << "\n從檔案中讀取到的token數量" << tokennum << endl;
	cout << "\n去除重複的單字後，dictionary中的token數量" << dicnodenum << endl;

	cout << "\n==========open addressing hashing的inorder trasversal==========" << endl;
	hash.Display();

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
	int countBST = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//刪除token中的標點符號
		token_test1[j].erase(
			remove_if(token_test1[j].begin(), token_test1[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test1[j].end());

		//設定找到token時印出訊息
		int hashingnum = PreHashing2(token_test1[j]);
		string find = hash.Search(hashingnum);

		if (find != "no such data")
		{
			//cout << setw(13) << token_test1[j] << setw(20) << "-> 可以在open addressing hasging中找到";
			countBST++;
		}
		else
		{
			//cout << setw(13) << token_test1[j] << setw(20) << "-> 在open addressing hasging中找不到";
		}
	}
	double successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n在open addressing hasging找到token的成功率：" << successBST << " %" << endl;

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
	countBST = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//刪除token中的標點符號
		token_test2[j].erase(
			remove_if(token_test2[j].begin(), token_test2[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test2[j].end());

		//設定找到token時印出訊息
		int hashingnum = PreHashing2(token_test2[j]);
		string find = hash.Search(hashingnum);

		if (find != "no such data")
		{
			//cout << setw(13) << token_test2[j] << setw(20) << "-> 可以在open addressing hasging中找到";
			countBST++;
		}
		else
		{
			//cout << setw(13) << token_test2[j] << setw(20) << "-> 在open addressing hasging中找不到";
		}
	}
	successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n在open addressing hasging找到token的成功率：" << successBST << " %" << endl;

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
	countBST = 0;
	for (int j = 0; j < tokennum; j++)
	{
		//刪除token中的標點符號
		token_test3[j].erase(
			remove_if(token_test3[j].begin(), token_test3[j].end(), static_cast<int(*)(int)>(&ispunct)),
			token_test3[j].end());

		//設定找到token時印出訊息
		int hashingnum = PreHashing2(token_test3[j]);
		string find = hash.Search(hashingnum);

		if (find != "no such data")
		{
			//cout << setw(13) << token_test3[j] << setw(20) << "-> 可以在open addressing hasging中找到";
			countBST++;
		}
		else
		{
			//cout << setw(13) << token_test3[j] << setw(20) << "-> 在open addressing hasging中找不到";
		}
	}
	successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n在open addressing hasging找到token的成功率：" << successBST << " %" << endl;

	_LARGE_INTEGER Timestart, Timeend, Pintime;
	QueryPerformanceFrequency(&Pintime);

	//以下處理使用者輸入的部分
	int selection = 0;      //建立一個變數存取使用者輸入值
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
			int hashingnum = PreHashing2(user_token);
			string find = hash.Search(hashingnum);			// 先查詢此key值是否已存在BST中
			if (find != "no such data")                            //若已存在，則輸出訊息
				cout << "此token值已存在於BST中 ";
			else
			{
				cout << "成功新增到open addressing hashing" << endl;
				hash.Insert(hashingnum, user_token);
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n新增到open addressing hashing花費的時間： " << time << "ms" << endl;
			hash.Display();

		}
		else if (selection == 2)  //刪除key
		{
			cout << "\n輸入欲刪除的token值: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//轉成小寫
			QueryPerformanceCounter(&Timestart);
			int hashingnum = PreHashing2(user_token);
			string find = hash.Search(hashingnum);			// 先查詢此key值是否已存在BST
			if (find == "no such data")                            //若已存在，則輸出訊息
				cout << "\n此open addressing hashing值不存在於BST中 ";
			else
			{
				hash.Delete(hashingnum);
				cout << "\n從open addressing hasging刪除成功" << endl;
				cout << "\n刪除" << user_token << "後的open addressing hashing中序結果：\n" << endl;                  //輸出中序表示式           
				hash.Display();
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n從hashing刪除或搜尋花費的時間： " << time << "ms" << endl;

		}
		else if (selection == 3)   //查詢key
		{
			cout << "請輸入欲查找的資料: ";
			cin >> user_token;
			transform(user_token.begin(), user_token.end(), user_token.begin(), tolower);	//轉成小寫

			QueryPerformanceCounter(&Timestart);
			int hashingnum = PreHashing2(user_token);
			string find = hash.Search(hashingnum);

			if (find == "no such data")                            //若已存在，則輸出訊息
				cout << "\n" << user_token << "不存在於open addressing hashing中" << endl;
			else
				cout << "\n" << user_token << "存在於open addressing hashing中" << endl;
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n在hashing搜尋花費的時間： " << time << "ms" << endl;

		}


	} while (selection != 4);   //輸入4以結束迴圈

	TestFile1.close();
	TestFile11.close();
	system("PAUSE");
	return (0);
}
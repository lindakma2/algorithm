// C++ code
#include <iostream>
#include <string>
#include <vector>
#include <math.h>       // floor()
#include <fstream>	  //�}���ɸ�Ƭy
#include <cctype>     //�Ω�R��token�����Ÿ�
#include <algorithm>  //�Ω�R��token�����Ÿ�
#include <iomanip>	  //�Ψ�����X�r�ꪺsetw()
#include <sstream>	  //�Ω�Ū�ɮɪ�stringstream
#include <ctime>	  //�Ω��H������priority����
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
		string find = hash.Search(hashingnum);			// ���d�ߦ�key�ȬO�_�w�s�bBST��
		if (find == "no such data")								//���JBST
		{
			hash.Insert(hashingnum, token[j]);
			dicnodenum++;
		}
		//cout << token[j] << " ";
	}
	end = clock();
	cout << "\n���J open addressing hashing �᪺�ɶ�: " << end - start << endl;
	cout << "\n�q�ɮפ�Ū���쪺token�ƶq" << tokennum << endl;
	cout << "\n�h�����ƪ���r��Adictionary����token�ƶq" << dicnodenum << endl;

	cout << "\n==========open addressing hashing��inorder trasversal==========" << endl;
	hash.Display();

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
			//cout << setw(13) << token_test1[j] << setw(20) << "-> �i�H�bopen addressing hasging�����";
			countBST++;
		}
		else
		{
			//cout << setw(13) << token_test1[j] << setw(20) << "-> �bopen addressing hasging���䤣��";
		}
	}
	double successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n�bopen addressing hasging���token�����\�v�G" << successBST << " %" << endl;

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
			//cout << setw(13) << token_test2[j] << setw(20) << "-> �i�H�bopen addressing hasging�����";
			countBST++;
		}
		else
		{
			//cout << setw(13) << token_test2[j] << setw(20) << "-> �bopen addressing hasging���䤣��";
		}
	}
	successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n�bopen addressing hasging���token�����\�v�G" << successBST << " %" << endl;

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
		int hashingnum = PreHashing2(token_test3[j]);
		string find = hash.Search(hashingnum);

		if (find != "no such data")
		{
			//cout << setw(13) << token_test3[j] << setw(20) << "-> �i�H�bopen addressing hasging�����";
			countBST++;
		}
		else
		{
			//cout << setw(13) << token_test3[j] << setw(20) << "-> �bopen addressing hasging���䤣��";
		}
	}
	successBST = 100.0 * (double(countBST) / double(tokennum));
	cout << "\n�bopen addressing hasging���token�����\�v�G" << successBST << " %" << endl;

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
				cout << "��token�Ȥw�s�b��BST�� ";
			else
			{
				cout << "���\�s�W��open addressing hashing" << endl;
				hash.Insert(hashingnum, user_token);
			}
			QueryPerformanceCounter(&Timeend);
			double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
			cout << "\n�s�W��open addressing hashing��O���ɶ��G " << time << "ms" << endl;
			hash.Display();

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
				cout << "\n��open addressing hashing�Ȥ��s�b��BST�� ";
			else
			{
				hash.Delete(hashingnum);
				cout << "\n�qopen addressing hasging�R�����\" << endl;
				cout << "\n�R��" << user_token << "�᪺open addressing hashing���ǵ��G�G\n" << endl;                  //��X���Ǫ�ܦ�           
				hash.Display();
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
				cout << "\n" << user_token << "���s�b��open addressing hashing��" << endl;
			else
				cout << "\n" << user_token << "�s�b��open addressing hashing��" << endl;
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
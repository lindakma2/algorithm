#include <iostream>
#include <Windows.h>
using namespace std;
//basic
bool isPrime(int n)
{

    if (n <= 1)
        return false;


    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;

    return true;
}

int power(long long int a, int n, int p)
{
    int res = 1;
    a = a % p;

    while (n > 0)
    {
        if (n % 2 == 1)
            res = (res * a) % p;
        n = n / 2;
        a = (a * a) % p;
    }

    return res;
}
//format
bool FermatPrimality(int num)
{
    bool check = false;
    if (num % 2 != 0)
    {
        int res = power(2, num - 1, num);
        if (res == 1)
        {
            check = true;
        }
    }
    if (num % 3 != 0)
    {

        int res = power(3, num - 1, num);
        if (res == 1)
        {
            check = true;
        }
    }
    return check;
}
//miller

bool check(int d, int n)
{

    long long int x = power(2, d, n);

    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1)
    {
        x = (x * x) % n;
        d = d * 2;
        if (x == 1)      return false;
        if (x == n - 1)    return true;
    }

    return false;
}

void MillerRabin(int number)
{
    int num = number - 1;
    while (num % 2 == 0)
        num = num / 2;
    if (check(num, number))
    {
        cout << "it is prime" << endl;
    }
    else
    {
        cout << "it is not prime" << endl;
    }

    return;
}
//sieve
int prime[100000000];

void reset(int number)
{
    for (int i = 0; i < number; i++)
    {
        prime[i] = 1;
    }
}

void FindPrime(int n)
{
    for (int p = 2; p * p <= n; p++)
    {
        if (prime[p] == 1)
        {
            for (int i = p * p; i <= n; i += p)
                prime[i] = 0;
        }
    }
}
int main()
{
    int number;
    _LARGE_INTEGER Timestart, Timeend, Pintime;
    QueryPerformanceFrequency(&Pintime);
    cout << "please enter a number";
    cin >> number;
    //basic
    cout << "basic" << endl;
    QueryPerformanceCounter(&Timestart);
    if (isPrime(number))
    {
        cout << "it is prime" << endl;
    }
    else
    {
        cout << "it is not prime" << endl;
    }
    QueryPerformanceCounter(&Timeend);
    double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "time:" << time << "ms"<<endl;
    //format
    cout << "Format" << endl;
    QueryPerformanceCounter(&Timestart);
    if (FermatPrimality(number))
    {
        cout << "it is prime" << endl;
    }
    else
    {
        cout << "it is not prime" << endl;
    }
    QueryPerformanceCounter(&Timeend);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "time:" << time << "ms"<<endl;
    //miller
    cout << "miller" << endl;
    QueryPerformanceCounter(&Timestart);
    MillerRabin(number);
    QueryPerformanceCounter(&Timeend);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "time:" << time << "ms"<<endl;
    //sieve
    cout << "sieve" << endl;
    reset(number + 1);
    QueryPerformanceCounter(&Timestart);
    FindPrime(number);
    if (prime[number] == 1)
    {
        cout << "it is prime" << endl;
    }
    else
    {
        cout << "it is not prime" << endl;
    }
    QueryPerformanceCounter(&Timeend);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "time:" << time << "ms";
    return 0;
}
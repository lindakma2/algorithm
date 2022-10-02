#include <vector>
#include <iostream>
#include <algorithm>
#include <Windows.h>
using namespace std;
int array1[6] = { 5, 3, 1, 2, 6, 4 };
int array2[20] = {6,16,61,82,57,56,20,90,77,72,22,12,33,76,30,67,18,75,47,80};
int array3[40] = {65,110,152,80,119,118,73,30,185,66,79,170,163,115,38,122,111,27,171,84,161,90,121,129,17,184,39,124,82,48,97,21,83,194,142,174,104,133,149,93};
int temp[40];
vector<int> tempv;
vector<int> arrayv1 = { 5, 3, 1, 2, 6, 4 };
vector<int> arrayv2 = { 6,16,61,82,57,56,20,90,77,72,22,12,33,76,30,67,18,75,47,80 };
vector<int> arrayv3 = { 65,110,152,80,119,118,73,30,185,66,79,170,163,115,38,122,111,27,171,84,161,90,121,129,17,184,39,124,82,48,97,21,83,194,142,174,104,133,149,93 };
void startarray(int* arr, int size, vector<int>& nums)
{
	for (int i = 0; i < size; i++)
	{
		temp[i] = arr[i];
        tempv.push_back(nums[i]);
	}
   
}

//insertionsort
void InsertionSort(int* arr, int size) {

    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (key < arr[j] && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void PrintArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

//mergesort

void Merge(int A[], int p, int q, int m) {
	int n1 = m - p + 1;
	int n2 = q - m;

	int* L = new int[n1];
	int* R = new int[n2];

	for (int i = 0; i < n1; i++) {
		L[i] = A[p + i];
	}
	for (int i = 0; i < n2; i++) {
		R[i] = A[i + m + 1];
	}
	L[n1] = 2147483647;
	R[n2] = 2147483647;
	int i = 0, j = 0;
	for (int k = p; k <= q; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
	}
}
void Merge_Sort(int A[], int p, int q) {
	if (p < q) {
		int m = (p + q) / 2;
		Merge_Sort(A, p, m);  
		Merge_Sort(A, m + 1, q); 
		Merge(A, p, q, m);  
	}
}

//quicksort
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int Partition(int* arr, int front, int end) {
    int pivot = arr[end];
    int i = front - 1;
    for (int j = front; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}
void QuickSort(int* arr, int front, int end) {
    if (front < end) {
        int pivot = Partition(arr, front, end);
        QuickSort(arr, front, pivot - 1);
        QuickSort(arr, pivot + 1, end);
    }
}


//quickselect


int partition(int arr[], const int left, const int right)
{
    int pivot = arr[right]; 
    int i = (left - 1);
    int j = left;
    for (j = left; j <= (right - 1); j++)
    {
        if (arr[j] < pivot)
        {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return (i + 1);
}

int quickselect(int arr[], const int left, const int right, const int k)
{
   
    if (k > 0 && k <= (right - left + 1))
    {
        
        int index = partition(arr, left, right);
        
        if (index - left == k - 1)
            return arr[index];
        
        if (index - left > k - 1)
            return quickselect(arr, left, index - 1, k);
       
        return quickselect(arr, index + 1, right,
            k - index + left - 1);
    }
}

//median of median 3
int pivotthree(vector<int>& nums, int s, int e, int m) {
    int prev = s;
    int run = s;
    int last = e - 1;

    while (run <= last) {
        if (nums[run] == m) {
            run++;
        }
        else if (nums[run] < m) {
            swap(nums[run], nums[prev]);
            prev++;
            run++;
        }
        else {
            swap(nums[run], nums[last]);
            last--;
        }
    }

    return prev;
}

int KthLargestthree(vector<int>& nums, int k, int s, int e) {
    if (e - s <= 6) {
        sort(begin(nums) + s, begin(nums) + e);
        return nums[s + k - 1];
    }

    vector<int> medians;

    for (int i = s; i < e; i += 3) {
        if (e - i <= 6) {
            sort(begin(nums) + i, begin(nums) + e);
            medians.push_back(nums[(e + i) / 2]);
        }
        else {
            sort(begin(nums) + i, begin(nums) + i + 3);
            medians.push_back(nums[i + 2]);
        }
    }

    int median = KthLargestthree(medians, medians.size() / 2 + 1, 0, medians.size());
    int p = pivotthree(nums, s, e, median);

    if (p - s + 1 == k) {
        return nums[p];
    }

    if (p - s + 1 > k) {
        return KthLargestthree(nums, k, s, p);
    }

    return KthLargestthree(nums, k - (p - s + 1), p + 1, e);
}

int findKthLargestthree(vector<int>& nums, int k) {
    return KthLargestthree(nums, nums.size() - k + 1, 0, nums.size());
}

//median of median5
int pivotfive(vector<int>& nums, int s, int e, int m) {
    int prev = s;
    int run = s;
    int last = e - 1;

    while (run <= last) {
        if (nums[run] == m) {
            run++;
        }
        else if (nums[run] < m) {
            swap(nums[run], nums[prev]);
            prev++;
            run++;
        }
        else {
            swap(nums[run], nums[last]);
            last--;
        }
    }

    return prev;
}

int KthLargestfive(vector<int>& nums, int k, int s, int e) {
    if (e - s <= 10) {
        sort(begin(nums) + s, begin(nums) + e);
        return nums[s + k - 1];
    }

    vector<int> medians;

    for (int i = s; i < e; i += 5) {
        if (e - i <= 10) {
            sort(begin(nums) + i, begin(nums) + e);
            medians.push_back(nums[(e + i) / 2]);
        }
        else {
            sort(begin(nums) + i, begin(nums) + i + 5);
            medians.push_back(nums[i + 2]);
        }
    }

    int median = KthLargestfive(medians, medians.size() / 2 + 1, 0, medians.size());
    int p = pivotfive(nums, s, e, median);

    if (p - s + 1 == k) {
        return nums[p];
    }

    if (p - s + 1 > k) {
        return KthLargestfive(nums, k, s, p);
    }

    return KthLargestfive(nums, k - (p - s + 1), p + 1, e);
}

int findKthLargestfive(vector<int>& nums, int k) {
    return KthLargestfive(nums, nums.size() - k + 1, 0, nums.size());
}

//median of median7
int pivotseven(vector<int>& nums, int s, int e, int m) {
    int prev = s;
    int run = s;
    int last = e - 1;

    while (run <= last) {
        if (nums[run] == m) {
            run++;
        }
        else if (nums[run] < m) {
            swap(nums[run], nums[prev]);
            prev++;
            run++;
        }
        else {
            swap(nums[run], nums[last]);
            last--;
        }
    }

    return prev;
}

int KthLargestseven(vector<int>& nums, int k, int s, int e) {
    if (e - s <= 10) {
        sort(begin(nums) + s, begin(nums) + e);
        return nums[s + k - 1];
    }

    vector<int> medians;

    for (int i = s; i < e; i += 5) {
        if (e - i <= 10) {
            sort(begin(nums) + i, begin(nums) + e);
            medians.push_back(nums[(e + i) / 2]);
        }
        else {
            sort(begin(nums) + i, begin(nums) + i + 5);
            medians.push_back(nums[i + 2]);
        }
    }

    int median = KthLargestseven(medians, medians.size() / 2 + 1, 0, medians.size());
    int p = pivotseven(nums, s, e, median);

    if (p - s + 1 == k) {
        return nums[p];
    }

    if (p - s + 1 > k) {
        return KthLargestseven(nums, k, s, p);
    }

    return KthLargestseven(nums, k - (p - s + 1), p + 1, e);
}

int findKthLargestseven(vector<int>& nums, int k) {
    return KthLargestseven(nums, nums.size() - k + 1, 0, nums.size());
}
int main() 
{
    _LARGE_INTEGER Timestart, Timeend, Pintime;
    QueryPerformanceFrequency(&Pintime);
    int size, k;
    cout << "please enter input size";
    cin >> size;
    cout << "please enter min k";
    cin >> k;
	//insertion
    cout << "insertion" << endl;
	startarray(array3, size, arrayv3);
    PrintArray(temp, size);
    QueryPerformanceCounter(&Timestart);
    InsertionSort(temp, size);
    QueryPerformanceCounter(&Timeend);
    PrintArray(temp, size);
    double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "sort time:" << time << "ms" << endl;
    
    QueryPerformanceCounter(&Timestart);
    int num = temp[k - 1];
    QueryPerformanceCounter(&Timeend);
    cout << "min k is" << num<<endl;
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "findmin time:" << time << "ms" << endl;

	//merge
    cout << "merge" << endl;
    startarray(array3, size, arrayv3);
    PrintArray(temp, size);
    QueryPerformanceCounter(&Timestart);
    Merge_Sort(temp, 0, size - 1);
    QueryPerformanceCounter(&Timeend);
    PrintArray(temp, size);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "sort time:" << time << "ms" << endl;

    QueryPerformanceCounter(&Timestart);
    num = temp[k - 1];
    QueryPerformanceCounter(&Timeend);
    cout << "min k is" << num << endl;
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "findmin time:" << time << "ms" << endl;

	//quicksort
    cout << "quicksort" << endl;
    startarray(array3, size, arrayv3);
	PrintArray(temp, size);
    QueryPerformanceCounter(&Timestart);
    QuickSort(temp, 0, size - 1);
    QueryPerformanceCounter(&Timeend);
    PrintArray(temp, size);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "sort time:" << time << "ms" << endl;

    QueryPerformanceCounter(&Timestart);
    num = temp[k - 1];
    QueryPerformanceCounter(&Timeend);
    cout << "min k is" << num << endl;
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "findmin time:" << time << "ms" << endl;

    //quickselect
    cout << "quickselect" << endl;
    startarray(array3, size, arrayv3);
    QueryPerformanceCounter(&Timestart);
    num = quickselect(temp, 0, size - 1, k);
    QueryPerformanceCounter(&Timeend);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "findmin time:" << time << "ms" << endl;
    cout<< "min k is" << num<<endl;

    //median of median 3
    cout << "m of m g=3" << endl;
    startarray(array3, size, arrayv3);
    QueryPerformanceCounter(&Timestart);
    int median = findKthLargestthree(tempv, tempv.size() / 2);
    QueryPerformanceCounter(&Timeend);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "findmedian time:" << time << "ms" << endl;
    cout <<"median " << median << endl;
 
    //median of median 5
    cout << "m of m g=5" << endl;
    startarray(array3, size, arrayv3);
    QueryPerformanceCounter(&Timestart);
    median = findKthLargestfive(tempv, tempv.size() / 2);
    QueryPerformanceCounter(&Timeend);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "findmedian time:" << time << "ms" << endl;
    cout << "median " << median << endl;

    //median of median 7
    cout << "m of m g=7" << endl;
    startarray(array3, size, arrayv3);
    QueryPerformanceCounter(&Timestart);
    median = findKthLargestseven(tempv, tempv.size() / 2);
    QueryPerformanceCounter(&Timeend);
    time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
    cout << "findmedian time:" << time << "ms" << endl;
    cout << "median " << median << endl;
    return 0;
}
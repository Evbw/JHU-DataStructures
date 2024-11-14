#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node{
    public:
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr){}
};

void insertionSort(int arr[], int n, int m) {
    int data;
    int j;
    for (int i = n + 1; i <= m; i++) {
        data = arr[i];
        j = i - 1;

        while (j >= n && arr[j] > data) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = data;
    }
}

int partition(int arr[], int left, int right, int pivotType) {
    int pivot;
    int i = left + 1;
    int j = right;

    switch (pivotType){
        case 1: {
             pivot = arr[left];
            break;
        }
        case 2: {
            if (right - left + 1 <= 100) {
                insertionSort(arr, left, right);
                return left;
            }
            pivot = arr[left];
            break;
        }
        case 3: {
            if (right - left + 1 <= 50) {
                insertionSort(arr, left, right);
                return left;
            }
            pivot = arr[left];
            break;
        }
        case 4: {
            int mid = (left + right)/2;
            if ((arr[left] < arr[mid] && arr[mid] < arr[right]) || (arr[right] < arr[mid] && arr[mid] < arr[left])) {
                pivot = arr[mid];
                swap(arr[left], arr[mid]);
            } else if ((arr[mid] < arr[left] && arr[left] < arr[right]) || (arr[right] < arr[left] && arr[left] < arr[mid])) {
                pivot = arr[left];
            } else {
                pivot = arr[right];
                swap(arr[left], arr[right]);
            }
            break;
        }
        default: {
            pivot = arr[left];
        }
    }

    while (i <= j) {
        while (i <= j && arr[i] < pivot) {
            i++;
        }
        while (i <= j && arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[left], arr[j]);
    return j;    
}

void quickSortPivot1(int arr[], int left, int right) {
    if (left < right) {
        int pivotIndex = partition(arr, left, right, 1);
        quickSortPivot1(arr, left, pivotIndex-1);
        quickSortPivot1(arr, pivotIndex+1, right);
    }
}

void quickSortPivot50(int arr[], int left, int right) {
    
}

void quickSortPivot100(int arr[], int left, int right) {
    
}

void quickSortPivotMedian(int arr[], int left, int right) {
    
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void mergeSort(Node* root) {

}

void splitIntoRuns(Node* root, Node* next) {

}

Node* sortedMerge(Node* a, Node* b) {
    return a;
}

void insert(Node*& head, int data) {

}

int countNumbers(const string& filename) {
    int count = 0;
    char c;
    bool inNumber = false;

    ifstream file(filename);
    while (!file.is_open()) {
        cout<<"Error opening file: "<<filename<<endl;
        return 0;
    }

    while (file.get(c)) {
        if (c >= '0' && c <= '9') {
            inNumber = true;
        } else if (inNumber) {
            count++;
            inNumber = false;
        }
    }

    if (inNumber) {
        count++;
    }

    file.close();
    return count;
}

int* readFile(const string& filename, int& size) {
    size = countNumbers(filename);
    if (size == 0) {
        return nullptr;
    }
    int* numbers = new int[size];

    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Error opening file: "<<filename<<endl;
        delete[] numbers;
        return nullptr;
    }
    
    int index = 0;
    string currentNumber = "";
    char c;
    while (file.get(c)) {
        if (c >= '0' && c <= '9') {
            currentNumber += c;
        } else if (!currentNumber.empty()) {
            numbers[index++] = stoi(currentNumber);
            currentNumber = "";
        }
    }

    if (!currentNumber.empty()) {
        numbers[index++] = stoi(currentNumber);
    }

    file.close();
    return numbers;
}

int main() {
    int size = 0;
    string filename;
    cout<<"This program is intended to compare quick sort and merge sort."<<endl;
    cout<<"Please enter a file consisting of integers:"<<endl;
    cin>>filename;

    int* numbers = readFile(filename, size);

    if (numbers != nullptr) {

        //for (int i = 0; i < size; i++) {
        //    cout<<numbers[i]<<" ";
        //}
        cout<<endl;
        
        quickSortPivot1(numbers, 0, size - 1);
        cout<<"Sorted: "<<endl;
        for (int i = 0; i < size; i++) {
            cout<<numbers[i]<<" ";
        }
        cout<<endl;
        delete[] numbers;
    } else {
        cout<<"Reading failed."<<endl;
    }
    return 0;
}
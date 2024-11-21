#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int COMPARISONS = 0;
int EXCHANGES = 0;

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
        while (i <= j && arr[i] <= pivot) {
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

void quickSortPivot1(int arr[], int left, int right, int& comparisons, int& exchanges) {
    if (left >= right) {
        return;
    }

    if (right == left + 1) {
        if (arr[left] > arr[right]) {
            swap(arr[left],arr[right]);
        }
        return;
    }

    if (left < right) {
        int pivotIndex = partition(arr, left, right, 1);
        quickSortPivot1(arr, left, pivotIndex - 1, comparisons, exchanges);
        quickSortPivot1(arr, pivotIndex + 1, right, comparisons, exchanges);
    }
}

void quickSortPivot50(int arr[], int left, int right, int& comparisons, int& exchanges) {
    if (left >= right) {
        return;
    }

    if (right == left + 1) {
        if (arr[left] > arr[right]) {
            swap(arr[left],arr[right]);
        }
        return;
    }

    int pivotIndex = partition(arr, left, right, 3);

    if (pivotIndex - left > 50) {
        quickSortPivot50(arr, left, pivotIndex - 1, comparisons, exchanges);
    }
    if (right - pivotIndex > 50) {
        quickSortPivot50(arr, pivotIndex + 1, right, comparisons, exchanges);
    }
}

void quickSortPivot100(int arr[], int left, int right, int& comparisons, int& exchanges) {
    if (left >= right) {
        return;
    }

    if (right == left + 1) {
        if (arr[left] > arr[right]) {
            swap(arr[left],arr[right]);
        }
        return;
    }

    int pivotIndex = partition(arr, left, right, 3);

    if (pivotIndex - left > 100) {
        quickSortPivot100(arr, left, pivotIndex - 1, comparisons, exchanges);
    }
    if (right - pivotIndex > 100) {
        quickSortPivot100(arr, pivotIndex + 1, right, comparisons, exchanges);
    }
}

void quickSortPivotMedian(int arr[], int left, int right, int& comparisons, int& exchanges) {
    if (left >= right) {
        return;
    }

    int pivotIndex = partition(arr, left, right, 4);

    quickSortPivotMedian(arr, left, pivotIndex - 1);
    quickSortPivotMedian(arr, pivotIndex + 1, right);
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

class Node {
    public:
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr){}
};

class RunNode {
    public:
        Node* runRoot;
        RunNode* next;
        RunNode(Node* root) : runRoot(root), next(nullptr){}
};

Node* readFileToList(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Error opening file: "<<filename<<endl;
        return nullptr;
    }

    Node* root = nullptr;
    Node* tail = nullptr;

    int n;
    while (file >> n) {
        Node* newNode = new Node(n);
        if(!root) {
            root = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    file.close();
    return root;
}

void printList(Node* root) {
    Node* current = root;
    while (current) {
        cout<<current->data<<" ";
        current = current->next;
    }
    cout<<endl;
}

void splitIntoRuns(Node* root, RunNode*& runsRoot) {
    runsRoot = nullptr;
    RunNode* tail = nullptr;

    Node* current = root;

    while (current) {
        Node* runStart = current;

        while ((current->next) && (current->data <= current->next->data)) {
            current = current->next;
        }

        Node* nextRun = current->next;
        current->next = nullptr;

        RunNode* newRun = new RunNode(runStart);
        if (!runsRoot) {
            runsRoot = newRun;
        } else {
            tail->next = newRun;
        }
        tail = newRun;
        current = nextRun;
    }
}

Node* sortedMerge(Node* a, Node* b) {
    if (!a) {
        return b;
    }
    if (!b) {
        return a;
    }

    Node* result = nullptr;

    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

Node* mergeRuns(RunNode* runsRoot) {
    while (runsRoot && runsRoot->next) {
        RunNode* current = runsRoot;
        RunNode* nextRun = runsRoot->next;

        current->runRoot = sortedMerge(current->runRoot, nextRun->runRoot);

        runsRoot->next = nextRun->next;
        delete nextRun;
    }
    return runsRoot ? runsRoot->runRoot : nullptr;
}

void mergeSort(Node*& root) {
    if (!root || !root->next) {
        return;
    }

    RunNode* runsRoot = nullptr;
    splitIntoRuns(root, runsRoot);

    root = mergeRuns(runsRoot);
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
    int maxFiles = 100;                                                         //Arbitrary size for the maximum number of files.
    string* filenames = new string[maxFiles];                                   //Create an array because of the library restriction.
    int fileCount = 0;
    int size = 0;
    string filename;

    cout<<"This program is intended to compare quick sort and merge sort."<<endl;
    cout<<"Please enter the names of the files consisting of integers (type 'done' to finish):"<<endl;
    while (fileCount < maxFiles && cin>>filename && filename != "done"){
        filenames[fileCount++] = filename;
    }

    string outputFilename;
    cout<<"Enter the name of the output file for the results:"<<endl;
    cin>>outputFilename;

    ofstream resultFile(outputFilename);
    while (!resultFile.is_open()) {
        cout<<"Error opening output file. Please try again"<<endl;
        cin>>outputFilename;
    }

    resultFile<<"File,Sort Method,Comparisons,Exchanges"<<endl;

    int* numbers = readFile(filename, size);

    if (numbers != nullptr) {

        cout<<endl;
        
        quickSortPivot1(numbers, 0, size - 1);
        cout<<"Quick Sorted: "<<endl;
        for (int i = 0; i < size; i++) {
            cout<<numbers[i]<<" ";
        }
        cout<<endl;
        delete[] numbers;
    } else {
        cout<<"Reading failed."<<endl;
    }

    if (numbers != nullptr) {

        cout<<endl;
        
        quickSortPivot50(numbers, 0, size - 1);
        cout<<"Quick Sort partition size 50: "<<endl;
        for (int i = 0; i < size; i++) {
            cout<<numbers[i]<<" ";
        }
        cout<<endl;
        delete[] numbers;
    } else {
        cout<<"Reading failed."<<endl;
    }

    if (numbers != nullptr) {

        cout<<endl;
        
        quickSortPivot100(numbers, 0, size - 1);
        cout<<"Quick Sort partition size 100: "<<endl;
        for (int i = 0; i < size; i++) {
            cout<<numbers[i]<<" ";
        }
        cout<<endl;
        delete[] numbers;
    } else {
        cout<<"Reading failed."<<endl;
    }

    if (numbers != nullptr) {

        cout<<endl;
        
        quickSortPivotMedian(numbers, 0, size - 1);
        cout<<"Quick Sort median of three: "<<endl;
        for (int i = 0; i < size; i++) {
            cout<<numbers[i]<<" ";
        }
        cout<<endl;
        delete[] numbers;
    } else {
        cout<<"Reading failed."<<endl;
    }

    Node* root = readFileToList(filename);
    if (!root) {
        cout<<"Failed to read file"<<endl;
        return 1;
    }

    mergeSort(root);
    cout<<"Merge Sorted:"<<endl;
    printList(root);

    Node* current = root;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
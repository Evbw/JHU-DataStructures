#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int comparisons = 0;
int exchanges = 0;
int totalComparisons[5] = {0};
int totalExchanges[5] = {0};
int grandTotalComparisons = 0;
int grandTotalExchanges = 0;

/*  ----------------------------------------------------------
    Function: insertionSort
    Description: Performs an insertion sort on a subarray within the range [n,m] of the input array
    Parameters:
        - arr (int[]): Array to be sorted.
        - n (int): Starting index of the subarray.
        - m (int): Ending index of the subarray.
        - comparisons (int&): Reference to the counter for comparisons.
        - exchanges (int&): Reference to the counter for exchanges.
    ----------------------------------------------------------
*/

void insertionSort(int arr[], int n, int m, int& comparisons, int& exchanges) {
    int data;
    int j;
    for (int i = n + 1; i <= m; i++) {
        data = arr[i];
        j = i - 1;

        while (j >= n && arr[j] > data) {
            comparisons++;
            arr[j + 1] = arr[j];
            exchanges++;
            j--;
        }

        comparisons++;
        arr[j + 1] = data;
    }
}

/*  ----------------------------------------------------------
    Function: partition
    Description: Partitions the array into two halves based on a pivot values and organizes elements around it.
    Parameters:
        - arr (int[]): Array to partition.
        - left (int): Starting index of the array.
        - right (int): Ending index of the array.
        - pivotType (int): Determines the pivot selection strategy.
                1 - First element.
                2/3 - Use insertion sort for smaller subarrays.
                4 - Median-of-three
    Returns:
        - (int): Final pivot position after partitioning.
    ----------------------------------------------------------
*/

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
                insertionSort(arr, left, right, comparisons, exchanges);
                return left;
            }
            pivot = arr[left];
            break;
        }
        case 3: {
            if (right - left + 1 <= 50) {
                insertionSort(arr, left, right, comparisons, exchanges);
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
            comparisons++;
            i++;
        }
        while (i <= j && arr[j] > pivot) {
            comparisons++;
            j--;
        }
        if (i < j) {
            exchanges++;
            swap(arr[i], arr[j]);
        }
    }
    exchanges++;
    swap(arr[left], arr[j]);
    return j;    
}

/*  ----------------------------------------------------------
    Function: quickSortPivot1
    Description: Uses first element of the array as the pivot to implement QuickSort
    Parameters:
        - arr (int[]): Array to be sorted.
        - left (int): Starting index of the array.
        - right (int): Ending index of the array.
        - comparisons (int&): Reference to the counter for comparisons.
        - exchanges (int&): Reference to the counter for exchanges.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Function: quickSortPivot50
    Description: Uses a hybrid approach using QuickSort, but implementing InsertionSort on partitions less than 50 elements.
    Parameters:
        - arr (int[]): Array to be sorted.
        - left (int): Starting index of the array.
        - right (int): Ending index of the array.
        - comparisons (int&): Reference to the counter for comparisons.
        - exchanges (int&): Reference to the counter for exchanges.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Function: quickSortPivot100
    Description: Uses a hybrid approach using QuickSort, but implementing InsertionSort on partitions less than 100 elements.
    Parameters:
        - arr (int[]): Array to be sorted.
        - left (int): Starting index of the array.
        - right (int): Ending index of the array.
        - comparisons (int&): Reference to the counter for comparisons.
        - exchanges (int&): Reference to the counter for exchanges.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Function: quickSortPivot50
    Description: Uses a median-of-three method for QuickSort pivot selection.
    Parameters:
        - arr (int[]): Array to be sorted.
        - left (int): Starting index of the array.
        - right (int): Ending index of the array.
        - comparisons (int&): Reference to the counter for comparisons.
        - exchanges (int&): Reference to the counter for exchanges.
    ----------------------------------------------------------
*/

void quickSortPivotMedian(int arr[], int left, int right, int& comparisons, int& exchanges) {
    if (left >= right) {
        return;
    }

    int pivotIndex = partition(arr, left, right, 4);

    quickSortPivotMedian(arr, left, pivotIndex - 1, comparisons, exchanges);
    quickSortPivotMedian(arr, pivotIndex + 1, right, comparisons, exchanges);
}

/*  ----------------------------------------------------------
    Function: Swap
    Description: Swaps the values of two integers.
    Parameters:
        - a (int&): Reference to the first integer.
        - b (int&): Reference to the second integer.
    ----------------------------------------------------------
*/

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/*  ----------------------------------------------------------
    Class: Node
    Description: Represents a node in the tree.
    Members:
        - data (int): The integer in the tree to be sorted.
        - next (Node*): Pointer to the next node in the list.
    Constructors:
        - Node(int val): Initializes a node with an integer.
    ----------------------------------------------------------
*/

class Node {
    public:
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr){}
};

/*  ----------------------------------------------------------
    Class: RunNode
    Description: Represents a node in the tree that is part of a sorted sub-sequence.
    Members:
        - runRoot (Node&): The head node in the sequence of sorted integers.
        - next (RunNode*): Pointer to the next node in the list.
    Constructors:
        - RunNode(Node* root): Initializes a node as the head of a run.
    ----------------------------------------------------------
*/

class RunNode {
    public:
        Node* runRoot;
        RunNode* next;
        RunNode(Node* root) : runRoot(root), next(nullptr){}
};

/*  ----------------------------------------------------------
    Function: readFileToList
    Description: Reads integers from a file and creates linked list from them.
    Parameters:
        - filename (string): Name of the file to read.
    Returns:
        - (Node*): Pointer to the head of the linked list.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Function: splitIntoRuns
    Description: Splits a linked list into monotonic runs.
    Parameters:
        - root (Node*): Pointer to the head of the input list.
        - runsRoot (RunNode*&): Reference to the head of the runs.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Function: sortedMerge
    Description: Merges two sorted linked lists into a single sorted linked list.
    Parameters:
        - a (Node*): Reference to the first list.
        - b (Node*): Reference to the second list.
        - comparisons (int&): Reference to the counter for comparisons.
        - exchanges (int&): Reference to the counter for exchanges.
    Returns:
        - (Node*): Pointer to the head of the merged list.
    ----------------------------------------------------------
*/

Node* sortedMerge(Node* a, Node* b, int& comparisons, int& exchanges) {
    if (!a) {
        return b;
    }
    if (!b) {
        return a;
    }

    Node* result = nullptr;

    comparisons++;
    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b, comparisons, exchanges);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next, comparisons, exchanges);
        exchanges++;
    }

    return result;
}

/*  ----------------------------------------------------------
    Function: mergeRuns
    Description: Merges runs from the RunNode linked list into a single list.
    Parameters:
        - runsRoot (RunNode*): Pointer to the head of the runs list.
        - comparisons (int&): Reference to the counter for comparisons.
        - exchanges (int&): Reference to the counter for exchanges.
    Returns:
        - (Node*): Pointer to the head of the merged list.
    ----------------------------------------------------------
*/

Node* mergeRuns(RunNode* runsRoot, int& comparisons, int& exchanges) {
    while (runsRoot && runsRoot->next) {
        RunNode* current = runsRoot;
        RunNode* nextRun = runsRoot->next;

        current->runRoot = sortedMerge(current->runRoot, nextRun->runRoot, comparisons, exchanges);

        runsRoot->next = nextRun->next;
        delete nextRun;
    }
    return runsRoot ? runsRoot->runRoot : nullptr;
}

/*  ----------------------------------------------------------
    Function: mergeSort
    Description: Sorts a linked list using merge sort.
    Parameters:
        - root (Node*&): Reference to the head of the list.
        - comparisons (int&): Reference to the counter for comparisons.
        - exchanges (int&): Reference to the counter for exchanges.
    ----------------------------------------------------------
*/

void mergeSort(Node*& root, int& comparisons, int& exchanges) {
    if (!root || !root->next) {
        return;
    }

    RunNode* runsRoot = nullptr;
    splitIntoRuns(root, runsRoot);

    root = mergeRuns(runsRoot, comparisons, exchanges);
}

/*  ----------------------------------------------------------
    Function: arrayToList
    Description: Converts an array of integers into a linked list.
    Parameters:
        - arr (int[]): Array of integers.
        - size (int): Size of the array.
    Returns:
        - (Node*): Pointer to the head of the new list.
    ----------------------------------------------------------
*/

Node* arrayToList(int arr[], int size) {
    Node* root = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < size; i++) {
        Node* newNode = new Node(arr[i]);
        if (!root) {
            root = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    return root;
}

/*  ----------------------------------------------------------
    Function: listToArray
    Description: Converts a linked list into an array and deallocates the list.
    Parameters:
        - root (Node*): Pointer to the head of the list.
        - arr (int[]): Array to store the list elements.
        - size (int): Size of the array.
    ----------------------------------------------------------
*/

void listToArray(Node* root, int arr[], int size) {
    Node* current = root;
    int index = 0;

    while (current && index < size) {
        arr[index++] = current->data;
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

/*  ----------------------------------------------------------
    Function: countNumbers
    Description: Counts the number of values in a file.
    Parameters:
        - filename (string): Name of the file to read.
    Returns:
        - count (int): Total count of numbers in the file.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Function: readFile
    Description: Reads integers from a file into an array.
    Parameters:
        - filename (string): Name of the file to read.
        - size (int&): Reference to the size of the array.
    Returns:
        - numbers (int*): Pointer to the array containing the numbers.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Function: main
    Description: Entry point for the program. Handles input, sorts files, and writes to an output file.
    ----------------------------------------------------------
*/

int main() {
    int maxFiles = 100;                                                         //Arbitrary size for the maximum number of files.
    string* filenames = new string[maxFiles];                                   //Create an array because of the library restriction.
    int fileCount = 0;
    int size = 0;
    string filename;
    string methodNames[] = {"QuickSort", "QSPartition50", "QSPartition100", "QSMedianOfThree", "MergeSort"};

    cout<<"This program is intended to compare quick sort and merge sort."<<endl;
    cout<<"Please enter the names of the files consisting of integers (type 'done' to finish):"<<endl;
    while (fileCount < maxFiles && cin>>filename && filename != "done"){
        filenames[fileCount++] = filename;
    }
    cin.ignore();
    string outputFilename;
    cout<<"Enter the name of the output file for the results:"<<endl;
    getline(cin,outputFilename);

    if (outputFilename.find(".csv") == string::npos) {
        outputFilename += ".csv";
    }

    ofstream resultFile(outputFilename);
    while (!resultFile.is_open()) {
        cout<<"Error opening output file. Please try again"<<endl;
        cin>>outputFilename;
    }

    resultFile<<"File,Sort Method,comparisons,exchanges"<<endl;

    for (int i = 0; i < fileCount; i++) {
        string file = filenames[i];
        int size = 0;

        int* numbers = readFile(file, size);

        if (!numbers) {
            cout<<"Failed to read file: "<<file<<endl;
            continue;
        }

        for (int methodIndex = 0; methodIndex < 5; methodIndex++) {
            comparisons = 0;
            exchanges = 0;
            
            int* data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = numbers[i];
            }

            switch(methodIndex + 1) {
                case 1: {
                    quickSortPivot1(data, 0, size -1, comparisons, exchanges);
                    break;
                }
                case 2: {
                    quickSortPivot50(data, 0, size -1, comparisons, exchanges);
                    break;  
                }
                case 3: {
                    quickSortPivot100(data, 0, size -1, comparisons, exchanges);
                    break;
                }
                case 4: {
                    quickSortPivotMedian(data, 0, size -1, comparisons, exchanges);
                    break;
                }
                case 5: {
                    Node* root = arrayToList(data, size);
                    mergeSort(root, comparisons, exchanges);
                    listToArray(root, data, size);
                    break;
                }
            }

            totalComparisons[methodIndex] += comparisons;
            totalExchanges[methodIndex] += exchanges;
            grandTotalComparisons += comparisons;
            grandTotalExchanges += exchanges;

            resultFile<<file<<","<<methodNames[methodIndex]<<","<<comparisons<<","<<exchanges<<endl;
            
            if (size == 50 || size == 51) {
                string sortedFile = file + " " + methodNames[methodIndex] + "_sorted.txt";
                ofstream sortedOutput(sortedFile);
                for (int j = 0; j < size; j++) {
                    sortedOutput<<data[j]<<" ";
                }
                sortedOutput.close();
            }

            delete[] data;
        }

        delete[] numbers;
    }

    resultFile<<endl<<"Summary of Results"<<endl;
    resultFile<<","<<"Method,Total Comparisons,Total Exchanges"<<endl;

    for (int i = 0; i < 5; i++) {
        resultFile<<","<<methodNames[i]<<","<<totalComparisons[i]<<","<<totalExchanges[i]<<endl;
    }

    resultFile<<","<<"Grand Total,"<<grandTotalComparisons<<","<<grandTotalExchanges<<endl;
    cout<<"Results written to "<<outputFilename<<endl;

    cout<<endl<<"Summary of Results"<<endl;
    cout<<"Method"<<"\t\tTotal Comparisons"<<"\tTotal Exchanges"<<endl;
    for (int i = 0; i < 5; i++) {
        cout<<methodNames[i]<<"\t"<<totalComparisons[i]<<"\t\t\t"<<totalExchanges[i]<<endl;
    }
    cout<<"Grand Total"<<"\t"<<grandTotalComparisons<<"\t\t\t"<<grandTotalExchanges<<endl;

    return 0;
}
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

int partition(int arr[], int left, int right, int pivotType) {
    int pivot;
    int i = left + 1;
    int j = right;

    switch (pivotType){
        case 1:
            pivot = arr[left];
            break;
        case 2:
            if (right - left + 1 <= 100) {
                insertionSort(arr, left, right);
                return left;
            }
            pivot = arr[left];
            break;
        case 3:
            if (right - left + 1 <= 50) {
                insertionSort(arr, left, right);
                return left;
            }
            pivot = arr[left];
            break;
        case 4:
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
        default:
            pivot = arr[left];
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

void quickSortPivot100(int arr[], int left, int right) {
    
}

void quickSortPivot50(int arr[], int left, int right) {
    
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

}

void insert(Node*& head, int data) {

}

int main() {

}
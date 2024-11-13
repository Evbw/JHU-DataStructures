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

void quickSortPivot1(int arr[], int left, int right) {

}

void quickSortPivot100(int arr[], int left, int right) {
    
}

void quickSortPivot50(int arr[], int left, int right) {
    
}

void quickSortPivotMedian(int arr[], int left, int right) {
    
}

int partition(int arr[], int left, int right, int pivotType) {
    int pivot = arr[left];
    int i = left + 1;
    int j = right;

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
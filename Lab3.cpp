#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
    Node(int freq, Node* l, Node* r) : character('\0'), frequency(freq), left(l), right(r) {}
};

int main() {

    return 0;
}
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

class PriorityQueue {

};

Node* buildHuffmanTree(char characters[], int frequencesp[], int n) {

}

void preOrderTraversal(Node* root, string code) {
    
}

int readFrequencyTable(const string& filename, char characters[], int frequencies[]) {        //File opening operation
    ifstream inFile;
    inFile.open(filename);                                      //Open file!

    while (!inFile) {                                           //If the file fails to open, enter a loop until a valid file name is chosen
        cout<<"Error reading frequency table. Please try again"<<endl;
        return 0;
    }

    int count = 0;
    char hyphen;

    while (inFile>>characters[count]>>hyphen>>frequencies[count]) {
        if (hyphen != '-') {
            cout<<"hypen error"<<endl;
            return 0;
        }
        count++;
    }
    inFile.close();
    cout<<count<<endl;
    return count;
}

void readTextFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Error opening file: "<<filename<<endl;
        return;
    }

    string line;
    while(getline(file, line)) {
        cout<<line<<endl;
    }
    file.close();
}

int main() {
    string freqFileTable, clearTextFile, encodedFile, choice = "y";
    cout<<"This program is intended to build a Huffman encoding tree which will return results in preorder traversal."<<endl<<endl;
    cout<<"Enter the name of the file containing the frequency table: "<<endl;
    cin>>freqFileTable;
    cout<<"Enter the name of the file containing plain text: "<<endl;
    cin>>clearTextFile;
    cout<<"Enter the name of the file containing encoded text: "<<endl;
    cin>>encodedFile;

    char characters[26];
    int frequencies[26];

    if (readFrequencyTable(freqFileTable, characters, frequencies) == 0) {
        cout<<"Error reading frequency table. Please try again"<<endl;
        return 0;
    }

    cout<<"Plain text file contents: "<<endl;
    readTextFile(clearTextFile);

    cout<<endl;
    cout<<"Encoded text file contents: "<<endl;
    readTextFile(encodedFile);

    cout<<endl;
    cout<<"Exiting program. Come back now, ya hear?"<<endl;
    return 0;
}
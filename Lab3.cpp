#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void openInputFile(ifstream& inFile, string& filename) {        //File opening operation
    cout<<"Enter the filename: "<<endl;                         //Request name of input file
    getline(cin, filename);                                     //Get input
    inFile.open(filename);                                      //Open file!
    while (!inFile) {                                           //If the file fails to open, enter a loop until a valid file name is chosen
        cout<<"File failed to open. Please ensure the file exists and you have the correct permissions."<<endl;
        cout<<"Enter the filename: "<<endl;
        inFile.clear();
        getline(cin, filename);
        inFile.open(filename);
    }
}

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

int main() {
    ifstream inFile;
    string freqFileTable, clearTextFile, encodedFile, choice = "y";
    cout<<"This program is intended to build a Huffman encoding tree which will return results in preorder traversal."<<endl<<endl;
    cout<<"Enter the name of the file containing the frequency table: "<<endl;
    cin>>freqFileTable;

    do {                                        //do while loop to allow multiple inputs from the user
        openInputFile(inFile, freqFileTable);

        if(inFile) {
            
        }
        else {
            cout<<"Error reading file. Would you like to try again?";
            cin>>choice;
        }

        inFile.close();                         //Close and clear the file for multiple inputs.
        inFile.clear();
        
    } while (choice == "y" || choice == "yes" || choice == "Y" || choice == "Yes");


    cout<<endl;
    cout<<"Exiting program. Come back now, ya hear?"<<endl;
    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node {

    public:
        char character;
        int frequency;
        Node* left;
        Node* right;

        Node(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
        Node(int freq, Node* l, Node* r) : character('\0'), frequency(freq), left(l), right(r) {}
};

class PriorityQueue {
    private:
        Node* elements[1000]; //arbitrary size for testing
        int size;
    public:
        PriorityQueue() : size(0) {}

        void push(Node* newNode) {

            int i = size;
            elements[size++] = newNode;

            while (i > 0 && elements[(i-1)/2]->frequency>elements[i]->frequency) {
                swap(elements[i], elements[(i-1)/2]);
                i = (i-1)/2;
            }
        }

        Node* pop() {
            if (size == 0) {
                return nullptr;
            }
            Node* minNode = elements[0];
            elements[0] = elements[--size];

            int i = 0;
            while (2 * i + 1<size) {
                int j = 2 * i + 1;
                if (j +1 < size && elements[j]->frequency > elements[j+1]->frequency) {
                    j++;
                }
                if (elements[i]->frequency <= elements[j]->frequency) {
                    break;
                }
                swap(elements[i], elements[j]);
                i = j;
            }
            return minNode;
        }

        int getSize() const {
            return size;
        }
};

Node* buildHuffmanTree(char characters[], int frequencies[], int n) {
    PriorityQueue pq;

    for (int i = 0; i < n; i++) {
        Node* newNode = new Node(characters[i], frequencies[i]);
        pq.push(newNode);
    }

    while (pq.getSize() > 1) {
        Node* left = pq.pop();
        Node* right = pq.pop();
        Node* newNode = new Node(left->frequency + right->frequency, left, right);
        pq.push(newNode);
    }

    return pq.pop();
}

void preOrderTraversal(Node* root, string code, char codeCharacters[], string codes[], int& codeIndex, string& treeStructure) {
    if (!root) return;
    if (root->character != '\0') {
        cout<<root->character<<":"<<code<<endl;
        codeCharacters[codeIndex] = root->character;
        codes[codeIndex] = code;
        codeIndex++;

        treeStructure += string(1, root->character) + ":" + to_string(root->frequency) + " ";
    }

    preOrderTraversal(root->left, code+"0", codeCharacters, codes, codeIndex, treeStructure);
    preOrderTraversal(root->right, code+"1", codeCharacters, codes, codeIndex, treeStructure);
}

string encodeText(const string& text, char codeCharacters[], string codes[], int codeIndex) {
    string encodedText;
    for (char c : text) {

        if (c == '\n') {
            encodedText += "\n";
            continue;
        }

        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) {
            continue;
        }

        char searchChar = (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c;
        bool found = false;
        for (int i = 0; i < codeIndex; i++) {
            if (codeCharacters[i] == searchChar) {
                encodedText += codes[i];
                found = true;
                break;
            }
        }

        if (!found && c != '\n') {
            cout<<"Warning: Character '"<<c<<"' not found in Huffman codes. Skipping it."<<endl;
        }
    }
    return encodedText;
}

string decodeText(const string& encodedText, Node* root) {
    string decodedText;
    Node* currentNode = root;

    for (char bit : encodedText) {
        if (bit == '\n') {
            decodedText += '\n';
        }

        if (bit == '0') {
            currentNode = currentNode->left;
        } else if (bit == '1') {
            currentNode = currentNode->right;
        }

        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            decodedText += currentNode->character;
            currentNode = root;
        }
    }

    return decodedText;
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
        bool found = false;

        if (hyphen != '-') {
            cout<<"Hyphen error"<<endl;
            return 0;
        }

        if ((characters[count] >= 'a' && characters[count] <= 'z')) {
            characters[count] = characters[count] - 'a' + 'A';
        }

        if (characters[count] >= 'a' && characters[count] <= 'z') {
            characters[count] = characters[count] - 'a' + 'A';
        }

        for (int i = 0; i < count; i++) {
            if (characters[i] == characters[count]) {
                frequencies[i] += frequencies[count];
                found = true;
                break;
            }
        }
        if (!found) {
            count++;
        }
    }
    inFile.close();
    return count;
}

string readTextFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Error opening file: "<<filename<<endl;
        return "";
    }

    string text, line;
    while(getline(file, line)) {
        text += line + "\n";
    }
    file.close();
    return text;
}

int main() {
    string freqFileTable, clearTextFile, encodedFile, treeStructure, choice = "y";

    cout<<"This program is intended to build a Huffman encoding tree which will return results in preorder traversal."<<endl<<endl;
    cout<<"Enter the name of the file containing the frequency table: "<<endl;
    cin>>freqFileTable;
    cout<<"Enter the name of the file containing plain text: "<<endl;
    cin>>clearTextFile;
    cout<<"Enter the name of the file containing encoded text: "<<endl;
    cin>>encodedFile;

    char characters[26];
    int frequencies[26];
    char codeCharacters[26];
    string codes[26];
    int codeIndex = 0;

    int n = readFrequencyTable(freqFileTable, characters, frequencies);
    if ( n == 0) {
        cout<<"Error reading frequency table. Please try again"<<endl;
        return 0;
    }
    
    Node* root = buildHuffmanTree(characters, frequencies, n);

    cout<<"Huffman Codes:"<<endl<<endl;
    preOrderTraversal(root, "", codeCharacters, codes, codeIndex, treeStructure);

    cout<<endl<<"The tree in preorder is: "<<treeStructure<<endl;

    string clearText = readTextFile(clearTextFile);

    cout<<endl;
    cout<<"Encoded Text:"<<endl<<encodeText(clearText, codeCharacters, codes, codeIndex);

    cout<<endl;
    cout<<"Exiting program. Come back now, ya hear?"<<endl;
    return 0;
}
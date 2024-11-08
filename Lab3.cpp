#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node {

    public:
        string characters;
        int frequency;
        Node* left;
        Node* right;

        Node(char c, int freq) : characters(1, c), frequency(freq), left(nullptr), right(nullptr) {}
        Node(string chars, int freq, Node* l, Node* r) : characters(chars), frequency(freq), left(l), right(r) {}
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
        Node* newNode = new Node(left->characters + right->characters, left->frequency + right->frequency, left, right);
        pq.push(newNode);

    }

    return pq.pop();
}

void preOrderTraversal(Node* root, string code, char codeCharacters[], string codes[], int& codeIndex, string& treeStructure) {
    if (!root) return;

    treeStructure += root->characters + ":" + to_string(root->frequency) + " ";

    if (root->left == nullptr && root->right == nullptr) {
        cout<<root->characters<<":"<<code<<endl;
        codeCharacters[codeIndex] = root->characters[0];
        codes[codeIndex] = code;
        codeIndex++;
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
            decodedText += currentNode->characters;
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

void createFrequencyTable(char characters[], int frequencies[], int& n) {
    cout<<"Enter the frequency table in the format 'A 0' or 'A 00', where A is a letter (upper or lowercase) and 0 is a number 0-9. Type END to finish."<<endl;
    string line;
    n = 0;
    
    while (true) {
        cout<<"Enter entry #"<<(n+1)<<": ";
        getline(cin, line);
        if (line == "END") {
            break;
        }
        
        if (line.length() >= 2 && line[1] == ' ') {
            char character = line[0];
            int frequency = stoi(line.substr(1));

            if ((character < 'A' || (character > 'Z' && character < 'a') || character > 'z') || frequency < 0) {
                cout<<"Invalid input. Please enter an upper or lowercase letter followed by a frequency at or above 0."<<endl;
                continue;
            }

            if (character >= 'a' && character <= 'z') {
                character = character - 'a' + 'A';
            }

            bool found = false;

            for (int i = 0; i < n; i++) {
                if (characters[i] == character) {
                    frequencies[i] += frequency;
                    found = true;
                    break;
                }
            }

            if (!found) {
                characters[n] = character;
                frequencies[n] = frequency;
                n++;
            } else if (found) {
                cout<<"Invalid format. Entry already made."<<endl;
            } else {
                cout<<"Invalid format. Enter the frequency table in the format 'A 0' or 'A 00', where 0 is a number 0-9."<<endl;
            }
        }
    }
    cout<<"Frequency Table entry complete."<<endl;
}

string readTextFile(const string& filename) {
    ifstream file(filename);
    while (!file.is_open()) {
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

string readEncodedText(const string& filename) {
    ifstream file(filename);
    while (!file.is_open()) {
        cout<<"Error opening file: "<<filename<<endl;
        return "";
    }

    string encodedText, line;
    while (getline(file, line)) {
        encodedText += line + "\n";
    }
    file.close();
    return encodedText;
}

/*  ----------------------------------------------------------
    Method: writeOutput
    Description: Writes the processed results to the output file. Ensures the valid results are written.
    Parameters:
        - result (const string&): The result from the parseAndPush function, a postfix expression.
        - input (const string&): The string that contains the prefix expression
        - outFile (ofstream&): The output file, to which the results are added.
    ----------------------------------------------------------
*/

void writeOutput(ofstream& outFile, const string& result) {  //Write the input and output to file
    outFile<<result<<endl;
}

/*  ----------------------------------------------------------
    Method: createOutputFilename
    Description: Creates the name of the output file
    Parameters:
        - filename (const string&): The input filename, to which "- output" is added.
    Returns:
        - A string containing the filename.
    ----------------------------------------------------------
*/   

string createOutputFilename(const string& filename) {       //Create a new filename with " - output" appended
    string outputFilename;
    cout<<"Enter the name of the output file or press enter to use default filename. Filetype will be a txt: "<<endl;
    getline(cin,outputFilename);

    if (outputFilename.empty()) {                           //If the user chooses to use the default file name, follow default behavior    
        int dotPos = filename.find_last_of('.');            //Find the position of the dot in the input file
        if (dotPos != string::npos) {
            return filename.substr(0, dotPos) + " - output" + ".txt"; //And presuming it exists, append " - output" to it
        }
        return filename + " output";                        //If the filename doesn't have a type associated, then just output will be appended
    } else {
            return outputFilename + ".txt";
         }

    return outputFilename;                                  //Return the user created filename.
}

int main() {
    string freqFileTable, clearTextFile, encodedFile, treeStructure, choice, encodedInput, decodedText, manualInput;
    char characters[26];
    int frequencies[26];
    char codeCharacters[26];
    string codes[26];
    int codeIndex = 0;
    int n = 0;
    Node* root = nullptr;
    string saveChoice;

    cout<<"This program is intended to build a Huffman encoding tree which will return results in preorder traversal."<<endl<<endl;
    
    while (true) {
        cout<<"Choose the method of entry for the frequency table"<<endl;
        cout<<"1. Load from file"<<endl;
        cout<<"2. Free entry"<<endl;
        cout<<"3. Use previous"<<endl;
        cout<<"4. Exit program"<<endl;
        cout<<"Select 1, 2, 3, or 4"<<endl;
        cin>>choice;
        cin.ignore();

        if (choice == "1") {
            cout<<"Enter the name of the file containing the frequency table: "<<endl;
            cin>>freqFileTable;
            cin.ignore();
            int n = readFrequencyTable(freqFileTable, characters, frequencies);
            if (n == 0) {
                cout<<"Error reading frequency table. Please try again"<<endl;
                continue;
            }
            root = buildHuffmanTree(characters, frequencies, n);
            cout<<"Frequency Table loaded from file."<<endl;
        } else if (choice == "2") {
            createFrequencyTable(characters, frequencies, n);
            if (n == 0) {
                cout<<"No valid frequency table entered. Please try again."<<endl;
                continue;
            }
            root = buildHuffmanTree(characters, frequencies, n);
        } else if (choice == "3"){
            if (root == nullptr) {
                cout<<"Frequency table required. Exiting program."<<endl;
                break;
            }
            cout<<"Using previously created frequency table"<<endl;
        } else {
            cout<<"Exiting program."<<endl;
            break;
        }
        codeIndex = 0;
        treeStructure.clear();
        cout<<endl<<"Huffman Codes:"<<endl<<endl;
        preOrderTraversal(root, "", codeCharacters, codes, codeIndex, treeStructure);
        cout<<endl<<"The tree in preorder is: "<<treeStructure<<endl;

        choice = "0";

        cout<<endl<<"Would you like to decode or encode text?"<<endl;
        cout<<"1. Decode text"<<endl;
        cout<<"2. Encode text"<<endl;
        cout<<"3. Exit program"<<endl;
        cout<<"Select 1, 2, or 3"<<endl;
        cin>>choice;
        cin.ignore();

       if (choice == "1") {
            choice = "0";
            cout<<endl<<"Would you like to decode from file or enter encoded text manually?"<<endl;
            cout<<"1. Decode from file"<<endl;
            cout<<"2. Decode manually"<<endl;
            cout<<"3. Exit program"<<endl;
            cout<<"Select 1, 2, or 3"<<endl;
            cin>>choice;
            cin.ignore();
            if (choice == "1") {
                cout<<endl<<"Enter the name of the file containing encoded text: "<<endl;
                cin>>encodedFile;
                cin.ignore();
                encodedInput = readEncodedText(encodedFile);
                decodedText = decodeText(encodedInput, root);
            } else if (choice == "2") {
                cout<<"Enter the encoded text in 1s and 0s: "<<endl;
                getline(cin, encodedInput);
                decodedText = decodeText(encodedInput, root);
            } else {
                cout<<"Exiting program."<<endl;
                break;
            }
            cout<<"Decoded text: "<<endl<<decodedText<<endl;
            cout<<"Would you like to save the result to a file? (y/n) "<<endl;
            char saveChoice;
            cin>>saveChoice;
            cin.ignore();
            if (tolower(saveChoice) == 'y') {
                string outputFilename = createOutputFilename(clearTextFile);
                ofstream outFile(outputFilename);
                if (!outFile){
                    cout<<"File creation failed. Please ensure you have the correct permissions."<<endl;
                } else {
                    writeOutput(outFile, decodedText);
                    cout<<"File saved as "<<outputFilename<<endl;
                    outFile.close();
                }
            }
       } else if (choice == "2") {
            choice = "0";
            cout<<"Would you like to encode from file or enter text manually?"<<endl;
            cout<<"1. Encode from file"<<endl;
            cout<<"2. Encode manually"<<endl;
            cout<<"3. Exit program"<<endl;
            cout<<"Select 1, 2, or 3"<<endl;
            cin>>choice;
            cin.ignore();
            if (choice == "1") {
                cout<<endl<<"Enter the name of the file containing encoded text: "<<endl;
                cin>>clearTextFile;
                cin.ignore();
                string clearText = readTextFile(clearTextFile);
                if (!clearText.empty()) {
                    encodedInput = encodeText(clearText, codeCharacters, codes, codeIndex);
                } else {
                    cout<<"Unable to read file. Please try again."<<endl;
                    continue;
                }
            } else if (choice == "2") {
                cout<<endl<<"Enter the text to be encoded: "<<endl;
                getline(cin, manualInput);
                encodedInput = encodeText(manualInput, codeCharacters, codes, codeIndex);
            } else {
                cout<<"Exiting program."<<endl;
                break;
            }
            cout<<"Encoded text: "<<endl<<encodedInput<<endl;
            cout<<"Would you like to save the result to a file? (y/n) "<<endl;
            char saveChoice;
            cin>>saveChoice;
            cin.ignore();
            if (tolower(saveChoice) == 'y') {
                string outputFilename = createOutputFilename(clearTextFile);
                ofstream outFile(outputFilename);
                if (!outFile){
                    cout<<"File creation failed. Please ensure you have the correct permissions."<<endl;
                } else {
                    writeOutput(outFile, encodedInput);
                    cout<<"File saved as "<<outputFilename<<endl;
                    outFile.close();
                }
            }
        } else {
            cout<<"Exiting program."<<endl;
            break;
        }
    }

    if (choice != "3" && choice != "4") {
        cout<<endl;
        cout<<"Exiting program. Come back now, ya hear?"<<endl;
    }
    return 0;
}
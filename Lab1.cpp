#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void openInputFile(ifstream& inFile) {      //File opening operation
    string filename;
    cout<<"Enter the filename: "<<endl;     //Request name of input file
    getline(cin,filename);                  //Get input
    inFile.open(filename);                  //Open file!
    while (!inFile) {                       //If the file fails to open, enter a loop until a valid file name is chosen
        cout<<"File failed to open."<<endl;
        cout<<"Enter the filename: "<<endl;
        getline(cin,filename);
        inFile.clear();
        inFile.open(filename);
    }
}

void parseAndPush(const string& input) {  //Read the file, create a stack, and push the items to it
    Stack stack(input.size());
    for ( size_t i = 0; i < input.size(); i++ ) {
            char c = input[i];
            stack.push(c);
        }
}

bool readLines(ifstream& inFile) {          //Add function to read file
    string input;

    while ( getline(inFile, input) ) {      //Accept input
        cout<<input<<endl;
        parseAndPush(input);
    }
}
class Stack {                               //Add Stack class to handle creation of stack and handling stack functions
    private:
        int top;
        int capacity;
        int* stackArray;
        
    public:
        Stack(int size) {                   //Constructor
            capacity = size;
            stackArray = new int[capacity];
            top = -1;
        }

        void push(int item) {               //Push an item onto the stack
            if (top < capacity - 1) {
                stackArray[++top] = item;
            } else {
                cout << "Stack overflow, cannot push." << endl;
                return -1;
            }
        }

        int pop() {                         //Pop an item from the stack
            if (top >= 0) {
                return stackArray[top--];
            } else {
                cout << "Stack underflow, cannot pop." << endl;
                return -1;
            }
        }

        int peek() {                        //View the top item of the stack
            if (top >= 0) {
                return stackArray[top];
            } else {
                cout << "Stack is empty, cannot peek." << endl;
                return -1;
            }
        }

        bool isEmpty() {                    //Return bool regarding the emptiness of the stack.
            return top == -1;
        }

        ~Stack() {                          //Destructor
            delete[] stackArray;
        }
};

int main() {                                //Main driver function. Accept input and call handler function
    ifstream inFile;
    openInputFile(inFile);

    if(inFile) {
        readLines(inFile);
        cout<<"Success opening the file!"<<endl;
    }
    else {
        cout<<"Try again"<<endl;
    }
    inFile.clear();
    return 0;
}
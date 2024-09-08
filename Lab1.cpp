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

bool readLines(ifstream& inFile) {          //Add function to read file
    string input;

    while ( getline(inFile, input) ) {      //Accept input
        cout<<input<<endl;
        for ( size_t i = 0; i < input.size(); i++ ) {
            char c = input[i];
            cout<<c<<endl;
        }
    }
}
class Stack {                               //Add Stack class to handle creation of stack and handling stack functions
    private:
        int top;
        int capacity;
        int* stackArray;
        
    public:
        Stack(int size) {                       //Constructor
            capacity = size;
            stackArray = new int[capacity];
            top = -1;
        }

        void push(int item) {                   //Push an item onto the stack
            if (top < capacity - 1) {
                stackArray[++top] = item;
            } else {
                cout << "Stack overflow, cannot push." << endl;
            }
        }

        int pop() {                             //Pop an item from the stack
            if (top >= 0) {
                return stackArray[top--];
            } else {
                cout << "Stack underflow, cannot pop." << endl;
                return -1;
            }
        }   

        ~Stack() {                              //Destructor
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
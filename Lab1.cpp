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
        cout<<"File failed to open. Please ensure the file exists and you have the correct permissions."<<endl;
        cout<<"Enter the filename: "<<endl;
        inFile.clear();
        getline(cin,filename);
        inFile.open(filename);
    }
}

class Stack {                               //Add Stack class to handle creation of stack and handling stack functions
    private:
        int top;
        int capacity;
        string* stackArray;
        
    public:
        Stack(int size) {                   //Constructor
            capacity = size;
            stackArray = new string[capacity];
            top = -1;
        }

        void push(string item) {            //Push an item onto the stack
            if (top < capacity - 1) {
                stackArray[++top] = item;
            } else {
                cout << "Stack overflow, cannot push." << endl;
            }
        }

        int size() {                        //Return the size of the stack. It indexed at zero, so we find the top and add one
            return top + 1;
        }

        string pop() {                      //Pop an item from the stack
            if (top >= 0) {
                return stackArray[top--];
            } else {
                cout << "Stack underflow, cannot pop." << endl;
                return "";
            }
        }

        string peek() {                        //View the top item of the stack
            if (top >= 0) {
                return stackArray[top];
            } else {
                cout << "Stack is empty, cannot peek." << endl;
                return "";
            }
        }

        bool isEmpty() {                    //Return bool regarding the emptiness of the stack.
            return top == -1;
        }

        ~Stack() {                          //Destructor
            delete[] stackArray;
        }
};

void preToPost(Stack& stack) {              //Translator function to get the equations from prefix to postfix form
    string operand1 = stack.pop();
    string operand2 = stack.pop();
    string op = stack.pop();
    string postfix = operand2 + operand1 + op;
    stack.push(postfix);
}

bool isOperator(const string& c) {         //Return bool regarding the emptiness of the stack.
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "$");
}

bool isOperand(const string& c) {
    return (c[0] >= 'A' && c[0] <= 'Z') || (c[0] >= '0' && c[0] <= '9');
}

bool validityChecker(const string& input, int lineNumber) {

    if (!isOperator(string(1, input[0]))) {
        cout<<"Invalid format for line #"<<lineNumber<<". Please confirm it is in prefix form."<<endl;
        return false;
    }

    for ( size_t i = 0; i < input.size(); i++ ) {
        string c = string(1, input[i]);
        if (!isOperator(c) && !isOperand(c)) {
            cout<<"Invalid format for line #"<<lineNumber<<". Please confirm it is in prefix form."<<endl;
            return false;
        }
    }
    return true;
}

void parseAndPush(const string& input) {    //Read the file, create a stack, and push the items to it
    Stack stack(input.size());

    for ( size_t i = 0; i < input.size(); i++ ) {
        string c = string(1, input[i]);
       
        stack.push(c);

        if (stack.size() >= 3) {
            string top1 = stack.pop();
            string top2 = stack.pop();
            string op = stack.pop();

            if (!isOperator(top1) && !isOperator(top2) && isOperator(op)) {
                string postfix = top2 + top1 + op;
                stack.push(postfix);

                while (stack.size() >= 3) {
                    string top1 = stack.pop();
                    string top2 = stack.pop();
                    string op = stack.pop();

                    if (!isOperator(top1) && !isOperator(top2) && isOperator(op)) {
                    string postfix = top2 + top1 + op;
                    stack.push(postfix);
                    } else {
                        stack.push(op);
                        stack.push(top2);
                        stack.push(top1);
                        break;
                    }
                }
            } else {
                stack.push(op);
                stack.push(top2);
                stack.push(top1);
            }
        }
    }

    while (!stack.isEmpty()) {
        cout<<stack.pop();
    }
    cout<<endl;
}

bool readLines(ifstream& inFile) {          //Add function to read file
    string input;
    int lineNumber = 1;

    while ( getline(inFile, input) ) {      //Accept input
        if (validityChecker(input, lineNumber)) {
            parseAndPush(input);
        }
        lineNumber++;
    }
    return true;
}

string convertToLowercase(const string& str) 
{ 
    string result = ""; 
  
    for (char ch : str) { 
        //Convert each character to lowercase using tolower 
        result += tolower(ch); 
    } 
  
    return result; 
} 

void menu() {
    ifstream inFile;
    string choice = "y";

    cout<<"Welcome! This program converts prefix equations into postfix form. "<<endl;

    do {
        openInputFile(inFile);

        if(inFile) {
            readLines(inFile);
        }
        else {
            cout<<"Error reading file. ";
        }

        inFile.close();
        inFile.clear();

        cout<<"Would you like to process another file? (Y/Yes/N/No): "<<endl;
        getline(cin, choice);

        convertToLowercase(choice);

        if (choice == "n" || choice == "no") {
            cout << "Exiting program." << endl;
            break;
        }
        
    } while (choice == "y" || choice == "yes");
    
}

int main() {                                //Main driver function. Accept input and call handler function
    menu();
    return 0;
}
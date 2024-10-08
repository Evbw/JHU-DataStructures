#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void openInputFile(ifstream& inFile, string& filename) {        //File opening operation
    cout<<"Enter the filename: "<<endl;                         //Request name of input file
    getline(cin, filename);                                      //Get input
    inFile.open(filename);                                      //Open file!
    while (!inFile) {                                           //If the file fails to open, enter a loop until a valid file name is chosen
        cout<<"File failed to open. Please ensure the file exists and you have the correct permissions."<<endl;
        cout<<"Enter the filename: "<<endl;
        inFile.clear();
        getline(cin, filename);
        inFile.open(filename);
    }
}

class Stack {                                                   //Add Stack class to handle creation of stack and handling stack functions
    private:
        int top;
        int capacity;
        string* stackArray;
        
    public:
        Stack(int size) {                                       //Constructor
            capacity = size;
            stackArray = new string[capacity];
            top = -1;
        }

        void push(string item) {                                //Push an item onto the stack
            if (top < capacity -1) {
                stackArray[++top] = item;
            } else {
                cout<<"Stack overflow, cannot push."<<endl;
            }
        }

        int size() {                                            //Return the size of the stack. It indexed at zero, so we find the top and add one
            return top + 1;
        }

        string pop() {                                          //Pop an item from the stack
            if (top >= 0) {
                return stackArray[top--];
            } else {
                cout<<"Stack underflow, cannot pop."<<endl;
                return "";
            }
        }

        string peek() {                                         //View the top item of the stack
            if (top >= 0) {
                return stackArray[top];
            } else {
                cout<<"Stack is empty, cannot peek."<<endl;
                return "";
            }
        }

        bool isEmpty() {                                        //Return bool regarding the emptiness of the stack.
            return top == -1;
        }

        ~Stack() {                                              //Destructor
            delete[] stackArray;
        }
};

bool isOperator(const string& c) {                              //Check if the character is an operator
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "$");
}

bool isOperand(const string& c) {                               //Check if the character is an operand
    return (c[0] >= 'A' && c[0] <= 'Z') || (c[0] >= '0' && c[0] <= '9');
}

bool validityChecker(const string& input, int lineNumber) {     //Check to confirm the line being checked is indeed a prefix form equation

    if (!isOperator(string(1, input[0]))) {                     //The first step is to see if the first character is an operator. If it is not, then it's not prefix form
        cout<<"Invalid format for line #"<<lineNumber<<". Please confirm it is in prefix form. Operands should only be capital letters (A-Z) and numbers (0-9)."<<endl;
        return false;
    }

    for (int i = 0; i < input.size(); i++) {                    //The next step is to iterate through all of the characters to confirm they are prefix
        string c = string(1, input[i]);                         //No spaces, no parentheses, and anything from A-Z or 0-9 is not allowed
        if (!isOperator(c) && !isOperand(c)) {
            cout<<"Invalid format for line #"<<lineNumber<<". Please confirm it is in prefix form. Operands should only be capital letters (A-Z) and numbers (0-9)."<<endl;
            return false;
        }
    }
    return true;
}

/*string parseAndPush(const string& input) {                      //Create a stack and push the items read from the line to it
    Stack stack(input.size());
    string result;

    for (int i = 0; i < input.size(); i++) {                    //Iterate through the stack
        string c = string(1, input[i]);                         //Extract the character
       
        stack.push(c);                                          //And push it to the stack

        if (stack.size() >= 3) {                                //Once we get to a size of 3 (or more), we check the previous three items
            string top1 = stack.pop();                          //And store them in temp variables for comparison
            string top2 = stack.pop();
            string op = stack.pop();

            if (isOperand(top1) && isOperand(top2) && isOperator(op)) { //If they match the conditionals, then they're candidates for being converted
                string postfix = top2 + top1 + op;              //Create a new string based on the combination
                stack.push(postfix);                            //And push it to the stack

                while (stack.size() >= 3) {                     //I will need to check previous additions to the stack, however, and compare them
                    string top1 = stack.pop();                  //The previous operands+operator combo will now be treated as a single string
                    string top2 = stack.pop();                  //So if the previous addition is also a string and the following variable is an
                    string op = stack.pop();                    //operator, then we can add that to the stack, too

                    if (isOperand(top1) && isOperand(top2) && isOperator(op)) {
                        string postfix = top2 + top1 + op;
                        stack.push(postfix);
                    } else {                                    //Otherwise we add them all back to the stack in order and exit the while loop
                        stack.push(op);
                        stack.push(top2);
                        stack.push(top1);
                        break;
                    }
                }
            } else {                                            //Putting the items we popped back in order to check the next character
                stack.push(op);
                stack.push(top2);
                stack.push(top1);
            }
        }
    }

    while (!stack.isEmpty()) {                                  //And then we pop everything off of the stack for display
        result += stack.pop();
    }
    return result;
}*/

void parseAndPush(const string& input) {                     //Driver function for the recursive parseAndPush
    Stack stack(input.size());
    int index = 0;  
    parseAndPush(input, index, stack);

    while (!stack.isEmpty()) {
        cout<<stack.pop();
    }
    cout<<endl;
}

void parseAndPush(const string& input, int& index, Stack& stack) { //Main recursive function
    if (index >= input.size()) {                             //Base case
        return;
    }

    string c = string(1, input[index]);
    index++;

    if (isOperator(c)) {
        parseAndPush(input, index, stack);
        parseAndPush(input, index, stack);

        string operand1 = stack.pop();
        string operand2 = stack.pop();
        string postfix = operand2 + operand1 + c;
        stack.push(postfix);
    } else {
        stack.push(c);
    }
}

void writeOutput(ofstream& outFile, const string& input, const string& result) {  //Write the input and output to file
    outFile<<input<<" = "<<result<<endl;
}

void readLines(ifstream& inFile, ofstream& outFile, string outputFilename, bool& outputWritten) {   //This will read individual lines from the file until eof
    string input;
    int lineNumber = 1;

    while (getline(inFile, input)) {                        //Set loop for each additional line
        if (validityChecker(input, lineNumber)) {           //Call validityChecker function to confirm the lines are in the proper format
            string result = parseAndPush(input);            //Call parseAndPush function to begin process of identifying output and set it to the result
            cout<<input<<" = "<<result<<endl;               //Display input and output to terminal
            if (result != "") {
                if (!outputWritten) {
                    outFile.open(outputFilename, ios::app); //Open output file for output to be appended
                    outputWritten = true;
                }
                writeOutput(outFile, input, result);        //Write output file
            }
        }
        lineNumber++;                                       //Increment line number for validityChecker
    }
}

string createOutputFilename(const string& filename) {       //Create a new filename with " - output" appended
    int dotPos = filename.find_last_of('.');                //Find the position of the dot
    if (dotPos != string::npos) {
        return filename.substr(0, dotPos) + " - output" + filename.substr(dotPos); //And presuming it exists, append " - output" to it
    }
    return filename + " output";                            //If the filename doesn't have a type associated, then just output will be appended
}

void menu() {                                   //This function welcomes the user and requests input
    ifstream inFile;
    ofstream outFile;
    string filename, choice = "y";

    cout<<"Welcome! This program converts prefix equations into postfix form. "<<endl;

    do {                                        //do while loop to allow multiple inputs from the user
        openInputFile(inFile, filename);

        if(inFile) {
            bool outputWritten = false;
            string outputFilename = createOutputFilename(filename);  //Create output filename                                              
            readLines(inFile, outFile, outputFilename, outputWritten);

            if (!outputWritten) {
                cout<<"No valid input found. No outputfile created."<<endl;
            } 
            else {
                outFile.close();
            }
        }
        else {
            cout<<"Error reading file. ";
        }

        inFile.close();                         //Close and clear the file for multiple inputs.
        inFile.clear();

        cout<<"Would you like to process another file? (Y/Yes for yes. Anything else for No):"<<endl;
        getline(cin, choice);
        
    } while (choice == "y" || choice == "yes" || choice == "Y" || choice == "Yes");
    cout<<endl;
    cout<<"Exiting program. Come back now, ya hear?"<<endl;
}

int main() {                                    //Main driver function. Calls handler function
    menu();
    return 0;
}
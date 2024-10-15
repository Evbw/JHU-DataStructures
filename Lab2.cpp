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

/*  ----------------------------------------------------------
    Class: Stack
    Description: This class implements a stack data structure for storing operators
                 and operands. The stack supports standard operations such as push,
                 pop, peek, and checking if it is empty.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Method: isOperator
    Description: This method checks if a given character is a valid operator (+, -, /, *, ^) for the submitted expression.
    Parameters:
        - c (const string&): The character to be checked.
    Return:
        - bool: Returns true if the character is valid as described in the return statement, false otherwise.
    ----------------------------------------------------------
*/

bool isOperator(const string& c) {                              //Check if the character is an operator
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "$");
}

/*  Method: isOperand
    Description: This method checks if a given character is a valid operand (a letter or number) for the submitted expression.
    Parameters:
        - c (const string&): The character to be checked.
    Return:
        - bool: Returns true if the character is valid as described in the return statement, false otherwise.
    ----------------------------------------------------------
*/

bool isOperand(const string& c) {                               //Check if the character is an operand
    return (c[0] >= 'A' && c[0] <= 'Z') || (c[0] >= '0' && c[0] <= '9');
}

/*  ----------------------------------------------------------
    Method: validityChecker
    Description: This method checks if a given input string is a valid prefix expression. It ensures that the expression
                 starts with an operator, contains valid characters, and has the correct number of operators and operands.
    Parameters:
        - input (const string&): The input string to be checked.
        - lineNumber (int): The line number of the input file being checked for error reporting.
    Return:
        - bool: Returns true if the input string is a valid prefix expression, false otherwise
    ----------------------------------------------------------
*/

bool validityChecker(const string& input, int lineNumber) {     //Check to confirm the line being checked is indeed a prefix form equation

    if (!isOperator(string(1, input[0]))) {                     //The first step is to see if the first character is an operator. If it is not, then it's not prefix form
        cout<<"Invalid format for line #"<<lineNumber<<". Please confirm it is in prefix form. Operands should only be capital letters (A-Z) and numbers (0-9)."<<endl;
        return false;
    }

    int operatorCount = 0;
    int operandCount = 0;

    for (int i = 0; i < input.size(); i++) {                    //The next step is to iterate through all of the characters to confirm they are prefix

        string c = string(1, input[i]);                         

        if (isOperator(c)) {                                    //Count operators
            operatorCount++;
            
        }
        else if (isOperand(c)) {                                //Count operands
            operandCount++;
        }
        else {                                                  //No spaces, no parentheses, and anything not from A-Z or 0-9 is not allowed
            cout<<"Invalid format for line #"<<lineNumber<<". Please confirm it is in prefix form. Operands should only be capital letters (A-Z) and numbers (0-9)."<<endl;
            return false;
        }

    }

    if (operatorCount != operandCount -1) {
        cout<<"Invalid number of operators on line"<<lineNumber<<". Please confirm it is in prefix form. Operands should only be capital letters (A-Z) and numbers (0-9)."<<endl;
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

/*  ----------------------------------------------------------
    Method: parseAndPushR
    Description: Recursively processes a character (operator or operand) from the input string and pushes it
                 onto the stack. It handles different cases depending on the character being an operator or
                 operand.
    Parameters:
        - stack (Stack&): The stack onto which the character is pushed.
        - index (int&): The index where the character resides on the input string.
        - input (const string&): The string that contains the prefix expression.
    ----------------------------------------------------------
*/

void parseAndPushR(const string& input, int& index, Stack& stack) { //Main recursive function
    if (index >= input.size()) {                                    //Base case
        return;
    }

    string c = string(1, input[index]);                             //Extract the character
    index++;                                                        //Increase the index

    if (isOperator(c)) {
        parseAndPushR(input, index, stack);                         //Begin recursive calls to balance the characters in the input
        parseAndPushR(input, index, stack);

        string operand1 = stack.pop();                              //The previous operands+operator combo will be combined into a single string
        string operand2 = stack.pop();
        string postfix = operand2 + operand1 + c;
        stack.push(postfix);
    } else {
        stack.push(c);                                              //Otherwise, push the operator to the stack
    }
}

/*  ----------------------------------------------------------
    Method: parseAndPush
    Description: Driver function for the recursive parseAndPushR.
    Parameters:
        - input (const string&): The string that contains the prefix expression
    Return:
        - The postfix result from the parseAndPushR method.
    ----------------------------------------------------------
*/

string parseAndPush(const string& input) {
    Stack stack(input.size());                                  //Initialize a stack of the input size
    int index = 0;                                              //Set index to 0
    string result;                                              //Create a variable to return
    parseAndPushR(input, index, stack);                         //Recursively called the parseAndPush function

    while (!stack.isEmpty()) {                                  //And then we pop everything off of the stack for display
        result += stack.pop();
    }
    return result;
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

void writeOutput(ofstream& outFile, const string& input, const string& result) {  //Write the input and output to file
    outFile<<input<<" = "<<result<<endl;
}

/*  ----------------------------------------------------------
    Method: readLines
    Description: Reads the input line by line, validates each line, then stores the result to print to terminal and pass
                 to the writeOutput method.
    Parameters:
        - outputWritten (bool&): A flag to indicate if any output has been written, and if not, open the output file.
        - outputFilename (string): The name of the output file.
        - outFile (ofstream&): The output file, to which the results are added.
        - inFile (ifstream&): The input file, from which the lines are read.
    ----------------------------------------------------------
*/

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
    int dotPos = filename.find_last_of('.');                //Find the position of the dot
    if (dotPos != string::npos) {
        return filename.substr(0, dotPos) + " - output" + filename.substr(dotPos); //And presuming it exists, append " - output" to it
    }
    return filename + " output";                            //If the filename doesn't have a type associated, then just output will be appended
}

/*  ----------------------------------------------------------
    Method: menu
    Description: Reads the input file, checks for valid input, and outputs the result
    Parameters:
        - The input file containing lines of prefix expressions.
    Return:
        - For each line, the program will output a valid expression or a message indicating it is invalid.
          Will output valid lines to a file.
    ----------------------------------------------------------
*/

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

/*  ----------------------------------------------------------
    Method: main
    Description: The entry point of the program. Relays to the menu function.
    Parameters:
        - none
    Return:
        - 0 when the program ends.
    ----------------------------------------------------------
*/

int main() {                                    //Main driver function. Calls handler function
    menu();
    return 0;
}
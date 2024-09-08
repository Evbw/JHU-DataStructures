#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void openInputFile(ifstream& inFile) {
    string filename;
    cout<<"Enter the filename: "<<endl;
    getline(cin,filename);
    inFile.open(filename);
    while (!inFile) {
        cout<<"File failed to open."<<endl;
        cout<<"Enter the filename: "<<endl;
        getline(cin,filename);
        inFile.clear();
        inFile.open(filename);
    }
}

int main() {
    ifstream inFile;
    openInputFile(inFile);

    if(inFile) {
        cout<<"Success opening the file!"<<endl;
    }
    else {
        cout<<"Try again"<<endl;
    }
    inFile.clear();
    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void openInputFile(ifstream& inFile) {
    string filename;
    cout<<"Enter the filename: "<<endl;
    cin>>filename;
    inFile.open(filename);
    while (!inFile) {
        cout<<"File failed to open."<<endl;
        cout<<"Enter the filename: "<<endl;
        cin>>filename;
        inFile.clear();
        inFile.open(filename);
    }
}
/**
    CS3307 Individual Assignment
    mycp.cpp
    Purpose: implementation of the mycp utility
    Copies a file to another file 
    Date: October 3 2019

    @author Maya Murad
    @studentnum 250850926
*/

#include "MyFile.cpp"

int main(int argc, char** argv) {
    string fileName1(argv[1]); //getting args
    string fileName2(argv[2]);
    MyFile sourceFile(fileName1); //creating MyFile objects
    MyFile destFile(fileName2);
    ofstream destination; //initilializing the ostream for the destination
    destination.open(destFile.getName()); //opening the ostream associated with the given destination file name
    sourceFile.Dump(destination); //dumping the contents and closing the file below
    destination.close();
}


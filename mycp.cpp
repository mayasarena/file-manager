//
// mycp.cpp
// CS3307 Individual Assignment
//
// Created by Maya Murad on 10/03/2019
//
// This is the implementation of the mycp utility.
//

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


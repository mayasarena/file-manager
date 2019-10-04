//
// mymv.cpp
// CS3307 Individual Assignment
//
// Created by Maya Murad on 10/02/2019
//
// This is the implementation of the mymv utility.
//

#include "MyFile.cpp"

int main(int argc, char** argv) {
    string fileName1(argv[1]); //converting the first and second arguments into strings
    string fileName2(argv[2]);
    MyFile file1(fileName1); //creating MyFile objects from the names
    MyFile file2(fileName2);
    file1.renameFile(file2.getName()); //using rename function to rename and move the files
}


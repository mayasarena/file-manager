//
// myrm.cpp
// CS3307 Individual Assignment
//
// Created by Maya Murad on 10/03/2019
//
// This is the implementation of the myrm utility.
// 

#include "MyFile.cpp"

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) { //looping through the given arguments
        string fileName(argv[i]); //creating MyFile objects and then deleting the files
        MyFile fileToDelete(fileName);
        fileToDelete.removeFile();
    }
}


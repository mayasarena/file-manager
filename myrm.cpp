/**
    CS3307 Individual Assignment
    myrm.cpp
    Purpose: implementation of the myrm utility
    Removes files from the file system
    Date: October 3 2019

    @author Maya Murad
    @studentnum 250850926
*/

#include "MyFile.cpp"

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) { //looping through the given arguments
        string fileName(argv[i]); //creating MyFile objects and then deleting the files
        MyFile fileToDelete(fileName);
        fileToDelete.removeFile();
    }
}


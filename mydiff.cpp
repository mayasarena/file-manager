/**
    CS3307 Individual Assignment
    mydiff.cpp
    Purpose: implementation of the mydiff utility
    Compares the two given files and informs user
    if their contents are the same or not
    Date: October 3 2019

    @author Maya Murad
    @studentnum 250850926
*/

#include "MyFile.cpp"

int main(int argc, char** argv) {
    string fileName1(argv[1]); //getting args
    string fileName2(argv[2]);
    MyFile file1(fileName1); //creating the objects
    MyFile file2(fileName2);
    int result = file1.compareFiles(file2); //will return 1 if the same, 0 otherwise
    if (result == 1){
        cout << "same" << endl;
    }
    else {
        cout << "different" << endl;
    }
}


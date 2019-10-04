//
// mydiff.cpp
// CS3307 Individual Assignment
//
// Created by Maya Murad on 10/03/2019
//
// This is the implementation of the mydiff utility.
// 

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


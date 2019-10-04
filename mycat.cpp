//
// mycat.cpp
// CS3307 Individual Assignment
//
// Created by Maya Murad on 10/03/2019
//
// This is the implementation of the mycat utility.
//

#include "MyFile.cpp"

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) { //looping through the arguments
        string fileName(argv[i]); //converting the args to strings and
        MyFile fileToCat(fileName); //creating MyFile objects
        fileToCat.Dump(cout); //using cout as our ostream because that easily outputs the stream to the terminal
    }
}


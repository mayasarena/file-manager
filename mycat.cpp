/**
    CS3307 Individual Assignment
    mycat.cpp
    Purpose: implementation of the mycat utility
    Prints contents of file to the terminal
    Date: October 3 2019

    @author Maya Murad
    @studentnum 250850926
*/

#include "MyFile.cpp"

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) { //looping through the arguments
        string fileName(argv[i]); //converting the args to strings and
        MyFile fileToCat(fileName); //creating MyFile objects
        fileToCat.Dump(cout); //using cout as our ostream because that easily outputs the stream to the terminal
    }
}


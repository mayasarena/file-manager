#include "MyFile.cpp"
#include <iostream>

int main(int argc, char** argv) {
    string fileName1(argv[1]);
    string fileName2(argv[2]);
    MyFile sourceFile(fileName1);
    MyFile destFile(fileName2);
    ofstream destination;
    destination.open(destFile.getName());
    sourceFile.Dump(destination);
    destination.close();
}


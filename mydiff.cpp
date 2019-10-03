#include "MyFile.cpp"
#include <iostream>

int main(int argc, char** argv) {
    string fileName1(argv[1]);
    string fileName2(argv[2]);
    MyFile file1(fileName1);
    MyFile file2(fileName2);
    int result = file1.compareFiles(file2); //will return 1 if the same, 0 otherwise
    if (result == 1){
        cout << "same" << endl;
    }
    else {
        cout << "different" << endl;
    }
}

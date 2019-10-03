#include "MyFile.cpp"
#include <iostream>

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        string fileName(argv[i]);
        cout << fileName << endl;
        MyFile fileToDelete(fileName);
        fileToDelete.removeFile();
    }
}

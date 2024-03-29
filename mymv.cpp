/**
    CS3307 Individual Assignment
    mymv.cpp
    Purpose: implementation of the mymv utility
    Can move files around a file system
    Date: October 3 2019

    @author Maya Murad
    @studentnum 250850926
*/

#include "MyFile.cpp"

int main(int argc, char** argv) {
    string fileName1(argv[1]); //converting the first and second arguments into strings
    string fileName2(argv[2]);
    MyFile file1(fileName1); //creating MyFile objects from the names
    MyFile file2(fileName2);
    file1.renameFile(file2.getName()); //using rename function to rename and move the files
    if (errno == EXDEV) { //checking if an EXDEV error has occured, meaning files are on different file systems        
        ofstream destination; //initilializing the ostream for the destination
        destination.open(file2.getName()); 
        file1.Dump(destination); //dumping the contents and closing the file below
        destination.close();
        file1.removeFile(); //removing the original file
    }
}


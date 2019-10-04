//
// mystat.cpp
// CS3307 Individual Assignment
//
// Created by Maya Murad on 10/03/2019
//
// This is the implementation of the mystat utility.
//

#include "MyFile.cpp"

int main(int argc, char** argv) {
    string fileName(argv[1]); //getting arg and creating MyFile object
    MyFile file(fileName);
    cout << "File: " << file.getName() << "     File Type: " << file.getType() << endl; //simply outputting everything to the terminal in an organized fashion
    cout << "Size: " << file.getSize() << "      " << "IO Block: " << file.getBlockSize() << endl;
    cout << "Permissions: " << file.getPermissions() << "   Uid: " << file.getOwnerID() << " / " << file.getOwnerName() <<
        "   Gid: " << file.getGroupID() << " / " << file.getGroupName() << endl; 
    cout << "Access: " << file.getAccessTime() << endl;
    cout << "Modify: " << file.getModTime() << endl;
    cout << "Change: " << file.getSCTime() << endl;
}



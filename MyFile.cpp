
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <vector>
#include <errno.h>
#include <cstring>
#include <cstdio>
#include "MyFile.h"//including the header file

using std::string;
using namespace std;

struct stat getStat(string name) { //getting access to the stat struct
    struct stat buf;
    int success = stat(name.c_str(), &buf);
    return buf;
}

//Constructor
MyFile::MyFile(string name_) {
    name = name_; //setting the name of the file object
    
    struct stat stats = getStat(name); //accessing stat for the named file
    
    size = stats.st_size; 
    type = stats.st_mode; 
    
    ownerID = stats.st_uid; 
    struct passwd pswd = *getpwuid(ownerID); //using getpwuid to get the owner name from the owner ID
    char* oname = pswd.pw_name; 
    ownerName = oname;
    

    groupID = stats.st_gid;
    struct group grp = *getgrgid(groupID); //using getgrgid to get the group name from the group ID
    char* gname = grp.gr_name; 
    groupName = gname;
    
    //making a string representation of the permissions
    //start with a string permission that will hold the current permission
    //then append the result into our permissions string
    string permission; 
    //checking if directory
    permission = (S_ISDIR(stats.st_mode)) ? "d" : "-";    
    permissions.append(permission);
    //user permissions
    permission = (S_IRUSR & stats.st_mode) ? "r" : "-"; 
    permissions.append(permission);  
    permission = (S_IWUSR & stats.st_mode) ? "w" : "-"; 
    permissions.append(permission); 
    permission = (S_IXUSR & stats.st_mode) ? "x" : "-"; 
    permissions.append(permission); 
    //group permissions
    permission = (S_IRGRP & stats.st_mode) ? "r" : "-"; 
    permissions.append(permission); 
    permission = (S_IWGRP & stats.st_mode) ? "w" : "-"; 
    permissions.append(permission); 
    permission = (S_IXGRP & stats.st_mode) ? "x" : "-"; 
    permissions.append(permission); 
    //other permissions
    permission = (S_IROTH & stats.st_mode) ? "r" : "-"; 
    permissions.append(permission); 
    permission = (S_IWOTH & stats.st_mode) ? "w" : "-"; 
    permissions.append(permission); 
    permission = (S_IXOTH & stats.st_mode) ? "x" : "-";    
    permissions.append(permission);
    
    //access time FIx THIS !!!!!!!!!!!!!!!!!!!!!!!!!!!
    accessTime = stats.st_atime;   
    //modification time
    modTime = stats.st_mtime;
    //status change time
    statusChangeTime = stats.st_ctime;
    
    blockSize = stats.st_blksize; 

    //creating child vector
    vector<MyFile> children;
    
    //setting error number
    errorNumber = 0;


    //checking if values are correct
//    cout << "name: " << name << endl;
//    cout << "size: " << size << endl;
//    cout << "type: " << type << endl;
//    cout << "owner ID: " << ownerID << endl;
//      cout << "owner name: " << ownerName << endl;
//    cout << "group ID: " << groupID << endl;
//    cout << "group name: " << groupName << endl;
//    cout << "permissions: " << permissions << endl;
//    cout << "access time: " << accessTime << endl;
//    cout << "modify time: " << modTime << endl;
//    cout << "status change time: " << statusChangeTime << endl;
//    cout << "file block size: " << blockSize << endl;
    //cout << "number of children: " << children.size() << endl;
}

//Destructor
MyFile::~MyFile() {
            
}

void MyFile::Dump(ostream &fileStream) {
    char line[blockSize + 1] = {};
    int numRead = 0; 
    ifstream myfile;
    myfile.open(name);
    if (!myfile.is_open()) {
        cout << "error ";
        errorNumber = errno;
        cout << errorNumber << endl;
        return;
    }
    while (numRead = myfile.readsome(line, blockSize)) {
        line[numRead] = 0;
        fileStream << line;
    }
    myfile.close();
}

void MyFile::renameFile(string newName) {
    int value;
    const char *currentName = name.c_str();
    const char *newName_ = newName.c_str();
    value = rename(currentName, newName_);
    if (value == 0) {
        name = newName;
        cout << "name successfully changed to: " << newName << endl;
    }
    else {
        errorNumber = errno;
        cout << "error changing name. error number: " << errorNumber << endl;
    }
}

void MyFile::removeFile() {
    const char *file = name.c_str();
    int value;
    value = unlink(file);
    if (value != 0) {
        errorNumber = errno; 
        cout << "error deleting file. error number: " << errorNumber << endl;
        return;
    }
    name.clear();
    type = 0;
    size = 0;
    ownerID = 0;
    ownerName.clear();
    groupID = 0;
    groupName.clear();
    permissions.clear();
    accessTime = 0;
    modTime = 0;
    statusChangeTime = 0;
    blockSize = 0;
    children.clear();
    errorNumber = 0;
}

int MyFile::compareFiles(MyFile file) {
    cout << "compare file size: " << file.getSize() << ". file size: " << size << endl;
    if (file.getSize() != size) {
        cout << "compare file size: " << file.getSize() << ". file size: " << size << endl;
        cout << "contents not equivalent" << endl;
        return 0;
    }
    char line[blockSize] = {};
    char compareLine[blockSize] = {};
    ifstream myfile(name);
    ifstream otherFile(file.getName());
    if (!(myfile.is_open() && otherFile.is_open())) {
        cout << "error ";
        errorNumber = errno;
        return errorNumber;
    }
    while (myfile.getline(line, blockSize)) {
        otherFile.getline(compareLine, blockSize);
        if (strcmp(line, compareLine) != 0) {
            cout << "contents are not equal" << endl;
            return 0;
        }
    }
    cout << "contents are equal" << endl;
    myfile.close();
    otherFile.close();
    return 1;
}

void MyFile::Expand() {  
    struct stat stats = getStat(name); //accessing stat for the named file
    struct dirent *child;
    DIR *directory = opendir(name.c_str());
    if (!S_ISDIR(stats.st_mode) || directory == NULL) {
        cout << "not a directory" << endl;
        return;
    }
    while ((child = readdir(directory)) != NULL) {
        string childName(child->d_name);
        if (childName == "" || childName == "." || childName == "..") {
            continue;
        }
        MyFile newFile(name + "/" + childName);
        children.push_back(newFile);
    }
}

//GETTERS
string MyFile::getName() {
    return name;
}

long MyFile::getSize() {
    return size;
}

mode_t MyFile::getType() {
    return type;
}

uid_t MyFile::getOwnerID() {
    return ownerID;
}

string MyFile::getOwnerName() {
    return ownerName; /////fix this man
}

gid_t MyFile::getGroupID() {
    return groupID;
}

string MyFile::getGroupName() {
    return groupName; 
}


string MyFile::getPermissions() {
    return permissions;
}

time_t MyFile::getAccessTime() {
    return accessTime;
}

time_t MyFile::getModTime() {
    return modTime;
}

time_t MyFile::getSCTime() {
    return statusChangeTime;
}

blksize_t MyFile::getBlockSize() {
    return blockSize;
}

int MyFile::getErrorNum() {
    return errorNumber;
}

vector<MyFile> MyFile::getChildren() {
    return children;
}


//int main() {
//    MyFile testMyFile("poop");
//    testMyFile.getOwnerName();
//    testMyFile.getGroupName();
//}

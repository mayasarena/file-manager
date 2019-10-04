//
// MyFile.cpp
// CS3307 Individual Assignment
//
// Created by Maya Murad on 09/25/2019
//
// This file contains the implementation of the MyFile object
// along with functions that go along with it.
// 

#include "MyFile.h"

using std::string;
using namespace std;

struct stat getStat(string name) { //creates a stat struct in order to get access to all of its contents
    struct stat buf;
    int success = stat(name.c_str(), &buf);
    return buf;
}

MyFile::MyFile(string name_) { //constructor
    //initializing variables:
    name = name_;
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
   
    accessTime = stats.st_atime;   
    modTime = stats.st_mtime;
    statusChangeTime = stats.st_ctime; 
    blockSize = stats.st_blksize; 
    vector<MyFile> children;
    errorNumber = 0; 
}

MyFile::~MyFile() { //destructor
            
}

//creating getters:
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
    return ownerName; 
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

vector<MyFile> MyFile::getChildren() {
    return children;
}

blksize_t MyFile::getBlockSize() {
    return blockSize;
}

int MyFile::getErrorNum() {
    return errorNumber;
}

void MyFile::setName(string newName){
    renameFile(newName);
}

//dump function takes an ostream as parameter and dumps the file contents to the ostream
//ostream was used since cout is an ostream, making it efficient in printing to the terminal
void MyFile::Dump(ostream &fileStream) { 
    struct stat stats = getStat(name); //accessing stat for the named file
    if (S_ISDIR(stats.st_mode)) { //checking if the current file is a dir, throws error if it is
        errorNumber = ENOTSUP;
        cout << "This is a directory. Dump can only be used on a file." << endl;
        return;
    }
    char line[blockSize + 1] = {};
    int numRead = 0; 
    ifstream myfile;
    myfile.open(name);
    if (!myfile.is_open()) { //error if the stream cannot be opened 
        cout << "error ";
        errorNumber = errno;
        return;
    }
    while (numRead = myfile.readsome(line, blockSize)) { //reads lines from the file using blocksize as the buffer
        line[numRead] = 0;
        fileStream << line; //dumping the lines into the file stream one by one
    }
    myfile.close();
    errorNumber = 0;
}

//renamefile function takes a string as parameter and renames the file to this given name
void MyFile::renameFile(string newName) {
    int value;
    const char *currentName = name.c_str();
    const char *newName_ = newName.c_str();
    value = rename(currentName, newName_);
    if (value == 0) {
        name = newName;
        errorNumber = 0;
    }
    else { //error number is set if operation cannot be completed
        errorNumber = errno;
    }
}

//removefile function removes the current file
void MyFile::removeFile() {
    const char *file = name.c_str();
    int value;
    value = unlink(file);
    if (value != 0) { //if there's an error, errno is stored and function is exited
        errorNumber = errno; 
        return;
    }
    //clearing all variables of the object
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

//comparefiles function takes a file object as parameter and compares the file contents
//with this file
int MyFile::compareFiles(MyFile file) {
    if (file.getSize() != size) { //if files have different sizes, we can assume that
        return 0; //the contents are not the same. 0 is returned to indicate they are not the same.
    }
    char line[blockSize] = {};
    char compareLine[blockSize] = {};
    ifstream myfile(name);
    ifstream otherFile(file.getName());
    if (!(myfile.is_open() && otherFile.is_open())) {
        errorNumber = errno; //errno is stored if an error occurs while opening files
        return errorNumber;
    }
    //the following loop iterates through each file, comparing them line by line
    //if a difference is observed, 0 is returned, indicating that the file contents are different
    while (myfile.getline(line, blockSize)) {
        otherFile.getline(compareLine, blockSize);
        if (strcmp(line, compareLine) != 0) {
            return 0;
        }
    }
    myfile.close();
    otherFile.close();
    return 1; //1 means that the file contents are equivalent
    errorNumber = 0;
}

//expand function fills the child vector with child objects from the given directory
void MyFile::Expand() {  
    struct stat stats = getStat(name); //accessing stat for the named file
    struct dirent *child;
    DIR *directory = opendir(name.c_str());
    if (!S_ISDIR(stats.st_mode) || directory == NULL) { //checking if the current file is a dir or not
        errorNumber = ENOTSUP;
        cout << "This is a file. Expand can only be used on a directory." << endl;
    }
    while ((child = readdir(directory)) != NULL) {
        string childName(child->d_name);
        if (childName == "" || childName == "." || childName == "..") { //don't include the following files
            continue;
        }
        MyFile newFile(name + "/" + childName); //creating a new file from the path
        children.push_back(newFile);
        errorNumber = 0;
    }
}


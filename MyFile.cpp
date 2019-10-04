/**
    CS3307 Individual Assignment
    MyFile.cpp
    Purpose: a MyFile class that is a part of a File Manager system
    Date: October 3 2019

    @author Maya Murad
    @studentnum 250850926
*/
#include "MyFile.h"

using std::string;
using namespace std;


/**
    returns a stat structure
    @param name the string name of the file that 
    we want to receive info about
    @return buf a stat struct which can be used 
    to learn more about the file
*/
struct stat getStat(string name) { //creates a stat struct in order to get access to all of its contents
    struct stat buf;
    int success = stat(name.c_str(), &buf);
    return buf;
}

/**
    Constructor - constructs a MyFile object
    @param name_ the string name of the file
*/
MyFile::MyFile(string name_) {
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

/**
    Destructor - destructs a MyFile object
*/
MyFile::~MyFile() {
            
}

//creating getters:

/**
    Returns the name of the file
    @return the name as a string
*/
string MyFile::getName() {
    return name;
}

/**
    Returns the size of the file
    @return the size as a long
*/
long MyFile::getSize() {
    return size;
}

/**
    Returns the type of the file
    @return the type as a mode_t
*/
mode_t MyFile::getType() {
    return type;
}

/**
    Returns the owner ID of the file
    @return the owner id as a uid_t
*/
uid_t MyFile::getOwnerID() {
    return ownerID;
}

/**
    Returns the owner name of the file
    @return the owner name
*/
string MyFile::getOwnerName() {
    return ownerName; 
}

/**
    Returns the group ID of the file
    @return group ID as a gid_t
*/
gid_t MyFile::getGroupID() {
    return groupID;
}

/**
    Returns the group name of the file
    @return group name as a string
*/
string MyFile::getGroupName() {
    return groupName; 
}

/**
    Returns the permissions of the file
    @return permissions as a string
*/
string MyFile::getPermissions() {
    return permissions;
}

/**
    Returns the access time of the file
    @return access time as a time_t
*/
time_t MyFile::getAccessTime() {
    return accessTime;
}

/**
    Returns the mod time of the file
    @return mod time as a time_t
*/
time_t MyFile::getModTime() {
    return modTime;
}

/**
    Returns the status time of the file
    @return status time as a time_t
*/
time_t MyFile::getSCTime() {
    return statusChangeTime;
}

/**
    Returns the children(a listing of 
    files and directories) of the file
    @return children as MyFile objects in a vector,
    empty if it does not contain the objects yet
    or if the file is not a directory
*/
vector<MyFile> MyFile::getChildren() {
    return children;
}

/**
    Returns the block size of the file
    @return block size as a blksize_t
*/
blksize_t MyFile::getBlockSize() {
    return blockSize;
}

/**
    Returns the error number of the file
    @return error number as an int
*/
int MyFile::getErrorNum() {
    return errorNumber;
}

/**
    Sets the name of the file
    @param the new name of the file as a string
*/
void MyFile::setName(string newName){
    renameFile(newName);
}

/**
    Dump function dumps the contents of a file into a file stream
    @param an ostream of the file you would like the content 
    to be dumped to
*/
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

/**
    renameFile renames the file
    @param string newName which is the new name
    to be given to the file
*/
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

/**
    removeFile removes the file
*/
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

/**
    compareFiles compares the contents of two files
    @param a MyFile object that you would like to compare
    @return an int, 0 if they are different
    and 1 if they are the same
*/
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

/**
    Expand fills the children vector with MyFile objects of each file
    This only works on directories
*/
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


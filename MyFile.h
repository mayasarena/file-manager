//
// MyFile.h
// CS3307 Individual Assignment
//
// Created by Maya Murad on 09/25/2019
//
// This is a MyFile header file that declares 
// data members and functions. 
// 

#ifndef MyFile_h
#define MyFile_h

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

class MyFile {
    
    public:
        MyFile(std::string name);
        ~MyFile(); 
        std::string getName();
        long getSize();
        mode_t getType();
        uid_t getOwnerID();
        std::string getOwnerName();
        gid_t getGroupID();
        std::string getGroupName();
        std::string getPermissions();
        time_t getAccessTime();
        time_t getModTime();
        time_t getSCTime();
        std::vector<MyFile> getChildren();
        blksize_t getBlockSize();
        int getErrorNum();
        void setName(std::string newName);
        void Dump(std::ostream &fileStream);
        void renameFile(std::string newName);
        void removeFile ();
        int compareFiles(MyFile file);
        void Expand();
    
    private:
        std::string name;
        long size;
        mode_t type; 
        uid_t ownerID;
        std::string ownerName;
        gid_t groupID;
        std::string groupName;
        std::string permissions;
        time_t accessTime;
        time_t modTime;
        time_t statusChangeTime;
        blksize_t blockSize;
        std::vector<MyFile> children;
        int errorNumber;
};

#endif //MyFile_h


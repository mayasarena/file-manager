#include <string>
#include <vector>
#include <fstream>
using std::string;
using std::vector;
using namespace std;

class MyFile {
    private:
        string name;
        long size;
        mode_t type; 
        uid_t ownerID;
        string ownerName;
        gid_t groupID;
        string groupName;
        string permissions;
        time_t accessTime;
        time_t modTime;
        time_t statusChangeTime;
        blksize_t blockSize;
        vector<MyFile> children;
        int errorNumber;

    public:
        MyFile(string name); //constructor
        ~MyFile(); //destructor
        string getName();
        long getSize();
        mode_t getType();
        uid_t getOwnerID();
        string getOwnerName();
        gid_t getGroupID();
        string getGroupName();
        string getPermissions();
        time_t getAccessTime();
        time_t getModTime();
        time_t getSCTime();
        vector<MyFile> getChildren();
        blksize_t getBlockSize();
        int getErrorNum();
        void Dump(ostream &fileStream);
        void renameFile (string newName);
        void removeFile ();
        int compareFiles(MyFile file);
        void Expand();
};

//
// myls.cpp
// CS3307 Individual Assignment
//
// Created by Maya Murad on 10/02/2019
//
// This is the implementation of the myls utility.
//

#include "MyFile.cpp"

//notAPath function converts a path into a direct name
string notAPath(string currentName, vector<MyFile> children, int i) {
    currentName = children[i].getName(); //setting the name of the current child
    size_t found = currentName.find_last_of("/\\"); //we want to find the last instance of a "/"
    string name = currentName.substr(found+1); //we get the substring
    return name;
}

int main(int argc, char** argv) {

    //getting the current working directory     
    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    string currentWorkingDir(buff);
    MyFile directory(currentWorkingDir);

    string arg1; //converting argument to string to check for -l IF it is not empty (or else there is an error)
    if (argv[1] != NULL) {
        arg1 = argv[1];
    }

    if (argv[1] == NULL || (arg1 == "-l" && argv[2] == NULL)) { //case 1: no files or directories are given
        directory.Expand();
        vector<MyFile> children = directory.getChildren();
        for (int i = 0; i < children.size(); i++) { //iterating through the child vector to get all of the file objects
            string currentName;
            string name = notAPath(currentName, children, i); //converting the paths into a name
            if (name.at(0) != '.') { //we ignore the file if the name begins with a "." - like swp files etc.
                if (argv[1] == NULL) { //if there is no -l, we just print the name
                    cout << name << "  ";
                }
                else { //if there is an -l, we print more information
                    cout << children[i].getPermissions() <<" " << children[i].getOwnerName() << " " << children[i].getGroupName() << 
                    " " << children[i].getSize() << " " << children[i].getModTime() << " " << name << endl;
                }
            }
        }
        cout << endl;
    }

    else if (arg1 == "-l") { //case 2: we are given files/directories and we are also given -l
        string fileName(argv[2]);
        MyFile file(fileName);
        if (!S_ISDIR(file.getType())) { //this is a file, so we do not have to expand
            cout << file.getPermissions() << " " << file.getOwnerName() << " " << file.getGroupName() << " " 
            << file.getSize() << " " << file.getModTime() << " " << fileName << endl;
            return 0; //exit function
        }
        file.Expand(); //otherwise, we expand to get the file functions and repeat what we did above in order to display them
        vector<MyFile> children = file.getChildren();
        for (int i = 0; i < children.size(); i++) {
            string currentName;
            string name = notAPath(currentName, children, i);
            if (name.at(0) != '.') {
                cout << children[i].getPermissions() << " " << children[i].getOwnerName() << " " << children[i].getGroupName() << 
                " " << children[i].getSize() << " " << children[i].getModTime() << " " << name << endl;
            }
         }
    }

    else { //case 3: no -l is given but we are given other args 
        string fileName(argv[1]);
        MyFile file(fileName);
        if (!S_ISDIR(file.getType())) { //this is a file, so we do not need to expand
            cout << file.getName() << endl;
            return 0; //exit
        }
        file.Expand(); //otherwise, we expand and print everything
        vector<MyFile> children = file.getChildren(); 
        for (int i = 0; i < children.size(); i++) { 
            string currentName; 
            string name = notAPath(currentName, children, i);
            if (name.at(0) != '.') {
                cout << name << "  ";
            }
         }
        cout << endl;
    }    
}


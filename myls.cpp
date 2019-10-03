#include "MyFile.cpp"
#include <iostream>


string notAPath(string currentName, vector<MyFile> children, int i) {
    currentName = children[i].getName();
    size_t found = currentName.find_last_of("/\\");
    string name = currentName.substr(found+1);
    return name;
}

int main(int argc, char** argv) {

    //getting the current working directory     
    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    string currentWorkingDir(buff);
    MyFile directory(currentWorkingDir);
    //converting argument to string to check for -l IF it is not empty (or else there is an error)
    string arg1;
    if (argv[1] != NULL) {
        arg1 = argv[1];
    }
    //case if no arguments are given
    if (argv[1] == NULL || (arg1 == "-l" && argv[2] == NULL)) {
        directory.Expand();
        vector<MyFile> children = directory.getChildren();
        for (int i = 0; i < children.size(); i++) {
            string currentName;
            string name = notAPath(currentName, children, i);
            if (name.at(0) != '.') {
                if (argv[1] == NULL) {
                    cout << name << "  ";
                }
                else {
                    cout << children[i].getPermissions() << " " << children[i].getChildren().size() << " " << children[i].getOwnerName() << " " <<
                        children[i].getGroupName() << " " << children[i].getSize() << " " << children[i].getModTime() << " " << name << endl;
                }
            }
        }
        cout << endl;
    }
    else if (arg1 == "-l") {
        string fileName(argv[2]);
        MyFile file(fileName);
        if (!S_ISDIR(file.getType())) {
            cout << file.getPermissions() << " " << file.getChildren().size() << " " << file.getOwnerName() << " " <<
                file.getGroupName() << " " << file.getSize() << " " << file.getModTime() << " " << fileName << endl;
            return 0; //exit function
        }
        file.Expand();
        vector<MyFile> children = file.getChildren();
        for (int i = 0; i < children.size(); i++) {
            string currentName;
            string name = notAPath(currentName, children, i);
            if (name.at(0) != '.') {
                cout << children[i].getPermissions() << " " << children[i].getChildren().size() << " " << children[i].getOwnerName() << " " <<
                    children[i].getGroupName() << " " << children[i].getSize() << " " << children[i].getModTime() << " " << name << endl;
            }
         }
    }
    else {
        string fileName(argv[1]);
        MyFile file(fileName);
        if (!S_ISDIR(file.getType())) {
            cout << file.getName() << endl;
            return 0; //exit
        }
        file.Expand();
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


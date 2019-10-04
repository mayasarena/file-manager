rm -rf bin
mkdir bin
cd bin
THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
echo "export PATH=\$PATH:$THIS_DIR" >> $HOME/.bashrc
PATH=$PATH:$THIS_DIR
cd ..
g++ myrm.cpp -o bin/myrm
g++ mymv.cpp -o bin/mymv
g++ mycp.cpp -o bin/mycp
g++ myls.cpp -o bin/myls
g++ mycat.cpp -o bin/mycat
g++ mydiff.cpp -o bin/mydiff
g++ mystat.cpp -o bin/mystat

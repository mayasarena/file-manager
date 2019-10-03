mkdir bin
cd bin
THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
echo "export PATH=\$PATH:$THIS_DIR" >> $HOME/.bashrc
PATH=$PATH:$THIS_DIR
cd ..
g++ myrm.cpp -o bin/myrm

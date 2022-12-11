#include <iostream>
#include "VMTranslator/VMTranslator.h"

using namespace std;

int main(int argc, char * argv[]) {
    if(argc != 2) {
        cout << "input format: ./vm_translator <file>";
        exit(1);
    }
    string path = argv[1];



    VMTranslator VMT(path);
    string outputFile;
    if(filesystem::is_directory(path)){

        string permissionsSet = "chmod 777 " + path + "/*.vm";
        system((permissionsSet.c_str()));

        string directoryName;
        int posOfLastSlash = 0;
        for(int i=0;i<path.size();i++) if(path[i] == '/') posOfLastSlash = i;
        directoryName = path.substr(posOfLastSlash, path.size()-1);
        outputFile =  path + '/' + directoryName + ".asm";
    }else{
        outputFile = path.substr(0,path.size() - 2) + "asm";
    }
    ofstream outStream(outputFile);
    for(auto assemblyCode : VMT.assembly){
        outStream << assemblyCode << '\n';
    }

    outStream.close();

    return 0;
}

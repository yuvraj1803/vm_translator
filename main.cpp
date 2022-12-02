#include <iostream>
#include "VMTranslator/VMTranslator.h"

using namespace std;

int main(int argc, char * argv[]) {
    if(argc != 2) {
        cout << "input format: ./vm_translator <file>";
        exit(1);
    }
    string file = argv[1];
    VMTranslator VMT(file);
    string outputFile = file.substr(0,file.size() - 2) + "asm";
    ofstream outStream(outputFile);
    for(auto assemblyCode : VMT.assembly){
        outStream << assemblyCode << '\n';
    }

    outStream.close();

    return 0;
}

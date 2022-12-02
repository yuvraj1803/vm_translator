//
// Created by Yuvraj Sakshith on 01/12/22.
//

#ifndef VM_TRANSLATOR_CODEWRITER_H
#define VM_TRANSLATOR_CODEWRITER_H

#include "../Misc/reference.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class CodeWriter {
private:
    vector<string> generateArithmetic(vector<string> &instruction);
    vector<string> generatePush(vector<string> &instruction);
    vector<string> generatePop(vector<string> &instruction);
    unordered_map<string, int> base_address;
    string fileName;
    int jumpCount = 0;
public:
    CodeWriter(string &file);
    vector<string> generateAssembly(vector<string> &instruction, int instructionType, int lineNr);
};


#endif //VM_TRANSLATOR_CODEWRITER_H

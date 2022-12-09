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
    vector<string> generateInit(vector<string> &instruction);
    vector<string> generateArithmetic(vector<string> &instruction);
    vector<string> generatePush(vector<string> &instruction);
    vector<string> generatePop(vector<string> &instruction);
    vector<string> generateLabel(vector<string> &instruction);
    vector<string> generateIf(vector<string> &instruction);
    vector<string> generateGoto(vector<string> &instruction);
    vector<string> generateFunction(vector<string> &instruction);
    vector<string> generateCall(vector<string> &instruction);
    vector<string> generateReturn();

    unordered_map<string, int> base_address;
    string fileName;
    string currentFunction;
    int jumpCount = 0;
    int retCount = 0;

public:
    CodeWriter(string &file);
    vector<string> generateAssembly(vector<string> &instruction, int instructionType, int lineNr);
};


#endif //VM_TRANSLATOR_CODEWRITER_H

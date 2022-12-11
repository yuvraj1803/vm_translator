//
// Created by Yuvraj Sakshith on 01/12/22.
//

#ifndef VM_TRANSLATOR_CODEWRITER_H
#define VM_TRANSLATOR_CODEWRITER_H

#include "../Misc/reference.h"
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <filesystem>
using namespace std;

class CodeWriter {
private:
    vector<string> generateArithmetic(vector<string> &instruction);
    vector<string> generatePush(vector<string> &instruction);
    vector<string> generatePop(vector<string> &instruction);
    vector<string> generateLabel(vector<string> &instruction);
    vector<string> generateIf(vector<string> &instruction);
    vector<string> generateGoto(vector<string> &instruction);
    vector<string> generateFunction(vector<string> &instruction);
    vector<string> generateReturn();

    unordered_map<string, int> base_address;
    string fileName;
    int jumpCount = 0;
    int retCount = 0;
    int localAddCount = 0;

public:
    CodeWriter();
    vector<string> generateInit();
    vector<string> generateCall(vector<string> &instruction);
    vector<string> generateAssembly(vector<string> &instruction, int instructionType, int lineNr);
    void setFile(string &file);
    stack<string> functionStack;
};


#endif //VM_TRANSLATOR_CODEWRITER_H

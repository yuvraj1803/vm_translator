//
// Created by Yuvraj Sakshith on 01/12/22.
//

#ifndef VM_TRANSLATOR_VMTRANSLATOR_H
#define VM_TRANSLATOR_VMTRANSLATOR_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../Parser/Parser.h"

using namespace std;

class VMTranslator {

private:

public:
    VMTranslator(string &file);
    vector<string> assembly;

};


#endif //VM_TRANSLATOR_VMTRANSLATOR_H

//
// Created by Yuvraj Sakshith on 01/12/22.
//

#ifndef VM_TRANSLATOR_PARSER_H
#define VM_TRANSLATOR_PARSER_H

#include <vector>
#include <string>
using namespace std;

class Parser {

public:

    explicit Parser(vector<string> &vmcode, string &file);
    vector<vector<string>> _vmcode; // vmcode broken down into its lexical components

};


#endif //VM_TRANSLATOR_PARSER_H

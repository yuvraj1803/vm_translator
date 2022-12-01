//
// Created by Yuvraj Sakshith on 01/12/22.
//

#include "Parser.h"


Parser::Parser(vector<string> &vmcode, string &file) {
        for(const auto& instruction : vmcode){
        vector<string> parsed_instruction;
        string temp;
        for(auto c : instruction){
            if(c == ' ') {
                parsed_instruction.push_back(temp);
                temp = string();
            }
            else temp += c;
        }
        if(!temp.empty()) parsed_instruction.push_back(temp);

        _vmcode.push_back(parsed_instruction);
    }

}
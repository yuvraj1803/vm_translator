//
// Created by Yuvraj Sakshith on 01/12/22.
//

#include "VMTranslator.h"
#include "../CodeWriter/CodeWriter.h"
VMTranslator::VMTranslator(string &file) {
    ifstream fileStream(file);

    if(fileStream.is_open()){
        string temp;
        while(getline(fileStream,temp)){
            while(*temp.begin() == ' ') temp.erase(temp.begin()); //  removing spaces
            string line;
            for(auto c : temp){ // removing comments
                if(c == '/') break;
                line.push_back(c);
            }
            if(!line.empty() and line.back() == '\r') line.pop_back();
            if(!line.empty()) vmcode.push_back(line);

        }

        fileStream.close();
    }else{
        cout << "error opening the file. check for its existence and read-permissions" << '\n';
    }

    Parser VMP(vmcode, file);
    CodeWriter CW(file);
    int lineNumber = 0;
    for(auto parsed_instruction : VMP._vmcode){
        int instructionType = 0xffff;

        if(parsed_instruction[0] == "push") instructionType = PUSH;
        else if(parsed_instruction[0] == "pop") instructionType = POP;
        else if(parsed_instruction[0] == "add" || parsed_instruction[0] == "sub" || parsed_instruction[0] == "lt" || parsed_instruction[0] == "gt" || parsed_instruction[0] == "neg" || parsed_instruction[0] == "eq" || parsed_instruction[0] == "and" || parsed_instruction[0] == "or" || parsed_instruction[0] == "not") instructionType = ARITHMETIC;

        for(auto assembly_instruction : CW.generateAssembly(parsed_instruction, instructionType, lineNumber)){
            assembly.push_back(assembly_instruction);
        }

        lineNumber++;
    }

    assembly.push_back("(END)");
    assembly.push_back("@END");
    assembly.push_back("0;JMP");


}


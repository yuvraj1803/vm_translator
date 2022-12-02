//
// Created by Yuvraj Sakshith on 01/12/22.
//

#include "CodeWriter.h"


CodeWriter::CodeWriter(string &file) {
    base_address["SP"] = 256;
    base_address["LCL"] = 300;
    base_address["ARG"] = 400;
    base_address["THIS"] = 3000;
    base_address["THAT"] = 3010;

    for(int i=file.size()-1;i>=0;i--){
        if(file[i] == '/') break;
        fileName.push_back(file[i]);
    }
    reverse(fileName.begin(), fileName.end());


}

vector<string> CodeWriter::generateAssembly(vector<string> &instruction, int instructionType, int lineNr = -1) {
    switch (instructionType) {
        case ARITHMETIC:
            return generateArithmetic(instruction);
            break;
        case PUSH:
            return generatePush(instruction);
            break;
        case POP:
            return generatePop(instruction);
            break;

        default:
            return vector<string>(1,"error generating assembly code for instruction on line " + to_string(lineNr));
    }
}

vector<string> CodeWriter::generateArithmetic(vector<string> &instruction){
    vector<string> asmInstruction;
    string operation = instruction[0];

    if(operation == "add"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("M=D+M");
    }
    else if(operation == "sub"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("M=M-D");
    }
    else if(operation == "neg"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("M=-M");
    }
    else if(operation == "eq"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("D=M-D");
        asmInstruction.push_back("M=-1");
        asmInstruction.push_back("@" + fileName + ".jmp." + to_string(jumpCount));
        asmInstruction.push_back("D;JEQ");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("M=0");
        asmInstruction.push_back("(" + fileName + ".jmp." + to_string(jumpCount) + ')');

        jumpCount++;


    }
    else if(operation == "gt"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("D=M-D");
        asmInstruction.push_back("M=-1");
        asmInstruction.push_back("@" + fileName + ".jmp." + to_string(jumpCount));
        asmInstruction.push_back("D;JGT");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("M=0");
        asmInstruction.push_back("(" + fileName + ".jmp." + to_string(jumpCount) + ')');

        jumpCount++;
    }
    else if(operation == "lt"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("D=M-D");
        asmInstruction.push_back("M=-1");
        asmInstruction.push_back("@" + fileName + ".jmp." + to_string(jumpCount));
        asmInstruction.push_back("D;JLT");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("M=0");
        asmInstruction.push_back("(" + fileName + ".jmp." + to_string(jumpCount) + ')');

        jumpCount++;

    }
    else if(operation == "and"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("M=D&M");

    }
    else if(operation == "or"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("M=D|M");
    }
    else if(operation == "not"){
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("M=!M");
    }

    return asmInstruction;

}
vector<string> CodeWriter::generatePop(vector<string> &instruction) {
    vector<string> asmInstruction;
    string memSegment = instruction[1];

    if(memSegment == "constant"){
        // error handling coming soon!
    }else if(memSegment == "static"){

        asmInstruction.push_back("@" + fileName + '.' + instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@addr1");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@addr1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");

    }else if(memSegment == "local") {

        asmInstruction.push_back("@"+instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@LCL");
        asmInstruction.push_back("D=D+M");
        asmInstruction.push_back("@addr1");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@addr1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");

    }else if(memSegment == "argument"){

        asmInstruction.push_back("@"+instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@ARG");
        asmInstruction.push_back("D=D+M");
        asmInstruction.push_back("@addr1");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@addr1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");


    }else if(memSegment == "pointer"){

        if(instruction[2] == "0"){
            asmInstruction.push_back("@THIS");
            asmInstruction.push_back("D=A");
            asmInstruction.push_back("@addr1");
            asmInstruction.push_back("M=D");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("M=M-1");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("D=M");
            asmInstruction.push_back("@addr1");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("M=D");
        }else{
            asmInstruction.push_back("@THAT");
            asmInstruction.push_back("D=A");
            asmInstruction.push_back("@addr1");
            asmInstruction.push_back("M=D");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("M=M-1");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("D=M");
            asmInstruction.push_back("@addr1");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("M=D");
        }

    }else if(memSegment == "temp"){

        asmInstruction.push_back("@5");
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@"+instruction[2]);
        asmInstruction.push_back("D=D+A");
        asmInstruction.push_back("@addr1");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@addr1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");

    }else if(memSegment == "this"){

        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@THIS");
        asmInstruction.push_back("D=D+M");
        asmInstruction.push_back("@tempvar");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@tempvar");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");


    }else if(memSegment == "that"){

        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@THAT");
        asmInstruction.push_back("D=D+M");
        asmInstruction.push_back("@tempvar");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M-1");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@tempvar");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");

    }else{
        // error handling coming soon!
    }

    return asmInstruction;
}

vector<string> CodeWriter::generatePush(vector<string> &instruction) { // ex. "push local 4"
    string memSegment = instruction[1];

    vector<string> asmInstruction;
    if(memSegment == "constant"){

            asmInstruction.push_back("@"+instruction[2]);
            asmInstruction.push_back("D=A");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("M=D");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("M=M+1");

    }else if(memSegment == "static"){

            asmInstruction.push_back("@" + fileName + '.' + instruction[2]);
            asmInstruction.push_back("D=M");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("M=D");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("M=M+1");

    }else if(memSegment == "local") {

            asmInstruction.push_back("@" + instruction[2]);
            asmInstruction.push_back("D=A");
            asmInstruction.push_back("@LCL");
            asmInstruction.push_back("A=D+M");
            asmInstruction.push_back("D=M");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("M=D");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("M=M+1");

    }else if(memSegment == "argument"){

            asmInstruction.push_back("@" + instruction[2]);
            asmInstruction.push_back("D=A");
            asmInstruction.push_back("@ARG");
            asmInstruction.push_back("A=D+M");
            asmInstruction.push_back("D=M");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("M=D");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("M=M+1");

    }else if(memSegment == "pointer"){

        if(instruction[2] == "0"){
            asmInstruction.push_back("@THIS");
            asmInstruction.push_back("D=M");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("M=D");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("M=M+1");
        }else{
            asmInstruction.push_back("@THAT");
            asmInstruction.push_back("D=M");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("A=M");
            asmInstruction.push_back("M=D");
            asmInstruction.push_back("@SP");
            asmInstruction.push_back("M=M+1");
        }

    }else if(memSegment == "temp"){

        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@R5");
        asmInstruction.push_back("A=D+A");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");

    }else if(memSegment == "this"){

        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@THIS");
        asmInstruction.push_back("A=D+M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");

    }else if(memSegment == "that"){

        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@THAT");
        asmInstruction.push_back("A=D+M");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");
    }else{
         // error handling coming soon!
    }

    return asmInstruction;


}

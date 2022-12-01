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
    fileName = file;

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
        /*
         * @SP
         * A=M-1
         * D=M
         * A=A-1
         * D=D+M
         * M=D
         * D=A
         * @SP
         * M=D+1
         * */
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("D=D+M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=D+1");
    }
    else if(operation == "sub"){
        /*
         * @SP
         * A=M-1
         * D=M
         * A=A-1
         * D=M-D
         * M=D
         * D=A
         * @SP
         * M=D+1
         * */
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("D=M-D");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=D+1");
    }
    else if(operation == "neg"){
        /* (BASICALLY X -> (2^16 - 1 - X) + 1 .. AKA 2'S COMPLIMENT)
         * @1111111111111111
         * D=A
         * @SP
         * A=M-1
         * M=D-M
         * M=M+1
         * */
        asmInstruction.push_back("@1111111111111111");
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("M=D-M");
        asmInstruction.push_back("M=M+1");
    }
    else if(operation == "eq"){

    }
    else if(operation == "gt"){}
    else if(operation == "lt"){}
    else if(operation == "and"){
        /*
         * @SP
         * A=M-1
         * D=M
         * A=A-1
         * M=D&M
         * D=A
         * @SP
         * M=D+1
         * */
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("M=D&M");
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=D+1");

    }
    else if(operation == "or"){
        /*
        * @SP
        * A=M-1
        * D=M
        * A=A-1
        * M=D|M
        * D=A
        * @SP
        * M=D+1
        * */
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M-1");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("A=A-1");
        asmInstruction.push_back("M=D|M");
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=D+1");
    }
    else if(operation == "not"){

    }

    return asmInstruction;

}
vector<string> CodeWriter::generatePop(vector<string> &instruction) {
    vector<string> asmInstruction;
    string memSegment = instruction[1];

    if(memSegment == "constant"){
        // error handling coming soon!
    }else if(memSegment == "static"){
        /*
         * pop static 5
         * @SP
         * A=M-1
         * D=M
         * @SP
         * M=M-1
         * @file.5
         * M=D
         * */
    }else if(memSegment == "local") {

    }else if(memSegment == "argument"){

    }else if(memSegment == "pointer"){

    }else if(memSegment == "temp"){

    }else if(memSegment == "this"){

    }else if(memSegment == "that"){

    }else{
        // error handling coming soon!
    }

    return asmInstruction;
}

vector<string> CodeWriter::generatePush(vector<string> &instruction) { // ex. "push local 4"
    string memSegment = instruction[1];

    vector<string> asmInstruction;
    if(memSegment == "constant"){
        /* push constant 4
         * @4
         * D=A
         * @SP
         * A=M
         * M=D
         * @SP
         * M=M+1
         * */
        asmInstruction.push_back("@"+instruction[2]);
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");

    }else if(memSegment == "static"){
        /* push static 5
         * @file.5
         * D=M
         * @SP
         * A=M
         * M=D
         * @SP
         * M=M+1
         * */
        asmInstruction.push_back("@" + fileName + '.' + instruction[2]);
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");

    }else if(memSegment == "local") {

        /*
         * push local 4
         * @LCL
         * D=M
         * @4
         * D=D+A
         * A=D
         * D=M
         * @SP
         * A=M
         * M=D
         * @SP
         * M=M+1
         * */
        asmInstruction.push_back("@LCL");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=D+A");
        asmInstruction.push_back("A=D");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");

    }else if(memSegment == "argument"){
        /*
        * push argument 4
        * @ARG
        * D=M
        * @4
        * D=D+A
        * A=D
        * D=M
        * @SP
        * A=M
        * M=D
        * @SP
        * M=M+1
        * */
        asmInstruction.push_back("@ARG");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=D+A");
        asmInstruction.push_back("A=D");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");
    }else if(memSegment == "pointer"){
        /* 0->THIS 1->THAT
        *
        * push pointer 0
        * @THIS
        * D=M
        * @SP
        * A=M
        * M=D
        * @SP
        * M=M+1
        * */
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
        /*
        * push temp 4
        * @5
        * D=A
        * @4
        * D=D+A
        * A=D
        * D=M
        * @SP
        * A=M
        * M=D
        * @SP
        * M=M+1
        * */
        asmInstruction.push_back("@5");
        asmInstruction.push_back("D=A");
        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=D+A");
        asmInstruction.push_back("A=D");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");
    }else if(memSegment == "this"){
        /*
         * push this 5
         *
         * @THIS
         * D=M
         * @5
         * D=D+A
         * D=M
         * @SP
         * A=M
         * M=D
         * @SP
         * M=M+1
         * */
        asmInstruction.push_back("@THIS");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=D+A");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("A=M");
        asmInstruction.push_back("M=D");
        asmInstruction.push_back("@SP");
        asmInstruction.push_back("M=M+1");

    }else if(memSegment == "that"){
        /*
         * push that 5
         *
         * @THAT
         * D=M
         * @5
         * D=D+A
         * D=M
         * @SP
         * A=M
         * M=D
         * @SP
         * M=M+1
         * */
        asmInstruction.push_back("@THAT");
        asmInstruction.push_back("D=M");
        asmInstruction.push_back("@" + instruction[2]);
        asmInstruction.push_back("D=D+A");
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

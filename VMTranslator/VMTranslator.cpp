//
// Created by Yuvraj Sakshith on 01/12/22.
//

#include "VMTranslator.h"
#include "../CodeWriter/CodeWriter.h"

VMTranslator::VMTranslator(string &path) {
    vector<string> files; // contains all the files in the directory. has filename in files[0] if path is not a directory
    bool sysFilePresent = false;
    if(filesystem::is_directory(path)){


        for(auto file_name : filesystem::directory_iterator(path)){
            if(file_name.path().stem() == "Sys"){
                sysFilePresent = true;
                continue;
            }
            if(file_name.path().extension() == ".vm"){
                files.push_back(file_name.path());
            }

        }
        if(sysFilePresent) files.push_back(path + "/Sys.vm");
    }else{
        files.push_back(path);
    }

    if(files.empty()){
        cout << "no files provided!" << '\n';
        exit(1);
    }

    if(!sysFilePresent and filesystem::is_directory(path)){
        cout << "Sys.vm not found!" << '\n';
        exit(1);
    }

    CodeWriter * CW = new CodeWriter();

    if(filesystem::is_directory(path)){
        CW->setFile(path);
        assembly.push_back("// init");
        for(auto initInstruction : CW->generateInit()){
            assembly.push_back(initInstruction);
        }
        string sysFile = path + "/Sys.vm";
        CW->setFile(sysFile);
        vector<string> call_sys_init = {"call", "Sys.init"};
        assembly.push_back("// call Sys.init 0");
        for (auto sys_init_instruction: CW->generateCall(call_sys_init)) {
            assembly.push_back(sys_init_instruction);
        }
    }


    for(auto file : files) {
        vector<string> vmcode;

        ifstream fileStream(file);
        if (fileStream.is_open()) {
            string temp;
            while (getline(fileStream, temp)) {
                while (*temp.begin() == ' ') temp.erase(temp.begin()); //  removing spaces
                string line;
                for (auto c: temp) { // removing comments
                    if (c == '/') break;
                    line.push_back(c);
                }
                if (!line.empty() and line.back() == '\r') line.pop_back();
                if (!line.empty()) vmcode.push_back(line);

            }

            fileStream.close();
        } else {
            cout << "error opening the file " << file << ". check for its existence and read-permissions" << '\n';
        }

        Parser * VMP = new Parser(vmcode, file);
        CW->setFile(file);

        int lineNumber = 0;
        for (auto parsed_instruction: VMP->_vmcode) {
            int instructionType = 0xffff;

            if (parsed_instruction[0] == "push") instructionType = PUSH;
            else if (parsed_instruction[0] == "pop") instructionType = POP;
            else if (parsed_instruction[0] == "add" || parsed_instruction[0] == "sub" ||
                     parsed_instruction[0] == "lt" || parsed_instruction[0] == "gt" || parsed_instruction[0] == "neg" ||
                     parsed_instruction[0] == "eq" || parsed_instruction[0] == "and" || parsed_instruction[0] == "or" ||
                     parsed_instruction[0] == "not")
                instructionType = ARITHMETIC;
            else if (parsed_instruction[0] == "label") instructionType = LABEL;
            else if (parsed_instruction[0] == "if-goto") instructionType = IF;
            else if (parsed_instruction[0] == "goto") instructionType = GOTO;
            else if (parsed_instruction[0] == "function") instructionType = FUNCTION;
            else if (parsed_instruction[0] == "call") instructionType = CALL;
            else if (parsed_instruction[0] == "return") instructionType = RETURN;

            string commentedVMCode = "//";
            for (auto inst: parsed_instruction) commentedVMCode += inst + ' ';
            assembly.push_back(commentedVMCode);
            for (auto assembly_instruction: CW->generateAssembly(parsed_instruction, instructionType, lineNumber)) {


                assembly.push_back(assembly_instruction);
            }

            lineNumber++;
        }

//        assembly.push_back("(END)");
//        assembly.push_back("@END");
//        assembly.push_back("0;JMP");


        free(VMP);

    }
    free(CW);


}



cmake_minimum_required(VERSION 3.23)
project(vm_translator)

set(CMAKE_CXX_STANDARD 17)

add_executable(vm_translator main.cpp
        VMTranslator/VMTranslator.cpp
        VMTranslator/VMTranslator.h
        CodeWriter/CodeWriter.cpp
        CodeWriter/CodeWriter.h
        Parser/Parser.cpp
        Parser/Parser.h
        Misc/reference.h
        )

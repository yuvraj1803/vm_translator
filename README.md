**VM Translator (Hack Architecture)**

The Hack Virtual Machine Translator (STACK MACHINE) converts the VM code **(similar to Java's Byte Code)** to the Hack Assembly code. This piece of software has been written in C++17.
This project takes advantage of the C++ Standard Template Library and the I/O Streams.

<img width="821" alt="project_diagram" src="https://user-images.githubusercontent.com/37622719/205267717-b3a06f18-1168-4c21-af23-de865f8b4373.png">

**Usage**
1. Navigate to 'cmake-build-debug' directory.
2. type './vm_translator <vm_file_path>'
3. This should create a .asm file in the same location as your .vm file.

Examples: 
**VM Code:** 



![vm_code](https://user-images.githubusercontent.com/37622719/205269562-38e398c5-9786-4b58-bbc9-6e59ca0c5487.png)



**Assembly Code:**



![asm_code](https://user-images.githubusercontent.com/37622719/205269603-e80bf4e9-3f86-4f79-90c6-c226882a9f18.png)

**Version 1**
1. supports arithmetic operations such as ***add, sub, neg, and, or, gt, lt, eq, not***.
2. supports memory access operations such as ***push and pop*** working with memory segments such as ***local, argument, static, constant, pointer, this and that***.

To know more about the Hack Architecture and the VM Translator, visit https://www.nand2tetris.org/project07


***Author: Yuvraj Sakshith***

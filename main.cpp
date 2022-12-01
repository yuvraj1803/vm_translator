#include <iostream>
#include "VMTranslator/VMTranslator.h"

using namespace std;

int main() {
    string file = "SimpleAdd/SimpleAdd.vm";
    VMTranslator VMT(file);

    for(auto i: VMT.vmcode) cout << i << '\n';
    cout << "-----------------------------------" << '\n';

    for(auto i: VMT.assembly){
        cout << i << '\n';
    }

    return 0;
}

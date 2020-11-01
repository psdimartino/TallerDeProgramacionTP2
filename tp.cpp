#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <stack>
#include "eBPFprogram.h"
using namespace std;

// enum nodeFlag {
//     UNVISITED,
//     VISITED,
//     POPED
// };

int main(int argc,char *argv[]){
    
    for(int i = 0;i < (argc - 2); ++i){
        ifstream aFile;
        // map<string, Instruction> labels;
        // vector<Instruction> instructions;
        // stack<Instruction> insStack;
        // nodeFlag flags[128] = { UNVISITED };
        // int numberOfLines;
        string fileName = argv[i+2];

        //Open file
        aFile.open(fileName);
        if(aFile.is_open() == false){
            std::cerr << "Couldn´t open file " << fileName << endl;
            return 1;
        }
        eBPFprogram program(aFile);
        fileName = fileName.substr(fileName.find_last_of('/') + 1);
        cout << fileName << " ";

        if(program.hasCycle()){
            cout << "FAIL: cycle detected" << endl;
        } else {
            cout << "GOOD" << endl;
        }

        //Close file
        aFile.close();
    }
    return 0;
}
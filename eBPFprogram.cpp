#include <sstream>
#include <stack>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "eBPFprogram.h"

using namespace std;

eBPFprogram::eBPFprogram::eBPFprogram(ifstream &initStream) {
    for(numberOfLines = 0; !initStream.eof(); ++numberOfLines){
        string auxString;
        std::getline(initStream,auxString);
        if(auxString.empty()){
            numberOfLines--;
            continue;
        }
        Instruction instruction(auxString,numberOfLines);
        instructions.push_back(instruction);
        if(instruction.isLabel()){
            labels.insert(pair<string, int>(instruction.getLabel(),numberOfLines));
        }
    }
}

bool eBPFprogram::hasCycles(){
    stack<int> insStack;
    nodeFlag flags[128] = { UNVISITED };

    insStack.push(0);
    while (!insStack.empty()) {
        Instruction instruction = instructions[insStack.top()];
        insStack.pop();
        flags[instruction.getPosition()] = POPED;
        for (int next : instruction.getNext(labels)){
            if(flags[next] == VISITED) return true;
            flags[next] = VISITED;
            insStack.push(next);
        }
    }
    return false;
}

bool eBPFprogram::hasUnusedInstructions(){
    stack<int> insStack;
    nodeFlag flags[128] = { UNVISITED };

    insStack.push(0);
    while (!insStack.empty()) {
        Instruction instruction = instructions[insStack.top()];
        insStack.pop();
        flags[instruction.getPosition()] = POPED;
        for (int next : instruction.getNext(labels)){
            if(flags[next] != VISITED){
                flags[next] = VISITED;
                insStack.push(next);
            }
        }
    }
    
    for(Instruction instruction : instructions){
        if( flags[instruction.getPosition()] == UNVISITED ){
            return true;
        }
    }
    return false;
}

eBPFprogram::eBPFprogram::eBPFprogram() {
}

eBPFprogram::eBPFprogram::~eBPFprogram() {
}
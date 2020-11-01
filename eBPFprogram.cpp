#include <sstream>
#include <stack>
#include <fstream>
#include "eBPFprogram.h"

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
            labels.insert(pair<string, Instruction>(instruction.getLabel(),instruction));
        }
    }
}

bool eBPFprogram::hasCycles(){
    stack<Instruction> insStack;
    nodeFlag flags[128] = { UNVISITED };

    insStack.push(instructions.front());
    while (!insStack.empty()) {
        Instruction instruction = insStack.top();
        insStack.pop();
        flags[instruction.getPosition()] = POPED;
        switch (instruction.getType()) {
            case CONDITIONAL_SIMPLE:
                if(flags[labels.at( instruction.getArguments().front() ) .getPosition()] == POPED){
                    return true;
                }
                flags[labels.at( instruction.getArguments().front() ) .getPosition()] = VISITED;
                insStack.push( labels.at( instruction.getArguments().front() ) );

            case NOJUMP:
                if(flags[instructions[instruction.getPosition() + 1].getPosition()] == POPED){
                    return true;
                }
                flags[instructions[instruction.getPosition() + 1].getPosition()] = POPED;
                insStack.push( instructions[instruction.getPosition() + 1] );
                break;
            case INCONDITIONAL:
            case CONDITIONAL_DOUBLE:
                for (string label : instruction.getArguments()){
                    if(flags[labels.at(label).getPosition()] == VISITED){
                        return true;
                    }
                    flags[labels.at(label).getPosition()] = VISITED;
                    insStack.push( labels.at(label) );
                }
                break;
            case RET:
                break;
        }
    }
    return false;
}

eBPFprogram::eBPFprogram::eBPFprogram() {
}

eBPFprogram::eBPFprogram::~eBPFprogram() {
}
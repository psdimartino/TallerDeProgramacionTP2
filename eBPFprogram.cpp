#include <sstream>
#include <stack>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include "eBPFprogram.h"


eBPFprogram::eBPFprogram::eBPFprogram(std::ifstream &initStream) {
    for ( lines = 0; !initStream.eof(); ++lines ) {
        std::string auxString;
        std::getline(initStream, auxString);
        if ( auxString.empty() ) {
            lines--;
            continue;
        }
        Instruction instruction(auxString, lines);
        instructions.push_back(instruction);
        if ( instruction.isLabel() ) {
            labels.insert(
                std::pair<std::string,
                int>(instruction.getLabel(), lines));
        }
    }
}

bool eBPFprogram::hasCycles() {
    std::stack<int> insStack;
    std::vector<nodeFlag> flags;

    for ( Instruction instruction : instructions ) {
        flags.emplace_back(UNVISITED);
    }

    insStack.push(0);
    while (!insStack.empty()) {
        Instruction instruction = instructions[insStack.top()];
        insStack.pop();
        flags[instruction.getPosition()] = POPED;
        for ( int next : instruction.getNext(labels) ) {
            if ( flags[next] == VISITED ) return true;
            flags[next] = VISITED;
            insStack.push(next);
        }
    }
    return false;
}
bool isUnvisited(nodeFlag flag) {
    return flag == UNVISITED;
}

bool eBPFprogram::hasUnusedInstructions() {
    std::stack<int> insStack;
    std::vector<nodeFlag> flags;

    for ( Instruction instruction : instructions ) {
        flags.emplace_back(UNVISITED);
    }

    insStack.push(0);
    while (!insStack.empty()) {
        Instruction instruction = instructions[insStack.top()];
        insStack.pop();
        flags[instruction.getPosition()] = POPED;
        for ( int next : instruction.getNext(labels) ) {
            if ( flags[next] != VISITED ) {
                flags[next] = VISITED;
                insStack.push(next);
            }
        }
    }
    if ( std::any_of(flags.begin(), flags.end(), isUnvisited) ) {
        return true;
    }
    return false;
}

eBPFprogram::eBPFprogram::eBPFprogram() {
}

eBPFprogram::eBPFprogram::~eBPFprogram() {
}

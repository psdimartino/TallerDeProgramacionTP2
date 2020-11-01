#ifndef EBPFPROGRAM_H
#define EBPFPROGRAM_H

#include <string>
#include <vector>
#include <list>
#include "Instruction.h"
#include <map>
#include <fstream>

enum nodeFlag {
    UNVISITED,
    VISITED,
    POPED
};

class eBPFprogram
{
private:
    vector<Instruction> instructions;
    map<string, Instruction> labels;
    int numberOfLines;
public:
    eBPFprogram();
    explicit eBPFprogram(ifstream &);
    ~eBPFprogram();
    bool hasCycles();
};

#endif
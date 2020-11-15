#ifndef EBPFPROGRAM_H_
#define EBPFPROGRAM_H_

#include <string>
#include "Instruction.h"
#include <map>
#include <fstream>
#include <vector>

enum nodeFlag {
    UNVISITED,
    VISITED,
    POPED
};

class eBPFprogram{
 private:
    std::vector<Instruction> instructions;
    std::map<std::string, int> labels;
    int lines;
 public:
    eBPFprogram();
    explicit eBPFprogram(std::ifstream &);
    ~eBPFprogram();
    bool hasCycles();
    bool hasUnusedInstructions();
};

#endif  //  EBPFPROGRAM_H_

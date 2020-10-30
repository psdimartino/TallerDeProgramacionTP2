#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
#include <list>

using namespace std;

enum InstructionType {
    INCONDITIONAL,
    CONDITIONAL_SIMPLE,
    CONDITIONAL_DOUBLE,
    NOJUMP, 
    RET
};

class Instruction{
private:
    const std::vector<std::string> jumpOpcodes = {"jmp","ja","jeq","jneq","jne","jlt","jle","jgt","jge","jset"};
    // std::string label, opcode, argument1,argument2,argument3;
    string label, opcode;
    list<string> arguments;
    InstructionType type;
    int position;
public:
    Instruction(const Instruction &);
    explicit Instruction(const std::string &, int);
    void imprimir() const;
    bool isLabel() const;
    list<string> getArguments() const;
    string getLabel() const;
    InstructionType getType() const;
    int getPosition() const;
    Instruction& operator=(const Instruction &);
};

#endif
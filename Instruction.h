#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <string>
#include <vector>
#include <list>
#include <map>

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
    const std::vector<std::string> jOpcodes =
        {"jmp", "ja", "jeq", "jneq", "jne", "jlt", "jle", "jgt", "jge", "jset"};
    // std::string label, opcode, argument1,argument2,argument3;
    string label, opcode;
    list<string> arguments;
    InstructionType type;
    int position;
 public:
    Instruction();
    Instruction(const Instruction &);
    explicit Instruction(const std::string &, int);
    void imprimir() const;
    bool isLabel() const;
    list<string> getArguments() const;
    string getLabel() const;
    InstructionType getType() const;
    int getPosition() const;
    Instruction& operator=(const Instruction &);
    list<int> getNext(map<string, int>);
};

#endif  //  INSTRUCTION_H_

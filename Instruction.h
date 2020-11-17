#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <string>
#include <vector>
#include <list>
#include <map>

enum InstructionType {
    INCONDITIONAL,
    CONDITIONAL_SIMPLE,
    CONDITIONAL_DOUBLE,
    NOJUMP,
    RET
};

class Instruction{
 private:
    const std::vector<std::string> jumps =
        {"jmp", "ja", "jeq", "jneq", "jne", "jlt", "jle", "jgt", "jge", "jset"};
    std::string label, opcode;
    std::list<std::string> arguments;
    InstructionType type;
    int position;
    void setType(std::string opcode, std::istringstream &argStream);
 public:
    Instruction();
    Instruction(const Instruction &);
    explicit Instruction(const std::string &, int);
    void imprimir() const;
    bool isLabel() const;
    std::string getLabel() const;
    int getPosition() const;
    Instruction& operator=(const Instruction &);
    std::list<int> getNext(std::map<std::string, int>);
};

#endif  //  INSTRUCTION_H_

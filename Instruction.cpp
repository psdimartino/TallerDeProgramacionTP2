#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "Instruction.h"

using namespace std;

Instruction::Instruction(const Instruction &toCopy) {
    this->opcode = toCopy.opcode;
    this->label = toCopy.label;
    this->position = toCopy.position;
    this->type = toCopy.type;
    this->arguments = toCopy.arguments;
}

Instruction::Instruction() {
}

Instruction& Instruction::operator=(const Instruction &toCopy) {
    this->opcode = toCopy.opcode;
    this->label = toCopy.label;
    this->position = toCopy.position;
    this->type = toCopy.type;
    this->arguments = toCopy.arguments;
    return *this;
}

Instruction::Instruction(const std::string &initString, int _position ) {
    position = _position;
    istringstream auxStream(initString);
    string auxString;

    auxStream >> auxString;
    if ( auxString.back() == ':' ) {
        auxString.erase(auxString.length()-1);
        label = auxString;
        auxStream >> auxString;
    }
    opcode = auxString;

    if ( opcode.compare("ret") == 0 ) {
        type = RET;
        return;
    }

    if ( (find(jOpcodes.cbegin(), jOpcodes.cend(), opcode))
                                     == jOpcodes.cend() ) {
        type = NOJUMP;
        return;
    }

    int i = 0;
    for ( ; !auxStream.eof(); ++i) {
        auxStream >> auxString;
        if ( auxString.back() == ',' ) {
            auxString.erase(auxString.length()-1);
        }
        if ( auxString.front() != '[' && auxString.front() != '#' ) {
            arguments.push_back(auxString);
        }
    }

    switch (i) {
    case 1:
        type = INCONDITIONAL;
        break;
    case 2:
        type = CONDITIONAL_SIMPLE;
        break;
    case 3:
        type = CONDITIONAL_DOUBLE;
        break;
    }
}

void Instruction::imprimir() const {
    cout << position + 1 << endl;
    cout << endl;
}

bool Instruction::isLabel() const {
    return !label.empty();
}

string Instruction::getLabel() const {
    return label;
}

list<string> Instruction::getArguments() const {
    return arguments;
}

InstructionType Instruction::getType() const {
    return type;
}

int Instruction::getPosition() const {
    return position;
}

list<int> Instruction::getNext(map<string, int> labels) {
    list<int> nextInstructions;
    switch (type) {
        case CONDITIONAL_SIMPLE:
            nextInstructions.push_front(labels.at(arguments.front()) );
            if ( (position + 1) == labels.at(arguments.front())) break;
        case NOJUMP:
            nextInstructions.push_front(position + 1);
            break;
        case INCONDITIONAL:
            nextInstructions.push_front(labels.at(arguments.front()));
            break;
        case CONDITIONAL_DOUBLE:
            nextInstructions.push_front(labels.at(arguments.front()));
            if ( arguments.front() == arguments.back() ) {
                nextInstructions.push_front(labels.at(arguments.back()));
            }
            break;
        case RET:
            break;
    }
    return nextInstructions;
}

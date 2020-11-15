#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "Instruction.h"

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
    std::istringstream auxStream(initString);
    std::string auxString;

    while (!auxStream.eof()) {
        auxStream >> auxString;
        if ( auxString.back() == ':' ) {
            label = auxString.erase(auxString.length()-1);
            continue;
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
        for (int i = 0; !auxStream.eof(); i++) {
            auxStream >> auxString;
            if ( auxString.back() == ',' ) {
                auxString.erase(auxString.length()-1);
            }
            if ( auxString.front() != '[' && auxString.front() != '#' ) {
                arguments.push_back(auxString);
            }
            switch (i) {
                case 0:
                    type = INCONDITIONAL;
                    break;
                case 1:
                    type = CONDITIONAL_SIMPLE;
                    break;
                case 2:
                    type = CONDITIONAL_DOUBLE;
                    break;
            }
        }
    }
}

bool Instruction::isLabel() const {
    return !label.empty();
}

std::string Instruction::getLabel() const {
    return label;
}


int Instruction::getPosition() const {
    return position;
}

std::list<int> Instruction::getNext(std::map<std::string, int> labels) {
    std::list<int> nextInstructions;
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

void Instruction::imprimir() const {
    // if (!label.empty()) {
    //     std::cerr << label << ":";
    // }
    // std::cerr << "\t";
    // if (!opcode.empty()) {
    //     std::cerr << opcode;
    // } else {
    //     std::cerr << "ERR";
    // }
    // std::cerr << " ";
    // for ( std::string argument : arguments ) {
    //     std::cerr << argument << ", ";
    // }
    // switch (type) {
    //     case RET:
    //         std::cerr << "\t\tRET";
    //         break;
    //     case NOJUMP:
    //         std::cerr << "\t\tNOJUMP";
    //         break;
    //     case INCONDITIONAL:
    //         std::cerr << "\t\tINCONDITIONAL";
    //         break;
    //     case CONDITIONAL_SIMPLE:
    //         std::cerr << "\t\tCONDITIONAL_SIMPLE";
    //         break;
    //     case CONDITIONAL_DOUBLE:
    //         std::cerr << "\t\tCONDITIONAL_DOUBLE";
    //         break;
    // }
    // std::cerr << std::endl;
}

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "Instruction.h"

using namespace std;

Instruction::Instruction(const Instruction &toCopy){
    this->opcode = toCopy.opcode;
    this->label = toCopy.label;
    this->position = toCopy.position;
    this->type = toCopy.type;
    this->arguments = toCopy.arguments;
}

Instruction::Instruction(){
}

Instruction& Instruction::operator=(const Instruction &toCopy){
    this->opcode = toCopy.opcode;
    this->label = toCopy.label;
    this->position = toCopy.position;
    this->type = toCopy.type;
    this->arguments = toCopy.arguments;
    return *this;
}

Instruction::Instruction (const std::string &initString, int _position ) {
    position = _position;
    //Parsear la informacion de la linea
    istringstream auxStream(initString);
    string auxString;

    //Primer tramo
    auxStream >> auxString;
    if ( auxString.back() == ':' ) {
        auxString.erase(auxString.length()-1);
        label = auxString;
        auxStream >> auxString;
    }
    opcode = auxString;

    //Buscar tipo
    if ( opcode.compare("ret") == 0){
        // cout << "Type RET" << endl;
        type = RET;
        return;
    }

    if( (find(jumpOpcodes.cbegin(), jumpOpcodes.cend(),opcode)) == jumpOpcodes.cend() ){
        //  cout << "Type NOJUMP" << endl;
        type = NOJUMP;
        return;
    }

    //Ver que tipo de jump es
    int i = 0;
    for(; !auxStream.eof();++i){
        auxStream >> auxString;
        if(auxString.back() == ',') {
            auxString.erase(auxString.length()-1);
        }
        if( auxString.front() != '[' && auxString.front() != '#' ){
            arguments.push_back(auxString);
        }
    }

    switch (i) {
    case 1:
        // cout << "INCONDITIONAL" << endl;
        type = INCONDITIONAL;
        break;
    case 2:
        // cout << "CONDITIONAL_SIMPLE" << endl;
        type = CONDITIONAL_SIMPLE;
        break;
    case 3:
        // cout << "CONDITIONAL_DOUBLE" << endl;
        type = CONDITIONAL_DOUBLE;
        break;
    }
}

void Instruction::imprimir() const {
    // if(!label.empty())cout << " label: " << label;
    // if(!opcode.empty())cout << " opcode: " << opcode;
    // for(string arg : arguments){
    //     cout << " " << arg;
    // }
    cout << position + 1 << endl;
    cout << endl;
}

bool Instruction::isLabel() const{
    return !label.empty();
}

string Instruction::getLabel() const {
    return label;
}

list<string> Instruction::getArguments() const{
    return arguments;
}

InstructionType Instruction::getType() const{
    return type;
}

int Instruction::getPosition() const{
    return position;
}
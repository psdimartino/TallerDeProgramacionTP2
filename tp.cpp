#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <stack>
#include "Instruction.h"
using namespace std;

int main(int argc,char *argv[]){
    
    for(int i = 0;i < (argc - 2); ++i){
        ifstream aFile;
        map<string, Instruction> labels;
        vector<Instruction> instructions;
        stack<Instruction> insStack;
        int numberOfLines;
        // //Para cambiar el directorio - Borrar
        string fileName = argv[i+2];
        // fileName = fileName.substr(0,fileName.find('.'));
        // fileName = "./" + fileName + "/" + argv[i+2];

        //Open file
        aFile.open(fileName);
        if(aFile.is_open() == false){
            std::cerr << "Couldn´t open file " << fileName << endl;
            return 1;
        }
        cout << "----------------------------------------------------------------------------------------------------------- " << endl;
        cout << "Opened " << fileName << endl;
        //Recorro todas las lineas, guardandome la posicion de cada label y la cantidad de lineas
        for(numberOfLines = 0; !aFile.eof(); ++numberOfLines){
            string auxString;
            std::getline(aFile,auxString);
            if(auxString.empty()){
                numberOfLines--;
                continue;
            }
            // cout << numberOfLines << ": ";
            Instruction instruction(auxString,numberOfLines);
            instructions.push_back(instruction);
            if(instruction.isLabel()){
                labels.insert(pair<string, Instruction>(instruction.getLabel(),instruction));//push_front(instruction);
                // cout << "was label" << endl;
            }
        }

        cout << "Instructions:" << endl;
        for(size_t j = 0; j < instructions.size() ;j++){
            instructions[j].imprimir();
        }
        // cout << "Labels:" << endl;
        // for( pair<string, Instruction> ins : labels){
        //     ins.second.imprimir();
        // }

        // cout << "Labels:" << endl;
        // for( pair<string, Instruction> ins : labels){
        //     labels.at(ins.first).imprimir();
        // }
        /*
        Stackeo la primera linea
        Para cada linea
            Si no es jump, stackeo la siguiente
            Si es jump incondicional, stackeo label
            Si es jump condicional simple, stackeo la siguiente y label
            Si es jump doble, stackeo ambos labels
        */  
        insStack.push(instructions.front());
        cout << endl << "Stack:" << endl;
        Instruction instruction = insStack.top();
        while (!insStack.empty()) {
            cout << endl;
            instruction = insStack.top();

            cout << "Size of stack:" << insStack.size() << endl << "Instruction =";
            instruction.imprimir();

            insStack.pop();
            switch (instruction.getType()) {
                case CONDITIONAL_SIMPLE:
                    labels.at( instruction.getArguments().front() ).imprimir();

                    cout << "SIMPLE. PUSH: " << endl;
                    insStack.push( labels.at( instruction.getArguments().front() ) );
                case NOJUMP:
                    (instructions[instruction.getPosition() + 1]).imprimir();

                    cout << "NOJUMP. PUSH: "<< instruction.getPosition() + 1 << endl;
                    insStack.push( instructions[instruction.getPosition() + 1] );
                    break;
                case INCONDITIONAL:
                case CONDITIONAL_DOUBLE:
                    for (string label : instruction.getArguments()){
                        insStack.push( labels.at(label) );
                        labels.at(label).imprimir();
                    }
                    cout << "INC+COND_DOUBLE. PUSH: " << endl;
                    break;
                case RET:
                    cout << "RET" << endl;
                    break;
            }
        }   
        
        // //Close file
        aFile.close();
    }
    return 0;
}
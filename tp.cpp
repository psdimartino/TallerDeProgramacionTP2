#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <stack>
#include "Graph.h"
#include "Instruction.h"
using namespace std;

int main(int argc,char *argv[]){
    string fileName;
    ifstream aFile;
    map<string, Instruction> labels;
    vector<Instruction> instructions;
    stack<Instruction> insStack;
    int numberOfLines;
    
    for(int i = 0;i < (argc - 2); i++){
        //Para cambiar el directorio - Borrar
        fileName = argv[i+2];
        fileName = fileName.substr(0,fileName.find('.'));
        fileName = "./" + fileName + "/" + argv[i+2];

        //Open file
        aFile.open("./test/" + fileName);
        if(aFile.is_open() == false){
            std::cerr << "Couldn´t open file " << argv[i+2] << endl;
            return 1;
        }

        //Recorro todas las lineas, guardandome la posicion de cada label y la cantidad de lineas
        for(numberOfLines = 0; !aFile.eof(); ++numberOfLines){
            string auxString;
            std::getline(aFile,auxString);
            if(auxString.empty()){
                numberOfLines--;
                continue;
            }
            cout << numberOfLines << ": ";
            Instruction instruction(auxString,numberOfLines);
            instructions.push_back(instruction);
            if(instruction.isLabel()){
                labels.insert(pair<string, Instruction>(instruction.getLabel(),instruction));//push_front(instruction);
                cout << "was label" << endl;
            }
        }

        cout << "Instructions:" << endl;
        for( Instruction ins : instructions){
            ins.imprimir();
        }
        cout << "Labels:" << endl;
        for( pair<string, Instruction> ins : labels){
            ins.second.imprimir();
        }

        cout << "Labels:" << endl;
        for( pair<string, Instruction> ins : labels){
            labels.at(ins.first).imprimir();
        }
        /*
        Stackeo la primera linea
        Para cada linea
            Si no es jump, stackeo la siguiente
            Si es jump incondicional, stackeo label
            Si es jump condicional simple, stackeo la siguiente y label
            Si es jump doble, stackeo ambos labels
        */  
        insStack.push(instructions.front());
        cout << "Stack:" << endl;
        Instruction instruction = insStack.top();
        while (!insStack.empty()) {
            cout << endl;
            instruction = insStack.top();

            cout << "Size of stack:" << insStack.size() << " Instruction: ";
            insStack.pop();
            instruction.imprimir();

            switch (instruction.getType()) {
                case CONDITIONAL_SIMPLE:
                    cout << "SIMPLE. PUSH: " << endl;
                    labels.at( instruction.getArguments().front() ).imprimir();
                    insStack.push( labels.at( instruction.getArguments().front() ) );
                case NOJUMP:
                    cout << "NOJUMP. PUSH: "<< instruction.getPosition() << endl;
                    instructions[instruction.getPosition() + 1].imprimir();
                    insStack.push(instructions[instruction.getPosition() + 1]);
                    break;
                case INCONDITIONAL:
                case CONDITIONAL_DOUBLE:
                    cout << "INC+COND_DOUBLE. PUSH: " << endl;
                    for (string label : instruction.getArguments()){
                        labels.at(label).imprimir();
                        insStack.push( labels.at(label) );
                    }
                    break;
                case RET:
                    cout << "RET" << endl;
                    break;
            }
        }   
        

        //Close file
        aFile.close();
    }
    return 0;
}
        // //Parse stream
        // while (!aFile.eof()){
        //     string auxString;
        //     std::getline(aFile,auxString);
        //     if(auxString.empty()) continue;
        //     Instruction instruction(auxString);
        //     instruction.imprimir();
        //     instructions.push_front(instruction);
        //     if(instruction.isLabel()){
        //         labels.push_front(instruction);
        //         printf("was label\n");
        //     }
        // }

        // //Generate tree
        // for(int j =0; !instructions.empty(); j++){
        //     Instruction instruction = instructions.front();
        //     for(string label : instruction.getArguments()){
        //     }
        //     instructions.pop_front();
        // }
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <stack>
#include <thread>
#include <mutex>
#include "Thread.h"
#include "eBPFprogram.h"
#include "ProgramsEvaluator.h"
#include "ProtectedQueue.h"
#include "ProtectedList.h"
#include "Result.h"

int main(int argc, char *argv[]) {
    ProtectedQueue<Result> programs;
    ProtectedList<Result> results;
    std::vector<Thread*> threads;
    int numberOfThreads = atoi(argv[1]);

    for ( int i = 0; i < (argc - 2); ++i ) {
        std::ifstream aFile;
        std::string fileName = argv[i+2];

        aFile.open(fileName);
        if ( aFile.is_open() == false ) {
            return 1;
        }
        fileName = fileName.substr(fileName.find_last_of('/') + 1);
        eBPFprogram program(aFile);
        Result result(fileName, program);
        programs.push(result);
        aFile.close();
    }
    programs.endLoading();

    for ( int i = 0; i < numberOfThreads ; ++i ) {
        Thread *t = new ProgramsEvaluator(programs, results);
        t->start();
        threads.push_back(t);
    }

    for ( int i = 0; i < numberOfThreads ; i++ ) {
        threads[i]->join();
        delete threads[i];
    }

    results.sort();

    Result result;
    for ( int i = 0; i < (argc - 2); ++i ) {
        std::cout << results.front() << std::endl;
    }
    return 0;
}


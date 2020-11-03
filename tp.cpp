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
using namespace std;

#define N 2

int compareResults(Result& result1, Result& result2) {
    return result2.programName().compare(result1.programName());
}

int main(int argc, char *argv[]) {
    ProtectedQueue<Result> programs;
    ProtectedList<Result> results;
    vector<Thread*> threads;

    for ( int i = 0; i < (argc - 2); ++i ) {
        ifstream aFile;
        string fileName = argv[i+2];

        aFile.open(fileName);
        if ( aFile.is_open() == false ) {
            std::cerr << "Couldn´t open file " << fileName << endl;
            return 1;
        }
        fileName = fileName.substr(fileName.find_last_of('/') + 1);
        cerr << "Loaded file number " << i + 1 << " named " << fileName <<endl;
        eBPFprogram program(aFile);
        Result result(fileName, program);
        programs.push(result);
        aFile.close();
    }
    programs.endLoading();

    for ( int i = 0; i < N ; ++i ) {
        Thread *t = new ProgramsEvaluator(programs, results);
        t->start();
        threads.push_back(t);
        cerr << "Loaded thread number " << i + 1 << endl;
    }

    for ( int i = 0; i < N ; i++ ) {
        cerr << "Asking thread number " << i + 1 << " to join" << endl;
        threads[i]->join();
        cerr << "Thread number " << i + 1<< " joined" << endl;
        delete threads[i];
    }
    cerr << "All threads joined" << endl;

    results.sort(&compareResults);
    cerr << "Results sorted" << endl;

    Result result;
    for ( int i = 0; i < (argc - 2); ++i ) {
        cout << results.front() << endl;
    }
    return 0;
}


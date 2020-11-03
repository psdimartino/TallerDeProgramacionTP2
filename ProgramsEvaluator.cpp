#include "ProgramsEvaluator.h"

ProgramsEvaluator::~ProgramsEvaluator() {
}

void ProgramsEvaluator::run() {  // Override
    Result result;
    while ( q.front(&result) ) {
        if ( result.program().hasCycles() ) {
            result.hasCycle(true);
        } else {
            result.hasCycle(false);
            result.hasUnusedInstructions(
                result.program().hasUnusedInstructions());
        }
        l.push_front(result);
    }
    cerr << "The queue is empty" << endl;
}

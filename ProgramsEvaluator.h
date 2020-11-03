#ifndef PROGRAMSEVALUATOR_H_
#define PROGRAMSEVALUATOR_H_

#include <queue>
#include "Thread.h"
#include "eBPFprogram.h"
#include "ProtectedQueue.h"
#include "ProtectedList.h"
#include "Result.h"
#include <iostream>

class ProgramsEvaluator : public Thread {
 private:
    ProtectedQueue<Result> &q;
    ProtectedList<Result> &l;
 public:
    explicit ProgramsEvaluator(ProtectedQueue<Result> &q_,
                                 ProtectedList<Result> &l_)
                                          : q(q_), l(l_) {}
    ~ProgramsEvaluator();
    void run() override;
};

#endif  //  PROGRAMSEVALUATOR_H_

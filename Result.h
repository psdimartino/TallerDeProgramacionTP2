#ifndef RESULT_H_
#define RESULT_H_
#include <string>
#include "eBPFprogram.h"

class Result {
 private:
    eBPFprogram ebpfprogram;
    std::string programName_;
    bool hasCycle_, hasUnusedInstructions_;
 public:
    explicit Result(std::string, eBPFprogram);
    Result();
    ~Result();
    eBPFprogram& program();
    std::string programName();
    void hasCycle(bool);
    void hasUnusedInstructions(bool);
    friend std::ostream& operator<<(std::ostream& os, const Result &other) {
        os << other.programName_;
        if ( other.hasCycle_ ) {
            os << " FAIL: cycle detected";
        } else if ( other.hasUnusedInstructions_ ) {
            os << " FAIL: unused instructions detected";
        } else { os << " GOOD"; }
        return os;
    }
    bool operator <(const Result & other) const;
};

#endif  // RESULT_H_

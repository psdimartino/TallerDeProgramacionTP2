#include "Result.h"
#include <iostream>

void Result::hasCycle(bool result) {
    hasCycle_ = result;
}

void Result::hasUnusedInstructions(bool result) {
    hasUnusedInstructions_ = result;
}

Result::Result(std::string const programName, eBPFprogram ebpfprogram) {
    this->programName_ = programName;
    this->ebpfprogram = ebpfprogram;
}

bool Result::operator<(const Result & other) const {
    return this->programName_ < other.programName_;
}

std::string Result::programName() {
    return programName_;
}

eBPFprogram& Result::program() {
    return ebpfprogram;
}

Result::Result() {
}

Result::~Result() {
}

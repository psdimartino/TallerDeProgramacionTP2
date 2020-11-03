#include <thread>
#include "Thread.h"

void Thread::start() {
    /* Run the subclass in the thread*/
    t = std::thread(&Thread::run, this);
}

Thread::Thread() {
}

void Thread::join() {
    t.join();
}

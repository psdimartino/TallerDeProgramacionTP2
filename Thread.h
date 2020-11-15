#ifndef THREAD_H_
#define THREAD_H_

#include <thread>

class Thread {
 private:
    std::thread t;
 public:
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    virtual ~Thread() {}
};

#endif  // THREAD_H_

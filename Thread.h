#ifndef THREAD_H_
#define THREAD_H_

#include <thread>

using namespace std;

class Thread {
 private:
    std::thread t;
 public:
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    virtual ~Thread() {}

    // Thread(const Thread&) = delete;
    // Thread& operator=(const Thread&) = delete;
    // Thread(Thread&& other) {
    //     this->t = std::move(other.t);
    // }
    // Thread& operator=(Thread&& other) {
    //     this->t = std::move(other.t);
    //     return *this;
    // }
};

#endif  // THREAD_H_

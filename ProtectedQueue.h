#ifndef PROTECTEDQUEUE_H_
#define PROTECTEDQUEUE_H_

#include <mutex>
#include <queue>
#include <condition_variable>
#include "Thread.h"

template <typename T>
class ProtectedQueue {
 private:
    std::mutex m;
    std::queue<T> q;
    std::condition_variable cv;
    bool isWaiting;
 public:
    ProtectedQueue();
    ~ProtectedQueue();
    bool front(T*);
    void push(T const &);
    // bool empty();
    bool waiting();
    void endLoading();
    ProtectedQueue& operator=(ProtectedQueue&&);
};

template <typename T>
ProtectedQueue<T>::ProtectedQueue() {
    isWaiting = true;
}

template <typename T>
ProtectedQueue<T>::~ProtectedQueue() {
}

template <typename T>
bool ProtectedQueue<T>::front(T *frontElement) {
    std::unique_lock<std::mutex> lock(m);
    while ( waiting() ) {  // spourious wake-ups
        // blocks the current thread until the condition variable is woken up
        cv.wait(lock);
    }
    if ( q.empty() ) return false;
    *frontElement = q.front();
    q.pop();
    return true;
}

template <typename T>
void ProtectedQueue<T>::push(T const &element) {
    std::unique_lock<std::mutex> lock(m);
    q.push(element);
    cv.notify_all();  // notify all threads that a element has been pushed
}

template <typename T>
bool ProtectedQueue<T>::waiting() {
    return isWaiting;
}

template <typename T>
void ProtectedQueue<T>::endLoading() {
    isWaiting = false;
}
#endif  // PROTECTEDQUEUE_H_

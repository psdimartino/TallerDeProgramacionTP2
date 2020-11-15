#ifndef PROTECTEDLIST_H_
#define PROTECTEDLIST_H_
#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
#include <algorithm>

template <typename T>
class ProtectedList {
 private:
    std::list<T> l;
    std::mutex m;
    std::condition_variable cv;
 public:
    ProtectedList();
    ~ProtectedList();
    void push_front(T element);
    T front();
    void sort();
};

template <typename T>
void ProtectedList<T>::push_front(T element) {
    std::unique_lock<std::mutex> lock(m);
    l.push_front(element);
}

template <typename T>
T ProtectedList<T>::front() {
    std::unique_lock<std::mutex> lock(m);
    T ret = l.front();
    l.pop_front();
    cv.notify_all();
    return ret;
}

template <typename T>
void ProtectedList<T>::sort() {
    // std::unique_lock<std::mutex> lock(m);
    l.sort();
    cv.notify_all();
}

template <typename T>
ProtectedList<T>::ProtectedList() {
}

template <typename T>
ProtectedList<T>::~ProtectedList() {
}

#endif  // PROTECTEDLIST_H_

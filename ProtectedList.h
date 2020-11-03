#ifndef PROTECTEDLIST_H_
#define PROTECTEDLIST_H_
#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
#include <algorithm>

using namespace std;

template <typename T>
class ProtectedList {
 private:
    list<T> l;
    mutex m;
    condition_variable cv;
 public:
    ProtectedList();
    ~ProtectedList();
    void push_front(T element);
    T front();
    void sort(int (*comp)(T &, T &));
};

template <typename T>
void ProtectedList<T>::push_front(T element) {
    unique_lock<mutex> lock(m);
    l.push_front(element);
    cerr << "Result list " << element << endl;
}

template <typename T>
T ProtectedList<T>::front() {
    unique_lock<mutex> lock(m);
    T ret = l.front();
    l.pop_front();
    cv.notify_all();
    return ret;
}

template <typename T>
void ProtectedList<T>::sort( int (*comp)(T &, T &) ) {
    unique_lock<mutex> lock(m);
    l.sort(comp);
    cv.notify_all();
}

template <typename T>
ProtectedList<T>::ProtectedList() {
}

template <typename T>
ProtectedList<T>::~ProtectedList() {
}

#endif  // PROTECTEDLIST_H_

//
// Created by manjaro on 3/28/20.
//
#ifndef LAB3_DYNAMIC_ARRAY_H
#define LAB3_DYNAMIC_ARRAY_H
#include <cmath>
template<typename T>
class DynArray {
  T* items_;
  size_t capacity_;

public:
  explicit DynArray(size_t cap): capacity_ {cap} { items_ = new T[cap]; }
  ~DynArray() { delete[] items_; }

  size_t size() { return capacity_; }
  T& operator[](size_t i) { return items_[i]; }

  void resize(size_t cap) {
    T* newArr = new T[cap];
    for (size_t i = 0; i < fmin(capacity_, cap); i++)
      newArr[i] = items_[i];
    delete[] items_;
    items_ = newArr;
    capacity_ = cap;
  }
};

#endif    // LAB3_DYNAMIC_ARRAY_H

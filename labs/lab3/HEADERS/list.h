//
// Created by manjaro on 3/28/20.
//

#ifndef LAB3_LIST_H
#define LAB3_LIST_H
#include "dynamic_array.h"
template<typename T>
class List {
  DynArray<T> _array = new DynArray<T>[size_];
  int size_;

public:
  List(): _array {16}, size_ {0} {}
  ~List() = default;

  int size() { return size_; }

  T& operator[](size_t i) { return _array[i]; }
  void insert(size_t index, T value) {
    _array.resize(_array.size() + 1);
    for (size_t i = 0; size_ - i > index; i++)
      _array[size_ - i] = _array[size_ - i - 1];
    _array[index] = value;
    size_++;
  }
  void remove_at(size_t index) {
    for (size_t i = index; i < size_ - 1; i++) {
      _array[i] = _array[i + 1];
    }
    size_--;
  }
  void push_back(T value) {
    _array[size_] = value;
    size_++;
    if (size_ == _array.size()) _array.resize(_array.size() + 1);
  }
  void remove(T value) {
    for (size_t i = 0; i < size_; i++) {
      if (_array[i] == value) { remove_at(i); }
    }
  }
  int index_of(T value) {
    for (size_t i = 0; i < size_; i++) {
      if (_array[i] == value) return i;
    }
    return -1;
  }
  bool contains(T value) {
    for (size_t i = 0; i < size_; i++) {
      if (_array[i] == value) return true;
    }
    return false;
  }
  bool empty() { return size_ == 0; }
  void clear() { size_ = 0; }
};
bool operator==(const Organisation& o1, const Organisation& o2) {
  return o1.country == o2.country && o1.id == o2.id && o1.label == o2.label &&
         o1.founded_date == o2.founded_date && o1.founders == o2.founders &&
         o1.type == o2.type;
}
#endif    // LAB3_LIST_H

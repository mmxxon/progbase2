#ifndef __LIST_H
#define __LIST_H

#include "dynamic_array.h"

#include <iostream>
using namespace std;

class List {
  DynamicArray _array;
  int size_ = 0;

public:
  List();
  ~List();
  int size();

  float get(int index);
  void set(int index, float value);
  void insert(int index, float value);
  void remove_at(int index);
  void push_back(float value);
  void remove(float value);
  int index_of(float value);
  bool contains(float value);
  bool empty();
  void clear();
  void print();
};

#endif /* end of include guard: __LIST_H */

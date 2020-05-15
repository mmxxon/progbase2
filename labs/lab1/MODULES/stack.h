#ifndef __STACK_H
#define __STACK_H

#include "dynamic_array.h"

#include <iostream>
using namespace std;

class Stack {
  DynamicArray _array;
  int size_ = 0;

public:
  Stack();
  ~Stack();
  int size();
  void push(float value);
  float peek();
  float pop();
  bool empty();
  void print();
};
#endif /* end of include guard: __STACK_H */

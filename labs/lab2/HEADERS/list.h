#ifndef __LIST2_H
#define __LIST2_H

#include "Organisations.h"
#include "dynamic_array.h"
#include <iomanip>
#include <iostream>
using namespace std;

bool operator==(Organisation o1, Organisation o2);
class List {
  DynamicArray _array;
  int size_;

public:
  List();
  ~List();
  int size();
  void insert(int index, Organisation value);
  void remove_at(int index);
  void push_back(Organisation value);
  void remove(Organisation value);
  int index_of(Organisation value);
  bool contains(Organisation value);
  bool empty();
  void clear();
  void print();
  Organisation &operator[](int i);
  int getMaxWidth(int val = 0);
};
#endif /* end of include guard: __LIST2_H */

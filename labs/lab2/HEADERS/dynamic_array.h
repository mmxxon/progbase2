#ifndef __DYNARR2_H
#define __DYNARR2_H
#include "Organisations.h"

class DynamicArray {
  Organisation *items_;
  int capacity_;

public:
  DynamicArray(int capacity);
  ~DynamicArray();
  int size();
  void resize(int capacity);
  Organisation &operator[](int i);
};

#endif /* end of include guard: __DYNARR2_H */

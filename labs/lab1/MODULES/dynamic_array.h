#ifndef __DYNARR_H
#define __DYNARR_H

#include <iostream>
class DynamicArray {
  float* items_;
  int capacity_;

public:
  DynamicArray(int capacity);
  ~DynamicArray();
  int size();
  void resize(int capacity);
  float get(int index);
  void set(int index, float value);
};

#endif /* end of include guard: __DYNARR_H */

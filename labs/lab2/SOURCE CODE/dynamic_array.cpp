#include "../HEADERS/dynamic_array.h"

DynamicArray::DynamicArray(int capacity) {
  items_ = new Organisation[capacity];
  capacity_ = capacity;
}
DynamicArray::~DynamicArray() { delete[] items_; }
Organisation& DynamicArray::operator[](int i) { return items_[i]; }

void DynamicArray::resize(int capacity) {
  Organisation* tmparr = new Organisation[capacity];
  for (int i = 0; i < capacity_; i++)
    tmparr[i] = items_[i];
  delete[] items_;
  items_ = tmparr;
  capacity_ = capacity;
}
int DynamicArray::size() { return capacity_; }

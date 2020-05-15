#include "dynamic_array.h"

DynamicArray::DynamicArray(int capacity) {
  items_ = new float[capacity];
  capacity_ = capacity;
}
DynamicArray::~DynamicArray() { delete[] items_; }
float DynamicArray::get(int index) { return items_[index]; }
void DynamicArray::set(int index, float value) { items_[index] = value; }
void DynamicArray::resize(int capacity) {
  float* tmp = new float[capacity];
  for (int i = 0; i < capacity_; i++)
    tmp[i] = items_[i];
  delete items_;
  items_ = tmp;
  capacity_ = capacity;
}
int DynamicArray::size() { return capacity_; }

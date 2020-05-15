#include "stack.h"

Stack::Stack(): _array {4} {}
Stack::~Stack() {}
int Stack::size() { return size_; }

void Stack::push(float value) {
  _array.set(size_, value);
  size_++;
  if (size_ == _array.size()) _array.resize(_array.size() * 2);
}

float Stack::peek() {
  if (empty()) {
    cout << "\033[;;41mSTACK IS EMPTY\033[0m\n" << endl;
    exit(EXIT_FAILURE);
  } else
    return _array.get(size_ - 1);
}

float Stack::pop() {
  if (empty()) {
    cout << "\033[;;41mSTACK IS EMPTY\033[0m\n" << endl;
    exit(EXIT_FAILURE);
  }
  float tmpVal = _array.get(size_ - 1);
  size_--;
  return tmpVal;
}

bool Stack::empty() { return size_ == 0; }

void Stack::print() {
  cout << "\033[;;42mStack:\033[0m ";
  for (int i = 0; i < size_; i++) {
    cout << "\n\033[;;46m" << i << ")\033[0m " << _array.get(size_ - 1 - i);
  }
  cout << endl << endl;
}

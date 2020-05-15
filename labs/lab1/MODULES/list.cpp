#include "list.h"

List::List(): _array {4} {}
List::~List() {}
int List::size() { return size_; }
float List::get(int index) {
  if (size_ >= index && index >= 0) { return _array.get(index); }
  perror("\033[;;41mWRONG INDEX\033[0m\n");
  exit(EXIT_FAILURE);
}
void List::set(int index, float value) {
  if (size_ >= index && index >= 0) {
    _array.set(index, value);
    return;
  }
  perror("\033[;;41mWRONG INDEX\033[0m\n");
  exit(EXIT_FAILURE);
}
void List::insert(int index, float value) {
  if (size_ == _array.size() - 1) _array.resize(_array.size() * 2);
  for (int i = 0; index + i < size_; i++) {
    set(size_, get(index + i));
  }
  set(index, value);
}
void List::remove_at(int index) {
  for (int i = index; i < size_ - 1; i++) {
    set(i, get(i + 1));
  }
  size_--;
}
void List::push_back(float value) {
  if (size_ == _array.size() - 1) _array.resize(_array.size() * 2);
  set(size_, value);
  size_++;
}
void List::remove(float value) {
  for (int i = 0; i < size_; i++) {
    if (get(i) == value) { remove_at(i); }
  }
}
int List::index_of(float value) {
  for (int i = 0; i < size_; i++) {
    if (get(i) == value) return i;
  }
  return -1;
}
bool List::contains(float value) {
  for (int i = 0; i < size_; i++) {
    if (get(i) == value) return true;
  }
  return false;
}
bool List::empty() { return size_ == 0; }
void List::clear() { size_ = 0; }
void List::print() {
  cout << "\033[;;44mList\033[0m";
  for (int i = 0; i < size_; i++) {
    cout << "\n\033[;;46m" << i << ")\033[0m " << get(i);
  }
  cout << "\033[0m" << endl;
  cout << "\033[;;44mSIZE\033[0m " << size();
  cout << "\033[0m" << endl;
  cout << "\033[;;44mCAPACITY:\033[0m " << _array.size() << endl;
  cout << endl;
}

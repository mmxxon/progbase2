#include "../HEADERS/list.h"
#define color1 "\033[31m"
#define color2 "\033[32m"
#define color3 "\033[33m"
#define color4 "\033[34m"
#define color5 "\033[35m"
#define color6 "\033[36m"
#define color7 "\033[37m"
#define restt "\033[0m"
List::List(): _array {5} {
  size_ = 0;
}
List::~List() {}
int List::size() {
  return size_;
}
Organisation& List::operator[](int i) {
  return _array[i];
}
void List::insert(int index, Organisation value) {
  _array.resize(_array.size() + 1);
  for (int i = 0; size_ - i > index; i++)
    _array[size_ - i] = _array[size_ - i - 1];
  _array[index] = value;
  size_++;
}
void List::remove_at(int index) {
  for (int i = index; i < size_ - 1; i++) {
    _array[i] = _array[i + 1];
  }
  size_--;
}
void List::push_back(Organisation value) {
  _array[size_] = value;
  size_++;
  if (size_ == _array.size())
    _array.resize(_array.size() + 1);
}
void List::remove(Organisation value) {
  for (int i = 0; i < size_; i++) {
    if (_array[i] == value) {
      remove_at(i);
    }
  }
}
int List::index_of(Organisation value) {
  for (int i = 0; i < size_; i++) {
    if (_array[i] == value)
      return i;
  }
  return -1;
}
bool List::contains(Organisation value) {
  for (int i = 0; i < size_; i++) {
    if (_array[i] == value)
      return true;
  }
  return false;
}
bool List::empty() {
  return size_ == 0;
}
void List::clear() {
  size_ = 0;
}
void List::print() {
  int l1 = 5;
  for (int i = 0; i < size_; i++) {
    if (_array[i].label.length() > l1)
      l1 = _array[i].label.length();
  }
  int l2 = 8;
  for (int i = 0; i < size_; i++) {
    if (_array[i].founders.length() > l2)
      l2 = _array[i].founders.length();
  }
  cout << color1 << left << setw(9) << "Country" << restt << color2 << left
       << setw(l1 + 3) << "Label" << restt << color4 << left << setw(16)
       << "Type" << restt << color5 << setw(l2 + 3) << "Founders" << color6
       << setw(9) << left << "Founded" << color7 << "NASDAQ" << restt << endl;
  for (int i = 0; i < size_; i++) {
    cout << color1 << left << setw(9) << _array[i].country << restt << color2
         << left << setw(l1 + 3) << _array[i].label << restt << color4 << left
         << setw(16) << _array[i].type << restt << color5 << setw(l2 + 3)
         << _array[i].founders << color6 << setw(9) << _array[i].founded_date
         << color7 << _array[i].NASDAQ << restt << endl;
  }
  cout << color3 << "SIZE: " << restt << size() << endl;
  cout << color3 << "CAPACITY: " << restt << _array.size() << endl;
}

bool operator==(Organisation o1, Organisation o2) {
  return o1.country == o2.country;
}

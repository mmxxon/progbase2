#ifndef LAB3_STRING_TABLE_H
#define LAB3_STRING_TABLE_H

#include <iostream>
#include <unistd.h>
using std::string, std::cout, std::endl;
class StringTable {

  string* cells_ = nullptr;
  size_t rows_ = 0;
  size_t cols_ = 0;

public:
  StringTable(size_t rows, size_t cols);
  ~StringTable();

  size_t size_rows() const;
  size_t size_columns() const;

  string& at(size_t rowIndex, size_t colIndex);

  void print();
};

#endif /* end of include guard: LAB3_STRING_TABLE_H */

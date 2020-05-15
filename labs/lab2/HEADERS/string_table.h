#ifndef __STRING_TABLE2_H
#define __STRING_TABLE2_H

#include <iostream>
#include <unistd.h>
using std::string, std::cout, std::endl;
class StringTable {
  std::string* cells_ = nullptr;    // allocated memory for matrix
  int nrows_ = 0;
  int ncols_ = 0;

public:
  StringTable(int rows, int cols);
  ~StringTable();

  int size_rows();
  int size_columns();

  string& at(int rowIndex, int colIndex);

  void print();
};

#endif /* end of include guard: __STRING_TABLE2_H */

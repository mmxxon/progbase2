#pragma once
using namespace std;
#include <string>
#include <iostream>
using namespace std;

class StringTable
{
   string *cells_ = nullptr;
   size_t nrows_ = 0;
   size_t ncols_ = 0;

public:
   StringTable(size_t rows, size_t cols);
   ~StringTable();

   size_t size_rows();
   size_t size_columns();

   string & at(int colIndex, int rowIndex);
   void print();
};

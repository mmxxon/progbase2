#include "../HEADERS/string_table.h"
StringTable::StringTable(size_t rows, size_t cols) {
  cells_ = new string[rows * cols];
  rows_ = rows;
  cols_ = cols;
}
StringTable::~StringTable() { delete[] cells_; }
size_t StringTable::size_rows() const { return rows_; }
size_t StringTable::size_columns() const { return cols_; }
std::string& StringTable::at(size_t rowIndex, size_t colIndex) {
  return cells_[cols_ * rowIndex + colIndex];
}
void StringTable::print() {
  for (size_t i = 0; i < size_rows(); i++) {
    for (size_t j = 0; j < size_columns(); j++) {
      string to_filter = at(i, j);
      for (size_t k = 0; k < to_filter.length(); k++) {
        if (to_filter[k] == '"') { to_filter.erase(k, 1); }
      }
      cout << '[' << to_filter << ']';
      usleep(10000);
    }
    cout << endl;
  }
}

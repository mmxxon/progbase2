#include "../HEADERS/string_table.h"
StringTable::StringTable(int rows, int cols) {
  cells_ = new string[rows * cols];
  nrows_ = rows;
  ncols_ = cols;
}
StringTable::~StringTable() {}
int StringTable::size_rows() {
  return nrows_;
}
int StringTable::size_columns() {
  return ncols_;
}
std::string& StringTable::at(int rowIndex, int colIndex) {
  return cells_[ncols_ * rowIndex + colIndex];
}
void StringTable::print() {
  for (size_t i = 0; i < size_rows(); i++) {
    for (size_t j = 0; j < size_columns(); j++) {
      string to_filter = at(i, j);
      for (size_t i = 0; i < to_filter.length(); i++) {
        if (to_filter[i] == '"') {
          to_filter.erase(i, 1);
        }
      }
      cout << '[' << to_filter << ']';
      usleep(10000);
    }
    cout << endl;
  }
}

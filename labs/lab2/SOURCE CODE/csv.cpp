#include "../HEADERS/csv.h"
StringTable Csv_parse(string& csvStr) {
  const char* begin = csvStr.c_str();
  bool quotes = 0;
  int mcols = 0, rows = 0, cols = 0;
  for (const char* p = begin; *p; p++) {
    if (*p == '"')
      quotes = !quotes;
    else if (*p == ',' and quotes == 0) {
      cols++;
      begin = p + 1;
    } else if (*p == '\n') {
      if (cols > mcols) mcols = cols;
      cols = 0;
      rows++;
      begin = p + 1;
    }
  }
  mcols++;
  StringTable table {rows, mcols};
  begin = csvStr.c_str();
  quotes = 0, cols = 0, rows = 0;
  for (const char* p = begin; *p; p++) {
    if (*p == '"')
      quotes = !quotes;
    else if (*p == ',' and quotes == 0) {
      table.at(rows, cols) = string(begin, p - begin);
      cols++;
      begin = p + 1;
    } else if (*p == '\n') {
      table.at(rows, cols) = string(begin, p - begin);
      for (cols++; cols < mcols; cols++) {
        table.at(rows, cols) = "";
      }
      cols = 0;
      rows++;
      begin = p + 1;
    }
  }
  return table;
}
string Csv_toString(StringTable& table) {
  string tmp;
  for (int i = 0; i < table.size_rows(); i++) {
    for (int j = 0; j < table.size_columns(); j++) {
      tmp += table.at(i, j) + ",";
    }
    tmp[tmp.length() - 1] = '\n';
  }
  return tmp;
}

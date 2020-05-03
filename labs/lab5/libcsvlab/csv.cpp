#include "csv.h"
using namespace std;
StringTable Csv_parse(string& csvStr) {

  size_t nrows = 0;
  size_t ncols = 0;
  int indprev = -1;
  bool r = true;
  int k = csvStr[0];
  int i = 1;
  while (k != '\n') {
    if (k == ',') ncols++;
    k = csvStr[i];
    i++;
  }
  ncols++;
  k = csvStr[0];
  i = 1;
  while (k != '\0') {
    if (k == '\n') nrows++;
    k = csvStr[i];
    i++;
  }
  StringTable st {nrows, ncols};
  indprev = -1;
  for (int i = 0; i < nrows; i++) {
    for (int j = 0; j < ncols - 1; j++) {
      int ind =
        csvStr.substr(indprev + 1, csvStr.size() - indprev - 1).find(",");
      if (indprev != -1) {
        ind += indprev;
        ind++;
      }
      st.at(i, j) = csvStr.substr(indprev + 1, ind - indprev - 1);
      indprev = ind;
    }
    int ind =
      csvStr.substr(indprev + 1, csvStr.size() - indprev - 1).find("\n");
    if (indprev != -1) {
      ind += indprev;
      ind++;
    }
    st.at(i, ncols - 1) = csvStr.substr(indprev + 1, ind - indprev - 1);
    indprev = ind;
  }
  return st;
}
string Csv_toString(StringTable& table) {
  string str = "";
  for (int i = 0; i < table.size_rows(); i++) {
    for (int j = 0; j < table.size_columns() - 1; j++) {
      str.append(table.at(i, j));
      str.push_back(',');
    }
    str.append(table.at(i, table.size_columns() - 1));
    if (i != table.size_rows() - 1) str.push_back('\n');
  }
  return str;
}
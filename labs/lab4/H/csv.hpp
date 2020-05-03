#ifndef CSV_H
#define CSV_H

#include "string_table.hpp"
using namespace std;
StringTable Csv_parse(string& csvStr);
string Csv_toString(StringTable& table);

#endif    // CSV_H

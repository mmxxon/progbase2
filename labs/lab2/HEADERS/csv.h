#ifndef __CSV2_H
#define __CSV2_H

#include "string_table.h"
using namespace std;
// parse csv, init and fill string table
StringTable Csv_parse(string& csvStr);

// create string and fill it with csv text
string Csv_toString(StringTable& table);

#endif /* end of include guard: __CSV2_H */

#ifndef LAB3_HEADERS_CSV
#define LAB3_HEADERS_CSV

#include "string_table.h"
using namespace std;
// parse csv, init and fill string table
StringTable Csv_parse(string& csvStr);

// create string and fill it with csv text
string Csv_toString(StringTable& table);

#endif /* end of include guard: LAB3_HEADERS_CSV */

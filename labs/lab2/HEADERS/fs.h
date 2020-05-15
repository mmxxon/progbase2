#ifndef __FS2_H
#define __FS2_H
#include "csv.h"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
void Check_CountOfArgs(int arg, int num);
void Check_isOpen(ifstream* file);
void Check_isClosed(ifstream* file);
StringTable Table_fromFile(string& file_name);
void File_fromTable(StringTable& table, string& file_name);

// void check_csv( char * arg );
#endif /* end of include guard: __FS2_H */

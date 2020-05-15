#include "../HEADERS/fs.h"

void Check_CountOfArgs(int arg, int num) {
  if (arg < num) {
    perror("\033[;;41mWRONG COUNT OF ARGUMENTS\033[0m\n");
    exit(EXIT_FAILURE);
  }
}
void Check_isOpen(ifstream* file) {
  if (!file->is_open()) {
    perror("\033[;;41mCAN'T OPEN FILE\033[0m\n");
    exit(EXIT_FAILURE);
  }
}
void Check_isClosed(ifstream* file) {
  if (file->is_open()) {
    perror("\033[;;41mCAN'T CLOSE FILE\033[0m\n");
    exit(EXIT_FAILURE);
  }
}
StringTable Table_fromFile(string& file_name) {
  ifstream file(file_name);
  Check_isOpen(&file);
  string from_file, temp;
  while (getline(file, temp)) {
    from_file += temp + "\n";
  }
  file.close();
  Check_isClosed(&file);
  return Csv_parse(from_file);
}
void File_fromTable(StringTable& table, string& file_name) {
  ofstream file(file_name);
  if (!file.is_open()) {
    perror("\033[;;41mCAN'T OPEN FILE\033[0m\n");
    exit(EXIT_FAILURE);
  }
  string out = Csv_toString(table);
  file << out << endl;
  return;
}
/*void check_csv( char * arg ) {
  std::string format = &arg[strlen( arg ) - 4];
  if( format != ".csv" ) {
    perror( "\033[;;41mFILE MUST BE .csv\033[0m\n" );
    exit( EXIT_FAILURE );
  }
}*/

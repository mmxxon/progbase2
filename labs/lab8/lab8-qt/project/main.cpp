#include "cui.hpp"

#include <stdio.h>
#include <string>

using namespace std;
auto main() -> int {
  cout << "\033[2J\033[H";
  int key = 0;
  char buff[FILENAME_MAX];
  getcwd(buff, FILENAME_MAX);
  string wdir(buff);
  cout << "Current dir: " << endl;
  cout << blu_f + wdir + res " |" << endl;
  for (int i = 0; i < (int) wdir.length() + 1; i++)
    cout << '_';
  cout << '|' << endl;
  cout << "Enter location of files " yel_f
          "(Press RETURN to use default location )" res
       << endl
       << blu_f;
  string str = "";
  getline(cin, str);
  while (1) {
    cout << res << "\033[2J\033[H";
    cout << yel_f "Choose file type" res << endl;
    cout << cya_f "[1] CSV" res << endl;
    cout << cya_f "[2] XML" res << endl;
    cout << cya_f "[3] SQL" res << endl;
    cout << cya_f "[4] EXIT ( not exactly a file type lol)" res << endl;
    do {
      key = getch();
    } while (49 > key || 52 < key);
    cout << "\033[2J\033[H";
    if (key == 49) {
      if (str == "") str.append("../../data/csv/");
      CsvStorage st {str};
      Storage* fs = &st;
      Cui cui {fs};
      cui.show();
    } else if (key == 50) {
      if (str == "") str.append("../../data/xml/");
      XmlStorage st {str};
      Storage* fs = &st;
      Cui cui {fs};
      cui.show();
    } else if (key == 51) {
      if (str == "") str.append("../../data/sqlite/");
      SqliteStorage st {str};
      Storage* fs = &st;
      Cui cui {fs};
      cui.show();
    } else {
      cout << "\033[2J\033[H";
      for (int i = 5; i > 0; --i) {
        cout << "\033[H" + string {"Exit on " + to_string(i) + "s"} << endl;
        sleep(1);
      }
      cout << "\033[2J\033[H";
      exit(0);
    }
  }
}

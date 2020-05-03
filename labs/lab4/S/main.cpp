#include "cui.hpp"

#include <string>
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef __unix__
#  include <unistd.h>
#  define GetCurrentDir getcwd
#elif defined(_WIN32) || defined(WIN32)
#  include <direct.h>
#  define GetCurrentDir _getcwd
#endif

#include<iostream>


using namespace std;
auto main() -> int {
  char buff[FILENAME_MAX];
  getcwd( buff, FILENAME_MAX );
  string wdir(buff);
  cout << "Current dir: " << endl;
  cout << blu_f + wdir + res " |" << endl;
  for (int i = 0; i < (int)wdir.length() + 1; i++) cout << '_';
  cout << '|' << endl;
  cout << "Enter location of files " yel_f "(Press RETURN to use ../data/ )" res << endl << blu_f;
  string str = "";
  getline(cin, str);
  cout << res;
  if (str == "") str.append("../data/");
  cout << cont << endl;
  getch();
  system("clear");
  FileStorage fs {str};
  Cui cui{&fs};
  cui.show();
}

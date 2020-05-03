#include "cui.h"

#include <string>
#include <vector>
using namespace std;
int main() {
  cout << "Please, enter name of directory" << endl;
  string str;
  cin >> str;
  FileStorage fs {str};
  Cui cui {&fs};
  cui.show();
}
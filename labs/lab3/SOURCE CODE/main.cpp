//
// Created by xon on 3/24/20.
//

#include "BsTree.h"
#include "Organisation.h"
#include "csv.h"
#include "list.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>
using namespace std;

StringTable processEntities(List<Organisation>& list, Organisation n);
void PrintList(List<Organisation>& list);
StringTable Table_fromFile(char* file_name);
void File_fromTable(StringTable& table, char* file_name);
List<Organisation> createEntityListFromTable(StringTable& csvTable);

int main(int argc, char* argv[]) {
  char* in = nullptr;
  char* out = nullptr;
  char* n = nullptr;
  size_t b = 0, c;
  bool isN = 0;

  // reading operands
  while ((c = getopt(argc, argv, "i:o:n:b")) != -1) {
    switch (c) {
      case 'i': in = optarg; break;
      case 'o': out = optarg; break;
      case 'n':
        n = optarg;
        isN = 1;
        break;
      case 'b': b = 1; break;
    }
  }
  // reading operands, that not assigned with '-' key
  for (size_t index = optind; index < argc; index++) {
    if (!in) {
      in = argv[index];
    } else if (!out) {
      out = argv[index];
    } else if (!n) {
      n = argv[index];
      isN = 1;
    }
  }
  // Check required files
  if (!in) {
    fprintf(stderr, " missing input file\n");
    exit(2);
  } else if (!out) {
    fprintf(stderr, " missing output file\n");
    exit(2);
  } else if (!n) {
    n = "";
  }
  // TABLE > FILE
  StringTable table = Table_fromFile(in);
  // COUT < TABLE
  table.print();
  // TABLE > LISTS
  List list = createEntityListFromTable(table);
  List list2 = createEntityListFromTable(table);
  // COUT < LIST
  PrintList(list);
  BSTree myTree {};
  if (b) {
    for (int i = 0; i < list.size(); i++) {
      // TREE < LIST
      myTree.insert(list[i]);
    }
    // COUT < TREE
    myTree.print();
  }
  Organisation org;
  org.country = n;
  // LIST = N || TABLE < LIST
  StringTable table2 = processEntities(list, org);
  if (isN) {
    // COUT < LIST
    PrintList(list);
    if (b) {
      for (int i = 0; i < list2.size(); i++) {
        // TREE = N
        if (!list.contains(list2[i])) { myTree.remove(list2[i].id); }
      }
      // COUT < TREE
      myTree.print();
    }
    // COUT < TABLE
    table2.print();
  }
  // CLEAR TREE
  myTree.clear();
  // OUT <<<<<<<
  if (!isN) {
    File_fromTable(table, out);
    return 0;
  }
  File_fromTable(table2, out);
}

StringTable Table_fromFile(char* file_name) {
  ifstream file(file_name);
  if (!file.is_open()) {
    perror("\033[;;41mCAN'T OPEN FILE\033[0m\n");
    exit(EXIT_FAILURE);
  }
  string from_file, temp;
  while (getline(file, temp)) {
    from_file += temp + "\n";
  }
  file.close();
  if (file.is_open()) {
    perror("\033[;;41mCAN'T CLOSE FILE\033[0m\n");
    exit(EXIT_FAILURE);
  }
  return Csv_parse(from_file);
}
void File_fromTable(StringTable& table, char* file_name) {
  ofstream file(file_name);
  if (!file.is_open()) {
    perror("\033[;;41mCAN'T OPEN FILE\033[0m\n");
    exit(EXIT_FAILURE);
  }
  string out = Csv_toString(table);
  file << out << endl;
  file.close();
  if (file.is_open()) {
    perror("\033[;;41mCAN'T CLOSE FILE\033[0m\n");
    exit(EXIT_FAILURE);
  }
}
int checknum(string str) {
  if (isdigit(str[0]))
    return stoi(str);
  else
    cout << "\nDate is not num\n";
  exit(1);
}

List<Organisation> createEntityListFromTable(StringTable& table) {
  List<Organisation> list;
  Organisation org;
  for (size_t i = 1; i < table.size_rows(); i++) {
    int col = -1;
    org.id = checknum(table.at(i, ++col));
    org.country = table.at(i, ++col);
    org.label = table.at(i, ++col);
    org.type = table.at(i, ++col);
    org.founded_date = checknum(table.at(i, ++col));
    org.founders = table.at(i, ++col);
    list.push_back(org);
  }
  return list;
}
void PrintList(List<Organisation>& list) {
  cout << left << setw(4) << "id";
  cout << left << setw(9) << "Country";
  cout << left << setw(23) << "Label";
  cout << left << setw(23) << "Type";
  cout << left << setw(9) << "Founded";
  cout << left << setw(23) << "Founders";
  cout << endl;
  for (int i = 0; i < list.size(); i++) {
    cout << left << setw(4) << list[i].id;
    cout << left << setw(9) << list[i].country;
    cout << left << setw(23) << list[i].label;
    cout << left << setw(25) << list[i].type;
    cout << left << setw(9) << list[i].founded_date;
    cout << left << setw(44) << list[i].founders;
    cout << endl;
  }
}
StringTable processEntities(List<Organisation>& list, Organisation n) {
  for (int i = list.size() - 1; i >= 0; i--)
    if (list[i].country != n.country) list.remove_at(i);
  StringTable table(list.size() + 1, 6);
  for (int i = 0; i < list.size(); i++) {
    int col = -1;
    table.at(i + 1, ++col) = to_string(list[i].id);
    table.at(i + 1, ++col) = list[i].country;
    table.at(i + 1, ++col) = list[i].label;
    table.at(i + 1, ++col) = list[i].type;
    table.at(i + 1, ++col) = to_string(list[i].founded_date);
    table.at(i + 1, ++col) = list[i].founders;
  }
  int col = -1;
  table.at(0, ++col) = "id";
  table.at(0, ++col) = "country";
  table.at(0, ++col) = "label";
  table.at(0, ++col) = "type";
  table.at(0, ++col) = "founded_date";
  table.at(0, ++col) = "founders";
  return table;
}

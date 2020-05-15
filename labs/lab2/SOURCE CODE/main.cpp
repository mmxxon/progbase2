//#include <unistd.h> //sleep|usleep
//#include <iomanip> //formatted output
#include "../HEADERS/csv.h"
#include "../HEADERS/dynamic_array.h"
#include "../HEADERS/fs.h"
#include "../HEADERS/list.h"
#include "../HEADERS/string_table.h"

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

List createEntityListFromTable(StringTable& csvTable);
StringTable processEntities(List& items,
                            Organisation n);    // T depends on your variant

int main(int argc, char* argv[]) {
  Check_CountOfArgs(argc, 3);
  string csv_file = argv[1];
  string out_file = argv[2];
  StringTable table = Table_fromFile(csv_file);
  table.print();
  List list = createEntityListFromTable(table);
  list.print();
  string input;
  cout << "Input country to filter: " << endl;
  cin >> input;
  Organisation org;
  org.country = input;
  StringTable table2 = processEntities(list, org);
  list.print();
  File_fromTable(table2, out_file);
  cout << "Writed to file successfully" << endl;
}

int checknum(string str) {
  if (isdigit(str[0]))
    return stoi(str);
  else
    cout << "\nDate is not num\n";
  exit(1);
}
List createEntityListFromTable(StringTable& table) {
  List list;
  Organisation org;
  for (int i = 1; i < table.size_rows(); i++) {
    org.country = table.at(i, 0);
    org.label = table.at(i, 1);
    org.type = table.at(i, 2);
    org.founders = table.at(i, 3);
    org.founded_date = checknum(table.at(i, 4));
    org.NASDAQ = table.at(i, 5);
    list.push_back(org);
  }
  return list;
}

StringTable processEntities(List& items, Organisation n) {
  for (int i = items.size() - 1; i >= 0; i--)
    if (items[i].country != n.country) items.remove_at(i);
  StringTable table(items.size() + 1, 6);
  for (size_t i = 0; i < items.size(); i++) {
    table.at(i + 1, 0) = items[i].country;
    table.at(i + 1, 1) = items[i].label;
    table.at(i + 1, 2) = items[i].type;
    table.at(i + 1, 3) = items[i].founders;
    table.at(i + 1, 4) = to_string(items[i].founded_date);
    table.at(i + 1, 5) = items[i].NASDAQ;
  }
  table.at(0, 0) = "country";
  table.at(0, 1) = "label";
  table.at(0, 2) = "type";
  table.at(0, 3) = "founders";
  table.at(0, 4) = "founded_date";
  table.at(0, 5) = "NASDAQ";
  return table;
}

#include "csvstorage.hpp"

static vector<Organisation> tableToOrg(StringTable& table) {
  vector<Organisation> orgs;
  for (int i = 1; i < (int) table.size_rows(); i++) {
    int row = -1;
    Organisation org;
    org.id = atoi(table.at(i, ++row).c_str());
    org.country = table.at(i, ++row);
    org.label = table.at(i, ++row);
    org.founders = table.at(i, ++row);
    orgs.push_back(org);
  }
  return orgs;
}
static StringTable OrgToTable(vector<Organisation> orgs) {
  StringTable table {orgs.size() + 1, 4};
  table.at(0, 0) = "id";
  table.at(0, 1) = "country";
  table.at(0, 2) = "label";
  table.at(0, 3) = "founder(s)";
  for (int i = 0; i < (int) orgs.size(); i++) {
    int row = -1;
    table.at(1 + i, ++row) = to_string(orgs[i].id);
    table.at(1 + i, ++row) = orgs[i].country;
    table.at(1 + i, ++row) = orgs[i].label;
    table.at(1 + i, ++row) = orgs[i].founders;
  }
  return table;
}

vector<Organisation> CsvStorage::loadOrgs() {
  if (!open()) {
    fprintf(stderr, "Error on opening");
    exit(1);
  }
  string s, temp;
  while (getline(orgs_file_, temp)) {
    s.append(temp + "\n");
  }
  close();
  StringTable table = Csv_parse(s);
  return tableToOrg(table);
}
void CsvStorage::saveOrgs(const vector<Organisation>& orgs) {
  StringTable table = OrgToTable(orgs);
  string str = Csv_toString(table);
  if (!open()) {
    fprintf(stderr, "Error on opening");
    exit(1);
  }
  close();
  orgs_file_.open(name(), ios::out);
  orgs_file_ << str;
  close();
}
int CsvStorage::getNewOrgId() {
  fstream id;
  int tmp = 0;
  vector<Organisation> orgs = getAllOrgs();
  for (auto& i: orgs) {
    if (i.id >= tmp) tmp = i.id + 1;
  }
  return tmp;
}

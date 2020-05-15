#include "storage.hpp"

#include "csv.hpp"

#include <string>

using namespace std;

FileStorage::FileStorage(const string& dir_name) { dir_name_ = dir_name; }
string FileStorage::name() const { return dir_name_; }
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
bool FileStorage::open() {
  orgs_file_.open(name() + "orgs.csv");
  return isOpen();
}
void FileStorage::close() { orgs_file_.close(); }

bool FileStorage::isOpen() const {
  if (orgs_file_.is_open()) return 1;
  return 0;
}
void FileStorage::setName(const string& dir_name) { dir_name_ = dir_name; }

vector<Organisation> FileStorage::loadOrgs() {
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
void FileStorage::saveOrgs(const vector<Organisation>& orgs) {
  StringTable table = OrgToTable(orgs);
  string str = Csv_toString(table);
  if (!open()) {
    fprintf(stderr, "Error on opening");
    exit(1);
  }
  close();
  orgs_file_.open(name() + "orgs.csv", ios::out);
  orgs_file_ << str;
  close();
}
vector<Organisation> FileStorage::getAllOrgs() { return loadOrgs(); }
optional<Organisation> FileStorage::getOrgById(int org_id) {
  vector<Organisation> orgs = loadOrgs();
  for (auto o: orgs) {
    if (o.id == org_id) return o;
  }
  return nullopt;
}
bool FileStorage::updateOrg(const Organisation& org) {
  vector<Organisation> orgs = loadOrgs();
  for (auto& o: orgs) {
    if (o.id == org.id) {
      o = org;
      saveOrgs(orgs);
      return 1;
    }
  }
  return 0;
}
bool FileStorage::removeOrg(int org_id) {
  vector<Organisation> orgs = loadOrgs();
  auto bit = orgs.begin();
  auto eit = orgs.end();
  for (; bit != eit; bit++) {
    if ((*bit).id == org_id) {
      orgs.erase(bit);
      saveOrgs(orgs);
      return 1;
    }
  }
  return 0;
}
int FileStorage::insertOrg(const Organisation& org) {
  int id = getNewOrgId();
  Organisation norg = org;
  norg.id = id;
  vector<Organisation> orgs = loadOrgs();
  orgs.push_back(norg);
  saveOrgs(orgs);
  return id;
}
int FileStorage::getNewOrgId() {
  fstream id;
  int tmp = 0;
  id.open(dir_name_ + "orgs_id", ios::in);
  if (!id.is_open()) {
    cout << "Id file cannot be opened" << endl;
    cout << "Getting new id from items" << endl;
    vector<Organisation> orgs = getAllOrgs();
    for (auto& i: orgs) {
      if (i.id >= tmp) tmp = i.id + 1;
    }
  } else {
    id >> tmp;
    id.close();
    id.open(dir_name_ + "orgs_id", ios::out);
    id << ++tmp;
    id.close();
  }
  return tmp;
}

#include "filestorage.hpp"

#include <csvlab.hpp>
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
static vector<Founder> tableToFndr(StringTable& table) {
  vector<Founder> fndrs;
  for (int i = 1; i < (int) table.size_rows(); i++) {
    int row = -1;
    Founder fndr;
    fndr.id = atoi(table.at(i, ++row).c_str());
    fndr.name = table.at(i, ++row);
    fndr.age = atoi(table.at(i, ++row).c_str());
    fndr.wealth = table.at(i, ++row);
    fndrs.push_back(fndr);
  }
  return fndrs;
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
static StringTable FndrToTable(vector<Founder> fndrs) {
  StringTable table {fndrs.size() + 1, 4};
  table.at(0, 0) = "id";
  table.at(0, 1) = "name";
  table.at(0, 2) = "age";
  table.at(0, 3) = "wealth";
  for (int i = 0; i < (int) fndrs.size(); i++) {
    int row = -1;
    table.at(1 + i, ++row) = to_string(fndrs[i].id);
    table.at(1 + i, ++row) = fndrs[i].name;
    table.at(1 + i, ++row) = to_string(fndrs[i].age);
    table.at(1 + i, ++row) = fndrs[i].wealth;
  }
  return table;
}

bool FileStorage::open() {
  orgs_file_.open(name() + "orgs.csv");
  fndrs_file_.open(name() + "fndrs.csv");
  return isOpen();
}
void FileStorage::close() {
  orgs_file_.close();
  fndrs_file_.close();
}

bool FileStorage::isOpen() const {
  if (orgs_file_.is_open() && fndrs_file_.is_open()) { return 1; }
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

vector<Founder> FileStorage::loadFndr() {
  if (!open()) {
    fprintf(stderr, "Error on opening");
    exit(1);
  }
  string s, temp;
  while (getline(fndrs_file_, temp)) {
    s.append(temp + "\n");
  }
  close();
  StringTable table = Csv_parse(s);
  return tableToFndr(table);
}
void FileStorage::saveFndrs(const vector<Founder>& fndr) {
  StringTable table = FndrToTable(fndr);
  string str = Csv_toString(table);
  if (!open()) {
    fprintf(stderr, "Error on opening");
    exit(1);
  }
  close();
  fndrs_file_.open(name() + "fndrs.csv", ios::out);
  fndrs_file_ << str;
  close();
}
vector<Founder> FileStorage::getAllFndrs() { return loadFndr(); }
optional<Founder> FileStorage::getFndrById(int fndr_id) {
  vector<Founder> fndrs = loadFndr();
  for (auto f: fndrs) {
    if (f.id == fndr_id) return f;
  }
  return nullopt;
}
bool FileStorage::updateFndr(const Founder& fndr) {
  vector<Founder> fndrs = loadFndr();
  for (auto& f: fndrs) {
    if (f.id == fndr.id) {
      f = fndr;
      saveFndrs(fndrs);
      return 1;
    }
  }
  return 0;
}
bool FileStorage::removeFndr(int fndr_id) {
  vector<Founder> fndrs = loadFndr();
  auto bit = fndrs.begin();
  auto eit = fndrs.end();
  for (; bit != eit; bit++) {
    if ((*bit).id == fndr_id) {
      fndrs.erase(bit);
      saveFndrs(fndrs);
      return 1;
    }
  }
  return 0;
}
int FileStorage::insertFndr(const Founder& fndr) {
  int id = getNewFndrId();
  Founder nfndr = fndr;
  nfndr.id = id;
  vector<Founder> fndrs = loadFndr();
  fndrs.push_back(nfndr);
  saveFndrs(fndrs);
  return id;
}
int FileStorage::getNewFndrId() {
  fstream id;
  int tmp = 0;
  id.open(dir_name_ + "fndrs_id", ios::in | ios::out);
  if (!id.is_open()) {
    cout << "Id file cannot be opened" << endl;
    cout << "Getting new id from items" << endl;
    vector<Founder> fndrs = getAllFndrs();
    for (auto& i: fndrs) {
      if (i.id >= tmp) tmp = i.id + 1;
    }
  } else {
    id >> tmp;
    id << ++tmp;
    id.close();
  }
  return tmp;
}

#include "storage.h"
static vector<Organisation> createEntityList(StringTable& table) {
  vector<Organisation> l;
  for (int i = 1; i < table.size_rows(); i++) {
    Organisation t;
    t.id = atoi(table.at(i, 0).c_str());
    t.country = table.at(i, 1);
    t.label = table.at(i, 2);
    t.type = table.at(i, 3);
    t.founded_date = atoi(table.at(i, 4).c_str());
    t.founders = table.at(i, 5);
    l.push_back(t);
  }
  return l;
}
vector<Organisation> FileStorage::loadOrgs() {
  open();
  if (!isOpen()) {
    fprintf(stderr, "ERROR");
    exit(1);
  }
  string str, buff;
  while (getline(orgs_file_, buff)) {
    str += buff + "\n";
  }
  close();
  StringTable csv = Csv_parse(str);
  vector<Organisation> items = createEntityList(csv);
  return items;
}
static StringTable createTable(vector<Organisation>& ls) {
  StringTable str {ls.size() + 1, 6};
  str.at(0, 0) = "id";
  str.at(0, 1) = "country";
  str.at(0, 2) = "label";
  str.at(0, 3) = "type";
  str.at(0, 4) = "founded";
  str.at(0, 5) = "founders";
  for (size_t i = 0; i < ls.size(); i++) {
    str.at(i + 1, 0) = to_string(ls[i].id);
    str.at(i + 1, 1) = ls[i].country;
    str.at(i + 1, 2) = ls[i].label;
    str.at(i + 1, 3) = ls[i].type;
    str.at(i + 1, 4) = to_string(ls[i].founded_date);
    str.at(1 + i, 5) = ls[i].founders;
  }
  return str;
}
void FileStorage::saveOrgs(const vector<Organisation> & orgs) {
  open();
  if (!isOpen()) {
    fprintf(stderr, "ERROR");
    exit(1);
  }
  vector<Organisation> cp = orgs;
  StringTable out = createTable(cp);
  string strout = Csv_toString(out);
  orgs_file_ << strout;
  close();
}
int FileStorage::getNewOrgsId() {
  int max = 0;
  for (Organisation& st: loadOrgs()) {
    if (st.id > max) { max = st.id; }
  }
  return max + 1;
}
FileStorage::FileStorage(const string& dir_name) { dir_name_ = dir_name; }
void FileStorage::setName(const string& dir_name) { dir_name_ = dir_name; }
string FileStorage::name() const { return dir_name_; }

bool FileStorage::isOpen() const { return orgs_file_.is_open(); }

bool FileStorage::open() {
  orgs_file_.open(dir_name_ + "data.csv");
  return orgs_file_.is_open();
}

void FileStorage::close() { orgs_file_.close(); }

vector<Organisation> FileStorage::getAllOrgs(void) { return loadOrgs(); }

optional<Organisation> FileStorage::getOrgsById(int orgs_id) {

  for (auto& st: loadOrgs()) {
    if (st.id == orgs_id) { return optional<Organisation> {st}; }
  }
  return nullopt;
}
bool FileStorage::updateOrgs(const Organisation& orgs) {
  vector<Organisation> pt = loadOrgs();
  for (int i = 0; i < pt.size(); i++) {
    if (pt[i].id == orgs.id) {
      pt[i].country = orgs.country;
      pt[i].label = orgs.label;
      pt[i].type = orgs.type;
      pt[i].founded_date = orgs.founded_date;
      pt[i].founders = orgs.founders;
      saveOrgs(pt);
      return true;
    }
  }
  return false;
}
bool FileStorage::removeOrgs(int orgs_id) {
  vector<Organisation> pt = loadOrgs();
  auto it = pt.begin();
  auto it_end = pt.end();
  for (; it != it_end; ++it) {
    if ((*it).id == orgs_id) {
      pt.erase(it);
      saveOrgs(pt);
      return true;
    }
  }
  return false;
}

int FileStorage::insertOrgs(const Organisation& orgs) {
  int new_id = this->getNewOrgsId();
  Organisation copy = orgs;
  copy.id = new_id;
  vector<Organisation> pt = loadOrgs();
  pt.push_back(copy);
  saveOrgs(pt);
  return new_id;
}

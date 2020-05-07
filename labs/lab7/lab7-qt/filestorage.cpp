#include "filestorage.hpp"

using namespace std;

FileStorage::FileStorage(const string& name) { name_ = name; }
string FileStorage::name() const { return name_; }

bool FileStorage::open() {
  if (filesystem::exists(name_)) {
    orgs_file_.open(name_);
  } else {
    orgs_file_.open(name_, ios::out);
    orgs_file_.close();
    orgs_file_.open(name_);
  }
  return isOpen();
}
void FileStorage::close() { orgs_file_.close(); }

bool FileStorage::isOpen() const { return orgs_file_.is_open(); }
void FileStorage::setName(const string& name) { name_ = name; }

vector<Organisation> FileStorage::getAllOrgs() { return loadOrgs(); }
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

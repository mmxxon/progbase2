#ifndef CSVSTORAGE_HPP
#define CSVSTORAGE_HPP

#include "csvlab.hpp"
#include "filestorage.hpp"

class CsvStorage: public FileStorage {
  vector<Organisation> loadOrgs();
  void saveOrgs(const vector<Organisation>& orgs);
  int getNewOrgId();

public:
  explicit CsvStorage(const string& name_ = ""): FileStorage(name_) {}
};

#endif    // CSVSTORAGE_HPP

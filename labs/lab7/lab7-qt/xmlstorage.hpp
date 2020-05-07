#ifndef XMLSTORAGE_HPP
#define XMLSTORAGE_HPP

#include "filestorage.hpp"

class XmlStorage: public FileStorage {
  vector<Organisation> loadOrgs();
  void saveOrgs(const vector<Organisation>& orgs);
  int getNewOrgId();

public:
  explicit XmlStorage(const string& name_ = ""): FileStorage(name_) {}
};

#endif    // XMLSTORAGE_HPP

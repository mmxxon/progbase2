#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "organisation.hpp"
#include "string_table.hpp"

#include <fstream>
#include <optional>
#include <vector>
#include <filesystem>
#include <QFile>

using namespace std;

class FileStorage {
  string name_;

protected:
  fstream orgs_file_;

  virtual vector<Organisation> loadOrgs() = 0;
  virtual void saveOrgs(const vector<Organisation>& orgs) = 0;
  virtual int getNewOrgId() = 0;

public:
  explicit FileStorage(const string& dir_name = "");
  virtual ~FileStorage() {}

  void setName(const string& dir_name);
  string name() const;
  bool isOpen() const;
  bool open();
  void close();

  vector<Organisation> getAllOrgs();
  bool updateOrg(const Organisation& org);
  bool removeOrg(int org_id);
  int insertOrg(const Organisation& org);
};

#endif    // FILESTORAGE_H

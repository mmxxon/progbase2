#ifndef STORAGE_H
#define STORAGE_H

#include "organisation.hpp"
#include "string_table.hpp"

#include <fstream>
#include <optional>
#include <string>
#include <vector>

using namespace std;

class FileStorage {
  string dir_name_;

  fstream orgs_file_;
  fstream fndrs_file_;

  vector<Organisation> loadOrgs();
  void saveOrgs(const vector<Organisation>& orgs);
  int getNewOrgId();

public:
  explicit FileStorage(const string& dir_name = "");

  void setName(const string& dir_name);
  string name() const;

  bool isOpen() const;
  bool open();
  void close();

  vector<Organisation> getAllOrgs();
  optional<Organisation> getOrgById(int org_id);
  bool updateOrg(const Organisation& org);
  bool removeOrg(int org_id);
  int insertOrg(const Organisation& org);
};

#endif    // STORAGE_H

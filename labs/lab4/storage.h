#pragma once
#include "csv.h"
#include "organisation.h"

#include <experimental/optional>
#include <fstream>
#include <vector>

using namespace experimental;
using namespace std;

class FileStorage {
  string dir_name_;

  fstream orgs_file_;

  // int max();
  vector<Organisation> loadOrgs();
  void saveOrgs(const vector<Organisation>& orgs);
  int getNewOrgsId();

public:
  explicit FileStorage(const string& dir_name = "");

  void setName(const string& dir_name);
  string name() const;

  bool isOpen() const;
  bool open();
  void close();

  vector<Organisation> getAllOrgs(void);
  optional<Organisation> getOrgsById(int orgs_id);
  bool updateOrgs(const Organisation& orgs);
  bool removeOrgs(int orgs_id);
  int insertOrgs(const Organisation& orgs);
};
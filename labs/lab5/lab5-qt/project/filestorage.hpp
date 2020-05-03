#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "founder.hpp"
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

  // students
  vector<Organisation> loadOrgs();
  void saveOrgs(const vector<Organisation>& orgs);
  int getNewOrgId();

  // courses
  vector<Founder> loadFndr();
  void saveFndrs(const vector<Founder>& fndrs);
  int getNewFndrId();

public:
  explicit FileStorage(const string& dir_name = "");

  void setName(const string& dir_name);
  string name() const;

  bool isOpen() const;
  bool open();
  void close();

  // students
  vector<Organisation> getAllOrgs();
  optional<Organisation> getOrgById(int org_id);
  bool updateOrg(const Organisation& org);
  bool removeOrg(int org_id);
  int insertOrg(const Organisation& org);

  // courses
  vector<Founder> getAllFndrs(void);
  optional<Founder> getFndrById(int fndr_id);
  bool updateFndr(const Founder& fndr);
  bool removeFndr(int fndr_id);
  int insertFndr(const Founder& fndr);
};

#endif    // FILESTORAGE_H

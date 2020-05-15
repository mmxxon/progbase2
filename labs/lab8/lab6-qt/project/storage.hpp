#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "founder.hpp"
#include "organisation.hpp"

#include <optional>
#include <string>
#include <vector>

using namespace std;

class Storage {
private:
  string dir_name_;

public:
  Storage();
  explicit Storage(const string& dir_name);
  virtual ~Storage() {}

  void setName(const string& dir_name);
  string name() const;

  virtual bool isOpen() const = 0;
  virtual bool open() = 0;
  virtual void close() = 0;

  virtual vector<Organisation> getAllOrgs(void) = 0;
  virtual optional<Organisation> getOrgById(int org_id) = 0;
  virtual bool updateOrg(const Organisation& org) = 0;
  virtual bool removeOrg(int org_id) = 0;
  virtual int insertOrg(const Organisation& org) = 0;

  // fndrs
  virtual vector<Founder> getAllFndrs(void) = 0;
  virtual optional<Founder> getFndrById(int fndr_id) = 0;
  virtual bool updateFndr(const Founder& fndr) = 0;
  virtual bool removeFndr(int fndr_id) = 0;
  virtual int insertFndr(const Founder& fndr) = 0;
};

#endif    // STORAGE_HPP

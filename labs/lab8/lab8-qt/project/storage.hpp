#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <QtDebug>
#include <vector>

#include <stdio.h>
#include <string>
#include <optional>
#include "organisation.hpp"
#include "founder.hpp"
#include <iomanip>
#include <termios.h>
#ifdef __unix__
#include <unistd.h>
#define GetCurrentDir getcwd
#elif defined(_WIN32) || defined(WIN32)
#include <direct.h>
#define GetCurrentDir _getcwd
#endif
#include <iostream>

using namespace std;

class Storage
{
private:
  string dir_name_;

public:
  Storage();
  explicit Storage(const string&);

  void setName(const string&);
  string name() const;

  virtual bool isOpen() const = 0;
  virtual bool open(string) = 0;
  virtual void close() = 0;

  // orgs
  virtual vector<Organisation> getAllOrgs() = 0;
  virtual optional<Organisation> getOrgById(int) = 0;
  virtual bool updateOrg(const Organisation&) = 0;
  virtual bool removeOrg(int) = 0;
  virtual int insertOrg(const Organisation&) = 0;

  // courses
  virtual vector<Founder> getAllFndrs() = 0;
  virtual optional<Founder> getFndrById(int) = 0;
  virtual bool updateFndr(const Founder&) = 0;
  virtual bool removeFndr(int) = 0;
  virtual int insertFndr(const Founder&) = 0;
};


#endif // STORAGE_HPP

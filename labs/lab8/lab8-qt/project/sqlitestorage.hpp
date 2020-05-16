#ifndef SQLITESTORAGE_HPP
#define SQLITESTORAGE_HPP

#include "storage.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>

using namespace std;

class SqliteStorage: public Storage {
  const string dir_name_;

protected:
  QSqlDatabase database_;

public:
  SqliteStorage(const string& dir_name_);
  bool isOpen() const;
  bool open(string = ".sqlite");
  void close();

  // orgs
  vector<Organisation> getAllOrgs(void);
  optional<Organisation> getOrgById(int id);
  bool updateOrg(const Organisation& org);
  bool removeOrg(int id);
  int insertOrg(const Organisation& org);

  // fndrs
  vector<Founder> getAllFndrs();
  optional<Founder> getFndrById(int id);
  bool updateFndr(const Founder& fndr);
  bool removeFndr(int id);
  int insertFndr(const Founder& fndr);
};

#endif    // SQLITESTORAGE_HPP

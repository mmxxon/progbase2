#ifndef SQLITESTORAGE_HPP
#define SQLITESTORAGE_HPP

#include <string>
#include <vector>
#include <QSqlDatabase>

#include <optional>
#include "organisation.hpp"
#include "founder.hpp"
#include "storage.hpp"

using namespace std;

class SqliteStorage : public Storage
{
 protected:
   QSqlDatabase database_;

 public:
   SqliteStorage(const string & dir_name) : Storage(dir_name) {}

   bool isOpen() const;
   bool open();
   void close();

   // orgs
   vector<Organisation> getAllOrgs(void);
   optional<Organisation> getOrgById(int org_id);
   bool updateOrg(const Organisation &org);
   bool removeOrg(int org_id);
   int insertOrg(const Organisation &org);

   // fndrs
   vector<Founder> getAllFndrs(void);
   optional<Founder> getFndrById(int fndr_id);
   bool updateFndr(const Founder &fndr);
   bool removeFndr(int fndr_id);
   int insertFndr(const Founder &fndr);
};

#endif // SQLITESTORAGE_HPP

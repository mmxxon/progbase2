#include "sqlitestorage.hpp"
SqliteStorage::SqliteStorage(const string& dir_name): Storage(dir_name) {
  database_ = QSqlDatabase::addDatabase("QSQLITE");
}
Organisation orgFrom(const QSqlQuery& q) {
  Organisation org;
  org.id = q.value("id").toInt();
  org.country = q.value("country").toString().toStdString();
  org.label = q.value("label").toString().toStdString();
  org.founders = q.value("founders").toString().toStdString();
  return org;
}
Founder fndrFrom(const QSqlQuery& q) {
  Founder fndr;
  fndr.id = q.value("id").toInt();
  fndr.name = q.value("name").toString().toStdString();
  fndr.age = q.value("age").toInt();
  fndr.wealth = q.value("wealth").toString().toStdString();
  return fndr;
}

bool SqliteStorage::isOpen() const { return database_.isOpen(); }
bool SqliteStorage::open(string type) {
  QString path = QString::fromStdString(name() + "/data" + type);
  database_.setDatabaseName(path);
  return database_.open();
}
void SqliteStorage::close() { database_.close(); }

vector<Organisation> SqliteStorage::getAllOrgs() {
  vector<Organisation> orgs;
  this->open();
  QSqlQuery q("SELECT * FROM orgs");
  while (q.next())
    orgs.push_back(orgFrom(q));
  this->close();
  return orgs;
}
optional<Organisation> SqliteStorage::getOrgById(int id) {
  QSqlQuery q;
  this->open();
  open(".sqlite");
  if (!q.prepare("SELECT * FROM orgs WHERE id = :id")) return nullopt;
  q.bindValue(":id", id);
  if (!q.exec() || !q.next()) {
    this->close();
    return nullopt;
  } else {
    Organisation org = orgFrom(q);
    this->close();
    return org;
  }
}
bool SqliteStorage::updateOrg(const Organisation& org) {
  QSqlQuery q;
  this->open();
  q.prepare(
    "UPDATE orgs SET country = :country, label = :label, founders = :founders "
    "WHERE id = :id");
  q.bindValue(":country", QString::fromStdString(org.country));
  q.bindValue(":label", QString::fromStdString(org.label));
  q.bindValue(":founders", QString::fromStdString(org.founders));
  q.bindValue(":id", org.id);
  if (!q.exec() || !q.next()) {
    this->close();
    return false;
  } else {
    this->close();
    return true;
  }
}
bool SqliteStorage::removeOrg(int id) {
  QSqlQuery q;
  this->open();
  q.prepare("DELETE FROM orgs WHERE id = :id");
  q.bindValue(":id", id);
  if (!q.exec() || q.numRowsAffected() == 0) {
    this->close();
    return false;
  } else {
    this->close();
    return true;
  }
}
int SqliteStorage::insertOrg(const Organisation& org) {
  QSqlQuery q;
  this->open();
  q.prepare(
    "INSERT INTO orgs (country, label, founders) VALUES (:country, :label, "
    ":founders)");
  q.bindValue(":country", QString::fromStdString(org.country));
  q.bindValue(":label", QString::fromStdString(org.label));
  q.bindValue(":founders", QString::fromStdString(org.founders));
  if (!q.exec()) {
    this->close();
    return 0;
  } else {
    int id = q.lastInsertId().toInt();
    this->close();
    return id;
  }
}

// fndrs
vector<Founder> SqliteStorage::getAllFndrs() {
  this->open();
  vector<Founder> fndrs;
  QSqlQuery q("SELECT * FROM founders");
  while (q.next())
    fndrs.push_back(fndrFrom(q));
  this->close();
  return fndrs;
}
optional<Founder> SqliteStorage::getFndrById(int id) {
  QSqlQuery q;
  this->open();
  q.prepare("SELECT * FROM founders WHERE id = :id");
  q.bindValue(":id", id);
  if (!q.exec() || !q.next()) {
    this->close();
    return nullopt;
  } else {
    Founder fndr = fndrFrom(q);
    this->close();
    return fndr;
  }
}
bool SqliteStorage::updateFndr(const Founder& fndr) {
  QSqlQuery q;
  this->open();
  q.prepare(
    "UPDATE founders SET name = :name, age = :age, wealth = :wealth WHERE id = "
    ":id");
  q.bindValue(":name", QString::fromStdString(fndr.name));
  q.bindValue(":age", fndr.age);
  q.bindValue(":wealth", QString::fromStdString(fndr.wealth));
  q.bindValue(":id", fndr.id);
  if (!q.exec() || q.numRowsAffected() == 0) {
    this->close();
    return false;
  } else {
    this->close();
    return true;
  }
}
bool SqliteStorage::removeFndr(int id) {
  QSqlQuery q;
  this->open();
  q.prepare("DELETE FROM founders WHERE id = :id");
  q.bindValue(":id", id);
  if (!q.exec() || q.numRowsAffected() == 0) {
    this->close();
    return false;
  } else {
    this->close();
    return true;
  }
}
int SqliteStorage::insertFndr(const Founder& fndr) {
  QSqlQuery q;
  this->open();
  q.prepare(
    "INSERT INTO founders SET (name, age, wealth) VALUES (:name, :age, "
    ":wealth)");
  q.bindValue(":name", QString::fromStdString(fndr.name));
  q.bindValue(":age", fndr.age);
  q.bindValue(":wealth", QString::fromStdString(fndr.wealth));
  if (!q.exec()) {
    this->close();
    return 0;
  } else {
    int id = q.lastInsertId().toInt();
    this->close();
    return id;
  }
}

#include "xmlstorage.hpp"

#include <QtDebug>
#include <QtXml>

static QDomElement orgXml(QDomDocument& doc, const Organisation& org) {
  QDomElement elOrg = doc.createElement("orgs");
  elOrg.setAttribute("id", org.id);
  elOrg.setAttribute("country", QString::fromStdString(org.country));
  elOrg.setAttribute("label", QString::fromStdString(org.label));
  elOrg.setAttribute("founders", QString::fromStdString(org.founders));
  return elOrg;
}

static Organisation xmlOrg(QDomElement& elOrg) {
  Organisation org;
  org.id = (elOrg.attribute("id").toInt());
  org.country = elOrg.attribute("country").toStdString();
  org.label = elOrg.attribute("label").toStdString();
  org.founders = elOrg.attribute("founders").toStdString();
  return org;
}

void XmlStorage::saveOrgs(const vector<Organisation>& orgs) {
  QDomDocument doc;
  QDomElement root = doc.createElement("org");
  for (const Organisation& org: orgs) {
    QDomElement orgEl = orgXml(doc, org);
    root.appendChild(orgEl);
  }
  doc.appendChild(root);
  if (!open()) {
    qDebug() <<"Error on opening";
    exit(1);
  }
  fstream orgs_file_(name(), ios::out);
  QString str = doc.toString(2);
  orgs_file_ << str.toStdString();
  this->close();
}
vector<Organisation> XmlStorage::loadOrgs() {
  if (!open()) {
    qDebug() <<"Error on opening";
    exit(1);
  }
  string s, temp;
  while (getline(orgs_file_, temp)) {
    s.append(temp + "\n");
  }
  this->close();
  QString str = QString::fromStdString(s);
  vector<Organisation> orgs;
  QDomDocument doc;
  QString errorMessage;
  if (!doc.setContent(str, &errorMessage)) {
    qDebug() << "Parse error" << errorMessage;
    exit(1);
  }
  QDomElement root = doc.documentElement();
  QDomNodeList rootCh = root.childNodes();
  for (int i = 0; i < rootCh.length(); i++) {
    QDomNode node = rootCh.at(i);
    QDomElement orgEl = node.toElement();
    Organisation org = xmlOrg(orgEl);
    orgs.push_back(org);
  }
  this->close();
  return orgs;
}

int XmlStorage::getNewOrgId() {
  int tmp = 0;
  vector<Organisation> orgs = getAllOrgs();
  for (auto& i: orgs) {
    if (i.id >= tmp) tmp = i.id + 1;
  }
  return tmp;
}

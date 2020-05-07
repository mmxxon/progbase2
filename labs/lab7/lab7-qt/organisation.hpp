#ifndef ORGANISATION_H
#define ORGANISATION_H
#include <QMetaType>
#include <iostream>

using std::string;
class Organisation {
public:
  Organisation() {}
  int id;
  string country;
  string label;
  string founders;
};
Q_DECLARE_METATYPE(Organisation);

#endif

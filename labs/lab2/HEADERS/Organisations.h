#ifndef __ENTITY_ORG_H
#define __ENTITY_ORG_H

#include <iostream>

using std::string;

struct Organisation {
  string country;
  string label;
  string type;
  string founders;
  int founded_date;
  string NASDAQ;
};

#endif /* end of include guard: __ENTITY_ORG_H */

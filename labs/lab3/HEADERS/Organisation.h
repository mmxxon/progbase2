#ifndef LAB3_STRUCT_ORGANISATION
#define LAB3_STRUCT_ORGANISATION

#include <iostream>

using std::string;

struct Organisation {
  int id;
  string country;
  string label;
  string type;
  int founded_date;
  string founders;
};

#endif /* end of include guard: LAB3_STRUCT_ORGANISATION */

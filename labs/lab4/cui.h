#pragma once
#include "organisation.h"
#include "storage.h"

#include <string>
using namespace std;
class Cui {
  FileStorage* const storage_;
  void OrgsMainMenu();
  void OrgsMenu(int orgs_id);
  void OrgsUpdataMenu(int orgs_id);
  void OrgsDeleteMenu(int orgs_id);
  void OrgsCreateMenu();

public:
  Cui(FileStorage* storage): storage_ {storage} {}

  void show();
};
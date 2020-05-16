#ifndef CUI_H
#define CUI_H
#include "csvstorage.hpp"
#include "xmlstorage.hpp"
#include "sqlitestorage.hpp"


#define blu_f "\033[32m"
#define yel_f "\033[33m"
#define cya_f "\033[36m"
#define red_f "\033[31m"
#define mag_f "\033[35m"
#define res "\033[0m"
#define cont "\n\033[32mPress any key to continue..\033[0m"

using namespace std;

class Cui {
  Storage* const storage_;
  void OrgsMainMenu();
  void OrgsMenu(int);
  void OrgsUpdateMenu(int);
  void OrgsDeleteMenu(int);
  void OrgsCreateMenu();

  void FndrsMainMenu();
  void FndrsMenu(int);
  void FndrsUpdateMenu(int);
  void FndrsDeleteMenu(int);
  void FndrsCreateMenu();

public:
  Cui(Storage* storage): storage_ {storage} {}
  void show();
};

char getch();

#endif    // CUI_H

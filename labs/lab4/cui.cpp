#include "cui.h"
using namespace std;
void Cui::OrgsMainMenu() {
  vector<Organisation> z = storage_->getAllOrgs();
  for (int i = 0; i < z.size(); i++) {
    cout << z[i].id << "|" << z[i].country << "|" << z[i].label << "|"
         << z[i].type << "|" << z[i].founders << "|" << z[i].founded_date
         << endl;
  }
}
void Cui::OrgsMenu(int poets_id) {
  optional<Organisation> coun = storage_->getOrgsById(poets_id);
  if (coun) {
    cout << coun->id << "," << coun->country << "," << coun->label << ","
         << coun->type << "," << coun->founders << "," << coun->founded_date
         << endl;
  } else {
    cout << "not found";
  }
}
void Cui::OrgsCreateMenu() {

  Organisation neworg;
  cout << "enter country" << endl;
  cin >> neworg.country;
  cout << "enter label" << endl;
  cin >> neworg.label;
  cout << "enter type" << endl;
  cin >> neworg.type;
  cout << "enter founders" << endl;
  cin >> neworg.founders;
  cout << "enter date of foundation" << endl;
  cin >> neworg.founded_date;
  neworg.id = 0;
  cout << storage_->insertOrgs(neworg);
}
void Cui::OrgsUpdataMenu(int orgs_id) {
  optional<Organisation> cap = storage_->getOrgsById(orgs_id);
  if (cap) {
    Organisation neworg;
    cout << "enter country" << endl;
    cin >> neworg.country;
    cout << "enter label" << endl;
    cin >> neworg.label;
    cout << "enter type" << endl;
    cin >> neworg.type;
    cout << "enter founders" << endl;
    cin >> neworg.founders;
    cout << "enter date of foundation" << endl;
    neworg.id = orgs_id;
    if (storage_->updateOrgs(neworg)) {
      cout << "updated" << endl;
    } else {
      cout << "error" << endl;
    }

  } else {
    cout << "not found" << endl;
  }
}
void Cui::OrgsDeleteMenu(int poets_id) {
  if (storage_->removeOrgs(poets_id)) {
    cout << "delete";
  } else {
    cout << "not found";
  }
}
void Cui::show() {
  while (true) {
    cout << endl;
    cout << "[1] List" << endl << "[2] Actions" << endl << "[3] New" << endl;
    cout << "> ";
    int cs;
    cin >> cs;
    if (cs == 1) {
      OrgsMainMenu();
    } else if (cs == 2) {
      cout << "id: ";
      int id;
      cin >> id;
      cout << "[1] Info | id = " << id << endl
           << "[2] Update | id = " << id << endl
           << "[3] Delete | id = " << id << endl;
      cout << "> ";
      int choice;
      cin >> choice;
      if (choice == 1) {
        OrgsMenu(id);
      } else if (choice == 2) {
        OrgsUpdataMenu(id);
      } else if (choice == 3) {
        OrgsDeleteMenu(id);
      }
    } else if (cs == 3) {
      OrgsCreateMenu();
    } else {
      break;
    }
  }
}
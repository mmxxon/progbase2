#include "MODULES/fs.h"
#include "MODULES/list.h"
#include "MODULES/stack.h"

#include <cstdlib>
#include <iostream>
using namespace std;

void connect(Stack* stack_first, Stack* stack_second, List* sh_list) {
  int tmp = stack_first->size();
  for (int i = 0; i < tmp; i++) {
    sh_list->push_back(stack_first->pop());
  }
  tmp = stack_second->size();
  for (int i = 0; i < tmp; i++) {
    sh_list->push_back(stack_second->pop());
  }
}

void push_back(List* abl) {
  int j = 0;
  for (int i = 0; i < abl->size(); i++) {
    if (abs(abl->get(j)) > 10) {
      float tmp = abl->get(j);
      abl->remove_at(j);
      abl->push_back(tmp);
    } else {
      j++;
    }
  }
}

void to_stack(List* abl, Stack* stack, int delta) {
  for (int i = delta; i < abl->size(); i += 2) {
    stack->push(abl->get(i));
  }
}

int main(int argc, char* argv[]) {
  check_args(argc, 2);
  FILE* fin = fopen(argv[1], "rw");
  check_open(fin);
  List list;
  float tmp = 0;
  while (fscanf(fin, "%f", &tmp) >= 0) {
    list.push_back(tmp);
  }

  cout << "\033[;;47mLIST AT BEGIN\033[0m" << endl;
  cout << "_____________" << endl;
  list.print();

  push_back(&list);
  cout << "\033[;;47mLIST AFTER PUSHING BACK\033[0m" << endl;
  cout << "_____________" << endl;
  list.print();

  Stack stack1;
  Stack stack2;

  to_stack(&list, &stack1, 1);
  to_stack(&list, &stack2, 0);
  cout << "\033[;;47mSTACK1 (odd indexes)\033[0m" << endl;
  cout << "_____________" << endl;
  stack1.print();
  cout << "\033[;;47mSTACK2 (even indexes)\033[0m" << endl;
  cout << "_____________" << endl;
  stack2.print();

  List mergedlist;
  connect(&stack1, &stack2, &mergedlist);
  cout << "\033[;;47mLIST AFTER MERGE\033[0m" << endl;
  cout << "_____________" << endl;
  mergedlist.print();
  cout << "\033[;;47mEND\033[0m" << endl;
  cout << "_____________" << endl;
  check_close(fin);
  cout << endl;
}

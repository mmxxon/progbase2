//
// Created by manjaro on 3/28/20.
//

#ifndef LAB3_BSTREE_H
#define LAB3_BSTREE_H
#include "BinTree.h"

#include <bits/stdc++.h>
using std::endl, std::cout;
class BSTree {
  BinTree* root_ = nullptr;
  size_t size_ = 0;

public:
  [[nodiscard]] size_t size() const;
  bool lookup(int key);
  Organisation search(int key);
  Organisation remove(int key);
  Organisation remove(int key, BinTree* node, BinTree* parent);
  void clear();
  void insert(Organisation val);
  void print();
  void print(BinTree* root, const string& prefix);
};

int getKey(Organisation value);

#endif    // LAB3_BSTREE_H
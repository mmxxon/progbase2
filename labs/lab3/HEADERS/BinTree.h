//
// Created by manjaro on 3/28/20.
//

#ifndef LAB3_BINTREE_H
#define LAB3_BINTREE_H

#include "Organisation.h"

#include <string>
struct Node {
  string value;    // set in ctor
  Node* left;
  Node* right;

  explicit Node(Organisation v): left(nullptr), right(nullptr) { value = v; }
} i

  class BinTree {
  Node* root_ = nullptr;
  size_t size_ = 0;

public:
  size_t size() const;
  Organisation remove(int key);
  Organisation remove(int key, BinTree* node, BinTree* parent);
  void insert(string val);
  void print();
  void print(BinTree* root, const string& prefix);
};
#endif    // LAB3_BINTREE_H

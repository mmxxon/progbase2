//
// Created by manjaro on 3/28/20.
//

#ifndef LAB3_BINTREE_H
#define LAB3_BINTREE_H

#include "Organisation.h"
struct BinTree {
  Organisation value;    // set in ctor
  BinTree* left;
  BinTree* right;

  explicit BinTree(Organisation v): left(nullptr), right(nullptr) { value = v; }
};
#endif    // LAB3_BINTREE_H

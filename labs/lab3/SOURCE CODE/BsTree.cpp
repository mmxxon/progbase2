//
// Created by manjaro on 3/28/20.
//
#include "BsTree.h"

size_t BSTree::size() const { return size_; }

int getKey(Organisation value) { return value.id; }

void BSTree::insert(Organisation val) {
  if (root_ == nullptr) {
    root_ = new BinTree(val);
  } else {
    BinTree* tmp = root_;
    while (true) {
      if (val.id == tmp->value.id) {
        cout << "Warning: Value already exists, so nothing will be done."
             << endl;
        return;
      }
      if (val.id < tmp->value.id) {
        if (tmp->left == nullptr) {
          tmp->left = new BinTree(val);
          break;
        } else {
          tmp = tmp->left;
        }
      } else {
        if (tmp->right == nullptr) {
          tmp->right = new BinTree(val);
          break;
        } else {
          tmp = tmp->right;
        }
      }
    }
  }
  size_++;
}
void BSTree::print() {
  if (root_ == nullptr) {
    cout << "Empty" << endl;
    return;
  }

  cout << "------" << endl << "SIZE: " << size() << endl;
  cout << root_->value.id << " " << root_->value.label << endl;
  print(root_, "");
  cout << "------" << endl;
}
void BSTree::print(BinTree* root, const string& prefix) {
  if (root == nullptr) { return; }

  bool buf_left = (root->left != nullptr);
  bool buf_right = (root->right != nullptr);

  if (!buf_left && !buf_right) { return; }

  cout << prefix;
  cout << ((buf_left && buf_right) ? "├── " : "");
  cout << ((!buf_left && buf_right) ? "└── " : "");

  if (buf_right) {
    bool printStrand =
      (buf_left && buf_right &&
       (root->right->right != nullptr || root->right->left != nullptr));
    string newPrefix = prefix + (printStrand ? "│   " : "    ");
    cout << root->right->value.id << " " << root->right->value.label << endl;
    print(root->right, newPrefix);
  }

  if (buf_left) {
    cout << (buf_right ? prefix : "") << "└── " << root->left->value.id
         << " "
            ""
         << root->left->value.label << endl;
    print(root->left, prefix + "    ");
  }
}

bool BSTree::lookup(int key) {
  BinTree* tmp = root_;
  while (true) {
    if (tmp == nullptr) {
      return false;
    } else if (key == tmp->value.id) {
      return true;
    } else if (key < tmp->value.id) {
      tmp = tmp->left;
    } else {
      tmp = tmp->right;
    }
  }
}

void BSTree::clear() {
  if (root_ == nullptr) return;
  std::queue<BinTree*> queue;
  queue.push(root_);
  while (!queue.empty()) {
    BinTree* tmp = queue.front();
    queue.pop();
    if (tmp->left != nullptr) { queue.push(tmp->left); }
    if (tmp->right != nullptr) { queue.push(tmp->right); }
    delete tmp;
  }
  size_ = 0;
}

Organisation BSTree::remove(int key, BinTree* node, BinTree* parent) {
  if (node->value.id == key) {
    int tkey = node->value.id;
    BinTree* root_right = node->right;
    BinTree* root_left = node->left;
    if (parent == nullptr) {
      if (root_right == nullptr) {
        root_ = root_left;
      } else {
        BinTree* right_left = root_right->left;
        if (right_left == nullptr) {
          root_ = root_right;
          root_right->left = root_left;
        } else {
          BinTree* right_pointer = root_right;
          while (right_left->left != nullptr) {
            right_pointer = right_left;
            right_left = right_left->left;
          }
          right_pointer->left = right_left->right;
          root_ = right_left;
          right_left->right = root_right;
          while (right_left->left != nullptr) {
            right_left = right_left->left;
          }
          right_left->left = root_left;
        }
      }
    } else {
      if (root_right == nullptr) {
        if (parent->left != nullptr) {
          if (parent->left->value.id == key) {
            parent->left = root_left;
          } else {
            parent->right = root_left;
          }
        } else {
          parent->right = root_left;
        }
      } else {
        BinTree* right_left = root_right->left;
        if (right_left == nullptr) {
          if (parent->left == nullptr) {
            if (parent->left->value.id == key) {
              parent->left = root_right;
            } else {
              parent->right = root_right;
            }
          } else {
            parent->right = root_right;
            root_right->left = root_left;
          }
        } else {
          BinTree* right = root_right;
          while (right_left->left != nullptr) {
            right = right_left;
            right_left = right_left->left;
          }
          right->left = right_left->right;
          if (parent->left != nullptr) {
            if (parent->left->value.id == key) {
              parent->left = right_left;
            } else {
              parent->right = right_left;
            }
          } else {
            parent->right = right_left;
          }
          right_left->right = root_right;
          right_left->left = root_left;
        }
      }
    }
    Organisation ret = node->value;
    delete node;
    size_--;
    return ret;
  }
  if (node->value.id < key) {
    return remove(key, node->right, node);
  } else {
    return remove(key, node->left, node);
  }
}

Organisation BSTree::remove(int key) {
  if (!lookup(key)) {
    perror("Key not exist");
    exit(1);
  } else {
    return remove(key, root_, nullptr);
  }
}
Organisation BSTree::search(int key) {
  BinTree* tmp = root_;
  while (true) {
    if (tmp == nullptr) {
      perror("Not found");
      exit(1);
    } else if (key == tmp->value.id) {
      return tmp->value;
    } else if (key < tmp->value.id) {
      tmp = tmp->left;
    } else {
      tmp = tmp->right;
    }
  }
}
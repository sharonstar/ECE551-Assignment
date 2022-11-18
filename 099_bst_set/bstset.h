#ifndef __SETMAP_H__
#define __SETMAP_H__
#include <cstdlib>
#include <iostream>

#include "set.h"
template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(T k) : key(k), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  // constructor
  BstSet<T>() : root(NULL) {}

  virtual void add(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else if (key == (*curr)->key) {
        return;
      }
      else {
        curr = &(*curr)->right;
      }
    }
    *curr = new Node(key);
  }
  virtual bool contains(const T & key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return true;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    return false;
  }

  Node * findMin(Node * curr) {
    while (curr != NULL && curr->left != NULL) {
      curr = curr->left;
    }
    return curr;
  }
  virtual void remove(const T & key) { root = removeHelper(root, key); }
  Node * removeHelper(Node * curr, const T & key) {
    if (curr == NULL) {
      return curr;
    }
    if (key == curr->key) {
      // left child is null
      if (curr->left == NULL) {
        Node * temp = curr->right;
        delete curr;
        return temp;
      }
      // right child is null
      else if (curr->right == NULL) {
        Node * temp = curr->left;
        delete curr;
        return temp;
      }
      // neither child is null
      else {
        Node * temp = findMin(curr->right);
        //std::swap(curr, temp);
        curr->key = temp->key;
        curr->right = removeHelper(curr->right, curr->key);
        return curr;
      }
    }
    // search key
    else if (key < curr->key) {
      curr->left = removeHelper(curr->left, key);
      return curr;
    }
    else {
      curr->right = removeHelper(curr->right, key);
      return curr;
    }
  }
  // destructor
  void destroy(Node * curr) {
    if (curr == NULL) {
      return;
    }
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
  }
  virtual ~BstSet<T>() { destroy(root); }
  // copy constructor
  Node * copyHelper(Node * rhs) {
    if (rhs == NULL) {
      return NULL;
    }
    Node * curr = new Node(rhs->key);
    curr->left = copyHelper(rhs->left);
    curr->right = copyHelper(rhs->right);
    return curr;
  }
  BstSet<T>(const BstSet<T> & rhs) : root(NULL) { root = copyHelper(rhs.root); }
  // assign operator
  BstSet<T> & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      BstSet<T> temp = rhs;
      std::swap(temp.root, root);
    }
    return *this;
  }
  // print the tree
  void inorder() { inorder_printer(root); }
  void inorder_printer(Node * root) {
    if (root != NULL) {
      inorder_printer(root->left);
      std::cout << root->key << " ";
      inorder_printer(root->right);
    }
  }
};
#endif

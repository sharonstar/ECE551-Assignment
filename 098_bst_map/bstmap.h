#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdlib>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  // constructor
  BstMap<K, V>() : root(NULL) {}

  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else if (key == (*curr)->key) {
        (*curr)->value = value;
        return;
      }
      else {
        curr = &(*curr)->right;
      }
    }
    *curr = new Node(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return curr->value;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    throw std::invalid_argument("Cannot find the key");
  }

  Node * findMin(Node * curr) {
    while (curr != NULL && curr->left != NULL) {
      curr = curr->left;
    }
    return curr;
  }
  virtual void remove(const K & key) { root = removeHelper(root, key); }
  Node * removeHelper(Node * curr, const K & key) {
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
        curr->key = temp->key;
        curr->value = temp->value;
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
  virtual ~BstMap<K, V>() { destroy(root); }
  // copy constructor
  Node * copyHelper(Node * rhs) {
    if (rhs == NULL) {
      return NULL;
    }
    Node * curr = new Node(rhs->key, rhs->value);
    curr->left = copyHelper(rhs->left);
    curr->right = copyHelper(rhs->right);
    return curr;
  }
  BstMap<K, V>(const BstMap<K, V> & rhs) : root(NULL) { root = copyHelper(rhs.root); }
  // assign operator
  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      BstMap<K, V> temp = rhs;
      std::swap(temp.root, root);
    }
    return *this;
  }

  // print the tree
  void inorder() { inorder_printer(root); }
  void inorder_printer(Node * root) {
    if (root != NULL) {
      inorder_printer(root->left);
      std::cout << root->key << "\n";
      inorder_printer(root->right);
    }
  }
};
#endif

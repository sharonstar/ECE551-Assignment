#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdio>
#include <cstdlib>

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
  BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
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
        delete temp;
        return temp;
      }
      // right child is null
      else if (curr->right == NULL) {
        Node * temp = curr->left;
        delete temp;
        return temp;
      }
      // neither child is null
      else {
        Node * temp = findMin(curr->right);
        curr->key = temp->key;
        curr->value = temp->value;
        curr->right = removeHelper(curr->right, key);
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

  virtual ~BstMap<K, V>() {}
};
#endif

#ifndef __BSTMAP_H__
#define __BSTMAP_H__
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
  // constructor
  BstMap<K, V>() : root(NULL) {}

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
  Node * copyHelper(Node * curr, Node * rhs) {
    if (curr == NULL) {
      return NULL;
    }
    curr = new Node(curr->key, curr->value);
    curr->left = copyHelper(curr->left, rhs->left);
    curr->right = copyHelper(curr->right, rhs->right);
    return curr;
  }
  BstMap<K, V>(const BstMap<K, V> & rhs) : root(NULL) {
    root = copyHelper(root, rhs.root);
  }
  // assign operator
  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      BstMap<K, V> temp = rhs;
      std::swap(temp.root, root);
    }
    return *this;
  }
};
#endif

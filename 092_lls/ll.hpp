#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class invalid : public std::exception {
 public:
  virtual const char * what() const throw() { return "invalid index"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(NULL), next(NULL), prev(NULL){};
    Node(T t, Node * n, Node * p) : data(t), next(n), prev(p){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      addBack(curr->data);
      curr = curr->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp(rhs);
      std::swap(temp.head, head);
      std::swap(temp.tail, tail);
      std::swap(temp.size, size);
    }
    return *this;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  Node * removeHelper(const T & data, Node * current) {
    if (current == NULL) {
      return NULL;
    }
    if (data == current->data) {
      // size = 1
      if (size == 1) {
        delete current;
        head = NULL;
        tail = NULL;
        size = 0;
        return NULL;
      }
      // size > 1
      Node * ans = current->next;
      // delete head
      if (current->prev == NULL) {
        head = ans;
        ans->prev = NULL;
      }  // delete tail, return null
      else if (current->next == NULL) {
        current->prev->next = NULL;
        tail = current->prev;
      }
      else {  // delete middle
        current->prev->next = current->next;
        current->next->prev = current->prev;
      }
      delete current;
      size--;
      return ans;
    }
    else {
      current->next = removeHelper(data, current->next);
      return current;
    }
  }
  bool remove(const T & item) {
    int sizeBefore = getSize();
    removeHelper(item, head);
    int sizeAfter = getSize();
    if (sizeAfter == sizeBefore) {
      return false;
    }
    return true;
  }
  T & operator[](int index) {
    Node * curr = head;
    if (index < 0 || index > size - 1) {
      throw invalid();
    }
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }
  T & operator[](int index) const {
    Node * curr = head;
    if (index < 0 || index > size - 1) {
      throw invalid();
    }
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }
  int find(const T & item) const {
    Node * curr = head;
    int index = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      curr = curr->next;
      index++;
    }
    return -1;
  }
  int getSize() const { return size; }
  friend class Tester;
};
#endif

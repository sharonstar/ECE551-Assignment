#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront0() {  // [0]
    IntList il;
    il.addFront(0);
    assert(il.head != NULL);
    assert(il.tail != NULL);

    assert(il.head->data == 0);
    assert(il.tail->data == 0);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
  }
  void testAddFront1() {  //[0, 1]
    IntList il;
    il.addFront(1);
    il.addFront(0);
    assert(il.head != NULL);
    assert(il.tail != NULL);

    assert(il.head->data == 0);
    assert(il.head->next->data == 1);
    assert(il.head->prev == NULL);

    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 0);
    //assert(il.head != il.tail);
  }
  void testAddBack0() {  // [0]
    IntList il;
    il.addBack(0);
    assert(il.head != NULL);
    assert(il.tail != NULL);

    assert(il.head->data == 0);
    assert(il.tail->data == 0);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
  }
  void testAddBack1() {  // [0,1]
    IntList il;
    il.addBack(0);
    il.addBack(1);
    assert(il.head != NULL);
    assert(il.tail != NULL);

    assert(il.head->data == 0);
    assert(il.head->next->data == 1);
    assert(il.head->prev == NULL);

    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 0);
  }
  void testCopy() {  //[1, 2, 3]
    IntList l1;
    l1.addBack(1);
    l1.addBack(2);
    l1.addBack(3);
    IntList l2(l1);

    IntList::Node * n1 = l1.head;
    IntList::Node * n2 = l2.head;
    while (n1->next != NULL && n2->next != NULL) {
      assert(n1->data == n2->data);
      n1 = n1->next;
      n2 = n2->next;
    }
    assert(n1->data == n2->data);
  }
  void testAssign() {  //[1, 2, 3]
    IntList l1;
    l1.addBack(1);
    l1.addBack(2);
    l1.addBack(3);
    IntList l2;
    l2.addBack(0);
    l2 = l1;

    IntList::Node * n1 = l1.head;
    IntList::Node * n2 = l2.head;
    while (n1->next != NULL && n2->next != NULL) {
      assert(n1->data == n2->data);
      n1 = n1->next;
      n2 = n2->next;
    }
    assert(n1->data == n2->data);
  }
  void testRemove1() {  //[1]
    IntList il;
    il.addFront(1);
    il.remove(1);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  void testRemoveFront() {  // [1, 2, 3]
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);
    il.remove(1);

    assert(il.head->data == 2);
    assert(il.head->next->data == 3);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
  }
  void testRemoveMiddle() {  // [1, 2, 3]
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);
    il.remove(2);

    assert(il.head->data == 1);
    assert(il.head->next->data == 3);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 1);
  }
  void testRemoveBack() {  // [1, 2, 3]
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);
    il.remove(3);

    assert(il.head->data == 1);
    assert(il.head->next->data == 2);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 2);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 1);
  }
  void testReturnValue() {
    IntList il;
    il.addFront(1);

    int a = il.remove(1);
    assert(a == true);

    il.addFront(1);
    int b = il.remove(2);
    assert(b == false);
  }
};
int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront0();
  // write calls to your other test methods here
  t.testAddFront1();
  t.testAddBack0();
  t.testAddBack1();
  t.testCopy();
  t.testAssign();
  t.testRemove1();
  t.testRemoveBack();
  t.testRemoveFront();
  t.testRemoveMiddle();
  t.testReturnValue();
  return EXIT_SUCCESS;
}

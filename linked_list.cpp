#include "linked_list.h"

HashNode::HashNode(long long key, const Data& val) : key(key), val(val), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr) {}
LinkedList::~LinkedList() {
  while (!empty()) {
    HashNode *next = head->next;
    delete head;
    head = next;
  }
}

bool LinkedList::empty() {
  return !head;
}

void LinkedList::push(long long key, const Data& val) {
  push_node(new HashNode(key, val));
}

void LinkedList::push_node(HashNode *node) {
  if (empty()) {
    head = node;
    return;
  }

  HashNode *prev = head;
  head = node;
  head->next = prev;
}

Data *LinkedList::find(long long key) {
  HashNode *cur = head;

  while (cur) {
    if (cur->key == key) return &cur->val;
    cur = cur->next;
  }

  return nullptr;
}

bool LinkedList::remove(long long key) {
  HashNode *cur = head;
  HashNode *prev = nullptr;
  while (cur) {
    if (cur->key == key) {
      if (!prev) {
        head = cur->next;
      } else {
        prev->next = cur->next;
      }

      delete cur;
      return true;
    }

    prev = cur;
    cur = cur->next;
  }

  return false;
}


void LinkedList::pop() {
  if (empty()) return;
  HashNode *temp = head;
  head = head->next;
  delete temp;
}

HashNode *LinkedList::pop_node() {
  if (empty()) return nullptr;

  HashNode *temp = head;
  head = head->next;
  temp->next = nullptr;
  return temp;
}

void LinkedList::print() {
  HashNode *cur = head;

  while (cur) {
    cur->val.print();
    cur = cur->next;
  }
}


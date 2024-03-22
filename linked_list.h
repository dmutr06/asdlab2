#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

struct HashNode {
  long long key;
  Data val;
  HashNode *next;

  HashNode(long long key, const Data& val); 
};

struct LinkedList {
private:
  HashNode *head;

public:
  LinkedList();
  ~LinkedList();
  Data *find(long long key);
  void push(long long key, const Data& val);
  void pop();
  void push_node(HashNode *node);
  HashNode *pop_node();
  bool remove(long long key);
  bool empty();
};

#endif

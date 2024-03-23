#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>

#include "common.h"
#include "linked_list.h"

#define MAX_LOAD_FACTOR .5

struct HashTable {
private:
  LinkedList *buckets;
  size_t total;
  size_t cap;
  size_t cap_idx;
  std::vector<size_t> primes;

  void expand();
  size_t hash(size_t key);

public:
  explicit HashTable();
  ~HashTable();

  size_t size();
  Data *find(long long key);
  void insert(long long key, const Data &val);
  void erase(long long key);
};

#endif

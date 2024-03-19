#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef>
#include <vector>

#include "common.h"
#include "linked_list.h"
#define INIT_CAP 16
#define INIT_MAX_LF .5

struct HashTable {
private:
  LinkedList *buckets;
  size_t total;
  size_t cap;
  size_t cap_idx;
  const float max_load_factor;
  std::vector<size_t> primes;

  void expand();
  size_t hash(size_t key);

public:
  HashTable(size_t init_cap = INIT_CAP, float init_max_lf = INIT_MAX_LF);
  ~HashTable();

  size_t size();
  Data *find(long long key);
  void insert(long long key, const Data &val);
  void erase(long long key);
  void print();
};

#endif

#include "hash_table.h"
#include "common.h"


HashTable::HashTable(size_t init_cap, float init_max_lf) : max_load_factor(init_max_lf) {
    cap_idx = 4;
    primes = get_primes(1000000, (float) 1 / max_load_factor);
    cap = primes[4];
    total = 0;
    buckets = new LinkedList[cap];
}

HashTable::~HashTable() {
    delete[] buckets;
}

size_t HashTable::size() {
  return total;
}

Data *HashTable::find(const long long key) {
  return buckets[hash(key)].find(key); 
}

void HashTable::insert(long long key, const Data &val) {
  if ((float) total / cap >= max_load_factor) expand();
  Data *existing_val = find(key);
  if (existing_val) {
    *existing_val = val;
    return;
  }
  
  buckets[hash(key)].push(key, val);  

  total++;
}

void HashTable::erase(long long key) {
  if (total == 0) return;
  if (buckets[hash(key)].remove(key)) total--;    
}

void HashTable::print() {
    for (size_t i = 0; i < cap; i++) {
      buckets[i].print();
    }
}

void HashTable::expand() {
  LinkedList *old_buckets = buckets;
  size_t old_cap = cap;
  cap = primes[++cap_idx];
  buckets = new LinkedList[cap];
  for (size_t i = 0; i < old_cap; i++) {
    LinkedList *bucket = old_buckets + i;
    while (!bucket->empty()) {
      HashNode *node = bucket->pop_node();
      buckets[hash(node->key)].push_node(node);
    }
  }

  delete[] old_buckets;
}

size_t HashTable::hash(size_t key) {
  return key % cap;
}

#ifndef LIN_HASH_TABLE_H
#define LIN_HASH_TABLE_H

#include "common.h"

#define MAX_LOAD_FACTOR 0.5
#define INIT_CAP_IDX 4

struct Item {
private:
  enum State {
    Empty,
    Occupied,
    Removed,
  } state;
public:
  long long key;
  Data val;

  explicit Item() : state(State::Empty), key(0), val(Data()) {}

  void occupy(long long key, const Data &val) {
    this->key = key;
    this->val = val;
    state = State::Occupied;
  }

  void remove() {
    state = State::Removed;
  }

  bool removed() {
    return state == State::Removed;
  }

  bool occupied() {
    return state == State::Occupied;
  }

  bool empty() {
    return state == State::Empty; 
  }
};

struct HashTable {
private:
  Item *buckets;
  size_t cap_idx;
  size_t total;
  std::vector<size_t> primes;
  
  size_t hash(long long key) {
    return key % primes[cap_idx];
  }

  void resize() {
    Item *old_buckets = buckets;
    buckets = new Item[primes[++cap_idx]];
    for (size_t i = 0; i < primes[cap_idx - 1]; i++) {
      Item *item = old_buckets + i;
      if (!item->occupied()) continue;
      internal_insert(item->key, item->val);
    }

    delete[] old_buckets;
  }

  Item *find_item(long long key) {
    if (total == 0) return nullptr;

    const size_t hashed_key = hash(key);
    size_t alt_key = hashed_key;
    Item *item;
    size_t probe = 0;
    do {
      item = buckets + alt_key;
      if (item->empty()) return nullptr; 
      if (item->key == key) return (item->removed() ? nullptr : item);  

      alt_key = (hashed_key + ++probe) % primes[cap_idx];
    } while (alt_key != hashed_key);

    return nullptr;
  }
  
  bool internal_insert(long long key, const Data &val) {
    Item *item;
    size_t hashed_key = hash(key);
    size_t alt_key = hashed_key;
    size_t probe = 0;
    do {
      item = buckets + alt_key;
      if (item->occupied()) {
        if (item->key == key) {
          item->val = val;
          return 0;
        }

        alt_key = (hashed_key + ++probe) % primes[cap_idx];
        continue;
      }

      item->occupy(key, val);
      return 1;

    } while (alt_key != hashed_key);

    return 0;
  }

public:
  explicit HashTable() {
    primes = get_primes(1000000, 2 / MAX_LOAD_FACTOR);
    cap_idx = INIT_CAP_IDX;
    total = 0;
    buckets = new Item[primes[cap_idx]];
  }

  ~HashTable() {
    delete[] buckets;
  }

  Data *find(long long key) {
    Item *item = find_item(key);
    
    if (item) return &item->val;
    return nullptr;
  }
  
  void insert(long long key, const Data &val) {
    if (total >= MAX_LOAD_FACTOR * primes[cap_idx]) resize();
    
    total += internal_insert(key, val);
  }

  void erase(long long key) {
    Item *item = find_item(key);
    
    if (item) {
      item->remove();
      total--;
    }
  }

  size_t size() {
    return total;
  }
};

#endif

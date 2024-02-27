#include <iostream>

#define INIT_CAP 8
#define LOAD_FACTOR 1

struct Person {
  std::string name;
  short age;
  
  void print() {
    std::cout << "Name: " << name << ". Age: " << age << '\n';
  }
};

template <typename T>
struct Node {
  const std::string key;
  T val;
  Node *next;

  Node(const std::string &key, T val) : key(key), val(val), next(nullptr) {}
};

size_t hash(const std::string &str) {
  size_t total = 0;
  for (const char ch : str) {
    total += ch;
  }

  return total; 
}

template <typename T>
struct HashTable {
private:
  Node<T> **buckets;
  size_t cap;
  size_t total;
  double load_factor;

  void expand() {
    Node<T> **old_buckets = buckets;
    buckets = new Node<T> *[cap *= 2] { nullptr };
    total = 0;

    for (size_t i = 0; i < cap / 2; i++) {
      Node<T> *cur = old_buckets[i];
      while (cur) {
        Node<T> *next = cur->next;
        cur->next = nullptr;
        insert_node(cur);     
        cur = next;
      }
    }

    delete[] old_buckets;
  }

  void insert_node(Node<T> *node) {
    total++;
    load_factor = (double) total / cap;
    size_t hashed_key = hash(node->key);
    Node<T> **bucket = buckets + (hashed_key % cap);

    if (!*bucket) {
      *bucket = node;
      return;
    }
    
    Node<T> *temp = *bucket;
    *bucket = node;
    (*bucket)->next = temp;
  }

public:
  HashTable(size_t init_cap = INIT_CAP) {
    cap = init_cap;
    total = 0;
    load_factor = 0;
    buckets = new Node<T> *[cap] { nullptr };
  }

  ~HashTable() {
    for (size_t i = 0; i < cap; i++) {
      Node<T> *cur = buckets[i];
      while (cur) {
        Node<T> *next = cur->next;
        delete cur;
        cur = next;
      } 
    }

    delete[] buckets;
  }

  size_t size() {
    return total;
  }

  T *find(const std::string &key) {
    if (total == 0) return nullptr;
    size_t hashed_key = hash(key);
    Node<T> **bucket = buckets + (hashed_key % cap);

    if (!*bucket)
      return nullptr;
    Node<T> *cur = *bucket;
    while (cur) {
      if (cur->key == key)
        return &cur->val;
      cur = cur->next;
    }
    
    return nullptr;
  }

  void insert(const std::string &key, T val) {
    if (load_factor >= LOAD_FACTOR) expand();
    T *existing_val = find(key);
    if (existing_val) {
      *existing_val = val;
      return;
    }

    insert_node(new Node<T>(key, val));
  }

  short erase(const std::string &key) {
    total--;
    size_t hashed_key = hash(key);
    Node<T> **bucket = buckets + (hashed_key % cap);

    if (!*bucket) return 0;
    
    Node<T> *cur = *bucket;
    Node<T> *prev = nullptr;
    while (cur) {
      if (cur->key == key) {
        if (!prev) {
          *bucket = cur->next;
        } else {
          prev->next = cur->next;
        }

        delete cur;
        return 1;
      }
      cur = cur->next;
    }

    return 0;
  }

  void print() {
    for (size_t i = 0; i < cap; i++) {
      Node<T> *cur = buckets[i];
      while (cur) {
        std::cout << cur->key << ": " << cur->val << '\n';
        cur = cur->next;
      }
    }
  }

};

template<> void HashTable<Person>::print() {
  for (size_t i = 0; i < cap; i++) {
    Node<Person> *cur = buckets[i];
    while (cur) {
      std::cout << cur->key << ": ";
      cur->val.print();
      cur = cur->next;
    }
  }
}

int main() {
  HashTable<Person> table;
  
  table.insert("first", Person { "name", 18 });
  table.insert("second", Person { "secname", 5 });

  HashTable<int> test_table;
  test_table.insert("a", 5);
  test_table.insert("b", 10);
  test_table.insert("ghfjkdghfd", 44);
  
  test_table.print();

  test_table.print();
  return 0;
}


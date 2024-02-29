#include <iostream>

#define INIT_CAP 8
#define LOAD_FACTOR 0.8

struct Person {
  std::string name;
  short age;
  
  void print() {
    std::cout << name << " - " << age << " yo\n";
  }
};


size_t hash(const std::string &str) {
  size_t total = 0;
  for (const char ch : str) {
    total += ch;
  }

  return total; 
}

struct HashTable {
private:
  struct Node {
    const std::string key;
    Person val;
    Node *next;

    Node(const std::string &key, const Person &val) : key(key), val(val), next(nullptr) {}
  };

  Node **buckets;
  size_t cap;
  size_t total;

  void expand() {
    Node **old_buckets = buckets;
    buckets = new Node *[cap *= 2] { nullptr };
    total = 0;

    for (size_t i = 0; i < cap / 2; i++) {
      Node *cur = old_buckets[i];
      while (cur) {
        Node *next = cur->next;
        cur->next = nullptr;
        insert_node(cur);     
        cur = next;
      }
    }

    delete[] old_buckets;
  }

  void insert_node(Node *node) {
    total++;
    size_t hashed_key = hash(node->key);
    Node **bucket = buckets + (hashed_key % cap);

    if (!*bucket) {
      *bucket = node;
      return;
    }
    
    Node *temp = *bucket;
    *bucket = node;
    (*bucket)->next = temp;
  }

public:
  HashTable(size_t init_cap = INIT_CAP) {
    cap = init_cap;
    total = 0;
    buckets = new Node *[cap] { nullptr };
  }

  ~HashTable() {
    for (size_t i = 0; i < cap; i++) {
      Node *cur = buckets[i];
      while (cur) {
        Node *next = cur->next;
        delete cur;
        cur = next;
      } 
    }

    delete[] buckets;
  }

  size_t size() {
    return total;
  }

  Person *find(const std::string &key) {
    if (total == 0) return nullptr;
    size_t hashed_key = hash(key);
    Node **bucket = buckets + (hashed_key % cap);

    if (!*bucket)
      return nullptr;
    Node *cur = *bucket;
    while (cur) {
      if (cur->key == key)
        return &cur->val;
      cur = cur->next;
    }
    
    return nullptr;
  }

  void insert(const std::string &key, Person val) {
    if ((double) total / cap >= LOAD_FACTOR) expand();
    Person *existing_val = find(key);
    if (existing_val) {
      *existing_val = val;
      return;
    }

    insert_node(new Node(key, val));
  }

  short erase(const std::string &key) {
    total--;
    size_t hashed_key = hash(key);
    Node **bucket = buckets + (hashed_key % cap);

    if (!*bucket) return 0;
    
    Node *cur = *bucket;
    Node *prev = nullptr;
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
      prev = cur;
      cur = cur->next;
    }

    return 0;
  }

  void print() {
    for (size_t i = 0; i < cap; i++) {
      Node *cur = buckets[i];
      while (cur) {
        std::cout << cur->key << ": ";
        cur->val.print();
        cur = cur->next;
      }
    }
  }
};


int main() {
  HashTable table;
  Person person { "name", 1 };
  std::string key = "g";
  for (size_t i = 'a'; i < 'z'; i++) {
    table.insert(key, person);
    person.age++;
    key.push_back(i);
  }
  
  table.find("ga")->print();

  return 0;
}


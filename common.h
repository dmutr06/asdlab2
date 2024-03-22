#ifndef COMMON_H 
#define COMMON_H

#include <iostream>
#include <cmath>
#include <vector>

const std::string COMPANIES[] = { "There", "could", "be", "real", "companies" };

struct Plane {
  std::string company;
  std::string number;
  double weight;
  size_t max_speed;

  explicit Plane() {
    company = COMPANIES[rand() % (sizeof(COMPANIES) / sizeof(std::string))];
    number = gen_number(30); 
    weight = 1500 + (double) (rand() % 10000) / (rand() % 99 + 1);
    max_speed = 1000 + rand() % 500;
  }
  
private:
  std::string gen_number(size_t len) {
    std::string number;
    for (size_t i = 0; i < len; i++) {
      number.push_back('z' - rand() % ('z' - 'a'));
    }

    return number;
  }
};

typedef Plane Data;

inline long long generateRandLong() {
  long long num = 0;
  for (size_t i = 0; i < 10; i++) {
    num += (rand() % 10) * pow(10, i);
  }

  return num;
 
}


inline std::vector<size_t> get_primes(size_t max_num, size_t min_diff) {
  std::vector<size_t> primes;
  bool *sieve = new bool[max_num + 1];
  sieve[0] = sieve[1] = 0;

  for (size_t i = 2; i <= max_num; i++) {
    sieve[i] = 1;
  }
  
  primes.push_back(2);
  for (size_t i = 2; i <= max_num; i++) {
    if (!sieve[i]) continue;
    if (i > primes.back() * min_diff) primes.push_back(i);
    for (size_t j = i * i; j <= max_num; j += i) {
      sieve[j] = false; 
    }
  }

  delete[] sieve;
  return primes;
}

#endif

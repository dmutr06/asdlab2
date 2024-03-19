#ifndef COMMON_H 
#define COMMON_H

#include <iostream>
#include <cmath>
#include <vector>

struct Data {
  std::string company;
  std::string number;
  double weight;
  double max_speed;
  void print() {
    std::cout << number << '\n';
  }

  Data() {
    company = "none";
    number = "43";
    weight = 2.29;
    max_speed = 0.5;
  }

  ~Data() {}
};

inline long long generateRandLong() {
  long long num = 0;
  for (size_t i = 0; i < 10; i++) {
    num += (rand() % 10) * std::pow(10, i);
  }

  return num;
 
}

inline const std::vector<size_t> get_primes(size_t max_num, size_t min_diff) {
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

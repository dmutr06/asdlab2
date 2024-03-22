#include <ctime>
#include <cstdlib>
#include "test.h"
// RABIN-CARP
// #include <vector>
// using namespace std;
//
// #define X 7
// #define P 101
//
// unsigned long long hash_str(const string &str) {
// 	unsigned long long total = 0;
// 	size_t len = str.length();
// 	for (size_t i = 0; i < len; i++) {
//     std::cout << unsigned(str[i] * pow(X, len - i - 1)) % P << std::endl;
// 	}
//
//   return total;
// }
//
// vector<int> stringMatch(const string &text, const string &pattern) {
// 	vector<int> idxs;
// 	unsigned long long pattern_hash = hash_str(pattern);
//   std::cout << "Pattern hash = " << pattern_hash << std::endl;
// 	for (size_t i = 0; i < text.length() - pattern.length(); i++) {
// 		if (hash_str(text.substr(i, pattern.length())) == pattern_hash) {
// 			idxs.push_back(i);
// 		}
// 	}
//
// 	return idxs;
// }


int main() {
  srand(time(NULL));

  testHashTable();
  return 0;
}


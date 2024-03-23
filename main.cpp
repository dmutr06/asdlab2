#include <ctime>
#include <cstdlib>
#include "test.h"


int main() {
  srand(time(NULL));

  testHashTable();
  return 0;
}


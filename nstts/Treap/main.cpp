#include "Treap.h"
#include <iostream>

int main() {
  std::cout << "Hello, World!\n";
  Treap treap;
  treap.insert(25);
  std::cout << treap.sum() << std::endl;
  return 0;
}

#include "Treap.h"
#include <iostream>

int main() {
  Treap treap(42);
  treap.insert(1);
  std::cout << treap.sum() << std::endl;
  treap.insert(4);
  std::cout << treap.sum() << std::endl;
  treap.insert(5);
  std::cout << treap.sum() << std::endl;
  treap.insert(8);
  std::cout << treap.sum() << std::endl;
  treap.insert(7);
  std::cout << treap.sum() << std::endl;
  treap.insert(6);
  std::cout << treap.sum() << std::endl;
  treap.insert(2);
  std::cout << treap.sum() << std::endl;
  return 0;
}

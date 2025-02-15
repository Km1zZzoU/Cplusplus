
#ifndef TREAP_H
#define TREAP_H

#include <utility>
class Treap {
  int key_;
public:
  int value;
  Treap *left;
  Treap *right;

  Treap();
  Treap(int value);
private:
  std::pair<Treap *, Treap *> split(int k);
  Treap *merge(Treap *t);
public:
  Treap *insert(int value);
  void remove(int value);
  int sum();
};



#endif //TREAP_H

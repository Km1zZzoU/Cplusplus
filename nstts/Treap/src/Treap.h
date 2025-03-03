
#ifndef TREAP_H
#define TREAP_H

#include <optional>
#include <utility>
class Treap {
  int key_;

public:
  std::optional<int> value;
  Treap*             left;
  Treap*             right;

  Treap();
  explicit Treap(int value);
  ~Treap();
  Treap(const Treap& other);
  Treap(Treap&& other);
  Treap&   operator=(Treap&& other);
  Treap& operator=(const Treap& other);

private:
  std::pair<Treap*, Treap*> split(int k);
  Treap*                    merge(Treap* t);
  Treap* clone() const;

  void free();
public:
  void insert(int value);
  void remove(int value);
  int  sum() const;
};


#endif // TREAP_H

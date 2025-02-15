
#include <cstdlib>
#include <optional>
#include <utility>

class Treap {
  int key_;

public:
  std::optional<int> value;
  Treap*             left;
  Treap*             right;

  Treap() {
    key_  = rand();
    left  = nullptr;
    right = nullptr;
    value = std::nullopt;
  }

  Treap(const int value) : Treap() { this->value = value; }

private:
  std::pair<Treap*, Treap*> split(const int k) {
    if (k > value) {
      if (!right)
        return {this, nullptr};
      auto [rl, rr] = right->split(k);
      right         = rl;
      return {this, rr};
    } else {
      if (!left)
        return {this, nullptr};
      auto [ll, lr] = right->split(k);
      left          = lr;
      return {ll, this};
    }
  }

  Treap* merge(Treap* t) {
    if (!t)
      return this;
    if (key_ < t->key_) {
      right = right->merge(t);
      return this;
    }
    t->left = t->merge(t->left);
    return t;
  }

public:
  void insert(int value) {
    if (!this->value.has_value()) {
      this->value.emplace(value);
      return;
    }
    Treap* node   = new Treap(value);
    auto [t1, t2] = this->split(value);
    *this         = *t2->merge(t1->merge(node));
  }

  void remove(int value) {
    auto [t1, t2] = split(value);
    t2            = t2->right;
    t1->merge(t2);
  }

  int sum() {
    return value.value() + (left ? left->sum() : 0) +
           (right ? right->sum() : 0);
  }
};
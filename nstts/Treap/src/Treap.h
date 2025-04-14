#ifndef TREAP_H
#define TREAP_H

#include <optional>
#include <utility>
#include <cstdlib>

template <typename T>
class Treap {
  int key_;

public:
  std::optional<T> value;
  Treap*           left;
  Treap*           right;

  Treap() : key_(rand()), value(std::nullopt), left(nullptr), right(nullptr) {}
  explicit Treap(T value) : Treap() { this->value = value; }
  ~Treap() {
    delete left;
    delete right;
    left = nullptr;
    right = nullptr;
  }

  Treap(const Treap& other)
      : key_(other.key_), value(other.value.value()) {
    left = other.left ? other.left->clone() : nullptr;
    right = other.right ? other.right->clone() : nullptr;
  }

  Treap(Treap&& other)
      : key_(other.key_), value(other.value), left(other.left), right(other.right) {
    other.left = nullptr;
    other.right = nullptr;
  }

  Treap& operator=(Treap&& other) {
    if (this == &other)
      return *this;
    key_ = other.key_;
    value = other.value;
    delete left;
    delete right;
    left = other.left;
    right = other.right;
    other.left = nullptr;
    other.right = nullptr;
    return *this;
  }

  Treap& operator=(const Treap& other) {
    value = other.value;
    key_ = other.key_;
    left = other.left ? other.left->clone() : nullptr;
    right = other.right ? other.right->clone() : nullptr;
    return *this;
  }

private:
  std::pair<Treap*, Treap*> split(T k) {
    if (k > value) {
      if (!right)
        return {this, nullptr};
      auto [rl, rr] = right->split(k);
      right = rl;
      return {this, rr};
    } else {
      if (!left)
        return {this, nullptr};
      auto [ll, lr] = left->split(k);
      left = lr;
      return {ll, this};
    }
  }

  Treap* merge(Treap* t) {
    if (!t)
      return this;
    if (key_ < t->key_) {
      right = t->merge(right);
      return this;
    }
    t->left = merge(t->left);
    return t;
  }

  Treap* clone() const {
    Treap* clone = new Treap();
    clone->key_ = key_;
    clone->value = value;
    clone->left = left ? left->clone() : nullptr;
    clone->right = right ? right->clone() : nullptr;
    return clone;
  }

public:
  void insert(T value) {
    if (!this->value.has_value()) {
      this->value.emplace(value);
      return;
    }
    auto copy_this = this->clone();
    auto [t1, t2] = copy_this->split(value);
    auto* node = new Treap(value);
    *this = std::move(*(t1 ? node->merge(t1->merge(t2)) : node->merge(t2->merge(t1))));
    if (node->key_ < copy_this->key_)
      delete node;
    else
      delete copy_this;
  }

  // void remove(T value) {
  //   auto [t1, t2] = split(value);
  //   t2 = t2 ? t2->right : nullptr;
  //   if (t1)
  //     t1->merge(t2);
  //   else
  //     t2->merge(t1);
  // }

  T sum() const {
    return value.value() + (left ? left->sum() : 0) + (right ? right->sum() : 0);
  }
};

#endif // TREAP_H


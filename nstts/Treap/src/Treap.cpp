
#include "Treap.h"
#include <cstdlib>
#include <optional>
#include <sys/types.h>
#include <utility>

using m = Treap;

Treap* m::clone() const {
  const auto clone = new Treap();
  clone->key_ = key_;
  clone->value = value;

  if (left)
    clone->left = left->clone();
  if (right)
    clone->right = right->clone();

  return clone;
}

m::Treap(const Treap& other)
    : key_(other.key_), value(other.value.value()) {
  if (other.left != nullptr)
    left = other.left->clone();
  else
    left = nullptr;

  if (other.right != nullptr)
    right = other.right->clone();
  else
    right = nullptr;
}

m::Treap(Treap&& other) : key_(other.key_), value(other.value) {
  left  = other.left;
  right = other.right;

  other.left  = nullptr;
  other.right = nullptr;
}

Treap& m::operator=(Treap&& other) {
  if (this == &other)
    return *this;
  key_ = other.key_;
  value = other.value;
  delete left;
  delete right;
  left = other.left;
  right = other.right;
  return *this;
}

Treap& m::operator=(const Treap& other) {
  value = other.value;
  key_ = other.key_;

  left = other.left == nullptr ? nullptr : other.left->clone();
  right = other.right == nullptr ? nullptr : other.right->clone();
  return *this;
}

void m::insert(int value) {
  if (!this->value.has_value()) {
    this->value.emplace(value);
    return;
  }
  auto copy_this = this->clone();
  auto [t1, t2]  = copy_this->split(value);
  auto* node     = new Treap(value);
  // delete this->left;
  // delete this->right;
  *this = std::move(*(t1 ? node->merge(t1->merge(t2)) : node->merge(t2->merge(t1))));
  if (node->key_ < copy_this->key_)
    delete node;
  else {
    delete copy_this;
  }
}

m::Treap() : key_(rand()), value(std::nullopt), left(nullptr), right(nullptr) {
}

m::Treap(const int value) : Treap() {
  this->value = value;
}

m::~Treap() {
  delete left;
  delete right;
}


std::pair<Treap*, Treap*> m::split(const int k) {
  if (k > value) {
    if (!right)
      return {this, nullptr};
    auto [rl, rr] = right->split(k);
    right         = rl;
    return {this, rr};
  } else {
    if (!left)
      return {this, nullptr};
    auto [ll, lr] = left->split(k);
    left          = lr;
    return {ll, this};
  }
}

Treap* m::merge(Treap* t) {
  if (!t)
    return this;
  if (key_ < t->key_) {
    right = t->merge(right);
    return this;
  }
  t->left = merge(t->left);
  return t;
}

void m::remove(const int value) {
  auto [t1, t2] = split(value);
  t2            = t2->right;
  if (t1)
    t1->merge(t2);
  else
    t2->merge(t1);
}

int m::sum() const {
  return value.value() + (left ? left->sum() : 0) + (right ? right->sum() : 0);
}

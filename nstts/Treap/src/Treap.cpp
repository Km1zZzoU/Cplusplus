
#include "Treap.h"
#include <cstdlib>
#include <iostream>
#include <optional>
#include <ostream>
#include <utility>

using m = Treap;

/* RE: about copy constructors
 * the main thing about them - they really should copy your data
 * It is looks too unefficient, but they should, they created for that purpuse
 * --
 * This implementation behave the same way as defaulted one
 * it is just copying _pointers_ to _data_, but not the _data_ itself 
 *
 * Please take a look to the test that I written, the problem is in copying pointers
 * If pointers is copied I can't using this ctr to copy this ds to function
 * cause _data_ under the pointer can be freed
 *
 * --
 * I ask you to implement copy ctr that creates new data that copied from the existing one
 */
m::Treap(const Treap& other)
    : key_(other.key_), value(other.value.value()), left(other.left),
      right(other.right) {
}

/* RE: same as above */
Treap& m::operator=(const Treap& other) = default;

/* Note: strange free
 * Memory can leak if we will use this function
 * I don't think that this function can be public
 */
void m::free() {
  left  = nullptr;
  right = nullptr;
  delete this;
}

void m::insert(int value) {
  if (!this->value.has_value()) {
    this->value.emplace(value);
    return;
  }
  auto copy_this = new Treap(*this);
  auto [t1, t2]        = copy_this->split(value);
  auto* node           = new Treap(value);
  *this = *(t1 ? node->merge(t1->merge(t2)) : node->merge(t2->merge(t1)));
  if (node->key_ < copy_this->key_)
    node->free();
  else
    copy_this->free();
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

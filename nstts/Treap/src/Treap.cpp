
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


/** RE: move assigment operator
  * Remember - the value wich bounds to rvalue reference
  * probably die very soon and you need take it to account
  * when writing move assigment operator
  *
  * You need to awoid dangling pointers here
  */
Treap& m::operator=(Treap&& other) {
  if (this == &other)
    return *this;
  key_ = other.key_;
  value = other.value;
  delete left;
  delete right;
  left = other.left;    // RE: if other will die, then left in current class is dangling pointer
  right = other.right;  // RE: if other will die, then left in current class is dangling pointer
  return *this;
}

Treap& m::operator=(const Treap& other) {
  value = other.value;
  key_ = other.key_;

  left = other.left == nullptr ? nullptr : other.left->clone();
  right = other.right == nullptr ? nullptr : other.right->clone();
  return *this;
}

/** RE: this operation should run in O(logN) time
  * but because of clone() it always runs in O(N)
  * actually cloning here is redundant operation
  * Try to avoid it here.
  *
  * And if you find youself stuck to do it - text me and I'll help
  */
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

  // Note: this line is really hard to read and debug
  *this = std::move(*(t1 ? node->merge(t1->merge(t2)) : node->merge(t2->merge(t1))));
  if (node->key_ < copy_this->key_)
    delete node;
  else {
    delete copy_this;
  }
}


/** Note: about random in C++ 
  *  Your data structure is probabilistic, and it's guaranties by time complixety
  *  depends on 'uniform' distribution of priorities 
  *  (in your implementation they called key's but for me priority is more convinient).
  *  By 'priorities distributed uniformly' we mean that all priorities have the same probability.
  *
  *  So for Treap it is important to think about priority generation.
  *
  *  And lets talk about random generators in C++
  *
  *  Generator - it is deterministic thing that generates sequence
  *  of numbers which looks like random numbers
  *
  *  So lets focus on word 'deterministic'. Such generators have
  *  a special parameter called 'seed'. It is used to generate different sequences
  *
  *  It means that two runs of generator with the same seeds yields some squences
  *
  *  For your data structure it means that for one treap sequence of random numbers
  *  will be the same for every run of program.
  *
  *  And also here can be problems with 'uniformity' of your sequences. 
  *  Firstly generator that you use not really good in that.
  *  It would be better to use mt19937 generator. 
  *
  *  Also 'uniformity' can be broken by type casts
  *  Generator yields numbers in range [0, RAND_MAX],
  *  where the RAND_MAX is some constant
  *
  *  On the other hand standart doesn't say that this constant fits to int 
  *
  *  So here can be overflow, and integer overflow architecture dependent thing too. It means
  *  that we don't know how actually integer will be overflowed.
  *  And it might leads us to lose of 'uniformity' of random sequences.
  *  After overflow some numbers will be generated with greater probability than the others
  *
  *  It's been a long backstory about why working with random numbers is trickier than it seems
  *
  *  But C++ has nice api for make this work easier! See reviewExamples/random.cpp example
  *  It is just note, no need to fix it right now)  
  */
    
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

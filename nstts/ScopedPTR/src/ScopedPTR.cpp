#include "ScopedPTR.hpp"

/** RE: Templates
 * Yep, this is correct ScopedPointer for Triple
 * but what if I wan't the same functionallity but for other class? 
 * There will be the same code, but with another class, this is not C++ way
 * So let's generalize this method using templates.
 * In this case it is very simple, all you need to is substitute Triple with your template parameter
 * And this will work
 */
class ScopedPTRdeep {
  Triple* p;
public:
  ScopedPTRdeep(Triple* p = nullptr): p(p) {}

  ~ScopedPTRdeep() { delete p; }

  ScopedPTRdeep(const ScopedPTRdeep& other) : p(new Triple(*other.p)) {}

  ScopedPTRdeep& operator=(const ScopedPTRdeep& other) {
    if (this != &other) {
      delete p;
      p = new Triple(*other.p);
    }
    return *this;
  }

  ScopedPTRdeep(ScopedPTRdeep&& other)  noexcept : p(other.p) { other.p = nullptr; }

  ScopedPTRdeep& operator=(ScopedPTRdeep&& other) noexcept {
    if (this != &other) {
      delete p;
      p = other.p;
      other.p = nullptr;
    }
    return *this;
  }

  /** RE: control of an access rights to guarded resource
   * Your pointers is trying to mimic real pointers.
   * But using real pointers you can control an access to pointee using 'const'
   * For example: const int* p guarantees that you cant change pounted int through this pointer;
   * But through your ScopedPTR it is always possible to change guarded resource
   * Try to provide an access rights to guarded resource using 'const' qualifier on methods
   * Hint: for hints you can recall scoped pointer example from lecture 5
   */
  Triple& operator*() const { return *p; }

  Triple* operator->() const { return p; }
};

/** RE: same comments as above */ 
class ScopedPTRtrans {
  Triple* p;
public:
  ScopedPTRtrans(Triple* p = nullptr) : p(p) {}

  ~ScopedPTRtrans() { delete p; }

  ScopedPTRtrans(const ScopedPTRtrans&) = delete;

  ScopedPTRtrans& operator=(const ScopedPTRtrans&) = delete;

  ScopedPTRtrans(ScopedPTRtrans&& other) noexcept : p(other.p) { other.p = nullptr; }

  ScopedPTRtrans& operator=(ScopedPTRtrans&& other) noexcept {
    if (this != &other) {
      delete p;
      p = other.p;
      other.p = nullptr;
    }
    return *this;
  }

  Triple& operator*() const { return *p; }

  Triple* operator->() const { return p; }
};

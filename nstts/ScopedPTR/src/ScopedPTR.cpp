#include "ScopedPTR.hpp"

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

  Triple& operator*() const { return *p; }

  Triple* operator->() const { return p; }
};

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
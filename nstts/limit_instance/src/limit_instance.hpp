
#include <stdexcept>
template <typename T, size_t c>
class limit_instance {
  static size_t counter;

public:
  limit_instance() {
    if (c == counter)
      throw std::runtime_error("limit instance error");
    counter++;
  }

  ~limit_instance() noexcept {
    --counter;
  }
};

template <typename T, size_t c>
size_t limit_instance<T, c>::counter = 0;
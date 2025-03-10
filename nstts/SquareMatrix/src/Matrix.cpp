#include "Matrix.hpp"
#include <cstddef>
#include <vector>

class VectorMatrix {
  double* data_;
  size_t  size_;
public:
  VectorMatrix(double* data_, size_t size_) : data_(data_), size_(size_) {}

  double& operator[](size_t index) const { return data_[index]; }
};

class Smatrix {
  double** data_;
  size_t   size_{};

public:
  VectorMatrix operator[](size_t i) const {
    return VectorMatrix(data_[i], size_);
  }

  Smatrix(size_t size) : size_(size) {
    if (!size_)
      return;

    data_ = new double*[size_];
    for (int i = 0; i < size_; data_[i++] = new double[size_])
      ;
  }

  Smatrix() : Smatrix(0) {}

  explicit Smatrix(double* d, size_t size_) : Smatrix(size_) {
    for (int i = 0; i < size_; data_[i][i] = d[i++])
      ;
  }

  explicit operator double() {
    double sum = 0;

    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; sum += data_[i][j++])
        ;
    }
    return sum;
  }

  Smatrix(double** m, size_t size_) : Smatrix(size_) {
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        data_[i][j] = m[i][j];
      }
    }
  }

  explicit Smatrix(size_t size, double value) : Smatrix(size) {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        data_[i][j] = value;
      }
    }
  }

  Smatrix(const Smatrix& other) {
    size_ = other.size_;
    data_ = new double*[size_];
    for (int i = 0; i < size_; ++i) {
      data_[i] = new double[size_];
      for (int j = 0; j < size_; ++j) {
        data_[i][j] = other.data_[i][j];
      }
    }
  }

  Smatrix(Smatrix&& other) noexcept
      : size_(std::move(other.size_)), data_(std::move(other.data_)) {
    other.data_ = nullptr;
    other.size_ = 0;
  }

  Smatrix& operator=(const Smatrix& other) {
    if (this != &other) {
      size_ = other.size_;
      data_ = new double*[size_];
      for (int i = 0; i < size_; ++i) {
        data_[i] = new double[size_];
        for (int j = 0; j < size_; ++j) {
          data_[i][j] = other.data_[i][j];
        }
      }
    }
    return *this;
  }

  Smatrix& operator=(Smatrix&& other) noexcept {
    if (this != &other) {
      data_ = other.data_;
      size_ = other.size_;
    }
    return *this;
  }

  ~Smatrix() {
    if (!size_)
      return;

    for (int i = 0; i < size_; delete[] data_[i++])
      ;

    delete[] data_;
  }

  Smatrix operator+(const Smatrix& other) const {
    if (size_ != other.size_) {
      throw "diff size";
    }
    Smatrix result(size_);

    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        result.data_[i][j] = other.data_[i][j] + data_[i][j];
      }
    }
    return result;
  }

  Smatrix operator+=(const Smatrix& other) {
    if (size_ != other.size_) {
      throw "diff size";
    }
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        data_[i][j] += other.data_[i][j];
      }
    }
    return *this;
  }

  Smatrix operator*(const Smatrix& other) const {
    if (size_ != other.size_) {
      throw "diff size";
    }
    Smatrix result(size_);

    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        result.data_[i][j] = 0;
        for (int k = 0; k < size_;
             result.data_[i][j] += data_[i][k] * other.data_[k++][j])
          ;
      }
    }
    return result;
  }

  Smatrix& operator*=(const Smatrix& other) {
    if (size_ != other.size_) {
      throw "diff size";
    }
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        data_[i][j] = 0;
        for (int k = 0; k < size_;
             data_[i][j] += data_[i][k] * other.data_[k++][j])
          ;
      }
    }
    return *this;
  }

  Smatrix operator*(const double a) const {
    Smatrix result(size_);
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; result.data_[i][j] = a * data_[i][j++])
        ;
    }
    return result;
  }

  Smatrix& operator*=(const double a) {
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; data_[i][j++] *= a)
        ;
    }
    return *this;
  }

  bool operator==(const Smatrix& other) const {
    if (size_ != other.size_) {
      return false;
    }
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        if (data_[i][j] != other.data_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Smatrix& other) const { return !(*this == other); }
};

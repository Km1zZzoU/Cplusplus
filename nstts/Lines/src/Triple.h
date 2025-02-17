

class Triple {
  double value;

public:
  Triple(const double v);

  bool operator==(const Triple& other) const;
  bool operator!=(const Triple& other) const;
};

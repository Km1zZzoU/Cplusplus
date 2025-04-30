class Triple {
  double value;

public:
  Triple(const double v); // Note: const in the type signature of 
                          // trivial values is redundant, cause they copied
                          // Note: also using copy initialization
                          // we can explicitly converts doubles to this class
                          // it can be useful in constructorsfor example

  bool operator==(const Triple& other) const;
  bool operator!=(const Triple& other) const;
};

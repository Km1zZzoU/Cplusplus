
/* RE: nice idea, but why you don't use it?
 * let's be more accurate in comparing doubles
 */
class Triple {
  double value;

public:
  Triple(const double v); // Note: const in the type signature of 
                          // trivial values is redundant, cause they copied

  bool operator==(const Triple& other) const;
  bool operator!=(const Triple& other) const;
};

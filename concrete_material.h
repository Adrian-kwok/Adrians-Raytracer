#ifndef CONCRETE_MAT
#define CONCRETE_MAT

#include "material.h"

// you could make all of these color fields patterns in their own right, that
// would be pretty cool...

// Later.

// all of these classes could be abstracted somewhat to inherit from some "color aggregate class"
// though I don't particularly care to

class striped : public pattern_aggregate {
  bool loop;
  color pattern_at_local(tuple point) const override;

 public:
  striped(std::vector<color> c = std::vector{BLACK, WHITE}, bool loop = false);
  striped(const striped& s);
  striped(striped&& s);
  striped& operator=(const striped& s);
  striped& operator=(striped&& s);

  std::unique_ptr<pattern> clone() const override;

  void set_loop(bool b);

  ~striped() = default;
};

class gradient : public pattern_aggregate {
  bool loop;
  bool ring;

  color pattern_at_local(tuple point) const override;

 public:
  gradient(std::vector<color> c = std::vector{BLACK, WHITE}, bool loop = false,
           bool ring = false);

  std::unique_ptr<pattern> clone() const override;

  void set_loop(bool b);
  void set_ring(bool r);

  ~gradient() = default;
};

// the colors array could be arbitrarily large, it's just that nothing will be done with it 
// past the first two elements of the array
class checker : public pattern_aggregate {
  color pattern_at_local(tuple point) const override;

 public:
  checker(std::vector<color> c = std::vector{BLACK, WHITE});
  
  std::unique_ptr<pattern> clone() const override;

  ~checker() = default;
};

#endif

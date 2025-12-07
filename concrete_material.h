#ifndef CONCRETE_MAT
#define CONCRETE_MAT

#include "material.h"

class striped : public pattern {
  std::vector<color> colors;
  bool loop;
  color pattern_at_local(tuple point) const override;

 public:
  striped(std::vector<color> c = std::vector{BLACK, WHITE});

  std::unique_ptr<pattern> clone() const override;

  const std::vector<color>& get_colors() const;

  void set_loop(bool b);

  void set_colors(const std::vector<color>& c);
  void set_colors(std::vector<color>&& c);

  ~striped() = default;
};

class gradient : public pattern {
  std::vector<color> colors;
  bool loop;
  bool ring;

  color pattern_at_local(tuple point) const override;

 public:
  gradient(std::vector<color> c = std::vector{BLACK, WHITE}, bool loop = false, bool ring = false);

  std::unique_ptr<pattern> clone() const override;

  const std::vector<color>& get_colors() const;

  void set_colors(const std::vector<color>& c);
  void set_colors(std::vector<color>&& c);
  void set_loop(bool b);
  void set_ring(bool r);

  ~gradient() = default;
};

#endif

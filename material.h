#ifndef MAT
#define MAT

#include "ray.h"
#include <algorithm>

class pattern : public obj {
  virtual color pattern_at_local(tuple point) const = 0;
  bool use_global = false;

 public:
  // if used for an object, expects that transformations have already been
  // applied to have this in "local space"
  color pattern_at(tuple point) const;

  void set_global(bool g);

  virtual std::unique_ptr<pattern> clone() const = 0;

  virtual ~pattern() = default;
};

// although this is a concrete class it's useful for creating defaults
class solid_color : public pattern {
  color c;

  color pattern_at_local(tuple point) const override;

 public:
  solid_color(color c);

  std::unique_ptr<pattern> clone() const override;

  void set_color(color c);

  ~solid_color() = default;
};

class material {
  std::unique_ptr<pattern> color_pattern;
  float ambient = 0.1;
  float diffuse = 0.7;
  float specular = 0.9;
  float shininess = 200.0;

  public:

  material(color c = color{1,1,1});
  material(const pattern& p, float ambient, float diffuse, float specular,
           float shininess);

  // big 5 to work with unique ptr
  material(const material& m);
  material& operator=(const material& m);
  material(material&& m);
  material& operator=(material&& m);
  ~material() = default;

  void set_color_pattern(const pattern& p);
  void set_ambient(const float& a);
  void set_diffuse(const float& d);
  void set_specular(const float& sp);
  void set_shininess(const float& sh);

  const pattern& get_color_pattern() const;
  pattern& get_color_pattern();
  //perhaps add a method that returns a pointer to the color pattern (non const)
  const float& get_ambient() const;
  const float& get_diffuse() const;
  const float& get_specular() const;
  const float& get_shininess() const;
};

// the whole point of this class is that it removes
// duplicate code patterns which base themselves off other
// patterns
class pattern_aggregate : public pattern {
  protected:
    std::vector<std::unique_ptr<pattern>> patterns;
    virtual color pattern_at_local(tuple point) const = 0;
  public:
    pattern_aggregate(const pattern_aggregate& other);
    pattern_aggregate(pattern_aggregate&& other);
    pattern_aggregate& operator=(const pattern_aggregate& other);
    pattern_aggregate& operator=(pattern_aggregate&& other);
    ~pattern_aggregate() = default;

    pattern_aggregate(); // creates pattern aggregate with an empty list
    void add_pat(pattern& p);
    void add_pat(pattern&& p);
    pattern& get_pat(int i); // better be in range bub >:(
    pattern* ptr_get_pat(int i);
    void remove_pat(int i); // takes an index to a pattern
    int num_pats() const;
};

#endif

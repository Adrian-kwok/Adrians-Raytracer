#include "light.h"

point_light::point_light(color c = color{1,1,1}): light_col{c} {}
color point_light::intensity() const {return light_col;}
tuple point_light::light_vec(tuple posn) const {return normalize(location() - posn);}

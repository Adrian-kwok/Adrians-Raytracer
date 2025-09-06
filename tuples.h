#ifndef TUPLES
#define TUPLES
#include <math.h>
#include "float_eq.cc"

enum tuple_type {
    POINT,
    VECTOR,
    COLOR
};

struct tuple {
    float x, y, z;
    virtual tuple_type type() = 0;

    tuple(float x, float y, float z);
};

struct tpoint : public tuple {
    tuple_type type() { return tuple_type::POINT;}
    tpoint(float x, float y, float z);
};

struct tvector : public tuple {
    tuple_type type() { return tuple_type::VECTOR;}
    tvector(float x, float y, float z);
};

struct tcolor : public tuple {
    tuple_type type() { return tuple_type::COLOR;}
    tcolor(float x, float y, float z);
};

//const tvector ZEROVEC;

tuple operator +(tuple t1, tuple t2);
tuple operator -(tuple t1, tuple t2);
tuple operator -(tuple t);
tuple operator *(tuple t, float scalar);
// scalar cannot be 0, else 0 vector is returned
tuple operator /(tuple t, float scalar);
bool operator == (tuple t1, tuple t2);

float norm(tvector t);
tvector normalize(tvector t);

float dot(tvector t1, tvector t2);
tvector cross(tvector t1, tvector t2);


#endif




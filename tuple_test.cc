#include <iostream>
#include "tuples.h"

struct projectile {
    tuple pos;  //point
    tuple dir;  //vec
};

struct environment {
    tuple wind; //vec   
    tuple grav; //vec
};

void tick (projectile& p, environment& e) {
    p.pos = p.pos + p.dir;
    p.dir = p.dir + e.wind + e.grav;
}

int main() {
    projectile ball {point(0, 1, 0), normalize(vector(1, 1, 0))};
    environment park {vector(0.1, 0, 0), vector(0, -0.02, 0)};

    while(ball.pos.y > 0) {
        tick(ball, park);
    }
    std::cout << ball.pos.x << std::endl;

}

#include <iostream>
#include "tuples.h"

int main() {
    tuple tp = point(1, 2, 3);
    std::cout << tp.x << std::endl;
    std::cout << tp.y << std::endl;
    std::cout << tp.z << std::endl;
    
    if (tp.type == tuple_type::POINT) {
        std::cout << "Code works!" << std::endl;
    } else {
        std::cout << "Uh oh..." << std::endl;
    }

    tuple tv = vector(1, 2, 3);
    std::cout << tv.x << std::endl;
    std::cout << tv.y << std::endl;
    std::cout << tv.z << std::endl;

    if (tv.type == tuple_type::VECTOR) {
        std::cout << "Code works!" << std::endl;
    } else {
        std::cout << "Uh oh..." << std::endl;
    }

    tuple t = tp + tv;
    std::cout << t.x << std::endl;
    std::cout << t.y << std::endl;
    std::cout << t.z << std::endl;
    if (t.type == tuple_type::POINT) {
        std::cout << "Code works!" << std::endl;
    } else {
        std::cout << "Uh oh..." << std::endl;
    }

    tuple foo = ZEROVEC + t + t;

    std::cout << foo.x << std::endl;
    std::cout << foo.y << std::endl;
    std::cout << foo.z << std::endl;
    if (foo.type == tuple_type::VECTOR) {
        std::cout << "Code works!" << std::endl;
    } else {
        std::cout << "Uh oh..." << std::endl;
    }

    t = point(1, 2, 3);

    foo = foo - t;
    std::cout << foo.x << std::endl;    // 3, 6 , 9
    std::cout << foo.y << std::endl;
    std::cout << foo.z << std::endl;

    foo = -foo;
    std::cout << foo.x << std::endl;    // negative versions
    std::cout << foo.y << std::endl;
    std::cout << foo.z << std::endl;
    foo = foo * (float(1) / float(3));
    std::cout << foo.x << std::endl;    // something close to 1 2 3
    std::cout << foo.y << std::endl;
    std::cout << foo.z << std::endl;
    foo = foo / 0.5;
    std::cout << foo.x << std::endl;    // something close to 2 4 6
    std::cout << foo.y << std::endl;
    std::cout << foo.z << std::endl;
    
    std::cout << (foo == t) << std::endl; // false
    std::cout << (-foo - t == t) << std::endl; // true
}

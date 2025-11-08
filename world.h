#ifndef WORLD
#define WORLD

#include "ray.h"

#include <vector>
#include <memory>

class World {
    // vector of render object pointers
    std::vector<std::unique_ptr<render_obj>> objs;
    std::vector<std::unique_ptr<light>> lights;

    public:
        color bg; // this is probably temporary

        World();
        World(const World& other);
        World(World&& other);
        World& operator=(const World& other);
        World& operator=(World&& other);
        ~World() = default;

        // moves ownership of the pointer to the world
        void add_obj(std::unique_ptr<render_obj> o);
        void add_obj(const render_obj& o);
        render_obj& obj_at(int i);
        render_obj* ptr_obj_at(int i);
        void delete_obj_at(int i);
        int num_obj() const;

        void add_light(std::unique_ptr<light> l);
        void add_light(const light& l);
        light& light_at(int i);
        light* ptr_light_at(int i);
        void delete_light_at(int i);
        int num_light() const;

        color shade_hit(const computation& c) const;
        color color_at(const ray& r) const;
        color background_col() const;
        
        std::vector<intersection> intersect(const ray& r) const;
};


#endif

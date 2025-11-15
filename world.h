#ifndef WORLD
#define WORLD

#include "ray.h"
#include "canvas.h"

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

// should be point, point, vector. though not super important
Matrix view_transform(tuple from, tuple to, tuple up);

class Camera {
    int hsize, vsize;
    double fov;
    double pixel_size;
    double half_height, half_width;
    Matrix transform = identity(TUPLE_SIZE);
    Matrix inverse_transform = identity(TUPLE_SIZE);

    void update_pixel_size();
    public:
        Camera(int h, int v, double fov); // default transform is identity

        int get_hsize() const;
        int get_vsize() const;
        double get_fov() const;
        double get_pixel_size() const;
        const Matrix& get_transform() const;

        void set_hsize(int new_h);
        void set_vsize(int new_v);
        void set_fov(double new_fov);
        void set_transform(const Matrix& m);
        void set_transform(Matrix&& m);
        void add_transform(const Matrix& m);

        ray ray_for_pixel(int h, int v) const;

        Canvas render(const World& w) const;
};


#endif

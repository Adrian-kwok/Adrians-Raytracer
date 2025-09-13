#ifndef CANVAS
#define CANVAS

#include "tuples.h"
#include "color.h"
#include <algorithm>

const color BLACK {0,0,0};

class Canvas {
    private:
    color** image;
    int x_size;
    int y_size;
    // x_size and y_size must always match the actual dimensions of the image!
    // otherwise, memory will leak!

    public:
        // default ctor + big 5
        Canvas(int w, int h);
        ~Canvas();
        
        Canvas(const Canvas& c);
        Canvas(Canvas&& c);
        Canvas& operator= (const Canvas& c);
        Canvas& operator= (Canvas&& c);

        int width() const;
        int height() const;

        color pixel_at(int x, int y) const;
        
        // true: successful write, false: unsuccessful
        bool write_pixel(int x, int y, color c);
};

#endif

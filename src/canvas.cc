#include "canvas.h"
#include <iostream>

// helper functions

std::string compress_color(float i) {
    if (i > 1) {
        return std::to_string(COLORDEPTH);
    } else if (i < 0) {
        return std::string("0");
    } else {
        return std::to_string(int(i * COLORDEPTH));
    }
}

// class functions

Canvas::Canvas(int width, int height)
    : image{nullptr}, x_size{width}, y_size{height} {
  image = new color*[width];
  for (int i = 0; i < width; i++) {
    image[i] = new color[height];
    for (int j = 0; j < height; j++) {
      image[i][j] = BLACK;
    }
  }
}

Canvas::Canvas(std::string filename): image{nullptr}, x_size{0}, y_size{0} {
    std::ifstream ifs {filename};
    std::string tempstr;
    ifs >> tempstr; // getting rid of P3 header
    ifs >> x_size;  // getting width
    ifs >> y_size;  // getting height

    int local_depth;    // getting color depth specified in file
    ifs >> local_depth;

    // copying in image
    image = new color*[x_size];
    for (int i = 0; i < x_size; i++) {
        image[i] = new color[y_size];
    }

    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size; j++) {
            ifs >> image[j][i].r;
            image[j][i].r /= local_depth;
            ifs >> image[j][i].g;
            image[j][i].g /= local_depth;
            ifs >> image[j][i].b;
            image[j][i].b /= local_depth;
        }
    }
    ifs.close();
}

Canvas::~Canvas() {
  if (image != nullptr) {  // move ctor will set this to nullptr
    for (int i = 0; i < x_size; i++) {
      delete[] image[i];
    }
    delete[] image;
  }
}

Canvas::Canvas(const Canvas& c)
    : image{nullptr}, x_size{c.x_size}, y_size{c.y_size} {
  image = new color*[c.x_size];
  for (int i = 0; i < c.x_size; i++) {
    image[i] = new color[c.y_size];
    for (int j = 0; j < c.y_size; j++) {
      image[i][j] = c.image[i][j];
    }
  }
}

Canvas::Canvas(Canvas&& c)
    : image{c.image}, x_size{c.x_size}, y_size{c.y_size} {
  c.image = nullptr;
}

Canvas& Canvas::operator=(const Canvas& c) {
  if (this == &c) {  // checking for self assignment
    return *this;
  }

  if (image != nullptr) {
    for (int i = 0; i < c.x_size; i++) {
      delete image[i];
    }
    delete[] image;
    image = nullptr;
  }

  x_size = c.x_size;
  y_size = c.y_size;
  image = new color*[c.x_size];
  for (int i = 0; i < c.x_size; i++) {
    image[i] = new color[c.y_size];
    for (int j = 0; j < c.y_size; j++) {
      image[i][j] = c.image[i][j];
    }
  }

  return *this;
}

Canvas& Canvas::operator=(Canvas&& c) {
    std::swap(c.image, image);
    std::swap(c.x_size, x_size);
    std::swap(c.y_size, y_size);

    return *this;
}

int Canvas::width() const {
    return x_size;
}

int Canvas::height() const {
    return y_size;
}

color Canvas::pixel_at(int x, int y) const {
    return image[x][y];
}

bool Canvas::write_pixel(int x, int y, color c) {
    if (x >= x_size || y >= y_size || x < 0 || y < 0) {
        return false;
    } else {
        image[x][y] = c;
        return true;
    }
}

void canvas_to_ppm(const Canvas& c, const std::string filename) {
    std::ofstream ofs {filename};
    
    int w = c.width();
    int h = c.height();

    // header
    ofs << "P3" << std::endl;
    ofs << w << " " << h << std::endl;
    ofs << COLORDEPTH << std::endl;

    //image data
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            ofs << compress_color(c.pixel_at(j,i).r) << " ";
            ofs << compress_color(c.pixel_at(j,i).g) << " ";
            ofs << compress_color(c.pixel_at(j,i).b) << " ";
        }
        ofs << std::endl;
    }
    ofs << std::endl;
    ofs.close();
}

#include "canvas.h"

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

Canvas::~Canvas() {
  if (image != nullptr) {  // move ctor will set this to nullptr
    for (int i = 0; i < x_size; i++) {
      delete image[i];
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

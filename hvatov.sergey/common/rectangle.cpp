#include "rectangle.hpp"

#include <stdexcept>

// Class constructor
hvatov::Rectangle::Rectangle(const point_t & center, double w, double h) :
  vertices_({ 
    {
      {center.x - w / 2, center.y + h / 2}, 
      {center.x + w / 2, center.y + h / 2}, 
      {center.x + w / 2, center.y - h / 2}, 
      {center.x - w / 2, center.y - h / 2}
    } 
  })
{
  // check if arguments are invalid
  if (w < 0 || h < 0)
  {
    // if so throw exception
    throw std::invalid_argument("Width and height of the rectangle must be >= 0!");
  }
  // otherwise
  width_ = w;
  height_ = h;
}

// Class constructor
hvatov::Rectangle::Rectangle(double x, double y, double w, double h) :
  Rectangle({x, y}, w, h)
{
}

// Scale method
void hvatov::Rectangle::scale(double k)
{
  // check if argument is invalid
  if (k < 0)
  {
    // throw an exception
    throw std::invalid_argument("Scale coefficient must be >= 0");
  }
  // otherwise scale the figure
  height_ *= k;
  width_ *= k;
  
  // Change the center of the rect
  point_t pos = getPosition();
  for (auto& p : vertices_)
  {
    p = { pos.x + k * (p.x - pos.x), pos.y + k * (p.y - pos.y) };
  }
}

// Rotate method
void hvatov::Rectangle::rotate(double angle) noexcept
{
  // get the position
  point_t cur_pos = getPosition();

  // Convert from degrees to radians
  angle = fromDegToRad(angle);

  // Transform vertices' coordinates
  for (auto& point : vertices_)
  {
    // Change the coordinates to new one
    point = {
      cur_pos.x + (point.x - cur_pos.x) * cos(angle) -
        (point.y - cur_pos.y) * sin(angle), // x = x0 + (x - x0) * cos(a) - (y - y0) * sin(a)
          cur_pos.y + (point.y - cur_pos.y) * cos(angle) +
            (point.x - cur_pos.x) * sin(angle)  // y = y0 + (y - y0) * cos(a) + (x - x0) * sin(a)
    };
  }
}

// Get area method
double hvatov::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

// Get frame rectangle method
hvatov::rectangle_t hvatov::Rectangle::getFrameRect() const noexcept
{
  // Set buffer position
  auto l_v = vertices_[0].x; 
  auto r_v = vertices_[0].x; 
  auto t_v = vertices_[0].y; 
  auto b_v = vertices_[0].y;

  for (const auto& p : vertices_) {
    if (p.x < l_v) {
      l_v = p.x;
    }
    if (p.x > r_v) {
      r_v = p.x;
    }
    if (p.y < b_v) {
      b_v = p.y;
    }
    if (p.y > t_v) {
      t_v = p.y;
    }
  }

  // Retutn new rectangle with new center
  return { { l_v + (r_v - l_v) / 2, b_v + (t_v - b_v) / 2 }, r_v - l_v, t_v - b_v };
}

// Move rect to the point method
void hvatov::Rectangle::move(const point_t & center) noexcept
{
  // Move all veertices of the rectangle
  vertices_[0] = { center.x - width_ / 2, center.y + height_ / 2 };
  vertices_[1] = { center.x + width_ / 2, center.y + height_ / 2 };
  vertices_[2] = { center.x + width_ / 2, center.y - height_ / 2 };
  vertices_[3] = { center.x - width_ / 2, center.y - height_ / 2 };
}

// Move rect by dx and dy method
void hvatov::Rectangle::move(double dx, double dy) noexcept
{
  // move by dx and dy
  for (auto& vert : vertices_)
  {
    vert.x += dx;
    vert.y += dy;
  }
}

// Operator << override
std::ostream& hvatov::operator<<(std::ostream &stream, const Rectangle &rect) {
  // use std::endl
  using std::endl;

  // buffer variable
  rectangle_t r = rect.getFrameRect();

  // write to the stream
  stream << "Rectangle object with following parameters:" << endl
    << "Position of the center: (" << r.pos.x << ";" << r.pos.y << ")" << endl
    << "Coordinates of the vertices: " << endl 
    << "\t(" << rect.vertices_[0].x << ";" << rect.vertices_[0].y << ")" << endl
    << "\t(" << rect.vertices_[1].x << ";" << rect.vertices_[1].y << ")" << endl
    << "\t(" << rect.vertices_[2].x << ";" << rect.vertices_[2].y << ")" << endl
    << "\t(" << rect.vertices_[3].x << ";" << rect.vertices_[3].y << ")" << endl
    << "Width and height of the rectangle are " << rect.width_ << " and " << rect.height_ << endl
    << "Area of the rect: " << rect.getArea() << endl
    << "Rectangle Frame has following parameters:" << endl
    << "\t Position of the center: (" << r.pos.x << ";" << r.pos.x << ")" << endl
    << "\t Width and height are: " << r.width << " and " << r.height << endl;
  return stream;
}

// Get the coordinates of current position method
hvatov::point_t hvatov::Rectangle::getPosition() const noexcept
{
  return getFrameRect().pos;
}

// Get width method
double hvatov::Rectangle::getWidth() const noexcept
{
  return width_;
}

// Get height method
double hvatov::Rectangle::getHeight() const noexcept
{
  return height_;
}

// Get the information of about shape
std::ostream & hvatov::Rectangle::getInfo(std::ostream & stream) const noexcept
{
  // use std::endl
  using std::endl;
  
  // write to the stream
  stream << *this << endl;

  return stream;
}


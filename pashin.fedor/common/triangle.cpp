#include "triangle.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

pashin::Triangle::Triangle(const point_t vertices[3])
{
  for (int i = 0; i < 3; ++i) {
    vertices_[i] = vertices[i];
  }
}

pashin::point_t pashin::Triangle::getCenter() const
{
  return {(vertices_[0].x + vertices_[1].x + vertices_[2].x) / 3,
          (vertices_[0].y + vertices_[1].y + vertices_[2].y) / 3};
}

double pashin::Triangle::getArea() const
{
  return abs((vertices_[0].x * (vertices_[1].y - vertices_[2].y) +
              vertices_[1].x * (vertices_[2].y - vertices_[0].y) +
              vertices_[2].x * (vertices_[0].y - vertices_[1].y)) / 2);
}

pashin::rectangle_t pashin::Triangle::getFrameRect() const
{
  double min_x = vertices_[0].x;
  double max_x = vertices_[0].x;
  double min_y = vertices_[0].y;
  double max_y = vertices_[0].y;
  for (const point_t& vertex: vertices_) {
    if (vertex.x < min_x) {
      min_x = vertex.x;
    } else if (vertex.x > max_x) {
      max_x = vertex.x;
    }
    if (vertex.y < min_y) {
      min_y = vertex.y;
    } else if (vertex.y > max_y) {
      max_y = vertex.y;
    }
  }
  
  return {{(min_x + max_x) / 2, (min_y + max_y) / 2},
          (max_x - min_x), (max_y - min_y)};
}

string pashin::Triangle::getInfo() const
{
  stringstream info;
  
  const point_t& center = getCenter();
  info << "Type: Triangle" << endl
      << "Center coordinates: (" << center.x << "; " << center.y << ")" << endl;
  for (int i = 0; i < 3; ++i) {
    info << "Vertex number " << i + 1 << " coordinates: ("
        << vertices_[i].x << "; " << vertices_[i].y << ")" << endl;
  }
  rectangle_t frame_rect = getFrameRect();
  info << "Area: " << getArea() << endl
      << "Frame Rectangle:" << endl
      << "\t" << "Center coordinates: ("
      << frame_rect.pos.x << "; "
      << frame_rect.pos.y << ")" << endl
      << "\t" << "Width: " << frame_rect.width << endl
      << "\t" << "Height: " << frame_rect.height << endl;
  
  return info.str();
}

void pashin::Triangle::move(double dx, double dy)
{
  for (point_t& vertex: vertices_) {
    vertex.x += dx;
    vertex.y += dy;
  }
}

void pashin::Triangle::move(const point_t& new_center)
{
  const point_t& center = getCenter();
  double dx = new_center.x - center.x;
  double dy = new_center.y - center.y;
  move(dx, dy);
}

void pashin::Triangle::scale(double k)
{
  if (!(k >= 0)) {
    throw invalid_argument("Invalid coefficient");
  }
  
  const point_t& center = getCenter();
  for (point_t& vertex: vertices_) {
    double xc = vertex.x - center.x;
    double yc = vertex.y - center.y;
    vertex.x = center.x + (xc * k);
    vertex.y = center.y + (yc * k);
  }
}

void pashin::Triangle::rotate(double angle)
{
  double angle_in_radians = angle * M_PI / 180;
  const point_t& center = getCenter();
  point_t old_vertex;
  for (point_t& vertex: vertices_) {
    old_vertex.x = vertex.x;
    old_vertex.y = vertex.y;
    vertex.x = center.x + (old_vertex.x - center.x) * cos(angle_in_radians)
                        - (old_vertex.y - center.y) * sin(angle_in_radians);
    vertex.y = center.y + (old_vertex.x - center.x) * sin(angle_in_radians)
                        + (old_vertex.y - center.y) * cos(angle_in_radians);
  }
}

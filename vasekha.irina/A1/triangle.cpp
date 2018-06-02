#include "triangle.hpp"
#include <algorithm>
#include <cmath>

Triangle::Triangle(const point_t & vertex_1, const point_t & vertex_2, const point_t & vertex_3):
  pos_({(vertex_1.x+vertex_2.x+vertex_3.x)/3.0, (vertex_1.y+vertex_2.y+vertex_3.y)/3.0}),
  vertices_({vertex_1,vertex_2,vertex_3})
{}

double Triangle::getArea() const
{
  return std::abs((vertices_[0].x-vertices_[2].x)*(vertices_[1].y-vertices_[2].y)-(vertices_[1].x
    -vertices_[2].x)*(vertices_[0].y-vertices_[2].y))/2.0;
}

rectangle_t Triangle::getFrameRect() const
{
  auto resX = std::minmax({vertices_[0].x,vertices_[1].x,vertices_[2].x});
  auto resY = std::minmax({vertices_[0].y,vertices_[1].y,vertices_[2].y});
  return {{(resX.first+resX.second)/2.0,(resY.first+resY.second)/2.0},resX.second-resX.first,resY.second-resY.first};
}

void Triangle::move(const point_t & point)
{
  move(point.x-pos_.x,point.y-pos_.y);
}

void Triangle::move(const double dx, const double dy)
{
  pos_.x+=dx;
  pos_.y+=dy;
  for(int i=0; i<3; ++i)
  {
    vertices_[i].x+=dx;
    vertices_[i].y+=dy;
  }
}

void Triangle::print(std::ostream & out) const
{
  out << "Triangle: center: (" << pos_.x << "," << pos_.y << "), A: (" << vertices_[0].x << ","
    << vertices_[0].y << "), B: (" << vertices_[1].x << "," << vertices_[1].y << "), C: (" << vertices_[2].x
      << "," << vertices_[2].y << ")" << std::endl;
}


#include "triangle.hpp"
#include <algorithm>
#include <cmath>

vasekha::Triangle::Triangle(const vasekha::point_t & vertex_1,const vasekha::point_t & vertex_2,const vasekha::point_t & vertex_3) noexcept:
  pos_({(vertex_1.x+vertex_2.x+vertex_3.x)/3.0, (vertex_1.y+vertex_2.y+vertex_3.y)/3.0}),
  vertices_({vertex_1,vertex_2,vertex_3})
{}

double vasekha::Triangle::getArea() const noexcept
{
  return std::abs((vertices_[0].x-vertices_[2].x)*(vertices_[1].y-vertices_[2].y)-(vertices_[1].x
    -vertices_[2].x)*(vertices_[0].y-vertices_[2].y))/2.0;
}

vasekha::rectangle_t vasekha::Triangle::getFrameRect() const noexcept
{
  auto resX = std::minmax({vertices_[0].x,vertices_[1].x,vertices_[2].x});
  auto resY = std::minmax({vertices_[0].y,vertices_[1].y,vertices_[2].y});
  return {{(resX.first+resX.second)/2.0,(resY.first+resY.second)/2.0},resX.second-resX.first,resY.second-resY.first};
}

void vasekha::Triangle::move(const vasekha::point_t & point) noexcept
{
  move(point.x-pos_.x,point.y-pos_.y);
}

void vasekha::Triangle::move(const double dx, const double dy) noexcept
{
  pos_.x+=dx;
  pos_.y+=dy;
  for(int i=0; i<3; ++i)
  {
    vertices_[i].x+=dx;
    vertices_[i].y+=dy;
  }
}

void vasekha::Triangle::scale(const double factor)
{
  if(factor<0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  for (int i=0;i<3;i++)
  {
    vertices_[i]={pos_.x+(vertices_[i].x-pos_.x)*factor,pos_.y+(vertices_[i].y-pos_.y)*factor};
  }
}

void vasekha::Triangle::rotate(const double angle) noexcept
{
  const double angle_rad=angle*M_PI/180.0;
  for(int i=0; i<3; ++i)
  {
    vertices_[i]={pos_.x+(vertices_[i].x-pos_.x)*cos(angle_rad)-(vertices_[i].y
      -pos_.y)*sin(angle_rad),pos_.y+(vertices_[i].y-pos_.y)*cos(angle_rad)
        +(vertices_[i].x-pos_.x)*sin(angle_rad)};
  }
}

void vasekha::Triangle::print(std::ostream & out) const noexcept
{
  out << "Triangle: center: (" << pos_.x << "," << pos_.y << "), A: (" << vertices_[0].x << "," 
    << vertices_[0].y << "), B: (" << vertices_[1].x << "," << vertices_[1].y << "), C: (" << vertices_[2].x
      << "," << vertices_[2].y << ")" << std::endl;
}

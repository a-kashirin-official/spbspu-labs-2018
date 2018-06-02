#include "shape.hpp"

void Shape::move(double dx, double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

void Shape::move(const point_t &newcentre)
{
  centre_ = newcentre;
}


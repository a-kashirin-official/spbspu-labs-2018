#ifndef RECTANLGE_HPP
#define RECTANLGE_HPP

#include "shape.hpp"

namespace khodyreva
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t & pos, const double height, const double width);
    double getArea() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & pos) override;
    rectangle_t getFrameRect() const override;
    void scale(const double ratio) override;
    void rotate(double angle) override;
    std::string getName() const override;
  private:
    double width_;
    double height_;
    point_t pos_;
    point_t vertex_[4];
  };
}

#endif

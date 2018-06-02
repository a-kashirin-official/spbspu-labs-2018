#ifndef POLYGON_HPP
#define POLYGON_HPP


#include <memory>
#include <cstdlib>
#include "shape.hpp"
namespace tseptsov
{
  class Polygon : public tseptsov::Shape
  {
  public:
    Polygon(const std::initializer_list < point_t > &pts);
    point_t operator[](std::size_t numb) const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double Ox, double Oy) override;
    void move(const point_t &pos) override;
    void scale(double coef) override;
    void rotate(double deg) override;
    void OutData() const override;
    point_t getCenter() const;
    bool convexity() const;

  private:
    std::size_t count_;
    std::unique_ptr < point_t[] > pts_;
  };
}

#endif

#ifndef POLIGON_HPP
#define POLIGON_HPP

#include <initializer_list>
#include <boost/smart_ptr.hpp>
#include "base-types.hpp"
#include "shape.hpp"

namespace golyshev
{
  class Polygon : public golyshev::Shape
  {
  public:
    Polygon(const std::initializer_list<point_t> &list);
    point_t operator[](size_t index) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double Ox, double Oy) override;
    void move(const point_t &point) override;
    void scale(double coeff) override;
    void rotate(const double angle) override;
    void OutInf() const override;


    size_t getSize() const;
    point_t getCentre() const;
    bool Convex() const;


  private:
    size_t size_;
    boost::shared_array<point_t> points_;
  };
}

#endif

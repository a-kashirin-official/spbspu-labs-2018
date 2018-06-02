#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t &point1, const point_t &pointt2, const point_t &pointt3);
  rectangle_t getFrameRect() const override;
  double getArea() const override;
  void move(const point_t &pos) override;
  void move(const double Ox, const double Oy) override;
  void printInf() override;
private:
  point_t findCenter() const;
  point_t A_;
  point_t B_;
  point_t C_;
  static double getLength(const point_t &point1, const point_t &point2);
};

#endif

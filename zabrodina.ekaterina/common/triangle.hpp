#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace zabrodina
{
  class Triangle : public Shape
  {
  public:
    Triangle(const zabrodina::point_t &point1, const zabrodina::point_t &pointt2, const zabrodina::point_t &pointt3);
    zabrodina::rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const zabrodina::point_t &pos) override;
    void move(const double Ox, const double Oy) override;
    void printInf() const override;
    void scale(const double coefficient) override;
  private:
    zabrodina::point_t findCenter() const;
    zabrodina::point_t A_;
    zabrodina::point_t B_;
    zabrodina::point_t C_;
    static double getLength(const zabrodina::point_t &point1, const zabrodina::point_t &point2);
  };
}

#endif

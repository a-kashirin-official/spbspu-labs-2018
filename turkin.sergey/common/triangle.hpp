//
// Created by 811432 on 05.04.2018.
//
#ifndef A1_TRIANGLE_HPP
#define A1_TRIANGLE_HPP

#include "shape.hpp"
namespace turkin
{
  class Triangle : public turkin::Shape
  {
  public:
    Triangle(const point_t &pos1, const point_t &pos2, const point_t &pos3);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double Ox, double Oy) override;
    void printInfo() override;
    void scale(double k) override;
    void rotate(double angle) override ;
    point_t getCenter() const override ;

  private:
    point_t pos1_;
    point_t pos2_;
    point_t pos3_;
    point_t center_;

  };
}

#endif

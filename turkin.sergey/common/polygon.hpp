

#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <memory>
#include "shape.hpp"

namespace turkin
{
  class Polygon : public turkin::Shape
  {
  public:
    explicit Polygon(const std::unique_ptr<turkin::point_t[]> & array, size_t size);
    turkin::point_t &operator[](unsigned int i) const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double Ox, double Oy) override;
    void printInfo() override;
    void scale(double k) override;
    void rotate(double angle) override;
    point_t getCenter() const override ;
    bool isConvex() const;

  private:
    size_t size_;
    std::unique_ptr<turkin::point_t[]> ver_;

    point_t center_;
  };
}
#endif

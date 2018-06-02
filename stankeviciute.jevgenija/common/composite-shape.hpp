#ifndef COMPOSITESHAPE_HPP_INCLUDED
#define COMPOSITESHAPE_HPP_INCLUDED
#include "shape.hpp"
#include <memory>

namespace stankeviciute
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> &);
    CompositeShape(const CompositeShape &);
    CompositeShape & operator=(const CompositeShape &);
    friend bool stankeviciute::operator==(const CompositeShape &, const CompositeShape &);
    void addShape(const std::shared_ptr<Shape> &);
    std::string getName() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printFeatures() const override {};
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double k) override;
    void rotate(double angle) override;

  private:
    std::unique_ptr <std::shared_ptr<Shape>[]> shapes_;
    size_t size_;
  };

  bool operator==(const CompositeShape &, const CompositeShape &);
}

#endif

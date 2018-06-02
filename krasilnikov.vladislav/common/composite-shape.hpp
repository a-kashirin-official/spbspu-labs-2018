#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace krasilnikov
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape(const std::shared_ptr< Shape > shape);
    CompositeShape(const CompositeShape & rhs);
    ~CompositeShape();
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newPosition) override;
    void move(const double dx, const double dy) override;
    point_t getPosition() const override;
    void scale(const double factor) override;

    int getCount() const;
    void addShape(const std::shared_ptr< Shape > shape);
    void removeShape(const int index);
    void clear();

    void rotate(const double angle) override;

    CompositeShape &operator=(const CompositeShape & rhs);
    std::shared_ptr< krasilnikov::Shape > operator[](const int index) const;

  private:
    std::unique_ptr< std::shared_ptr< Shape > [] >list_;
    int count_;
    double angle_;
  };
}

#endif

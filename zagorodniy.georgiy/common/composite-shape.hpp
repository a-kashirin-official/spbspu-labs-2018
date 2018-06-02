#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace zagorodniy {
  class CompositeShape :
    public Shape {
  public:
    explicit CompositeShape(std::shared_ptr< zagorodniy::Shape > shape);
    ~CompositeShape();
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newCenter) override;
    void move(double dx, double dy) override;
    void scale(double coef) override;

    int getCount() const;
    void addShape(std::shared_ptr< Shape > shape);
    void removeShape(int index);

  private:
    std::unique_ptr< std::shared_ptr < zagorodniy::Shape >[] > list_;
    int count_;
  };
}

#endif

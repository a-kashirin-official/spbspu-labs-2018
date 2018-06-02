#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <string>
#include <vector>

#include "shapes-partition.hpp"
#include "shape.hpp"
#include "array.hpp"

namespace pashin {
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    
    CompositeShape& operator=(const CompositeShape& rhs);
    point_t getCenter() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    std::string getInfo() const override;
    void move(double dx, double dy) override;
    void move(const point_t& new_center) override;
    void scale(double k) override;
    void rotate(double angle) override;
    const detail::Array<Shape*>& getShapes() const;
    const pashin::ShapesPartition& getLayers() const;
    void addShape(Shape* shape);
    void removeShape(Shape* shape);
    
  private:
    double angle_;
    detail::Array<Shape*> shapes_;
    ShapesPartition layers_;
  };
}

#endif  // COMPOSITE_SHAPE_HPP

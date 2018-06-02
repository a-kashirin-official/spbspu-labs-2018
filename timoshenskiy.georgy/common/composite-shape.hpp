//
//  composite-shape.hpp
//  A3
//
//  Created by Георгий Тимошенский on 06.05.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef composite_shape_hpp
#define composite_shape_hpp

#include <sstream>
#include <memory>
#include "shape.hpp"

namespace timoshenskiy
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr < timoshenskiy::Shape > shape);
    CompositeShape(const timoshenskiy::CompositeShape & compositeshape);
    CompositeShape(CompositeShape && compositeShape);

    CompositeShape & operator = (const timoshenskiy::CompositeShape & compositeShape);
    Shape* operator [] (int shapeNumber) const;
    bool operator == (const CompositeShape & compositeShape) const;
    bool operator != (const CompositeShape & compositeShape) const;
  
    double getArea() const override;
    timoshenskiy::rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t &position) override;
    void scale(const double multiplier) override;
    std::string printInformation() const;
    void addShape(std::shared_ptr < timoshenskiy::Shape > shape);
    void deleteShape(const int shapeNumber);
    void deleteAllShapes();

    void rotate(double degrees) override;
    point_t rotatePoint(const point_t &center, const point_t &p, double degrees);

  private:
    std::unique_ptr < std::shared_ptr < timoshenskiy::Shape > [] > shapes_;
    int size_;
    double angle_;
  };
}
#endif

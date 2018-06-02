//
//  shape.hpp
//  
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef shape_hpp
#define shape_hpp

#include "base-types.hpp"

namespace timoshenskiy
{
  class Shape
  {
  public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &position) = 0;
  virtual void move(const double dx , const double dy) = 0;
  virtual void scale(double multiplier) = 0;
  virtual void rotate(double degrees) = 0;
  };
}

#endif 

//
//  shape.hpp
//  A1
//
//  Created by Георгий Тимошенский on 12.03.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef shape_hpp
#define shape_hpp

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default ;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual point_t move(const point_t &position) = 0;
  virtual point_t move(const double dx , const double dy) = 0;
};

#endif

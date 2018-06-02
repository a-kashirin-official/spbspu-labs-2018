//
//  rectangle.hpp
//  A1
//
//  Created by Георгий Тимошенский on 12.03.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle: public Shape
{
public:
  Rectangle (const point_t & pos,const double rectangle_width,const double rectangle_height);
  double getArea() const;
  rectangle_t getFrameRect() const;
  point_t move(const point_t &position );
  point_t move(const double dx, const double dy);
  void printInformation() const;
private:
  point_t pos_;
  double width_, height_ ;
};

#endif

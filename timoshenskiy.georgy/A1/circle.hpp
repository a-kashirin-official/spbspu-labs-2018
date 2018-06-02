//
//  circle.hpp
//  A1
//
//  Created by Георгий Тимошенский on 12.03.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef circle_hpp
#define circle_hpp

#include "shape.hpp"
#include "base-types.hpp"

class Circle :public Shape
{
public:
  Circle(const point_t & pos,const double circle_radius);
  double getArea() const;
  rectangle_t getFrameRect() const;
  point_t move(const point_t &position );
  point_t move(const double dx, const double dy);
  void printInformation() const;
private:
  point_t pos_;
  double radius_;
};

#endif 


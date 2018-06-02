//
//  circle.hpp
// 
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef circle_hpp
#define circle_hpp

#include <sstream>
#include "shape.hpp"

namespace timoshenskiy
{
  class Circle :public Shape
  {
  public:
    Circle(const point_t & pos, const double circle_radius);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t &position);
    void move(const double dx, const double dy);
    void rotate(double /*degrees*/);
    std::string printInformation() const;
    void scale(double multiplier);
  private:
    point_t pos_;
    double radius_;
    double angle_;
  };
}
#endif 

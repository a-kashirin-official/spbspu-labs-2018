//
//  rectangle.hpp
// 
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include <sstream>
#include "shape.hpp"

namespace timoshenskiy
{
  class Rectangle: public Shape
  {
  public:
    Rectangle (const point_t & pos, const double rectangle_width, const double rectangle_height);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t &position);
    void move(const double dx, const double dy);
    void rotate(double degrees);
    std::string printInformation() const;
    void scale(double multiplier);
    double getDistance(const point_t &point1, const point_t &point2) const;
    void getPos();
    std::string printPeaks() const;
  private:
    point_t pos_;
    point_t peaks_[4];
    double angle_;
  };
}
#endif 

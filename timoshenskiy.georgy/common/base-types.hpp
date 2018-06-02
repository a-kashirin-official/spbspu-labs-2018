//
//  base-type.hpp
//
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef base_types_hpp
#define base_types_hpp

namespace timoshenskiy
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
}
#endif

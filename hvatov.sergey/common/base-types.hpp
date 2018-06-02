#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>

namespace hvatov
{
  // Point structure
  struct point_t {
    // X coordinate
    double x;
    // Y coordinate
    double y;
  };

  // Rectangle structure
  struct rectangle_t {
    // Position of the center
    point_t pos;
    // Width
    double width;
    // Height
    double height;
  };

  // Utility function to coonvert from degrees to radians
  inline constexpr double fromDegToRad(double degrees) noexcept
  { 
    return degrees * M_PI / 180; 
  }

  // New name for long type
  template <typename T>
  using ArrayType = std::unique_ptr<std::shared_ptr<T>[]>;
}
#endif //BASE_TYPES_HPP


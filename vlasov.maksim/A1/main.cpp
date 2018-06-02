#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Rectangle pryamoug(15.0, 15.0, {15.0, 15.0});
  Circle krujok(2.0, {60.0, 55.0});
  std::cout << "\n";
  std::cout << "Rectangle stats" << std::endl;
  pryamoug.showPosition();
  std::cout << pryamoug.getArea() << std::endl;
  pryamoug.move(45.0, 60.0);
  std::cout << "\n";
  std::cout << "Updated stats" << std::endl;
  std::cout << "moved by " << "x = " << 45.0 << ", y = " << 60.0 << std::endl;
  pryamoug.showPosition();
  std::cout << "\n";
  pryamoug.move({15.0, 20.0});
  std::cout << "Updated stats" << std::endl;
  std::cout << "moved to " << "x = " << 15.0 << ", y = " << 20.0 << std::endl;
  pryamoug.showPosition();
  std::cout << "\n";
  std::cout << "Circle stats" << std::endl;
  krujok.showPosition();
  std::cout << krujok.getArea() << std::endl;
  std::cout << "circle's frame (x, y, side length): ";
  std::cout << krujok.getFrameRect().pos.x << ", " << krujok.getFrameRect().pos.y<< ", "<< krujok.getFrameRect().height <<std::endl;
  krujok.move(45.0, 60.0);
  std::cout << "\n";
  std::cout << "Updated stats" << std::endl;
  std::cout << "moved by " << "x = " << 45.0 << ", y = " << 60.0 << std::endl;
  krujok.showPosition();
  std::cout << "\n";
  krujok.move({15.0, 20.0});
  std::cout << "Updated stats" << std::endl;
  std::cout << "moved to " << "x = " << 15.0 << ", y = " << 20.0 << std::endl;
  krujok.showPosition();
  return 0;
}

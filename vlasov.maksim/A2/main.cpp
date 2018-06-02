#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace vlasov;

int main()
{
  Rectangle pryamoug(15, 16, { 15,15 });
  Circle krujok(2.1, { 60,55 });
  std::cout << "\n";
  std::cout << "Rectangle stats" << std::endl;
  pryamoug.showPosition();
  std::cout << "Rectangle's dimensions: " << pryamoug.getFrameRect().width;
  std::cout << " " << pryamoug.getFrameRect().height << std::endl;
  std::cout << "Rectangle's area: " << pryamoug.getArea() << std::endl;
  pryamoug.move(45, 60);
  std::cout << "\n";
  std::cout << "Updated stats" << std::endl;
  std::cout << "Moved by " << "x = " << 45 << ", y = " << 60 << std::endl;
  pryamoug.showPosition();
  std::cout << "\n";
  pryamoug.move({ 15,20 });
  std::cout << "Updated stats" << std::endl;
  std::cout << "Moved to " << "x = " << 15 << ", y = " << 20<<std::endl;
  pryamoug.showPosition();
  std::cout << "\n";
  pryamoug.scale(9.0);
  std::cout << "Updated stats" << std::endl;
  std::cout << "Rectangle's dimensions scaled 9 times: " << pryamoug.getFrameRect().width;
  std::cout << " " << pryamoug.getFrameRect().height << std::endl;
  std::cout << "Area after scaling: " << pryamoug.getArea() << std::endl;
  std::cout << "\n";
  std::cout << "Circle stats" << std::endl;
  krujok.showPosition();
  std::cout << "Circle's radius: " << krujok.getFrameRect().width/2 << std::endl;
  std::cout << "Circle's area: " << krujok.getArea() << std::endl;
  std::cout << "Circle's frame (x, y, side length): ";
  std::cout << krujok.getFrameRect().pos.x << ", " << krujok.getFrameRect().pos.y<< ", "<< krujok.getFrameRect().height<<std::endl;
  krujok.move(45, 60);
  std::cout << "\n";
  std::cout << "Updated stats" << std::endl;
  std::cout << "Moved by " << "x = " << 45 << ", y = " << 60 << std::endl;
  krujok.showPosition();
  std::cout << "\n";
  krujok.move({ 15,20 });
  std::cout << "Updated stats" << std::endl;
  std::cout << "Moved to " << "x = " << 15 << ", y = " << 20 << std::endl;
  krujok.showPosition();
  std::cout << "\n";
  krujok.scale(15.0);
  std::cout << "Updated stats" << std::endl;
  std::cout << "Circle's radius scaled 15 times: " << krujok.getFrameRect().width/2 << std::endl;
  std::cout << "Area after scaling: " << krujok.getArea() << std::endl;
  std::cout << "\n";
  return 0;
}

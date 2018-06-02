#include <iostream>
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  std::cout << "Creating a rectangle:\n";
  std::cout << "Center: x = 6, y = 10;\n";
  std::cout << "Width = 20, Height = 30\n";

  point_t point = {6.0, 10.0};
  Rectangle rec(point, 20.0, 30.0);

  std::cout << "Area = " << rec.getArea() << "\n";

  std::cout << "Frame rectangle:" << "\n";
  rectangle_t f_rec = rec.getFrameRect();
  std::cout << "Center of Frame rectangle: x = " << f_rec.pos.x << ", y = " << f_rec.pos.y << "\n";
  std::cout << "Width = " << f_rec.width << ", Height = " << f_rec.height << "\n";

  std::cout << "Move to new position (x = 1, y = 8):\n";
  point_t new_pos = {1.0, 8.0};
  rec.move(new_pos);

  std::cout << "The movement of the offset by dx = 4 and dy = 9\n\n";
  rec.move(4.0,9.0);

  std::cout << "Creating a circle:\n";
  std::cout << "Center: x = 7, y = 14;\n";
  std::cout << "Radius = 9\n";

  point = {7.0, 14.0};
  Circle cir(point, 9.0);

  std::cout << "Area = " << cir.getArea() << "\n";

  std::cout << "Frame circle:" << "\n";
  f_rec = cir.getFrameRect();
  std::cout << "Center of Frame circle: x = " << f_rec.pos.x << ", y = " << f_rec.pos.y << "\n";
  std::cout << "Width = " << f_rec.width << ", Height = " << f_rec.height << "\n";

  std::cout << "Move to new position (x = 3, y = 12):\n";
  new_pos = {3.0, 12.0};
  cir.move(new_pos);

  std::cout << "The movement of the offset by dx = 5 and dy = 4\n";
  cir.move(5.0,4.0);
  return 0;
}

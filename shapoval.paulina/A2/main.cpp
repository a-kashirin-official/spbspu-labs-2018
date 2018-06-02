#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

void printFrameRect(const shapoval::Shape & object)
{
  const shapoval::rectangle_t frame = object.getFrameRect();
  std::cout << "Centre: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Height: " << frame.height << std::endl;
  std::cout << "Width: " << frame.width << std::endl;
}

void printArea(const shapoval::Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
}

int main()
{
  shapoval::Circle new_circle({0,0}, 10);

  std::cout << "CIRCLE  " << std::endl;
  printArea(new_circle);
  std::cout << "~~Start circleFrameRect parameters~~ " << std::endl;
  printFrameRect(new_circle);
  std::cout << "~~Expand the circle in 5 times~~ " << std::endl;
  new_circle.scale(5);
  printFrameRect(new_circle);
  printArea(new_circle);
  new_circle.move(10, 20);
  std::cout << "~~Move to x, y~~ " << std::endl;
  printFrameRect(new_circle);
  new_circle.move({20, 10});
  std::cout << "~~Move to point~~ " << std::endl;
  printFrameRect(new_circle);

  shapoval::Rectangle new_rectangle({0,0}, 10, 20);

  try
  {
    std::cout << "RECTANGLE  " << std::endl;
    printArea(new_rectangle);
    std::cout << "~~Start rectangle parameters~~ " << std::endl;
    printFrameRect(new_rectangle);
    std::cout << "~~Expand the rectangle in 5 times~~ " << std::endl;
    new_rectangle.scale(5);
    printFrameRect(new_rectangle);
    printArea(new_rectangle);
    new_rectangle.move(10, 20);
    std::cout << "~~Move to x, y~~" << std::endl;
    printFrameRect(new_rectangle);
    new_rectangle.move({20, 10});
    std::cout << "~~Move to point~~" << std::endl;
    printFrameRect(new_rectangle);
  }
  catch(std::invalid_argument & b)
  {
    std::cerr << b.what() << std::endl;
  }
  return 0;
}

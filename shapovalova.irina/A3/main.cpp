#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

void print(const shapovalova::rectangle_t & figure, const double area)
{
  std::cout << "Frame Rects of composite shape:" << std::endl;
  std::cout << "Area: " << area << std::endl;
  std::cout << "Coordinates: (" << figure.pos.x << ";" << figure.pos.y << ")" << std::endl;
  std::cout << "Height: " << figure.height << std::endl;
  std::cout << "Width: " << figure.width << std::endl;
  std::cout << std::endl;
}

int main()
{
  try
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{10.0, 5.0}, 20.0, 40.0}));
    shapovalova::CompositeShape List(rectanglePtr);
    shapovalova::rectangle_t frameRect = List.getFrameRect();
    double tmpArea = List.getArea();
    print(frameRect, tmpArea);

    std::shared_ptr<shapovalova::Shape> circlePtr =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({20.0, 10.0}, 80.0));
    List.add(circlePtr);
    frameRect = List.getFrameRect();
    tmpArea = List.getArea();
    print(frameRect, tmpArea);

    List.remove(1);
    frameRect = List.getFrameRect();
    tmpArea = List.getArea();
    print(frameRect, tmpArea);

    List.scale(2.0);
    frameRect = List.getFrameRect();
    tmpArea = List.getArea();
    print(frameRect, tmpArea);

    List.move({55.0, 77.0});
    frameRect = List.getFrameRect();
    tmpArea = List.getArea();
    print(frameRect, tmpArea);
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}

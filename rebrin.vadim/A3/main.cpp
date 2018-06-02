#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace rebrin;

int main()
{
  try
  {
    Rectangle my_rectangle({8.0, 8.0, {1.0, 0.0}});
    Circle my_circle({-5.0, 3.0}, 5.0);
    CompositeShape my_composite_shape(std::make_shared < rebrin::Rectangle > (my_rectangle));

    my_composite_shape.addShape(std::make_shared < rebrin::Circle > (my_circle));

    std::cout << "Center: (" << my_composite_shape.getFrameRect().pos.x << "; "
              << my_composite_shape.getFrameRect().pos.y << ")"<<std::endl;
    std::cout << "Width: " << my_composite_shape.getFrameRect().width << std::endl;
    std::cout << "Height: " << my_composite_shape.getFrameRect().height << std::endl;
    std::cout << "Area: " << my_composite_shape.getArea() << std::endl;

    my_composite_shape.scale(0.5);
    my_composite_shape.move({0.0, 0.0});

    std::cout << "Scale and move" << std::endl;
    std::cout << "Center: (" << my_composite_shape.getFrameRect().pos.x << "; "
              << my_composite_shape.getFrameRect().pos.y << ")"<<std::endl;
    std::cout << "Width: " << my_composite_shape.getFrameRect().width << std::endl;
    std::cout << "Height: " << my_composite_shape.getFrameRect().height << std::endl;
    std::cout << "Area: " << my_composite_shape.getArea() << std::endl;

    my_composite_shape.removeShape(0);

    std::cout << "Remove 0th shape" << std::endl;
    std::cout << "Center: (" << my_composite_shape.getFrameRect().pos.x << "; "
              << my_composite_shape.getFrameRect().pos.y << ")"<<std::endl;
    std::cout << "Width: " << my_composite_shape.getFrameRect().width << std::endl;
    std::cout << "Height: " << my_composite_shape.getFrameRect().height << std::endl;
    std::cout << "Area: " << my_composite_shape.getArea() << std::endl;


    my_composite_shape.clear();

  }
  catch (std::exception & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}

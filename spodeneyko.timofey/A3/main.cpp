#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr);
    spodeneyko::rectangle_t shapeFrameRect = comp_shape.getFrameRect();
    std::cout << "Composite Shape:" << std::endl;
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
    std::cout << "Area of Composite Shape = " << comp_shape.getArea() << std::endl;
    std::cout << std::endl;

    std::shared_ptr<spodeneyko::Shape> circlePtr
        = std::make_shared<spodeneyko::Circle>(spodeneyko::Circle(5.0, {10.0, 10.0}));
    comp_shape.addShape(circlePtr);
    shapeFrameRect = comp_shape.getFrameRect();
    std::cout << "Composite Shape:" << std::endl;
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
    std::cout << "Area of Composite Shape after adding new shape = " << comp_shape.getArea() << std::endl;
    std::cout << std::endl;

    comp_shape.removeShape(0);
    shapeFrameRect = comp_shape.getFrameRect();
    std::cout << "Composite Shape:" << std::endl;
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
    std::cout << "Area of Composite Shape after deleting first shape = " << comp_shape.getArea() << std::endl;
    std::cout << std::endl;

    comp_shape.scale(2.0);
    shapeFrameRect = comp_shape.getFrameRect();
    std::cout << "Composite Shape:" << std::endl;
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
    std::cout << "Area of scaled Composite Shape = " << comp_shape.getArea() << std::endl;
    std::cout << std::endl;

    comp_shape.move({256.0, 128.0});
    shapeFrameRect = comp_shape.getFrameRect();
    std::cout << "Composite Shape:" << std::endl;
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
    std::cout << "Area of moved Composite Shape = " << comp_shape.getArea() << std::endl;
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  catch (std::out_of_range & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}

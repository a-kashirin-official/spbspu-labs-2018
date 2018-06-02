#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr1
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr1);

    std::shared_ptr<spodeneyko::Shape> rectPtr2
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {150.0, 256.0}}));
    comp_shape.addShape(rectPtr2);
    
    std::shared_ptr<spodeneyko::Shape> circlePtr
        = std::make_shared<spodeneyko::Circle>(spodeneyko::Circle(10.0, {130.0, 256.0}));
    comp_shape.addShape(circlePtr);

    spodeneyko::rectangle_t frameRect = comp_shape.getFrameRect();
    std::cout << "Composite Shape: " << std::endl;
    std::cout << "Coords: (" << frameRect.pos.x << ";" << frameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << frameRect.width << " Height = " << frameRect.height << std::endl;
    std::cout << "Area of Composite Shape = " << comp_shape.getArea() << std::endl;
    std::cout << std::endl;

    comp_shape.rotate(90.0);
    frameRect = comp_shape.getFrameRect();
    std::cout << "Composite Shape: " << std::endl;
    std::cout << "Coords: (" << frameRect.pos.x << ";" << frameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << frameRect.width << " Height = " << frameRect.height << std::endl;
    std::cout << "Area of Composite Shape after rotating = " << comp_shape.getArea() << std::endl;
    std::cout << std::endl;

    spodeneyko::MatrixShape matrix_shape(rectPtr1);
    matrix_shape.addShape(rectPtr2);
    matrix_shape.addShape(circlePtr);
    std::cout << "Matrix of shapes:" << std::endl;
    matrix_shape.print();
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

#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

void print(const shapovalova::rectangle_t & figure, const double area)
{
  std::cout << "Frame Rects of composite shape:" << std::endl;
  std::cout << "Area: " << area << std::endl;
  std::cout << "Coordinates: (" << figure.pos.x << ";" << figure.pos.y << ")" << std::endl;
  std::cout << "Width: " << figure.width << std::endl;
  std::cout << "Height: " << figure.height << std::endl;
  std::cout << std::endl;
}

int main()
{
  try
  {
    std::shared_ptr<shapovalova::Shape> rect1 =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{2.0, 2.0}, 8.0, 4.0}));
    std::shared_ptr<shapovalova::Shape> rect2 =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{0.0, 8.0}, 2.0, 6.0}));
    std::shared_ptr<shapovalova::Shape> circ1 =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({9.0, 6.0}, 4.0));
    std::shared_ptr<shapovalova::Shape> circ2 =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({4.0, 7.0}, 4.0));
    shapovalova::CompositeShape List(rect1);
    List.add(rect2);
    List.add(circ1);
    List.add(circ2);
    shapovalova::rectangle_t frameRect = List.getFrameRect();
    double tmpArea = List.getArea();
    print(frameRect, tmpArea);

    std::cout << "Scale 2.0: " << std::endl;
    List.scale(2.0);
    frameRect = List.getFrameRect();
    tmpArea = List.getArea();
    print(frameRect, tmpArea);

    std::cout << "Move to (10.0, 15.0):" << std::endl;
    List.move({10.0, 15.0});
    frameRect = List.getFrameRect();
    tmpArea = List.getArea();
    print(frameRect, tmpArea);

    std::cout << "Rotate 90: " << std::endl;
    List.rotate(90);
    frameRect = List.getFrameRect();
    tmpArea = List.getArea();
    print(frameRect, tmpArea);

    shapovalova::Matrix matrix1(rect1);
    matrix1.addShape(rect2);
    matrix1.addShape(circ1);
    matrix1.addShape(circ2);
    matrix1.print();

  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}

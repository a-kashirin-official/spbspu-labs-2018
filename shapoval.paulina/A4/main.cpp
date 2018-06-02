#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

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
  try{
    shapoval::Circle new_circle({0,0}, 10);

    std::cout << "CIRCLE  " << std::endl;
    std::cout << "~~Start circleFrameRect parameters~~ " << std::endl;
    printArea(new_circle);
    printFrameRect(new_circle);
    std::cout << "~~Expand the circle in 2 times~~ " << std::endl;
    new_circle.scale(2);
    printArea(new_circle);
    printFrameRect(new_circle);
    std::cout << "~~Rotate on 90 degrees~~ " << std::endl;
    new_circle.rotate(90);
    printFrameRect(new_circle);
    std::cout << "~~Move to x, y~~ " << std::endl;
    new_circle.move(10, 20);
    printFrameRect(new_circle);
    std::cout << "~~Move to point~~ " << std::endl;
    new_circle.move({50, 0});
    printFrameRect(new_circle);

    shapoval::Rectangle new_rectangle({10,20}, 40, 20);

    std::cout << "RECTANGLE  " << std::endl;
    std::cout << "~~Start rectangle parameters~~ " << std::endl;
    printArea(new_rectangle);
    printFrameRect(new_rectangle);
    std::cout << "~~Expand the rectangle in 2 times~~ " << std::endl;
    new_rectangle.scale(2);
    printArea(new_rectangle);
    printFrameRect(new_rectangle);
    std::cout << "~~Rotate on 90 degrees~~ " << std::endl;
    new_rectangle.rotate(90);
    printFrameRect(new_rectangle);
    printArea(new_rectangle);
    std::cout << "~~Move to x, y~~" << std::endl;
    new_rectangle.move(10, 20);
    printFrameRect(new_rectangle);
    std::cout << "~~Move to point~~" << std::endl;
    new_rectangle.move({10, 20});
    printFrameRect(new_rectangle);

    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);


    std::cout << "COMPOSITE SHAPE  " << std::endl;
    std::cout << "~~Start composite shape parameters~~" << std::endl;
    printArea(new_compositeshape);
    printFrameRect(new_compositeshape);
    std::cout << "~~Add rectangle in composite shape~~" << std::endl;
    new_compositeshape.addShape(new_rectanglePtr);
    printArea(new_compositeshape);
    printFrameRect(new_compositeshape);
    std::cout << "~~Expend composite shape in 2 times~~" << std::endl;
    new_compositeshape.scale(2);
    printArea(new_compositeshape);
    printFrameRect(new_compositeshape);
    std::cout << "~~Rotate on 90 degrees~~ " << std::endl;
    new_compositeshape.rotate(90);
    printFrameRect(new_compositeshape);
    std::cout << "~~Remove circle from composite shape~~" << std::endl;
    new_compositeshape.removeShape(1);
    printArea(new_compositeshape);
    printFrameRect(new_compositeshape);
    std::cout << "~~Delete all shapes~~" << std::endl;
    new_compositeshape.deleteShapes();
    printArea(new_compositeshape);
    printFrameRect(new_compositeshape);

    shapoval::Rectangle new_rectangle2({70,70}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr2 = std::make_shared <shapoval::Rectangle> (new_rectangle2);

    shapoval::Matrix new_matrix(new_circlePtr);
    new_matrix.addShape(new_rectanglePtr);
    new_matrix.addShape(new_rectanglePtr2);

    std::cout << "MATRIX  " << std::endl;
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer1 = new_matrix[0];
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer2 = new_matrix[1];

    if (new_layer1[0] == new_circlePtr)
    {
      std::cout << "First layer [1] -- CIRCLE" << std::endl;
    }
    if (new_layer1[1] == new_rectanglePtr2)
    {
      std::cout << "First layer [2] -- RECTANGLE #2" << std::endl;
    }
    if (new_layer2[0] == new_rectanglePtr)
    {
      std::cout << "Second layer [1] -- RECTANGLE #1" << std::endl;
    }
  } catch(std::invalid_argument & f) {
    std::cerr << f.what() << std::endl;
  } catch(std::out_of_range & f) {
    std::cerr << f.what() << std::endl;
  } catch(...) {
    std::cerr << "Exeption was found!!" << std::endl;
  }

  return 0;
}

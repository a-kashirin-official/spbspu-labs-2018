
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <boost/shared_array.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace zhukova;

int main()
{
  try
  {
    std::cout << "Composite Shape" << std::endl;

    std::shared_ptr<Shape> rect_ptr { new Rectangle( { 0.0, 0.0 }, 13.0, 17.0 ) };
    CompositeShape compShape( rect_ptr );

    std::cout << "Composite Shape was initialized by rectangle that has width = 13, height = 17 and center in point (0, 0)."
        << std::endl;

    std::cout << "Composite Shape's frame rectangle width is " << std::fixed << std::setprecision(2) << compShape.getFrameRect().width
        << ", height is " << compShape.getFrameRect().height << std::endl;


    std::cout << "Adding circle. Its radius = 11 and its center is in (7, 7)." << std::endl;

    std::shared_ptr<Shape> circle_ptr{ new Circle( { 7.0, 7.0 }, 11.0 ) };
    compShape.addElement( circle_ptr );

    std::cout << "Composite Shape's frame rectangle width is " << compShape.getFrameRect().width << ", height is "
        << compShape.getFrameRect().height << std::endl;

    std::cout << "Area before scaling was " << compShape.getArea() << std::endl;
    compShape.scale(3.0);
    std::cout << "Area after scaling is " << compShape.getArea() << std::endl;


    std::cout << "Copy Constructor" << std::endl;

    CompositeShape copyCompShape(compShape);

    copyCompShape.move( { 0, 0 } );
    rectangle_t rec = compShape.getFrameRect();
    std::cout << "compShape " << rec.pos.x << "  " << rec.pos.y << std::endl;

    rec = copyCompShape.getFrameRect();
    std::cout << "copyCompShape " << rec.pos.x << "  " << rec.pos.y << std::endl;

    
    std::cout << "Copy assignment operator" << std::endl;
    copyCompShape = compShape;

    rec = compShape.getFrameRect();
    std::cout << "compShape " << rec.pos.x << "  " << rec.pos.y << std::endl;

    rec = copyCompShape.getFrameRect();
    std::cout << "copyCompShape " << rec.pos.x << "  " << rec.pos.y << std::endl;
    copyCompShape.move( { 0, 0 } );

    rec = compShape.getFrameRect();
    std::cout << "compShape " << rec.pos.x << "  " << rec.pos.y << std::endl;

    rec = copyCompShape.getFrameRect();
    std::cout << "copyCompShape " << rec.pos.x << "  " << rec.pos.y << std::endl;
  }
  catch (std::invalid_argument &exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }

  return 0;
}

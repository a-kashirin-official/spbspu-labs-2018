
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <boost/shared_array.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace zhukova;

int main()
{

  try
  {
    std::shared_ptr<Shape> rect_ptr{ new Rectangle({ 5.0, 5.0 }, 5.0, 5.0) };
    CompositeShape compShape(rect_ptr);

    rect_ptr = std::shared_ptr<Shape>{ new Rectangle({ 6.0, 6.0 }, 5.0, 5.0) };
    compShape.addElement(rect_ptr);

    rect_ptr = std::shared_ptr<Shape>{ new Rectangle({ 30.0, 30.0 }, 5.0, 5.0) };
    compShape.addElement(rect_ptr);

    Matrix * M = new Matrix(compShape);

    std::cout << M->getInfo() << std::endl;

    std::cout << std::endl << "Matrix element [0][1]" << std::endl;
    rectangle_t rec = (*M)[{0, 1}]->getFrameRect();
    std::cout << "\tcenter is in (" << rec.pos.x << ", "<< rec.pos.y << " )" << std::endl;

    std::cout << std::endl << "Matrix element [0][1]" << std::endl;
    rec = (*M)[0][1]->getFrameRect();
    std::cout << "\tcenter is in (" << rec.pos.x << ", " << rec.pos.y << " )" << std::endl;
 
    Matrix M2 (*M);

    delete M;

    std::cout << std::endl << "Validity of pointers check" << std::endl;
    std::cout << M2.getInfo() << std::endl;
    std::cout << std::endl;

    std::cout << "New composite shape" << std::endl;
    std::shared_ptr<Shape> rect_ptr2{ new Rectangle({ 5.0, 5.0 }, 5.0, 5.0) };
    CompositeShape compShape2(rect_ptr2);

    rect_ptr2 = std::shared_ptr<Shape>{ new Rectangle({ -5.0, -5.0 }, 6.0, 6.0) };
    compShape2.addElement(rect_ptr2);

    rec = compShape2[0]->getFrameRect();
    std::cout << "compShape2[0] has center in (" << rec.pos.x << ", " << rec.pos.y << " )" << std::endl;
    rec = compShape2[1]->getFrameRect();
    std::cout << "compShape2[1] has center in (" << rec.pos.x << ", " << rec.pos.y << " )" << std::endl;

    compShape2.rotate(180);

    std::cout << "\tComposite shape rotation check (180 degrees)" << std::endl;
    rec = compShape2[0]->getFrameRect();
    std::cout << "compShape2[0] has center in (" << rec.pos.x << ", " << rec.pos.y << " )" << std::endl;
    rec = compShape2[1]->getFrameRect();
    std::cout << "compShape2[1] has center in (" << rec.pos.x << ", " << rec.pos.y << " )" << std::endl;
 
  }
  catch (std::invalid_argument &exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }
  catch (std::bad_alloc &exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unexpected exception" << std::endl;
    return 1;
  }
  
  return 0;
}

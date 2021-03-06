#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"



void testOfShape(dudina::Shape & cObject)
{
  std::cout << "Shape test:" << std::endl;
  cObject.printInformation();
  std::cout << "Area of figure:" << cObject.getArea() << std::endl;
  std::cout << "Rectangle frame:" << std::endl;
  std::cout << " Center: {" << cObject.getFrameRect().pos.x << ";" << cObject.getFrameRect().pos.y << "}" << std::endl;
  std::cout << " Width:" << cObject.getFrameRect().width << std::endl;
  std::cout << " Height:" << cObject.getFrameRect().height << std::endl;

  cObject.move({ 5,2 });
  std::cout << "After move to {5,2}:" << std::endl;
  std::cout << "Rectangle frame:" << std::endl;
  std::cout << " Center: {" << cObject.getFrameRect().pos.x << ";" << cObject.getFrameRect().pos.y << "}" << std::endl;
  std::cout << " Width:" << cObject.getFrameRect().width << std::endl;
  std::cout << " Height:" << cObject.getFrameRect().height << std::endl;

  cObject.move(5, 2);
  std::cout << "After move on x=5 and y=2:" << std::endl;
  std::cout << "Rectangle frame:" << std::endl;
  std::cout << " Center: {" << cObject.getFrameRect().pos.x << ";" << cObject.getFrameRect().pos.y << "}" << std::endl;
  std::cout << " Width:" << cObject.getFrameRect().width << std::endl;
  std::cout << " Height:" << cObject.getFrameRect().height << std::endl;

  cObject.scale(2);
  std::cout << "After scale:" << std::endl;
  std::cout << "Area after scale:" << cObject.getArea() << std::endl;
  std::cout << "Rectangle frame:" << std::endl;
  std::cout << " Center: {" << cObject.getFrameRect().pos.x << ";" << cObject.getFrameRect().pos.y << "}" << std::endl;
  std::cout << " Width:" << cObject.getFrameRect().width << std::endl;
  std::cout << " Height:" << cObject.getFrameRect().height << std::endl;


}


int main()
{
  try 
  {
    dudina::Rectangle rect({ 2.0, 3.0 }, 4, 5);
    dudina::Circle circl({ 2.0, 3.0 }, 4);
    dudina::Triangle triangl({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });

    testOfShape(rect);
    testOfShape(circl);
    testOfShape(triangl);

  }
  catch (const std::invalid_argument & e) 
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}


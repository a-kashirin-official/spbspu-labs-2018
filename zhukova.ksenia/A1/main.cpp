
#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  std::cout << "Rectangle" << std::endl;
  Rectangle rect({ 0.0, 0.0 }, 13.0, 17.0);
  Shape *ptr = &rect;
  ptr->printParameters();
  ptr->getArea();

  std::cout << "FrameRect width is " << ptr->getFrameRect().width << ". FrameRect height is " << ptr->getFrameRect().height << std::endl <<  std::endl;

  ptr->move(31.0, 37.0);
  ptr->printParameters();

  ptr->move({ 31.0, 37.0 });
  ptr->printParameters();


  std::cout << "Circle" << std::endl;
  Circle circ({ 7.0, 7.0 }, 11.0);
  ptr = &circ;
  ptr->printParameters();
  ptr->getArea();

  std::cout << "FrameRect width is " << ptr->getFrameRect().width << ". FrameRect height is " << ptr->getFrameRect().height << std::endl <<  std::endl;

  ptr->move(51.0, 51.0);
  ptr->printParameters();

  ptr->move({ 1.0, 1.0 });
  ptr->printParameters();

  return 0;
}

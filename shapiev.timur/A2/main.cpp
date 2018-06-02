#include <iostream>
#include "shape.hpp"
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"



void resultIs ( shapiev::Shape &s){
  std::cout << "Area is " << s.getArea() << std::endl;
  shapiev::rectangle_t r = s.getFrameRect();
  std::cout << "Frame rectangle:" << std::endl;
  std::cout << "  Width is " << r.width << std::endl;
  std::cout << "  Hight is " << r.height << std::endl;
  std::cout << "  Center is in (" << r.pos.x << ", " << r.pos.y << ')' << std::endl;
}

int main()
{
  shapiev::Rectangle rect(3.5, 4.8, {4.3, 3.4});

  rect.printRect();
  resultIs(rect);
  std::cout << std::endl;
  std::cout << "Rectangle to point (25,10)" << std::endl;
  rect.move({25,10});
  rect.printRect();
  std::cout << std::endl;
  std::cout << "dx = 15 dy = 5" << std::endl;
  rect.move(15,5);
  rect.printRect();
  std::cout << std::endl;
  std::cout << "scaling for 3" << std::endl;
  rect.scale(3.0);
  rect.printRect();

  rect.printRect();
  resultIs(rect);
  std::cout << std::endl;
  std::cout << "Rectangle to point (25,10)" << std::endl;
  rect.move({25,10});
  rect.printRect();
  std::cout << std::endl;
  std::cout << "dx = 15 dy = 5" << std::endl;
  rect.move(15,5);
  rect.printRect();
  std::cout << std::endl;
  std::cout << "scaling for 3" << std::endl;
  rect.scale(3.0);
  rect.printRect();

  std::cout << std::endl;
  std::cout << std::endl;

  shapiev::Circle circ({5.9, 7.1}, 3.0);

  circ.printCircle();
  resultIs(circ);
  std::cout << std::endl;
  std::cout << "Circle to point (20,10)" << std::endl;
  circ.move({20,10});
  circ.printCircle();
  std::cout << std::endl;
  std::cout << "dx = 10 dy = 5" << std::endl;
  circ.move(10,5);
  circ.printCircle();
  std::cout << std::endl;
  std::cout << "scaling for 4" << std::endl;
  circ.scale(4.0);
  circ.printCircle();

  circ.printCircle();
  resultIs(circ);
  std::cout << std::endl;
  std::cout << "Circle to point (20,10)" << std::endl;
  circ.move({20,10});
  circ.printCircle();
  std::cout << std::endl;
  std::cout << "dx = 10 dy = 5" << std::endl;
  circ.move(10,5);
  circ.printCircle();
  std::cout << std::endl;
  std::cout << "scaling for 4" << std::endl;
  circ.scale(4.0);
  circ.printCircle();

  std::cout << std::endl;
  return 0;
}

//
//  main.cpp
//  A3
//
//  Created by Георгий Тимошенский on 06.05.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//
#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace timoshenskiy;

int main()
{
  Rectangle rect1({2.0, 2.0}, 2.0, 2.0);
  Rectangle rect2({6.0, 4.0}, 2.0, 2.0);
  Circle circle1({10.0, 12.0}, 10.0);
  Circle circle2({1.0, 10.0}, 10.0);
  std::shared_ptr < Shape > pRect1 = std::make_shared < Rectangle > (rect1);
  std::shared_ptr < Shape > pRect2 = std::make_shared < Rectangle > (rect2);
  std::shared_ptr < Shape > pCircle1 = std::make_shared < Circle > (circle1);
  std::shared_ptr < Shape > pCircle2 = std::make_shared < Circle > (circle2);
  CompositeShape compositeShape(pRect1);
  
  std::cout << "First shape (Rectangle): " << std::endl;
  std::cout << rect1.printInformation();
  
  std::cout << "Second shape (Rectangle): " << std::endl;
  std::cout << rect2.printInformation();
  
  std::cout << "Third shape (Circle): " << std::endl;
  std::cout << circle1.printInformation();
  
  std::cout << "Fourth shape (Circle): " << std::endl;
  std::cout << circle2.printInformation();
  
  std::cout << "Composite shape with first shape:" << std::endl << std::endl;
  std::cout << compositeShape.printInformation();
  
  std::cout << "Second shape was added:" << std::endl << std::endl;
  compositeShape.addShape(pRect2);
  std::cout << compositeShape.printInformation();
  
  std::cout << "Third shape was added:" << std::endl << std::endl;
  compositeShape.addShape(pCircle1);
  std::cout << compositeShape.printInformation();
  
  std::cout << "Fourth shape was added:" << std::endl << std::endl;
  compositeShape.addShape(pCircle2);
  std::cout << compositeShape.printInformation();
  
  std::cout << "Scale(3.0)" << std::endl << std::endl;
  compositeShape.scale(3.0);
  std::cout << compositeShape.printInformation();
  std::cout << "Move composite shape to (15, 20)" << std::endl << std::endl;
  compositeShape.move({25.0, 40.0});
  std::cout << compositeShape.printInformation();
  std::cout << "Delete shape (3)" << std::endl << std::endl;
  compositeShape.deleteShape(3);
  std::cout << compositeShape.printInformation();
  std::cout << "Delete shape (2)" << std::endl << std::endl;
  compositeShape.deleteShape(2);
  std::cout << compositeShape.printInformation();
  std::cout << "Delete all shapes" << std::endl << std::endl;
  compositeShape.deleteAllShapes();
  std::cout << compositeShape.printInformation();
  return 0;
}

//
//  main.cpp
//  A1
//
//  Created by Георгий Тимошенский on 12.03.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//
#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

using namespace timoshenskiy;

int main()
{
  Rectangle r({ 0.0, 1.0 }, 10.0, 14.0);
  Rectangle * rectangle = &r;
  rectangle->getFrameRect();
  std::cout << "The Initial Rectangle: " << std::endl;
  std::cout << rectangle->printInformation();
  rectangle->move({ 1.0, 2.0 });
  rectangle->getFrameRect();
  std::cout << "After moving in (1,2): " << std::endl;
  std::cout << rectangle->printInformation();
  rectangle->move(1.0, 0.0);
  rectangle->getFrameRect();
  std::cout << "After moving to (1,0): " << std::endl;
  std::cout << rectangle->printInformation();
  double multiplierR = 2.0;
  std::cout << "After scaling by " << multiplierR << ":" << std::endl;
  rectangle->scale(multiplierR);
  std::cout << rectangle->printInformation();
  
  Circle c({ 1.0, 0.0 }, 10.0);
  Circle * circle=&c;
  circle->getFrameRect();
  std::cout << "The Initial Circle: " << std::endl;
  std::cout << circle->printInformation();
  circle->move({ 5.0, 7.0 });
  circle->getFrameRect();
  std::cout << "After moving in (5,7): " << std::endl;
  std::cout << circle->printInformation();
  circle->move(5.0, 8.0);
  circle->getFrameRect();
  std::cout << "After moving to (5,8): " << std::endl;
  std::cout << circle->printInformation();
  double multiplierC = 3.0;
  std::cout << "After scaling by " << multiplierC << ":" << std::endl;
  circle->scale(multiplierC);
  std::cout << circle->printInformation();
  
  return 0;
}


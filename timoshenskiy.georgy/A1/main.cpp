//
//  main.cpp
//  A1
//
//  Created by Георгий Тимошенский on 12.03.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//
#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"//


int main()
{ 
  Rectangle r({2, 3},10, 14);
  Rectangle * rectangle = &r;
  rectangle->getFrameRect();
  std::cout << "The Initial Rectangle: " << std::endl;
  rectangle->printInformation();
  rectangle->move({1, 2});
  rectangle->getFrameRect();
  std::cout << "After moving in (1,2): " << std::endl;
  rectangle->printInformation();
  rectangle->move(1, 0);
  rectangle->getFrameRect();
  std::cout << "After moving to (1,0): " << std::endl;
  rectangle->printInformation();
  
  
  
  Circle c({5, 6}, 10);
  Circle * circle=&c;
  circle->getFrameRect();
  std::cout << "The Initial Circle: " << std::endl;
  circle->printInformation();
  circle->move({5, 7});
  circle->getFrameRect();
  std::cout << "After moving in (5,7): " << std::endl;
  circle->printInformation();
  circle->move(5, 8);
  circle->getFrameRect();
  std::cout << "After moving to (5,8): " << std::endl;
  circle->printInformation();
  return 0;
}

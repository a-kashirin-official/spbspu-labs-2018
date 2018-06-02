#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

using std::endl;

// Test function
void transformObject(hvatov::Shape& obj)
{
  // transform object
  // move object to the point with
  // coordinates (330, 330) and
  // scale object 5 times 
  obj.move({ 300, 300 });
  obj.move(30, 30);
  obj.scale(5);
}

// Test function for Circle object
void testObject(hvatov::Circle & obj)
{
  std::cout << "Circle before transformations:" << endl << obj << endl;
  transformObject(obj);
  std::cout << "Circle after transformations: " << endl << obj << endl;
}

// Test function for Rectangle object
void testObject(hvatov::Rectangle & obj)
{
  std::cout << "Rectangle before transformations:" << endl << obj << endl;
  transformObject(obj);
  std::cout << "Rectangle after transformations: " << endl << obj << endl;
}

// Main method
int main()
{
  // try following
  try
  {
    // buffer rectangle variable
    hvatov::Rectangle rect{ { 30, 30 }, 30, 30 };
    // buffer circle variable
    hvatov::Circle circle{ { 130, 130 }, 30 };

    // use test function to test the objects:
    testObject(rect);
    testObject(circle);
  }
  // catch the exception of invalid_argument
  catch (const std::exception& e)
  {
    // inform user about error and return 1
    std::cout << e.what();
    return 1;
  }
  // if all successful return 0
  return 0;
}


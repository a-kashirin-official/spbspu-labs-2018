#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

// using endline
using std::endl;

// Test function
void transformObject(hvatov::Shape& obj)
{
  // transform object
  // move object to the point with
  // coordinates (330, 330)
  obj.move({ 300, 300 });
  obj.move(30, 30);
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

// Main method of the program
int main()
{
  // try following
  try
  {
    // buffer rectangle variable
    hvatov::Rectangle rect{ { 30, 30 }, 30, 30 };
    // buffer circle variable
    hvatov::Circle circle{ { 130, 130 }, 30 };

    // buffer empty container
    hvatov::CompositeShape cmp;

    // fill conatiner
    cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Rectangle{100, 100, 100, 100}));
    cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Rectangle{ 120, 120, 120, 120 }));
    cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Circle{ 130, 130, 130}));

    // change [0] item of container
    std::shared_ptr<hvatov::Shape> s = std::make_shared<hvatov::Circle>(circle);
    cmp[0] = s;

    // output container
    std::cout << cmp;

    // delete [0] item of container
    cmp.deleteElement(0);
    std::cout << cmp;

    // clear container
    cmp.clear();
    std::cout << cmp;

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


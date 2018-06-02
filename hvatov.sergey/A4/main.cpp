#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using std::endl;

// Test function
void transformObject(hvatov::Shape& obj)
{
  // transform object
  // move object to the point with
  // coordinates (330, 330)
  obj.move({ 300, 300 });
  obj.move(30, 30);
  obj.scale(2);
  obj.rotate(90);
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

// Test function for matrix
void testMatrix()
{
  // buffer shapes
  std::shared_ptr< hvatov::Shape > rect1(new hvatov::Rectangle(100, 100, 30, 30)),
    rect2(new hvatov::Rectangle(30, 30, 30, 30)),
    rect3(new hvatov::Rectangle(45, 45, 30, 30)),
    rect4(new hvatov::Rectangle(45, 45, 30, 30));
  std::shared_ptr< hvatov::Shape > circ(new hvatov::Circle(100, 100, 1000));

  // buffer matrix
  hvatov::Matrix m = {rect1, rect3, rect4, rect2};

  // output matrix
  std::cout << m;

  m.clear();

  // buffer composite shape
  hvatov::CompositeShape cmp;
  // fill conatiner
  cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Rectangle{ 1000, 1000, 100, 100 }));
  cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Rectangle{ 10, 10, 60, 60 }));
  cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Circle{ 130, 130, 130 }));

  m.addElement(cmp);

  hvatov::Layer l = m.getLayer(1);

  std::cout << m << std::endl;
  std::cout << "Fisrt layer: " << l;

  // Set array of shapes
  hvatov::ArrayType<hvatov::Shape> arr(new std::shared_ptr<hvatov::Shape>[4]);
  arr[0] = rect1;
  arr[1] = rect2;
  arr[2] = rect3;
  arr[3] = rect4;

  hvatov::Matrix m1(arr, 4);

  std::cout << m1;
}

// Test function for composite shapes
void testCompShapes()
{
  // buffer empty container
  hvatov::CompositeShape cmp;

  std::cout << "\n\n\nTesting composite shape:\n\n";

  // fill conatiner
  cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Rectangle{100, 100, 100, 100}));
  cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Rectangle{120, 120, 120, 120 }));
  cmp.addElement(std::shared_ptr<hvatov::Shape>(new hvatov::Circle{130, 130, 130}));

  // change [0] item of container
  std::shared_ptr<hvatov::Shape> s(new hvatov::Circle{ 100, 100, 100 });
  cmp[0] = s;

  // output container
  std::cout << cmp;

  // delete [0] item of container
  cmp.deleteElement(0);
  std::cout << cmp;

  // clear container
  cmp.clear();
  std::cout << cmp;
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
    std::cout << "\n\n\nTesting other objects:\n\n";
    testObject(rect);
    testObject(circle);

    // Test matrix
    testMatrix();

    // Test Composite shape
    testCompShapes();
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


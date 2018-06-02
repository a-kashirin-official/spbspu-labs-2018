#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main()
{
    
    // create Rectangle
    pristup::Rectangle rectangle({5.0, 4.0, {3.0, 7.0}});
    pristup::Shape *shape = &rectangle;
    std::cout << "rectangle:" << std::endl;
    std::cout << "area before scaling: " << shape -> getArea() << std::endl;
    
    // scaling Rectangle
    shape -> scale(2.0);
    std::cout << "area after scaling: " << shape -> getArea() << std::endl;
    std::cout << std::endl;
      
    // create Circle
    pristup::Circle circle(6.0, {12.0, 12.0});
    shape = &circle;
    std::cout << "circle:" << std::endl;
    std::cout << "area before scaling: " << shape -> getArea() << std::endl;
    
    // scaling Circle
    shape -> scale(3.0);
    std::cout << "area after scaling: " << shape -> getArea() << std::endl;
    std::cout << std::endl;

    // create Triangle
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    shape = &triangle;
    std::cout << "triangle:" << std::endl;
    std::cout << "area before scaling: " << shape -> getArea() << std::endl;
    
    // scaling Circle
    shape -> scale(4.0);
    std::cout << "area after scaling: " << shape -> getArea() << std::endl;
    std::cout << std::endl;
    
  return 0;
}


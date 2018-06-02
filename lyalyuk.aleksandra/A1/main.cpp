#include <iostream>

#include "triangle.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"

int main()
{
    // create Rectangle
    Rectangle rectangle({5.0, 4.0, { 3.0, 7.0 }});
    Shape *shape = &rectangle;
    
    std::cout << "RECTANGLE" << std::endl;
    shape->print();
    std::cout << "move along Ox by " << 4
    << " and Oy by " << 9 << std::endl;
    shape->move(4, 9);
    shape->print();
    std::cout << "move to the point (" << 3
    << ";" << 5 << ")" << std::endl;
    shape->move({3, 5});
    shape->print();
    std::cout << std::endl;
    
    // create Circle
    Circle circle(6.0, { 3.0, 3.0 });
    shape = &circle;
    
    std::cout << "CIRCLE" << std::endl;
    shape->print();
    std::cout << "move along Ox by " << 4
    << " and Oy by " << 9 << std::endl;
    shape->move(4, 9);
    shape->print();
    std::cout << "move to the point (" << 3
    << ";" << 5 << ")" << std::endl;
    shape->move({3, 5});
    shape->print();
    std::cout << std::endl;
    
    // create Triangle
    Triangle triangle({ 3.0, 6.0 }, { 4.0, 4.0 }, { 7.0, 5.0 });
    shape = &triangle;
    
    std::cout << "TRIANGLE" << std::endl;
    shape->print();
    std::cout << "move along Ox by " << 4
    << " and Oy by " << 9 << std::endl;
    shape->move(4, 9);
    shape->print();
    std::cout << "move to the point (" << 3
    << ";" << 5 << ")" << std::endl;
    shape->move({3, 5});
    shape->print();
    std::cout << std::endl;
    
    return 0;
}



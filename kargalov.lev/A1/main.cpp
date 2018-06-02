#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>


void testShape(Shape &myShape)
{
    std::cout << "Area: " << myShape.getArea() << "\n";
    std::cout << "Get FrameRect.\n";
    std::cout << "height: " << myShape.getFrameRect().height << "\n";
    std::cout << "width: " << myShape.getFrameRect().width << "\n";
    std::cout << "Ox: "<< myShape.getFrameRect().pos.x << "\n";
    std::cout << "Oy: "<< myShape.getFrameRect().pos.y << "\n";
    myShape.move({100, 20});
    std::cout << "Move to new point: \n";
    std::cout << "Ox: " << myShape.getFrameRect().pos.x << "\n";
    std::cout << "Oy: " << myShape.getFrameRect().pos.y << "\n";
    myShape.move(23, 11);
    std::cout << "Shift by axes: \n";
    std::cout << "Ox: " << myShape.getFrameRect().pos.x << "\n";
    std::cout << "Oy: " << myShape.getFrameRect().pos.y << "\n";
}

int main()
{
    Rectangle myRectangle({1, 23, {10, 16}});
    Circle myCircle({24, 7}, 9);
    
    std::cout << "Test Rectangle\n";
    testShape(myRectangle);
    std::cout << "\n";
    std::cout << "Test Circle\n";
    testShape(myCircle);
    
    return 0;
}

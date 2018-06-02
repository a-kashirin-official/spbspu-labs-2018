
#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

void printInfo(const Shape & object)
{
    std::cout << "Area: " << object.getArea() << std::endl;
    const rectangle_t frame = object.getFrameRect();
    std::cout << "Frame for object:" << std::endl;
    std::cout << "\tMiddle of frame: " << frame.pos.x << ", " << frame.pos.y << std::endl;
    std::cout << "\tWidth of frame:" << frame.width << std::endl;
    std::cout << "\tHeight of frame" << frame.height << std::endl;
}

int main()
{
    Circle circle{ { 5.32, 27.63 }, 10.01 };
    Rectangle rectangle{ { 25.04, 6.12 }, 7.13, 4.82 };
    
    std::cout << "Circle:" << std::endl;
    printInfo(circle);
    circle.move( 2.45 , 6.16 );
    printInfo(circle);
    circle.move( { 52.90, 73.21 } );
    printInfo(circle);
    
    std::cout << "Rectangle:" << std::endl;
    printInfo(rectangle);
    rectangle.move( -5.23 , 19.08 );
    printInfo(rectangle);
    rectangle.move( { 3.03, 21.17 } );
    printInfo(rectangle);
    
    return 0;
}



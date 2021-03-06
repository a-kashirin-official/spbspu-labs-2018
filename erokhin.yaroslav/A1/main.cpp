#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
    point_t point = {50, 50};
    Rectangle rect(point, 3, 2);

    std::cout << "The area of rectangle is " << rect.getArea() << std::endl;
    std::cout << "The Frame of rectangle: height = " << rect.getFrameRect().height;
    std::cout << std::endl << "width = " << rect.getFrameRect().width << std::endl;
    std::cout << "At point (" << rect.getFrameRect().pos.x << ", ";
    std::cout << rect.getFrameRect().pos.y << ")" << std::endl;
    std::cout << "Changing location..." << std::endl;
    rect.move(60.5, 55.5);
    std::cout << "Rectangle at (" << rect.getFrameRect().pos.x << ", ";
    std::cout << rect.getFrameRect().pos.y << ")" << std::endl;

    Circle circ(point, 5);

    std::cout << "The area of circle is " << circ.getArea() << std::endl;
    std::cout << "The Frame rectangle of circle: height = " << circ.getFrameRect().height;
    std::cout << std::endl << "width = " << circ.getFrameRect().width << std::endl;
    std::cout << "At point (" <<  circ.getFrameRect().pos.x << ", ";
    std::cout << circ.getFrameRect().pos.y << ")" << std::endl;
    std::cout << "Changing location..." << std::endl;
    point = {777.7, 999.1};
    circ.move(point);
    std::cout << "Circle at (" << circ.getFrameRect().pos.x << ", ";
    std::cout << circ.getFrameRect().pos.y << ")" << std::endl;

    return 0;
}

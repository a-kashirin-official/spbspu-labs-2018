#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void showShapeDetails (Shape & shape1)
{
    std::cout << "Area:" << shape1.getArea() << std::endl;
    std::cout << "Frame rectangle: x = " << shape1.getFrameRect().pos.x << ", y = " << shape1.getFrameRect().pos.y <<
    ", height = " << shape1.getFrameRect().height << ", width = " << shape1.getFrameRect().width << std::endl;
    shape1.move({0 ,0 });
    std::cout << "Moved to (0, 0)" << std::endl;
    shape1.move(20, 30);
    std::cout << "Moved for 20 in x and for 30 in y" << std::endl;
    std::cout << "Frame rectangle: x = " << shape1.getFrameRect().pos.x << ", y = " << shape1.getFrameRect().pos.y <<
    ", height = " << shape1.getFrameRect().height << ", width = " << shape1.getFrameRect().width << std::endl;
}

int main()
{
    Circle circle1({1,0}, 11);
    std::cout << "circle1:" << std::endl;
    showShapeDetails(circle1);

    Rectangle rect1({1,1}, 3, 4);
    std::cout << "rect1:" << std::endl;
    showShapeDetails(rect1);

    Triangle triangle1({0,0}, {1,0}, {0,1});
    std::cout << "triangle1:" << std::endl;
    showShapeDetails(triangle1);

    std::cout << "Done" << std::endl;
    return 0;
}

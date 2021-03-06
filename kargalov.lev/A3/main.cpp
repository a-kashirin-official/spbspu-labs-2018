#include <iostream>
#include <memory>
#include <stdexcept>

#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

using namespace kargalov;

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
    std::cout << "height: " << myShape.getFrameRect().height << "\n";
    std::cout << "width: " << myShape.getFrameRect().width << "\n";
    
    myShape.move(23, 11);
    std::cout << "Shift by axes: \n";
    std::cout << "Ox: " << myShape.getFrameRect().pos.x << "\n";
    std::cout << "Oy: " << myShape.getFrameRect().pos.y << "\n";
    std::cout << "height: " << myShape.getFrameRect().height << "\n";
    std::cout << "width: " << myShape.getFrameRect().width << "\n";
    
     myShape.scale(2);
     std::cout << "Scale\n";
     std::cout << "Area: " << myShape.getArea() << "\n";
     std::cout << "height: " << myShape.getFrameRect().height << "\n";
     std::cout << "width: " << myShape.getFrameRect().width << "\n";
}

int main()
{
    Rectangle myRectangle({5, 2, {5.5, 5}});
    Circle myCircle({4.0, 2.0}, 3.0);
    auto ptrRect = std::make_shared<Rectangle>(myRectangle);
    auto ptrCirc = std::make_shared<Circle>(myCircle);
    CompositeShape myCompSh(ptrRect);
    CompositeShape emptyComp;
    myCompSh.addShape(ptrCirc);

    
    std::cout << "Test Composite\n";
    testShape(myCompSh);
    std::cout << "\n";
    
    std::cout << "Test Composite (remove)\n";
    myCompSh.removeShape(1);
    testShape(myCompSh);
    std::cout << "\n";
    
    std::cout << "Test Rectangle\n";
    testShape(myRectangle);
    std::cout << "\n";
    
    std::cout << "Test Circle\n";
    testShape(myCircle);
    
    std::cout << "Test Empty CompositeShape";
    
    testShape(emptyComp);
    

    
    return 0;
}

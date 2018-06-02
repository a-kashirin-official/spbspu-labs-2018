#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
    erokhin::point_t point = {50, 50};
    try {
        erokhin::Rectangle rect(point, 3, 2);

        std::cout << "The area of rectangle is " << rect.getArea() << std::endl;
        std::cout << "The Frame of rectangle: height = " << rect.getFrameRect().height;
        std::cout << std::endl << "width = " << rect.getFrameRect().width << std::endl;
        std::cout << "At point (" << rect.getFrameRect().pos.x << ", ";
        std::cout << rect.getFrameRect().pos.y << ")" << std::endl;
        std::cout << "Changing location..." << std::endl;
        rect.move(60.5, 55.5);
        std::cout << "Rectangle at (" << rect.getFrameRect().pos.x << ", ";
        std::cout << rect.getFrameRect().pos.y << ")" << std::endl;
        std::cout << "Changing scale..." << std::endl;
        rect.scale(10);
        std::cout << "The Frame of rectangle: height = " << rect.getFrameRect().height;
        std::cout << std::endl << "width = " << rect.getFrameRect().width << std::endl;
        std::cout << "The area of rectangle is " << rect.getArea() << std::endl;

        erokhin::Circle circ(point, 5);

        std::cout << "The area of circle is " << circ.getArea() << std::endl;
        std::cout << "The Frame rectangle of circle: height = " << circ.getFrameRect().height;
        std::cout << std::endl << "width = " << circ.getFrameRect().width << std::endl;
        std::cout << "At point (" << circ.getFrameRect().pos.x << ", ";
        std::cout << circ.getFrameRect().pos.y << ")" << std::endl;
        std::cout << "Changing location..." << std::endl;
        point = {777.7, 999.1};
        circ.move(point);
        std::cout << "Circle at (" << circ.getFrameRect().pos.x << ", ";
        std::cout << circ.getFrameRect().pos.y << ")" << std::endl;
        std::cout << "Changing scale..." << std::endl;
        circ.scale(5);
        std::cout << "The Frame rectangle of circle: height = " << circ.getFrameRect().height;
        std::cout << std::endl << "width = " << circ.getFrameRect().width << std::endl;
        std::cout << "The area of circle is " << circ.getArea() << std::endl;

        point = {10, 10};
        erokhin::point_t point1 = {0, 0};
        erokhin::Rectangle rect1(point, 6, 4);
        erokhin::Circle circ1(point1, 5);
        std::shared_ptr <erokhin::Shape> ptrrect1 = std::make_shared <erokhin::Rectangle> (rect1);
        std::shared_ptr <erokhin::Shape> ptrcirc1 = std::make_shared <erokhin::Circle> (circ1);
        erokhin::CompositeShape composite;
        composite.move(5, 5);
        std::cout << composite.getArea() << ' ' << composite.getFrameRect().width << ' ' << composite.getFrameRect().height;
        std::cout << ' ' << composite.getFrameRect().pos.x << ' ' << composite.getFrameRect().pos.y << std::endl;
        composite.add(ptrrect1);
        std::cout << composite.getArea() << ' ' << composite.getFrameRect().width << ' ' << composite.getFrameRect().height;
        std::cout << ' ' << composite.getFrameRect().pos.x << ' ' << composite.getFrameRect().pos.y << std::endl;
        composite.add(ptrcirc1);
        std::cout << composite.getArea() << ' ' << composite.getFrameRect().width << ' ' << composite.getFrameRect().height;
        std::cout << ' ' << composite.getFrameRect().pos.x << ' ' << composite.getFrameRect().pos.y << std::endl;
        composite.move(-7, 8);
        composite.scale(2);
        std::cout << composite.getArea() << ' ' << composite.getFrameRect().width << ' ' << composite.getFrameRect().height;
        std::cout << ' ' << composite.getFrameRect().pos.x << ' ' << composite.getFrameRect().pos.y << std::endl;
        composite.move(point1);
        std::cout << ' ' << composite.getFrameRect().pos.x << ' ' << composite.getFrameRect().pos.y << std::endl;
        erokhin::CompositeShape composite2(ptrrect1);
        std::cout << composite2.getArea();
    }
    catch(const std::invalid_argument &e)
    {
        std::cerr << "error: invalid argument(s): " << e.what();
        return 1;
    }
    return 0;
}

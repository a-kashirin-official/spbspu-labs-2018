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
    // moving along OX by 3 and OY by 4
    shape->move(3, 4);
    // moving to the point (9;3)
    shape->move({9, 3});
    
    // create Circle
    Circle circle(6.0, { 3.0, 3.0 });
    shape = &circle;
    // moving along OX by 5 and OY by 2
    shape->move(5, 2);
    // moving to the point (1;6)
    shape->move({1, 6});
    
    // create Triangle
    Triangle triangle({ 3.0, 6.0 }, { 4.0, 4.0 }, { 7.0, 5.0 });
    shape = &triangle;
    // moving along OX by 4 and OY by 9
    shape->move(4, 9);
    // moving to the point (2;5)
    shape->move({2, 5});
    
    return 0;
}



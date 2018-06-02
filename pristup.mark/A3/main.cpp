#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

int main()
{
    
    pristup::Rectangle rectangle({5.0, 10.0, {50.0, 100.0}});
    pristup::Shape * r = &rectangle;
    pristup::CompositeShape comp_shape(r);
    
    pristup::Circle circle(6.0, {12.0, 12.0});
    pristup::Shape * c = &circle;
    comp_shape.addShape(c);
    
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    pristup::Shape * t = &triangle;
    comp_shape.addShape(t);
    
    std::cout<< comp_shape.getArea() << "\n";
    
    comp_shape.move({100.0, 50.0});
    std::cout<< comp_shape.getArea() << "\n";
    
    comp_shape.move(30.0, 40.0);
    comp_shape.scale(2.0);
    std::cout<< comp_shape.getArea() << "\n";
    
    comp_shape.delShape(0);
    
    return 0;
}


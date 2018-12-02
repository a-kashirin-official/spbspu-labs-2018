#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include <iostream>
#include <memory>

using namespace kashirin;

int main()
{
  Rectangle rect(2 , 2, { 0, 1 });
  Circle circ(1 , { 2 , 2 });
  Triangle trian( { 2, 0 }, { 0, 0 }, { 3, 3 });
  try
  {
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    std::shared_ptr <Shape> trianPtr = std::make_shared <Triangle> (trian);
    CompositeShape comp(rectPtr);

    std::cout << "CompositeShape" << std::endl;
    std::cout << "Area of rect= " << rect.getArea() << std::endl;
    std::cout << "Area of comp= " << comp.getArea() << std::endl;

    comp.addShape(circPtr);
    std::cout << "add circ" << std::endl;
    std::cout << "Area of rect,circ= " << rect.getArea() << "  " << circ.getArea() << std::endl;
    std::cout << "Area of comp= " << comp.getArea() << std::endl;

    comp.addShape(trianPtr);
    std::cout << "add trian" << std::endl;
    std::cout << "Area of rect+circ+trian= " << rect.getArea() + circ.getArea() + trian.getArea() << std::endl;
    std::cout << "Area of comp= " << comp.getArea() << std::endl;
    std::cout << "frameRect " << comp.getFrameRect().width << " " << comp.getFrameRect().height << " " << comp.getFrameRect().pos.x << " " << comp.getFrameRect().pos.y << std::endl;

    comp.move(-1, -1);
    std::cout << "move(-1,-1)" << std::endl;
    std::cout << "frameRect " << comp.getFrameRect().width << " " << comp.getFrameRect().height << " " << comp.getFrameRect().pos.x << " " << comp.getFrameRect().pos.y << std::endl;

    comp.scale(2);
    std::cout << "scale(2)" << std::endl;
    std::cout << "frameRect " << comp.getFrameRect().width << " " << comp.getFrameRect().height << " " << comp.getFrameRect().pos.x << " " << comp.getFrameRect().pos.y << std::endl;
    std::cout << "Area " << comp.getArea() << std::endl;
    
    comp.removeFigure(2);
    std::cout << "remove circ" << std::endl;
    std::cout << "Area= " << comp.getArea() << std::endl;
    
    comp.removeAll();
    std::cout << "remove All" << std::endl;
    std::cout << "Area= " << comp.getArea() << std::endl;
  }
  catch(const std::invalid_argument &e) {
    std::cerr << e.what() <<std::endl;
    return 1;
  }
  return 0;
}

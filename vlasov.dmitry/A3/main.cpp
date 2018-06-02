#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace vlasov;

int getRectInfo(Rectangle objrect)
{
  std::cout << "Rectangle height: " << objrect.getFrameRect().height << " ";
  std::cout << " , Width: " << objrect.getFrameRect().width << " ";
  std::cout << " and center(x,y): " << objrect.getFrameRect().pos.x << " ";
  std::cout << "," << objrect.getFrameRect().pos.y << std::endl;
  std::cout << "Rectangle's area: " << objrect.getArea() << std::endl;
  return 0;
};
int getCircInfo(Circle objcircle)
{
  std::cout << "Circle limit for height: " << objcircle.getFrameRect().height << " ";
  std::cout << " , limit for width: " << objcircle.getFrameRect().width << " ";
  std::cout << " and center(x,y)" << objcircle.getFrameRect().pos.x << " ";
  std::cout << "," << objcircle.getFrameRect().pos.y << std::endl;
  std::cout << "Circle's area: " << objcircle.getArea() << std::endl;
  return 0;
}

int main()
{
  try
  {
    vlasov::Rectangle objrect({5, 11, 3, 6});
    getRectInfo(objrect);
    vlasov::Circle objcircle(3, {1, 1});
    getCircInfo(objcircle);
    std::shared_ptr<vlasov::Shape> rectPtr = std::make_shared<vlasov::Rectangle>(objrect);
    std::shared_ptr<vlasov::Shape> circPtr = std::make_shared<vlasov::Circle>(objcircle);

    CompositeShape compShape(rectPtr);
    std::cout << compShape.getArea() << "\n";
    std::cout << objrect.getArea() << "<-After Rectangle \n";

    compShape.addShape(circPtr);
    std::cout << compShape.getArea() << "\n";
    std::cout << objcircle.getArea() << "<-After Circle \n";

    compShape.scale(2);
    std::cout << compShape.getArea() << "<-After scale \n";

  } catch (std::invalid_argument & error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}

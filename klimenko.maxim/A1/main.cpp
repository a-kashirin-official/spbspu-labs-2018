#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

using namespace std;


void printInfo(const Shape & shape)
{
  cout << "\tgetArea = " << shape.getArea() << endl;
  const rectangle_t temp = shape.getFrameRect();
  cout << "\tFrameRect:" << endl;
  cout << "\tMid = (" << temp.pos.x << ", " << temp.pos.y << ")" << endl;
  cout << "\tWidth = " << temp.width << " Height = " << temp.height << endl;
  cout << endl;
}

int main()
{
  const point_t circcen{ 41.2, 22.4 };
  const point_t point1{ 51.3, 101.4 };
  const point_t point2{ 15.7, 11.9 };
  const point_t point3{ 25.2, 37.5 };
  const double rad1{ 10.0 };
  Shape * circ1 = nullptr;
  Shape * rect1 = nullptr;
  Shape * trng1 = nullptr;

  try
  {
    rect1 = new Rectangle({ 10.2, 5.9, { 50.1, 18.3 } });

    circ1 = new Circle(rad1 , circcen);

    trng1 = new Triangle(point1, point2, point3);

    cout << "Circle:" << endl;
    printInfo(* circ1);
    circ1->move(105.7, 15.6);
    printInfo(* circ1);

    delete circ1;

    cout << "Rectangle:" << endl;
    printInfo(* rect1);
    rect1->move(point1);
    printInfo(* rect1);

    delete rect1;

    cout << "Triangle:" << endl;
    printInfo(* trng1);
    trng1->move(point1);
    printInfo(* trng1);

    delete trng1;
  }

  catch (std::bad_alloc & b)
  {
    cerr << b.what() << endl;
    delete circ1;
    delete rect1;
    delete trng1;
    return 2;
  }

  catch(std::invalid_argument & i)
  {

    cerr << i.what() << endl;
    delete circ1;
    delete rect1;
    delete trng1;
    return 1;
  }
return 0;
};

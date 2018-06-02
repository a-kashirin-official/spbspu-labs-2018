#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using namespace sergeev;


int main()
{
  try
  {
    Circle circ{ {10.0, 15.0}, 5.0 };
    cout << "\t\tCIRCLE" << endl;
    cout << "Circle area: " << circ.getArea() << endl;
    circ.scale(20.0);
    cout << "Scaled circle(factor=20.0): " << circ.getArea() << endl << endl;

    Rectangle rect{ { {40.0, 40.0}, 15.0, 15.0 } };

    cout << "\t\tRECTANGLE" << endl;
    cout << "Rectangle area: " << rect.getArea() << endl;
    rect.scale(20.0);
    cout << "Scaled rectangle(factor=20.0): " << rect.getArea() << endl;
  }
  catch(std::invalid_argument & err)
  {
    cout << "-------------------------" << endl;
    cerr << err.what() << endl;
    cout << "-------------------------" << endl;

    return 1;
  }

  return 0;
}

#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace iliintsev;
using std::cout;
using std::endl;
using std::cerr;

int main()
{
  try
  {
    Circle Circle1({4.0 , 4.0} , 8.0);
    Rectangle Rectangle1({ {10.0 , 10.0} , 5.0 , 5.0 } );

    cout << "-------Before scaling-------" << endl << endl;

    cout << "Rectangle area : " << Rectangle1.getArea() << endl;
    cout << "Circle area : " << Circle1.getArea() << endl;

    const double ratio = 10.0;

    cout << "-------After scaling-------" << endl << endl;

    Rectangle1.scale(ratio);
    Circle1.scale(ratio);
    cout << "Rectangle area : " << Rectangle1.getArea() << endl;
    cout << "Circle area : " << Circle1.getArea() << endl;
  }
  
  catch(std::invalid_argument & ia)
  {
    cerr << ia.what() << endl;
    return(1);
  }

  return(0);
}

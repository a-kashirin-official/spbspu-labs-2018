#include <iostream>
#include "matrix.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace lobanova;

int main()
{
  try {
    Matrix m;
    Rectangle r({0, 0}, 2, 1);
    m.add(&r);
    Circle c({10, 10}, 1);
    m.add(&c);
    CompositeShape cs;
    cs.add(&r);
    cs.add(&c);
    m.add(&cs);
    std::cout << m;

  }
  catch (const std::out_of_range &e) {
    std::cerr << e.what() << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "There is some problem." << std::endl;
  }
  return 0;
}

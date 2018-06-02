#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace lashchenov;

int main()
{
  try {
    CompositeShape array;
    array.add(Rectangle(4, 3, {3, 2.5}));
    array.add(Rectangle(2, 4, {11, 0}));
    array.add(Circle(2, {8, 6}));
    array.printInfo();
    for (size_t i = 0; i < array.size(); ++i) {
      array[i].printInfo();
    }
    std::cout << std::endl << std::endl;
    array.rotate(70);
    for (size_t i = 0; i < array.size(); ++i) {
      array[i].printInfo();
    }
    std::cout << std::endl << std::endl;
    array.printInfo();


    CompositeShape cShape1;
    cShape1.add(Rectangle(4, 2, {3, -3}));
    cShape1.add(Circle(1, {7, -3}));
    CompositeShape cShape2;
    cShape2.add(Rectangle(2, 2, {2, 5}));
    cShape2.add(Circle(1, {3.2, 1}));

    Matrix matrix;
    matrix.add(Rectangle(2, 4, {2, 1}));
    matrix.add(Rectangle(6, 2, {7, 0}));
    matrix.add(Circle(1, {5, 3}));
    matrix.add(Rectangle(2, 2, {10, -1}));
    matrix.addElementsFromCShape(cShape1);
    matrix.add(Circle(0.4, {6, 4}));
    matrix.add(Rectangle(2, 3, {8, 3.5}));
    matrix.addElementsFromCShape(cShape1);
    matrix.addElementsFromCShape(cShape1);
    matrix.printInfo();
    matrix.remove(0, 1);
    matrix.printInfo();
    matrix[0][2].printInfo();
  }
  catch (std::exception & error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  catch (...) {
    std::cerr << "Something was wrong" << std::endl;
    return 2;
  }
  return 0;
}

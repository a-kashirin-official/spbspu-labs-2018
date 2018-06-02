#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace lashchenov;

int main()
{
  try {
    CompositeShape array(Rectangle(10, 10, {5, 6}));
    array.add(lashchenov::Rectangle(10, 10, {5, 6}));
    array.add(lashchenov::Rectangle(10, 10, {9, 1}));
    array.add(lashchenov::Rectangle(10, 10, {12, 13}));
    array.add(lashchenov::Rectangle(10, 10, {6, 7}));
    for (size_t i = 0; i < array.size(); ++i) {
      array[i].printInfo();
    }
    std::cout << std::endl;

    CompositeShape array3(array);
    array.scale(2);
    array.printInfo();
    array3.printInfo();
    array3.move(3, 3);
    for (size_t i = 0; i < array.size(); ++i) {
      array[i].printInfo();
      array3[i].printInfo();
    }

    CompositeShape array1;
    array1.add(Circle(4, {4, 4}));
    array1.add(Circle(3, {3, 3}));
    array1.remove(0);
    array1.printInfo();
    array1 = std::move(array);
    array1.printInfo();
    array.printInfo();

    CompositeShape array2(std::move(array1));
    array2.printInfo();
    array1.printInfo();
  }
  catch (std::exception & error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}

//
//  main.cpp
//  A3
//
//  Created by Георгий Тимошенский on 06.05.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"

using namespace timoshenskiy;

int main()
{
  Rectangle rectangle({2.0, 2.0}, 2.0, 4.0);
  Circle circle({6.0, 0.0}, 2.0);

  std::cout << "First shape (Rectangle): " << std::endl;
  std::cout << rectangle.printPeaks();
  std::cout << rectangle.printInformation();

  std::cout << "Move on (2,2): " << std::endl;
  rectangle.move(2, 2);
  std::cout << rectangle.printPeaks();
  std::cout << rectangle.printInformation();

  std::cout << "Move in (0,0): " << std::endl;
  rectangle.move({0, 0});
  std::cout << rectangle.printPeaks();
  std::cout << rectangle.printInformation();

  std::cout << "Scale(2.0): " << std::endl;
  rectangle.scale(2.0);
  std::cout << rectangle.printPeaks();
  std::cout << rectangle.printInformation();

  std::cout << "Rotate(90): " << std::endl;
  rectangle.rotate(90);
  std::cout << rectangle.printPeaks();
  std::cout << rectangle.printInformation();

  std::cout << "Second shape (Circle): " << std::endl;
  std::cout << circle.printInformation();

  std::cout << "Rotate(90): " << std::endl;
  circle.rotate(60);
  std::cout << circle.printInformation();

  std::shared_ptr < Shape > pRectangle = std::make_shared < Rectangle > (rectangle);
  std::shared_ptr < Shape > pCircle = std::make_shared < Circle > (circle);

  std::cout << "Composite shape with first shape:" << std::endl << std::endl;
  CompositeShape CompositeShape(pRectangle);
  std::cout << CompositeShape.printInformation();

  std::cout << "Rotate(90): " << std::endl;
  CompositeShape.rotate(90);
  std::cout << CompositeShape.printInformation() << std::endl;

  std::cout << "Second shape was added:" << std::endl << std::endl;
  CompositeShape.addShape(pCircle);
  std::cout << CompositeShape.printInformation();

  Circle matrixCircle({0.0, 0.0}, 2.0);
  Rectangle matrixRectangle({1.0, 0.0}, 2.0, 2.0);
  Rectangle matrixRectangle2({-3.0, 0.0 }, 4.0, 4.0);
  Circle matrixCircle2({3.0, 2.0}, 5.0);

  std::shared_ptr< timoshenskiy::Shape > pMatrixCircle = std::make_shared< timoshenskiy::Circle >(matrixCircle);
  std::shared_ptr< timoshenskiy::Shape > pMatrixRectangle = std::make_shared< timoshenskiy::Rectangle >(matrixRectangle);
  std::shared_ptr< timoshenskiy::Shape > pMatrixRectangle2 = std::make_shared< timoshenskiy::Rectangle >(matrixRectangle2);
  std::shared_ptr< timoshenskiy::Shape > pMatrixCircle2 = std::make_shared< timoshenskiy::Circle >(matrixCircle2);

  timoshenskiy::Matrix matrix(pMatrixCircle);
  matrix.addShape(pMatrixRectangle);
  matrix.addShape(pMatrixRectangle2);
  matrix.addShape(pMatrixCircle2);

  std::cout << "Matrix:" << std::endl << std::endl;

  std::cout << "Circle:" << std::endl;
  std::cout << matrix.printInformation(*matrix[0][0]);

  std::cout << "Rectangle:" << std::endl;
  std::cout << matrix.printInformation(*matrix[1][0]);

  std::cout << "Rectangle2:" << std::endl;
  std::cout << matrix.printInformation(*matrix[1][1]);

  std::cout << "Circle2:" << std::endl;
  std::cout << matrix.printInformation(*matrix[2][0]);
  
  return 0;
}

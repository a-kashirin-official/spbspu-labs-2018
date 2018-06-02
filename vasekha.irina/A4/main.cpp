#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace vasekha;

void test(Shape & shape)
{
  std::cout << shape;
  shape.rotate(30.0);
  std::cout << "after rotate" << std::endl << shape << std::endl;
}

int main()
{
  try
  {
    Rectangle rect{{2.0,3.0},4.0,4.0};
    Circle cir{{1.0,1.0},1.0};
    Triangle tr{{-6.0,3.0},{-4.0,3.0},{-1.0,8.0}};
    CompositeShape compSh;
    compSh.add(std::make_shared<Rectangle>(rect));
    compSh.add(std::make_shared<Circle>(cir));
    compSh.add(std::make_shared<Triangle>(tr));
    test(compSh);
    Rectangle rect1{{1.0,4.0},4.0,8.0};
    Circle cir1{{1.0,2.0},5.0};
    Triangle tr1{{-6.0,-3.0},{-4.0,-3.0},{-1.0,-8.0}};
    Matrix matrix;
    matrix.add(std::make_shared<CompositeShape>(compSh));
    matrix.add(std::make_shared<Rectangle>(rect1));
    matrix.add(std::make_shared<Triangle>(tr1));
    matrix.add(std::make_shared<Circle>(cir1));

    for(size_t i=0;i<matrix.getRows();++i)
    {
      std::cout << "Layer " << i << std::endl;
      for(size_t j=0; j<matrix.getCols();++j)
      {
        if(!matrix[i][j])
        {
          break;
        }
        std::cout << *matrix[i][j] << std::endl;
      }
    }
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
};

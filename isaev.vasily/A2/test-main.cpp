#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/triangle.hpp"
using namespace isaev;

//Test for rectangle class
BOOST_AUTO_TEST_SUITE(RectangleTests)

  const double possibleError = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(Rectangle( {4, 2}, -3, 7 ), std::invalid_argument);//length cant be negative
    BOOST_CHECK_THROW(Rectangle( {4, 2},  3,-7 ), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle( {4, 2}, -3,-7 ), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rectangle { {3, 4}, 9, 13.5};
    rectangle.move({4, 5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 9, possibleError);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 13.5, possibleError);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 4, possibleError);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 5, possibleError);
  }
  BOOST_AUTO_TEST_CASE(MoveToDelta)
  {
    Rectangle rectangle { {3, 4}, 9, 13.5};
    rectangle.move(4, 5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 9, possibleError);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 13.5, possibleError);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 7, possibleError);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 9, possibleError);
  }
  BOOST_AUTO_TEST_CASE(getArea)
  {
    Rectangle rectangle { {3, 4}, 9, 13.5 };
    BOOST_CHECK_CLOSE(rectangle.getArea(), 121.5, possibleError);
  }
  BOOST_AUTO_TEST_CASE(scale)
  {
    Rectangle rectangle { {3, 4}, 9, 13.5 };
    rectangle.scale(3);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 27, possibleError);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 40.5, possibleError);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 9 * 13.5 * 3 * 3, possibleError);
    BOOST_CHECK_THROW(rectangle.scale(-1), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

//test for circle class
BOOST_AUTO_TEST_SUITE(CircleTest)
  const double possibleError = 0.00001;
  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(Circle ({1 , 1} , -2), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(moveToPoint)
  {
    Circle circle { {1 ,1}, 5};
    circle.move({4, 5});
    BOOST_CHECK_CLOSE(circle.getRadius(), 5, possibleError);
    BOOST_CHECK_CLOSE(circle.getCenter().x, 4, possibleError);
    BOOST_CHECK_CLOSE(circle.getCenter().y, 5, possibleError);
  }
  BOOST_AUTO_TEST_CASE(moveToDelta)
  {
    Circle circle { {1 , 1} , 5};
    circle.move(4, 5);
    BOOST_CHECK_CLOSE(circle.getRadius(), 5, possibleError);
    BOOST_CHECK_CLOSE(circle.getCenter().x, 5, possibleError);
    BOOST_CHECK_CLOSE(circle.getCenter().y, 6, possibleError);
  }
  BOOST_AUTO_TEST_CASE(getArea)
  {
    Circle circle { {1 , 1} , 5};
    BOOST_CHECK_CLOSE(circle.getArea(), 78.53981633, possibleError);
  }
  BOOST_AUTO_TEST_CASE(scale)
  {
    Circle circle { {1 , 1} , 5};
    circle.scale(3);
    BOOST_CHECK_CLOSE(circle.getRadius(), 15, possibleError);
    BOOST_CHECK_CLOSE(circle.getCenter().x, 1, possibleError);
    BOOST_CHECK_CLOSE(circle.getCenter().y, 1, possibleError);
    BOOST_CHECK_CLOSE(circle.getArea(), 706.85834705, possibleError);
  }
BOOST_AUTO_TEST_SUITE_END()

//triangle test
BOOST_AUTO_TEST_SUITE(TriangleTest);
const double possibleError = 0.00001;
  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(Triangle ( {1 , 1} , {2 , 1} , {3 , 1} ), std::invalid_argument);//triangle with square = 0
    BOOST_CHECK_THROW(Triangle ( {0 , 0} , {0 , 0} , {0 , 0} ), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(moveToPoint)
  {
    Triangle triangle{ {0 , 0} , {3 , 0} , {0 ,3} };
    triangle.move({0 , 0});
    BOOST_CHECK_CLOSE(triangle.getVertex1().x , -1 , possibleError);
    BOOST_CHECK_CLOSE(triangle.getVertex1().y , -1 , possibleError);
    BOOST_CHECK_CLOSE(triangle.getCenter().x , 0 , possibleError); 
    BOOST_CHECK_CLOSE(triangle.getCenter().y , 0 , possibleError);
  }
  BOOST_AUTO_TEST_CASE(moveToDelta)
  {
    Triangle triangle { {0 , 0} , { 3 , 0 } , { 0 , 3} };
    triangle.move(1 , 1); 
    BOOST_CHECK_CLOSE(triangle.getVertex1().x , 1 , possibleError);
    BOOST_CHECK_CLOSE(triangle.getVertex1().y , 1 , possibleError);
    BOOST_CHECK_CLOSE(triangle.getCenter().x , 2 , possibleError); 
    BOOST_CHECK_CLOSE(triangle.getCenter().y , 2 , possibleError);
  }
  BOOST_AUTO_TEST_CASE(getArea)
  {
    Triangle triangle{ {0 , 0} , {3 , 0} , {0 , 3} };
    BOOST_CHECK_CLOSE(triangle.getArea(), 4.5, possibleError); 
  }
  BOOST_AUTO_TEST_CASE(scale)
  {
    Triangle triangle { {0 , 0} , {3 , 0} , {0 , 3} };
    triangle.scale(3);
    BOOST_CHECK_CLOSE(triangle.getVertex1().x, -2, possibleError);//1 + (0 - 1) * 3
    BOOST_CHECK_CLOSE(triangle.getVertex1().y, -2, possibleError);//1 + (0 - 1) * 3
    BOOST_CHECK_CLOSE(triangle.getVertex2().x,  7, possibleError);//1 + (3 - 1) * 3
    BOOST_CHECK_CLOSE(triangle.getVertex2().y, -2, possibleError);//1 + (0 - 1) * 3
    BOOST_CHECK_CLOSE(triangle.getArea(), 40.5, possibleError);  
  } 
BOOST_AUTO_TEST_SUITE_END()

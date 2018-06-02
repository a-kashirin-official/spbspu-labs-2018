#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define EPSILON 0.00001
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
using namespace ivanov;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(RectangleMoving)
  {
    Rectangle rect{ {{5.0, 7.0}, 10.0, 3.0} };
    double areaBeforeMoving = rect.getArea();
    rectangle_t objectBeforeMoving = rect.getFrameRect();
    rect.move(17.0, 12.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(objectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(objectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(QvadroAreaDiff)
  {
    Rectangle rect{ {{10.0, 7.0}, 5.0, 2.0} };
    double areaBeforeScaling = rect.getArea();
    double koefficient = 5.5;
    rect.scale(koefficient);
    double result = koefficient * koefficient * areaBeforeScaling;
    BOOST_CHECK_CLOSE(result, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW((Rectangle{ {{10.0, 7.0}, -4.0, 3.0} }), std::invalid_argument);
    BOOST_CHECK_THROW((Rectangle{ {{10.0, 7.0}, 4.0, -3.0} }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleKoeff)
  {
    Rectangle rect{ {{5.0, 7.0}, 10.0, 3.0} };
    double koefficient = -2.0;
    BOOST_CHECK_THROW(rect.scale(koefficient), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(ImmutabilityCharacteristicsOfObject)
  {
    Circle circ{ {1.0, 2.0}, 5.0 };
    double areaBeforeMoving = circ.getArea();
    rectangle_t squareBeforeMoving = circ.getFrameRect();
    point_t movement = {10.0, 5.0};
    circ.move(movement);
    BOOST_CHECK_EQUAL(areaBeforeMoving, circ.getArea());
    BOOST_CHECK_EQUAL(squareBeforeMoving.height, circ.getFrameRect().height);
    BOOST_CHECK_EQUAL(squareBeforeMoving.width, circ.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(QvadroAreaDifference)
  {
    Circle circ{ {1.0, 2.0}, 5.0 };
    double areaBeforeScaling = circ.getArea();
    double koefficient = 3.5;
    circ.scale(koefficient);
    double result = koefficient * koefficient * areaBeforeScaling;
    BOOST_CHECK_CLOSE(result, circ.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParams)
  {
    BOOST_CHECK_THROW((Circle{ {1.0, 2.0}, -100.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(NegativeScaling)
  {
    Circle circ{ {1.0, 2.0}, 5.0 };
    BOOST_CHECK_THROW(circ.scale(-4.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE(TriangleTest)

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(Triangle ( {1 , 1} , {2 , 1} , {3 , 1} ), std::invalid_argument);
    BOOST_CHECK_THROW(Triangle ( {0 , 0} , {0 , 0} , {0 , 0} ), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(moveToPoint)
  {
    Triangle triangle{ {0 , 0} , {3 , 0} , {0 ,3} };
    triangle.move({0 , 0});
    BOOST_CHECK_CLOSE(triangle.getVertex1().x , -1 , EPSILON);
    BOOST_CHECK_CLOSE(triangle.getVertex1().y , -1 , EPSILON);
    BOOST_CHECK_CLOSE(triangle.getCenter().x , 0 , EPSILON); 
    BOOST_CHECK_CLOSE(triangle.getCenter().y , 0 , EPSILON);
  }
  BOOST_AUTO_TEST_CASE(moveToDelta)
  {
    Triangle triangle { {0 , 0} , { 3 , 0 } , { 0 , 3} };
    triangle.move(1 , 1); 
    BOOST_CHECK_CLOSE(triangle.getVertex1().x , 1 , EPSILON);
    BOOST_CHECK_CLOSE(triangle.getVertex1().y , 1 , EPSILON);
    BOOST_CHECK_CLOSE(triangle.getCenter().x , 2 , EPSILON); 
    BOOST_CHECK_CLOSE(triangle.getCenter().y , 2 , EPSILON);
  }
  BOOST_AUTO_TEST_CASE(getArea)
  {
    Triangle triangle{ {0 , 0} , {3 , 0} , {0 , 3} };
    BOOST_CHECK_CLOSE(triangle.getArea(), 4.5, EPSILON); 
  }
  BOOST_AUTO_TEST_CASE(scale)
  {
    Triangle triangle { {0 , 0} , {3 , 0} , {0 , 3} };
    triangle.scale(3);
    BOOST_CHECK_CLOSE(triangle.getVertex1().x, -2, EPSILON);//1 + (0 - 1) * 3
    BOOST_CHECK_CLOSE(triangle.getVertex1().y, -2, EPSILON);//1 + (0 - 1) * 3
    BOOST_CHECK_CLOSE(triangle.getVertex2().x,  7, EPSILON);//1 + (3 - 1) * 3
    BOOST_CHECK_CLOSE(triangle.getVertex2().y, -2, EPSILON);//1 + (0 - 1) * 3
    BOOST_CHECK_CLOSE(triangle.getArea(), 40.5, EPSILON);
  }

}
BOOST_AUTO_TEST_SUITE_END()

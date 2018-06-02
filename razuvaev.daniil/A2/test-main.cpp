#define BOOST_TEST_MODULE mainTest
#include <stdexcept>
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"

using namespace razuvaev;

const double epsilon = 1e-4;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

  BOOST_AUTO_TEST_CASE(Moving)
  {
    Rectangle rectangle(3,3,10,15);
    rectangle.move(30,50);
    BOOST_CHECK_CLOSE(3,rectangle.getHeight(),epsilon);
    BOOST_CHECK_CLOSE(3,rectangle.getWidth(),epsilon);
    BOOST_CHECK_CLOSE(3*3,rectangle.getArea(),epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rectangle(3,3,10,15);
    rectangle.scale(2);
    BOOST_CHECK_CLOSE(3*3*2*2,rectangle.getArea(),epsilon);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameters)
  {
    Rectangle rectangle(3,3,10,15);
    BOOST_CHECK_THROW(rectangle.scale(-3),std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters1)
  {
    BOOST_CHECK_THROW(Rectangle rectangle(-3,7,10,15),std::invalid_argument );
  }
  
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters2)
  {
    BOOST_CHECK_THROW(Rectangle rectangle(3,-7,10,15),std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParametersAll)
  {
    BOOST_CHECK_THROW(Rectangle rectangle(-3,-7,10,15),std::invalid_argument );
  }

  
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

  BOOST_AUTO_TEST_CASE(Moving)
  {
    Circle circle(5,10,15);
    circle.move(20,40);
    BOOST_CHECK_CLOSE(5,circle.getRadius(),epsilon);
    BOOST_CHECK_CLOSE(5*5*M_PI,circle.getArea(),epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Circle circle(5,10,15);
    circle.scale(2);
    BOOST_CHECK_CLOSE(5*5*M_PI*2*2,circle.getArea(),epsilon);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameters)
  {
    Circle circle(5,10,15);
    BOOST_CHECK_THROW(circle.scale(-2),std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW(Circle circle(-5,10,15),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

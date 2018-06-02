#define BOOST_TEST_MODULE mainTest
#include <stdexcept>
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace averin;

const double epsilon = 1e-4;

BOOST_AUTO_TEST_SUITE(RectangleSuite)
  
  BOOST_AUTO_TEST_CASE(Moving)
  {
    Rectangle rec(3,3,10,15);
    rec.move(30,50);
    BOOST_CHECK_CLOSE(3,rec.getHeight(),epsilon);
    BOOST_CHECK_CLOSE(3,rec.getWidth(),epsilon);
    BOOST_CHECK_CLOSE(3*3,rec.getArea(),epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rec(3,3,10,15);
    rec.scale(2);
    BOOST_CHECK_CLOSE(3*3*2*2,rec.getArea(),epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidScaleParameters)
  {
    Rectangle rec(3,3,10,15);
    BOOST_CHECK_THROW(rec.scale(-3),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW(Rectangle rec(-3,-7,10,15),std::invalid_argument )
  }

BOOST_AUTO_TEST_SUITE_END()
        
BOOST_AUTO_TEST_SUITE(CircleSuite)
        
  BOOST_AUTO_TEST_CASE(Moving)
  {
    Circle cir(5,10,15);
    cir.move(20,40);
    BOOST_CHECK_CLOSE(5,cir.getRad(),epsilon);
    BOOST_CHECK_CLOSE(5*5*M_PI,cir.getArea(),epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Circle cir(5,10,15);
    cir.scale(2);
    BOOST_CHECK_CLOSE(5*5*M_PI*2*2,cir.getArea(),epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidScaleParameters)
  {
    Circle cir(5,10,15);
    BOOST_CHECK_THROW(cir.scale(-2),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW(Circle cir(-5,10,15),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

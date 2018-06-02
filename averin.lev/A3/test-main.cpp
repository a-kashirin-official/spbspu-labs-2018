#define BOOST_TEST_MODULE mainTest
#include <stdexcept>
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace averin;

const double epsilon = 1e-3;

BOOST_AUTO_TEST_SUITE(CompositeShapeSuite)

  BOOST_AUTO_TEST_CASE(Moving)
  {
    Rectangle rec(3,3,10,15);
    CompositeShape shp(&rec);
    shp.move(30,50);
    BOOST_CHECK_CLOSE(3,shp.getFrameRect().height,epsilon);
    BOOST_CHECK_CLOSE(3,shp.getFrameRect().width,epsilon);
    BOOST_CHECK_CLOSE(3*3,shp.getArea(),epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rec(3,3,10,15);
    CompositeShape shp(&rec);
    Circle cir(10,5,7);
    shp.addShape(&cir);
    shp.scale(2);
    BOOST_CHECK_CLOSE(((3*3)+(10*10*M_PI))*2*2,shp.getArea(),epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidScaleParameters)
  {
    Rectangle rec(3,3,10,15);
    CompositeShape shp(&rec);
    BOOST_CHECK_THROW(shp.scale(-3),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW(CompositeShape shp(nullptr),std::invalid_argument );
  }
  
  BOOST_AUTO_TEST_CASE(InvalidAddParameters)
  {
    Rectangle rec(3,3,10,15);
    CompositeShape shp(&rec);
    BOOST_CHECK_THROW(shp.addShape(nullptr),std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()

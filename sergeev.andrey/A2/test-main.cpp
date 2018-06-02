#define BOOST_TEST_MODULE

#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace sergeev;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTestSuite)
  
  BOOST_AUTO_TEST_CASE(WrongConstructorParam)
  {
    BOOST_CHECK_THROW(Rectangle rect({ {2.0, 2.0}, 5.0, -5.0}), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(MoveToPointTest)
  {
    Rectangle rect{ { {2.0, 2.0}, 5.0, 5.0} };
    
    rectangle_t rectBeforeMove = rect.getFrameRect();
    double areaBeforeMove = rect.getArea();
    
    rect.move( {10.0, 7.3} );
    
    BOOST_CHECK_EQUAL(areaBeforeMove, rect.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMove.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMove.height, rect.getFrameRect().height);
  }
  
  BOOST_AUTO_TEST_CASE(CoordMoveTest)
  {
    Rectangle rect{ { {2.0, 2.0}, 5.0, 5.0} };
    
    rectangle_t rectBeforeMove = rect.getFrameRect();
    double areaBeforeMove = rect.getArea();
    
    rect.move(-2.0, -10.3);
    
    BOOST_CHECK_EQUAL(areaBeforeMove, rect.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMove.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMove.height, rect.getFrameRect().height);
  }
  
  BOOST_AUTO_TEST_CASE(ScalingTest)
  {
    Rectangle rect{ { {2.0, 2.0}, 5.0, 5.0 } };
    
    double areaBeforeScale = rect.getArea();
    const double factor = 2.0;
    
    rect.scale(factor);
    
    double result = factor * factor * areaBeforeScale;
    
    BOOST_CHECK_CLOSE(result, rect.getArea(), EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(WrongScaleFactor)
  {
    Rectangle rect{ { {2.0, 2.0}, 5.0, 5.0 } };
    
    const double factor = -2.0;
    
    BOOST_CHECK_THROW(rect.scale(factor), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTestSuite)

  BOOST_AUTO_TEST_CASE(WrongConstructorParam)
  {
    BOOST_CHECK_THROW(Circle circ( {5.0, 5.0}, -20.0), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(MoveToPointTest)
  {
    Circle circ{ {5.0, 5.0}, 2.0};
    
    double areaBeforeMove = circ.getArea();
    rectangle_t rectBeforeMove = circ.getFrameRect();
    
    circ.move( {-5.0, -5.0} );
    
    BOOST_CHECK_EQUAL(areaBeforeMove, circ.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMove.width, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMove.height, circ.getFrameRect().height);
  }
  
  BOOST_AUTO_TEST_CASE(CoordMoveTest)
  {
    Circle circ{ {5.0, 5.0}, 2.0};
    
    double areaBeforeMove = circ.getArea();
    rectangle_t rectBeforeMove = circ.getFrameRect();
    
    circ.move(-10.0, -6.4);
    
    BOOST_CHECK_EQUAL(areaBeforeMove, circ.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMove.width, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMove.height, circ.getFrameRect().height);
  }
  
  BOOST_AUTO_TEST_CASE(ScalingTest)
  {
    Circle circ{ {5.0, 5.0}, 2.0};
    
    const double factor = 2.0;
    double areaBeforeScale = circ.getArea();
    
    circ.scale(factor);
    
    double result = factor * factor * areaBeforeScale;
    
    BOOST_CHECK_CLOSE(result, circ.getArea(), EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(WrongScaleFactor)
  {
    Circle circ{ {5.0, 5.0}, 2.0};
    const double factor = -2.0;
    BOOST_CHECK_THROW(circ.scale(factor), std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_MAIN

#include <stdexcept>
#include <math.h>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"


const double Epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleSuite)
  
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW(kudryakov::Rectangle rectangle({0,0}, -2, 3), std::invalid_argument)
    BOOST_CHECK_THROW(kudryakov::Rectangle rectangle({0,0}, 2, -3), std::invalid_argument)
  }
  
  BOOST_AUTO_TEST_CASE(Move)
  {
    kudryakov::Rectangle rectangle({0,0}, 2, 3);
    
    rectangle.move(1, 1);
    BOOST_CHECK_CLOSE(1, rectangle.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(1, rectangle.getFrameRect().pos.y, Epsilon);
    BOOST_CHECK_CLOSE(2, rectangle.getFrameRect().width, Epsilon);
    BOOST_CHECK_CLOSE(3, rectangle.getFrameRect().height, Epsilon);
    BOOST_CHECK_CLOSE(2*3, rectangle.getArea(), Epsilon);
    
    rectangle.move({0, 0});
    BOOST_CHECK_CLOSE(0, rectangle.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(0, rectangle.getFrameRect().pos.y, Epsilon);
    BOOST_CHECK_CLOSE(2, rectangle.getFrameRect().width, Epsilon);
    BOOST_CHECK_CLOSE(3, rectangle.getFrameRect().height, Epsilon);
    BOOST_CHECK_CLOSE(2*3, rectangle.getArea(), Epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    kudryakov::Rectangle rectangle({0,0}, 2, 3);
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(Scale)
  {
    kudryakov::Rectangle rectangle({0,0}, 2, 3);
    rectangle.scale(2);
    BOOST_CHECK_CLOSE(2*2*3*2, rectangle.getArea(), Epsilon);
  }
  
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(CircleSuite)
  
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW(kudryakov::Circle circle({0,0}, -5), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(Move)
  {
    kudryakov::Circle circle({0,0}, 5);
    
    circle.move(1,1);
    BOOST_CHECK_CLOSE(1, circle.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(1, circle.getFrameRect().pos.y, Epsilon);
    BOOST_CHECK_CLOSE(5, circle.getFrameRect().width/2, Epsilon);
    BOOST_CHECK_CLOSE(M_PI*5*5, circle.getArea(), Epsilon);
    
    circle.move({0, 0});
    BOOST_CHECK_CLOSE(0, circle.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(0, circle.getFrameRect().pos.y, Epsilon);
    BOOST_CHECK_CLOSE(5, circle.getFrameRect().width/2, Epsilon);
    BOOST_CHECK_CLOSE(M_PI*5*5, circle.getArea(), Epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    kudryakov::Circle circle({0,0}, 5);
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(Scale)
  {
    kudryakov::Circle circle({0,0}, 5);
    circle.scale(2);
    BOOST_CHECK_CLOSE(M_PI*5*2*5*2, circle.getArea(), Epsilon);
  }
  
BOOST_AUTO_TEST_SUITE_END()

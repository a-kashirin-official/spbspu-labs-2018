#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY = 1E-5;
const double FACTOR_POS = 2.0;
const double FACTOR_NEG = -3.5;

using namespace mordvintseva;

BOOST_AUTO_TEST_SUITE(TestRectangle)

  BOOST_AUTO_TEST_CASE(MoveToPoint) 
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    rectangle_t frame = rect.getFrameRect();
    double area = rect.getArea();
    //Move to point
    rect.move({ 60.8, 71.0 });
    //Check
    BOOST_CHECK_EQUAL(frame.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(frame.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(area, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(RelativeMove) 
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    rectangle_t frame = rect.getFrameRect();
    double area = rect.getArea();
    //Relative move
    rect.move(30.1, -5.2);
    //Check
    BOOST_CHECK_EQUAL(frame.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(frame.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(area, rect.getArea());
  }
  
  BOOST_AUTO_TEST_CASE(Scale)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    double area = rect.getArea();
    //Scale
    rect.scale(FACTOR_POS);
    //Check
    BOOST_CHECK_CLOSE(area * FACTOR_POS * FACTOR_POS, rect.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    BOOST_CHECK_THROW(Rectangle({ -20.0, 40.0, { 30.0, 54.0 } }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({ 20.0, -40.0, { 30.0, 54.0 } }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({ -20.0, -40.0, { 30.0, 54.0 } }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingFactor)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } });

    BOOST_CHECK_THROW(rect.scale(FACTOR_NEG), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)
  
  BOOST_AUTO_TEST_CASE(MoveToPoint) 
  {
    Circle circle(30.0, { -15.0, 36.0 }); 
    rectangle_t frame = circle.getFrameRect();
    double area = circle.getArea();
    //Move to point
    circle.move({ -92.2, 68.0 });
    //Check
    BOOST_CHECK_EQUAL(frame.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(frame.height, circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(area, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(RelativeMove) 
  {
    Circle circle(30.0, { -15.0, 36.0 }); 
    rectangle_t frame = circle.getFrameRect();
    double area = circle.getArea();
    //Move to point
    circle.move(-64.3, 15.2);
    //Check
    BOOST_CHECK_EQUAL(frame.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(frame.height, circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(area, circle.getArea());
  }
  
  BOOST_AUTO_TEST_CASE(Scale)
  {
    Circle circle(30.0, { -15.0, 36.0 }); 
    double area = circle.getArea();
    //Scale
    circle.scale(FACTOR_POS);
    //Check
    BOOST_CHECK_CLOSE(area * FACTOR_POS * FACTOR_POS, circle.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    BOOST_CHECK_THROW(Circle(-30.0, { -15.0, 36.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingFactor)
  {
    Circle circle(30.0, { -15.0, 36.0 }); 

    BOOST_CHECK_THROW(circle.scale(FACTOR_NEG), std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()

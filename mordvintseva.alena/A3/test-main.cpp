#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

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
    BOOST_CHECK_CLOSE(frame.width, rect.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, rect.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove) 
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    rectangle_t frame = rect.getFrameRect();
    double area = rect.getArea();
    //Relative move
    rect.move(30.1, -5.2);
    //Check
    BOOST_CHECK_CLOSE(frame.width, rect.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, rect.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY);
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
    BOOST_CHECK_CLOSE(frame.width, circle.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, circle.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove) 
  {
    Circle circle(30.0, { -15.0, 36.0 }); 
    rectangle_t frame = circle.getFrameRect();
    double area = circle.getArea();
    //Move to point
    circle.move(-64.3, 15.2);
    //Check
    BOOST_CHECK_CLOSE(frame.width, circle.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, circle.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
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

BOOST_AUTO_TEST_SUITE(TestCompositeShape)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    Circle circle(30.0, { -15.0, 36.0 }); 
    CompositeShape compositeShape(&rect);
    compositeShape.add(&circle);

    rectangle_t frame = compositeShape.getFrameRect();
    double area = compositeShape.getArea();

    compositeShape.move({ -46.2, 3.6 });

    BOOST_CHECK_CLOSE(frame.width, compositeShape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, compositeShape.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(area, compositeShape.getArea(), ACCURACY);
    compositeShape.clear();
  }

  BOOST_AUTO_TEST_CASE(RelativeMove)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    Circle circle(30.0, { -15.0, 36.0 }); 
    CompositeShape compositeShape(&rect);
    compositeShape.add(&circle);

    rectangle_t frame = compositeShape.getFrameRect();
    double area = compositeShape.getArea();

    compositeShape.move(32.1, -5.9);

    BOOST_CHECK_CLOSE(frame.width, compositeShape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, compositeShape.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(area, compositeShape.getArea(), ACCURACY);
    //compositeShape.clear();
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    Circle circle(30.0, { -15.0, 36.0 }); 
    CompositeShape compositeShape(&rect);
    compositeShape.add(&circle);

    double area = compositeShape.getArea();

    compositeShape.scale(FACTOR_POS);
    
    BOOST_CHECK_CLOSE(area * FACTOR_POS * FACTOR_POS, rect.getArea() + circle.getArea(), ACCURACY);
    //compositeShape.clear();
  }

  BOOST_AUTO_TEST_CASE(CheckCount)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    Circle circle(30.0, { -15.0, 36.0 }); 
    CompositeShape compositeShape(&rect);
    compositeShape.add(&circle);

    BOOST_CHECK_EQUAL(compositeShape.getCount(), 2);
    //compositeShape.clear();
  }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 }});
    CompositeShape compositeShape(&rect);

    BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(compositeShape.add(&rect), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RemoveNonexistenItem)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 }});
    CompositeShape compositeShape(&rect);

    BOOST_CHECK_THROW(compositeShape.remove(1), std::out_of_range);\

    compositeShape.remove(0);

    BOOST_CHECK_THROW(compositeShape[0], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingFactor)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 }});
    CompositeShape compositeShape(&rect);
    
    BOOST_CHECK_THROW(compositeShape.scale(FACTOR_NEG), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double ACCURACY = 0.01;

BOOST_AUTO_TEST_SUITE(CircleParametersTest)

  BOOST_AUTO_TEST_CASE(MovingToPointTest)
  {
    khmyrov::Circle circleObject({30.0, 30.0}, 10.0);
    
    const double area_before_moving = circleObject.getArea();
    const khmyrov::rectangle_t rect_before_moving = circleObject.getFrameRect();
    
    circleObject.move({20.0, 20.0});
    
    BOOST_CHECK_EQUAL(area_before_moving, circleObject.getArea());
    BOOST_CHECK_EQUAL(rect_before_moving.width, circleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rect_before_moving.height, circleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(khmyrov::Circle circleObject({30.0, 30.0}, -5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingForPointTest)
  {
    khmyrov::Circle circleObject({30.0, 30.0}, 10.0);
    
    const double area_before_moving = circleObject.getArea();
    const khmyrov::rectangle_t rect_before_moving = circleObject.getFrameRect();
    
    circleObject.move(20.0, 20.0);
    
    BOOST_CHECK_EQUAL(area_before_moving, circleObject.getArea());
    BOOST_CHECK_EQUAL(rect_before_moving.width, circleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rect_before_moving.height, circleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(ScalingTest)
  {
    khmyrov::Circle circleObject({30.0, 30.0}, 10.0);
    
    const double area_before_scaling = circleObject.getArea();
    const double coeff = 3.5;
    
    circleObject.scale(coeff);
    
    BOOST_CHECK_CLOSE(coeff * coeff * area_before_scaling, circleObject.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaling)
  {
    khmyrov::Circle circleObject({30.0, 30.0}, 10.0);
    
    BOOST_CHECK_THROW(circleObject.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleParametersTest)

  BOOST_AUTO_TEST_CASE(MovingToPointTest)
  {
    khmyrov::Rectangle rectangleObject({30.0, 30.0}, 10.0, 20.0);
    
    const double area_before_moving = rectangleObject.getArea();
    const khmyrov::rectangle_t rect_before_moving = rectangleObject.getFrameRect();
    
    rectangleObject.move({20.0, 20.0});
    
    BOOST_CHECK_EQUAL(area_before_moving, rectangleObject.getArea());
    BOOST_CHECK_EQUAL(rect_before_moving.width, rectangleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rect_before_moving.height, rectangleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(khmyrov::Rectangle rectangleObject({30.0, 30.0}, -5.0, 10.0), std::invalid_argument);
    BOOST_CHECK_THROW(khmyrov::Rectangle rectangleObject({30.0, 30.0}, 5.0, -10.0), std::invalid_argument);
    BOOST_CHECK_THROW(khmyrov::Rectangle rectangleObject({30.0, 30.0}, -5.0, -10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingForPointTest)
  {
    khmyrov::Rectangle rectangleObject({30.0, 30.0}, 10.0, 20.0);
    
    const double area_before_moving = rectangleObject.getArea();
    const khmyrov::rectangle_t rect_before_moving = rectangleObject.getFrameRect();
    
    rectangleObject.move(20.0, 20.0);
    
    BOOST_CHECK_EQUAL(area_before_moving, rectangleObject.getArea());
    BOOST_CHECK_EQUAL(rect_before_moving.width, rectangleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rect_before_moving.height, rectangleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(ScalingTest)
  {
    khmyrov::Rectangle rectangleObject({30.0, 30.0}, 10.0, 20.0);
    
    const double area_before_scaling = rectangleObject.getArea();
    const double coeff = 3.5;
    
    rectangleObject.scale(coeff);
    
    BOOST_CHECK_CLOSE(coeff * coeff * area_before_scaling, rectangleObject.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaling)
  {
    khmyrov::Rectangle rectangleObject({30.0, 30.0}, 10.0, 20.0);
    
    BOOST_CHECK_THROW(rectangleObject.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TriangleParametersTest)

  BOOST_AUTO_TEST_CASE(MovingToPointTest)
  {
    khmyrov::Triangle triangleObject({0.0, 0.0}, {90.0, 0.0}, {0.0, 30.0});
    
    const double area_before_moving = triangleObject.getArea();
    const khmyrov::rectangle_t rect_before_moving = triangleObject.getFrameRect();
    
    triangleObject.move({20.0, 20.0});
    
    BOOST_CHECK_EQUAL(area_before_moving, triangleObject.getArea());
    BOOST_CHECK_EQUAL(rect_before_moving.width, triangleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rect_before_moving.height, triangleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(khmyrov::Triangle triangleObject({0.0, 0.0}, {0.0, 0.0}, {0.0, 30.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingForPointTest)
  {
    khmyrov::Triangle triangleObject({0.0, 0.0}, {90.0, 0.0}, {0.0, 30.0});
    
    const double area_before_moving = triangleObject.getArea();
    const khmyrov::rectangle_t rect_before_moving = triangleObject.getFrameRect();
    
    triangleObject.move(20.0, 20.0);
    
    BOOST_CHECK_EQUAL(area_before_moving, triangleObject.getArea());
    BOOST_CHECK_EQUAL(rect_before_moving.width, triangleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rect_before_moving.height, triangleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(ScalingTest)
  {
    khmyrov::Triangle triangleObject({0.0, 0.0}, {90.0, 0.0}, {0.0, 30.0});
    
    const double area_before_scaling = triangleObject.getArea();
    const double coeff = 3.5;
    
    triangleObject.scale(coeff);
    
    BOOST_CHECK_CLOSE(coeff * coeff * area_before_scaling, triangleObject.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaling)
  {
    khmyrov::Triangle triangleObject({0.0, 0.0}, {90.0, 0.0}, {0.0, 30.0});
    
    BOOST_CHECK_THROW(triangleObject.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()



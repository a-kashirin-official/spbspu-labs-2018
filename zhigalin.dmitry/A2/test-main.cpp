#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double ACCURACY = 0.01; // if accuracy will < 0.01 triangle area after scaling can't pass the test

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(zhigalin::Circle circleObject({30.0, 30.0}, -5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingTo)
  {
    zhigalin::Circle circleObject({30.0, 30.0}, 10.0);
    
    const double areaBeforeMoving = circleObject.getArea();
    const zhigalin::rectangle_t rectBeforeMoving = circleObject.getFrameRect();

    circleObject.move({20.0, 20.0});

    BOOST_CHECK_EQUAL(areaBeforeMoving, circleObject.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MovingFor)
  {
    zhigalin::Circle circleObject({30.0, 30.0}, 10.0);
    
    const double areaBeforeMoving = circleObject.getArea();
    const zhigalin::rectangle_t rectBeforeMoving = circleObject.getFrameRect();

    circleObject.move(20.0, 20.0);

    BOOST_CHECK_EQUAL(areaBeforeMoving, circleObject.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    zhigalin::Circle circleObject({30.0, 30.0}, 10.0);
    
    const double areaBeforeScaling = circleObject.getArea();
    const double coeff = 3.5;

    circleObject.scale(coeff);

    BOOST_CHECK_CLOSE(coeff * coeff * areaBeforeScaling, circleObject.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaling)
  {
    zhigalin::Circle circleObject({30.0, 30.0}, 10.0);
    
    BOOST_CHECK_THROW(circleObject.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(zhigalin::Rectangle rectangleObject({30.0, 30.0}, -5.0, 10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingTo)
  {
    zhigalin::Rectangle rectangleObject({30.0, 30.0}, 10.0, 20.0);
    
    const double areaBeforeMoving = rectangleObject.getArea();
    const zhigalin::rectangle_t rectBeforeMoving = rectangleObject.getFrameRect();

    rectangleObject.move({20.0, 20.0});

    BOOST_CHECK_EQUAL(areaBeforeMoving, rectangleObject.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rectangleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rectangleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MovingFor)
  {
    zhigalin::Rectangle rectangleObject({30.0, 30.0}, 10.0, 20.0);
    
    const double areaBeforeMoving = rectangleObject.getArea();
    const zhigalin::rectangle_t rectBeforeMoving = rectangleObject.getFrameRect();

    rectangleObject.move(20.0, 20.0);

    BOOST_CHECK_EQUAL(areaBeforeMoving, rectangleObject.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rectangleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rectangleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    zhigalin::Rectangle rectangleObject({30.0, 30.0}, 10.0, 20.0);
    
    const double areaBeforeScaling = rectangleObject.getArea();
    const double coeff = 3.5;

    rectangleObject.scale(coeff);

    BOOST_CHECK_CLOSE(coeff * coeff * areaBeforeScaling, rectangleObject.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaling)
  {
    zhigalin::Rectangle rectangleObject({30.0, 30.0}, 10.0, 20.0);
    
    BOOST_CHECK_THROW(rectangleObject.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TriangleTest)

  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(zhigalin::Triangle triangleObject({0.0, 0.0}, {0.0, 0.0}, {0.0, 30.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingTo)
  {
    zhigalin::Triangle triangleObject({0.0, 0.0}, {90.0, 0.0}, {0.0, 30.0});
    
    const double areaBeforeMoving = triangleObject.getArea();
    const zhigalin::rectangle_t rectBeforeMoving = triangleObject.getFrameRect();

    triangleObject.move({20.0, 20.0});

    BOOST_CHECK_EQUAL(areaBeforeMoving, triangleObject.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, triangleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, triangleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MovingFor)
  {
    zhigalin::Triangle triangleObject({0.0, 0.0}, {90.0, 0.0}, {0.0, 30.0});
    
    const double areaBeforeMoving = triangleObject.getArea();
    const zhigalin::rectangle_t rectBeforeMoving = triangleObject.getFrameRect();

    triangleObject.move(20.0, 20.0);

    BOOST_CHECK_EQUAL(areaBeforeMoving, triangleObject.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, triangleObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, triangleObject.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    zhigalin::Triangle triangleObject({0.0, 0.0}, {90.0, 0.0}, {0.0, 30.0});
    
    const double areaBeforeScaling = triangleObject.getArea();
    const double coeff = 3.5;

    triangleObject.scale(coeff);

    BOOST_CHECK_CLOSE(coeff * coeff * areaBeforeScaling, triangleObject.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaling)
  {
    zhigalin::Triangle triangleObject({0.0, 0.0}, {90.0, 0.0}, {0.0, 30.0});
    
    BOOST_CHECK_THROW(triangleObject.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

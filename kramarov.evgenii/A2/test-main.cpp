#define BOOST_TEST_MODULE Main
#include "circle.hpp"
#include "rectangle.hpp"
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

const double delta = 0.000001;

BOOST_AUTO_TEST_SUITE(MainCheck)
  BOOST_AUTO_TEST_CASE(ReinitializingMovement)
  {
    kramarov::Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    double baseHeight = rectangle.getFrameRect().height;
    double baseWidth = rectangle.getFrameRect().width;
    double baseArea = rectangle.getArea();
    rectangle.move({20.0, 20.0});
    BOOST_CHECK_EQUAL(baseHeight, rectangle.getFrameRect().height);
    BOOST_CHECK_EQUAL(baseWidth, rectangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(baseArea, rectangle.getArea());
    //finished checking rectangle

    kramarov::Circle circle ({50.0,30.0}, 20.0);
    double baseRadius = circle.getFrameRect().height / 2;
    baseArea = circle.getArea();
    circle.move({35.0, 35.0});
    BOOST_CHECK_EQUAL(baseRadius, circle.getFrameRect().height / 2);
    BOOST_CHECK_EQUAL(baseArea, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(DifferencialMovement)
  {
    kramarov::Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    double baseHeight = rectangle.getFrameRect().height;
    double baseWidth = rectangle.getFrameRect().width;
    double baseArea = rectangle.getArea();
    rectangle.move(20.0, 20.0);
    BOOST_CHECK_EQUAL(baseHeight, rectangle.getFrameRect().height);
    BOOST_CHECK_EQUAL(baseWidth, rectangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(baseArea, rectangle.getArea());
    //finished checking rectangle

    kramarov::Circle circle ({50.0,30.0}, 20.0);
    double baseRadius = circle.getFrameRect().height / 2;
    baseArea = circle.getArea();
    circle.move(35.0, 35.0);
    BOOST_CHECK_EQUAL(baseRadius, circle.getFrameRect().height / 2);
    BOOST_CHECK_EQUAL(baseArea, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(Resizing)
  {
    kramarov::Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    double baseArea = rectangle.getArea();
    const double scaleRate = 3.35;
    rectangle.scale(scaleRate);
    BOOST_CHECK_CLOSE(baseArea * scaleRate * scaleRate, rectangle.getArea(), delta);
    //finished checking rectangle

    kramarov::Circle circle ({50.0,30.0}, 20.0);
    baseArea = circle.getArea();
    circle.scale(scaleRate);
    BOOST_CHECK_CLOSE(baseArea * scaleRate * scaleRate, circle.getArea(), delta);
  }

  BOOST_AUTO_TEST_CASE(ConstructorParameters)
  {
    BOOST_CHECK_THROW (kramarov::Rectangle(-1.5, 2.0, {10.0, 10.0}), std::invalid_argument);
    BOOST_CHECK_THROW (kramarov::Rectangle(1.5, -2.0, {10.0, 10.0}), std::invalid_argument);
    BOOST_CHECK_THROW (kramarov::Rectangle(-1.5, -2.0, {10.0, 10.0}), std::invalid_argument);
    BOOST_CHECK_THROW (kramarov::Circle({50.0, 30.0}, -20.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ResizingParameters)
  {
    kramarov::Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    BOOST_CHECK_THROW (rectangle.scale(-1.5), std::invalid_argument);
    kramarov::Circle circle({50.0,30.0}, 20.0);
    BOOST_CHECK_THROW (circle.scale(-1.5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

const double EPSILON = 1e-8;

BOOST_AUTO_TEST_SUITE(Rectangle)

  BOOST_AUTO_TEST_CASE(InvalidConstructorWidth)
  {
    BOOST_CHECK_THROW( brusnitsyna::Rectangle({-8.0, 7.0, {5.0, 2.0}}), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorHeight)
  {
    BOOST_CHECK_THROW( brusnitsyna::Rectangle({8.0, -7.0, {5.0, 2.0}}), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    brusnitsyna::Rectangle rect{ {8.0, 7.0, {5.0, 2.0}} };
    BOOST_CHECK_THROW( rect.scale(-1.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    brusnitsyna::Rectangle rect{ { 8.0, 7.0, {5.0, 2.0}} };
    brusnitsyna::rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();
    rect.move({7.0, 8.0});
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MoveByAxes)
  {
    brusnitsyna::Rectangle rect{ {8.0, 7.0, {5.0, 2.0}} };
    brusnitsyna::rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();
    rect.move(7.0, 9.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    brusnitsyna::Rectangle rect{ {8.0, 7.0, {5.0, 2.0},} };
    double areaBeforeScaling = rect.getArea();
    const double ratio = 5.0;
    rect.scale(ratio);
    BOOST_CHECK_CLOSE(ratio * ratio * areaBeforeScaling, rect.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle)

  BOOST_AUTO_TEST_CASE(InvalidConstructorRadius)
  {
    BOOST_CHECK_THROW( brusnitsyna::Circle({10.0, 5.0}, -2.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    brusnitsyna::Circle circle{ {10.0, 5.0}, 2.0 };
    BOOST_CHECK_THROW( circle.scale(-5.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    brusnitsyna::Circle circle{ {10.0, 5.0}, 2.0 };
    brusnitsyna::rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();
    circle.move({7.0, 8.0});
    BOOST_CHECK_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MoveByAxes)
  {
    brusnitsyna::Circle circle{ {10.0, 5.0}, 2.0 };
    brusnitsyna::rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();
    circle.move(8.0, 7.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);
  }

   BOOST_AUTO_TEST_CASE(Scaling)
  {
    brusnitsyna::Circle circle{ {10.0, 5.0}, 2.0 };
    double areaBeforeScaling = circle.getArea();
    const double ratio = 2.7;
    circle.scale(ratio);
    BOOST_CHECK_CLOSE(ratio * ratio * areaBeforeScaling, circle.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

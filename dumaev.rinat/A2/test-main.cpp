#define BOOST_TEST_MODULE Main
#include "circle.hpp"
#include "rectangle.hpp"
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>

const double EPSILON = 1e-4;


BOOST_AUTO_TEST_SUITE(RectangleSuite)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    dumaev::Rectangle rect({2, 3}, 1, 3);
    dumaev::rectangle_t frameRectBefore = rect.getFrameRect();
    double areaBefore = rect.getArea();

    rect.move({2, 5});

    BOOST_REQUIRE_EQUAL(frameRectBefore.height, rect.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(frameRectBefore.width, rect.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(areaBefore, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    dumaev::Rectangle rect({1, 1}, 2, 4);
    dumaev::rectangle_t frameRectBefore = rect.getFrameRect();
    double areaBefore = rect.getArea();

    rect.move(2, 4);

    BOOST_REQUIRE_EQUAL(frameRectBefore.height, rect.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(frameRectBefore.width, rect.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(areaBefore, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    dumaev::Rectangle rect({3, 3}, 5, 5);
    double areaBefore = rect.getArea();
    const double coefficient = 4;
    rect.scale(coefficient);

    BOOST_CHECK_CLOSE(coefficient * coefficient * areaBefore, rect.getArea(), EPSILON);
  }
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW( dumaev::Rectangle rectangle({1, 2}, 10, -15), std::invalid_argument);
    BOOST_CHECK_THROW( dumaev::Rectangle rectangle({1, 2}, -10, 15), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    dumaev::Rectangle rectangle({5, 6}, 3, 3);
    BOOST_CHECK_THROW( rectangle.scale(-15), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    dumaev::Circle circle({2, 3}, 3);
    dumaev::rectangle_t frameRectBefore = circle.getFrameRect();
    double areaBefore = circle.getArea();

    circle.move({1, 1});

    BOOST_REQUIRE_EQUAL(frameRectBefore.height, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(frameRectBefore.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(areaBefore, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    dumaev::Circle circle({0, 0}, 2);
    dumaev::rectangle_t frameRectBefore = circle.getFrameRect();
    double areaBefore = circle.getArea();

    circle.move(10, 14);

    BOOST_REQUIRE_EQUAL(frameRectBefore.height, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(frameRectBefore.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(areaBefore, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    dumaev::Circle circle({3, 3}, 3);
    double areaBefore = circle.getArea();
    const double coefficient = 5;
    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(coefficient * coefficient * areaBefore, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW( dumaev::Circle circle({10.0, 20.0}, -15), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    dumaev::Circle circle({5, 6}, 3);
    BOOST_CHECK_THROW( circle.scale(1-15), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

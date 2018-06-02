#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace ivanov;

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rectangle_({10.0, 12.0, {0.0, 0.0}});
    double initalWidth = rectangle_.getFrameRect().width;
    double initalHeight = rectangle_.getFrameRect().height;
    double initalArea = rectangle_.getArea();

    rectangle_.move({10.0, 4.2});

    BOOST_CHECK((rectangle_.getFrameRect().pos.x == 10.0) && (rectangle_.getFrameRect().pos.y == 4.2));
    BOOST_CHECK_CLOSE(initalHeight, rectangle_.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(initalWidth, rectangle_.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initalArea, rectangle_.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove)
  {
    Rectangle rectangle_({13.0, 12.1,{0.2, 0.1}});
    double initalHeight = rectangle_.getFrameRect().height;
    double initalWidth = rectangle_.getFrameRect().width;
    double initalArea = rectangle_.getArea();

    rectangle_.move(19.4, 12.7);

    BOOST_CHECK_CLOSE(initalHeight, rectangle_.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(initalWidth, rectangle_.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initalArea, rectangle_.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Rectangle rectangle_({13.0, 12.1,{0.2, 0.1}});
    double initalHeight = rectangle_.getFrameRect().height;
    double initalWidth = rectangle_.getFrameRect().width;
    double initalArea = rectangle_.getArea();

    rectangle_.scale(0.5);

    BOOST_CHECK_CLOSE(initalHeight * 0.5, rectangle_.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(initalWidth * 0.5, rectangle_.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE((initalArea * 0.5 * 0.5), rectangle_.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    Rectangle rectangle_({14.6, 15.4,{8.2, 3.1}});
    BOOST_CHECK_THROW(rectangle_.scale(-18.3), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidInit)
  {
    BOOST_CHECK_THROW(Rectangle({13.6, -18.7, {0.0, 0.0}}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({-78.6, 32.8, {0.0, 0.0}}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({-21.3, -4.7, {0.0, 0.0}}), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle circle_({0.0, 0.0}, 10.0);
    double initalHeight = circle_.getFrameRect().height;
    double initalWidth = circle_.getFrameRect().width;
    double initalArea = circle_.getArea();

    circle_.move({11.0, 7.2});

    BOOST_CHECK((circle_.getFrameRect().pos.x == 11.0) && (circle_.getFrameRect().pos.y == 7.2));
    BOOST_CHECK_CLOSE(initalWidth, circle_.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initalHeight, circle_.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(initalArea, circle_.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove)
  {
    Circle circle_({0.2, 0.1}, 12.1);
    double initalArea = circle_.getArea();
    double initalWidth = circle_.getFrameRect().width;
    double initalHeight = circle_.getFrameRect().height;

    circle_.move(19.4, 12.7);

    BOOST_CHECK_CLOSE(initalWidth, circle_.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initalHeight, circle_.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(initalArea, circle_.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Circle circle_({0.2, 0.1}, 12.1);
    double initalHeight = circle_.getFrameRect().height;
    double initalWidth = circle_.getFrameRect().width;
    double initalArea = circle_.getArea();

    circle_.scale(0.5);

    BOOST_CHECK_CLOSE(initalWidth * 0.5, circle_.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initalHeight * 0.5, circle_.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE((initalArea * 0.5 * 0.5), circle_.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    Circle circle_({8.2, 3.1}, 15.4);
    BOOST_CHECK_THROW(circle_.scale(-15.3), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidInit)
  {
    BOOST_CHECK_THROW(Circle({0.0, 0.0}, -18.7), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

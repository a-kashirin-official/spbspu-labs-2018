#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

#include <boost/test/included/unit_test.hpp>

const double EPS = 1e-4;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(DeltaMoving)
  {
    rebrin::Rectangle my_rectangle({10.0, 15.0, {0.0, 0.0}});
    const double width_before_moving = my_rectangle.getFrameRect().width;
    const double height_before_moving = my_rectangle.getFrameRect().height;
    const double area_before_moving = my_rectangle.getArea();

    my_rectangle.move(5.0, 4.0);

    BOOST_CHECK_CLOSE(my_rectangle.getFrameRect().width, width_before_moving, EPS);
    BOOST_CHECK_CLOSE(my_rectangle.getFrameRect().height, height_before_moving, EPS);
    BOOST_CHECK_CLOSE(my_rectangle.getArea(), area_before_moving, EPS);
  }

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    rebrin::Rectangle my_rectangle({10.0, 15.0, {0.0, 0.0}});
    const double width_before_moving = my_rectangle.getFrameRect().width;
    const double height_before_moving = my_rectangle.getFrameRect().height;
    const double area_before_moving = my_rectangle.getArea();

    my_rectangle.move({5.0, 4.0});

    BOOST_CHECK_CLOSE(my_rectangle.getFrameRect().width, width_before_moving, EPS);
    BOOST_CHECK_CLOSE(my_rectangle.getFrameRect().height, height_before_moving, EPS);
    BOOST_CHECK_CLOSE(my_rectangle.getArea(), area_before_moving, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    rebrin::Rectangle my_rectangle({10.0, 15.0, {0.0, 0.0}});
    const double area_before_scaling = my_rectangle.getArea();

    my_rectangle.scale(5.0);

    BOOST_CHECK_CLOSE(my_rectangle.getArea(), area_before_scaling * 5 * 5, EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidWidth)
  {
    BOOST_CHECK_THROW(rebrin::Rectangle my_rectangle({-1.0, 3.0, {0.0, 0.0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidHeight)
  {
    BOOST_CHECK_THROW(rebrin::Rectangle my_rectangle({1.0, -3.0, {0.0, 0.0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingFactor)
  {
    rebrin::Rectangle my_rectangle({5.0, 3.0, {0.0, 0.0}});
    BOOST_CHECK_THROW(my_rectangle.scale(-3.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(DeltaMoving)
  {
    rebrin::Circle my_circle({0.0, 0.0}, 3.0);
    const double diameter_before_moving = my_circle.getFrameRect().width;
    const double area_before_moving = my_circle.getArea();

    my_circle.move(3.0, -5.0);

    BOOST_CHECK_CLOSE(my_circle.getFrameRect().width, diameter_before_moving, EPS);
    BOOST_CHECK_CLOSE(my_circle.getArea(), area_before_moving, EPS);
  }

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    rebrin::Circle my_circle({0.0, 0.0}, 3.0);
    const double diameter_before_moving = my_circle.getFrameRect().width;
    const double area_before_moving = my_circle.getArea();

    my_circle.move({3.0, -4.0});

    BOOST_CHECK_CLOSE(my_circle.getFrameRect().width, diameter_before_moving, EPS);
    BOOST_CHECK_CLOSE(my_circle.getArea(), area_before_moving, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    rebrin::Circle my_circle({0.0, 0.0}, 3.0);
    const double area_before_scaling = my_circle.getArea();

    my_circle.scale(3.0);

    BOOST_CHECK_CLOSE(my_circle.getArea(), area_before_scaling * 3 * 3, EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidRadius)
  {
    BOOST_CHECK_THROW(rebrin::Circle my_circle({3.0, 3.0}, -2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingFactor)
  {
    rebrin::Circle my_circle({0.0, 0.0}, 3.0);

    BOOST_CHECK_THROW(my_circle.scale(-3.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

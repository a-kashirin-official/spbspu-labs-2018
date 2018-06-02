#define BOOST_TEST_MAIN

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE (CircleTest)
  BOOST_AUTO_TEST_CASE (MoveToPointTests)
  {
    volkov::Circle shape ({1, 1}, 3);
    volkov::Shape *circle = & shape;
    circle->move ({33, 13});
    BOOST_CHECK_CLOSE (shape.getRadius(), 3, epsilon);
    BOOST_CHECK_CLOSE (circle->getArea(), M_PI * 9, epsilon);
  }
  BOOST_AUTO_TEST_CASE (AbsoluteMoveTests)
  {
    volkov::Circle shape ({1, 1}, 3);
    volkov::Shape *circle = & shape;
    circle->move ({33, 13});
    BOOST_CHECK_CLOSE (shape.getRadius(), 3, epsilon);
    BOOST_CHECK_CLOSE (circle->getArea(), M_PI * 9, epsilon);
  }
  BOOST_AUTO_TEST_CASE (area_scale)
  {
    volkov::Circle shape ({1, 1}, 3);
    volkov::Shape *circle = & shape;
    circle->scale (2);
    BOOST_CHECK_CLOSE (circle->getArea(), M_PI * 36, epsilon);
  }
  BOOST_AUTO_TEST_CASE (invalid_radius)
  {
    BOOST_CHECK_THROW (volkov::Circle ({1, 1}, -2), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE (invalid_scale)
  {
    volkov::Circle shape ({1, 1}, 2);
    volkov::Shape *circle = & shape;
    BOOST_CHECK_THROW (circle->scale(-4), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE (RectangleTest)
  BOOST_AUTO_TEST_CASE (MoveToPointTests)
  {
    volkov::Rectangle shape ({1, 1}, 5, 9);
    volkov::Shape *rectangle = & shape;
    rectangle->move ({14, 24});
    BOOST_CHECK_CLOSE (shape.getWidth(), 5, epsilon);
    BOOST_CHECK_CLOSE (shape.getHeight(), 9, epsilon);
    BOOST_CHECK_CLOSE(shape.getFrameRect().pos.y, 24.0, epsilon);
    BOOST_CHECK_CLOSE(shape.getFrameRect().pos.x, 14.0, epsilon);
    BOOST_CHECK_CLOSE (rectangle->getArea(), 45, epsilon);
  }
  BOOST_AUTO_TEST_CASE (AbsoluteMoveTests)
  {
    volkov::Rectangle shape ({1, 1}, 5, 9);
    volkov::Shape *rectangle = & shape;
    rectangle->move (14, 24);
    BOOST_CHECK_CLOSE (shape.getWidth(), 5, epsilon);
    BOOST_CHECK_CLOSE (shape.getHeight(), 9, epsilon);
    BOOST_CHECK_CLOSE(shape.getFrameRect().pos.y, 25.0, epsilon);
    BOOST_CHECK_CLOSE(shape.getFrameRect().pos.x, 15.0, epsilon);
    BOOST_CHECK_CLOSE (rectangle->getArea(), 45, epsilon);
  }
  BOOST_AUTO_TEST_CASE (area_scale)
  {
    volkov::Rectangle shape ({1, 1}, 6, 9);
    volkov::Shape *rectangle = &shape;
    rectangle->scale (3);
    BOOST_CHECK_CLOSE (rectangle->getArea(), 486, epsilon);
  }
  BOOST_AUTO_TEST_CASE (invalid_width)
  {
    BOOST_CHECK_THROW (volkov::Rectangle shape ({1, 1}, -11, 5), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE (invalid_height)
  {
    BOOST_CHECK_THROW (volkov::Rectangle shape ({1, 1}, 7, -3), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE (invalid_scale)
  {
    volkov::Rectangle shape ({1, 1}, 14, 14);
    volkov::Shape *rectangle = &shape;
    BOOST_CHECK_THROW (rectangle->scale(-3), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

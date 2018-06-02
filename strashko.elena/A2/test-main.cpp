#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"

const double EPSILON = 0.001;

using namespace strashko;

BOOST_AUTO_TEST_SUITE(RectS)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    double areaBefore;
    rectangle_t rectangleBefore;
    point_t centre{3.0, -1.0};
    point_t newpos{8.0, 5.0};
    Rectangle rectangle(centre, 4.7, 1.3);
    areaBefore = rectangle.getArea();
    rectangleBefore = rectangle.getFrameRect();
    rectangle.move(newpos);

    BOOST_CHECK_EQUAL(areaBefore, rectangle.getArea());
    BOOST_CHECK_EQUAL(rectangleBefore.height, rectangle.getFrameRect().height);
    BOOST_CHECK_EQUAL(rectangleBefore.width, rectangle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(CompareMoveToXY)
  {
    double areaBefore;
    rectangle_t rectangleBefore;
    point_t centre{3.0, -1.0};
    Rectangle rectangle(centre, 4.7, 1.3);
    areaBefore = rectangle.getArea();
    rectangleBefore = rectangle.getFrameRect();
    rectangle.move(4.5, -2.7);

    BOOST_CHECK_EQUAL(areaBefore, rectangle.getArea());
    BOOST_CHECK_EQUAL(rectangleBefore.height, rectangle.getFrameRect().height);
    BOOST_CHECK_EQUAL(rectangleBefore.width, rectangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, 7.5);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, -3.7);
  }

  BOOST_AUTO_TEST_CASE(EnlargementOfArea)
  {
    double areaBefore;
    point_t centre{4.2, 6.4};
    Rectangle rectangle(centre, 3.2, 1.0);
    areaBefore = rectangle.getArea();
    rectangle.scale(0.5);
    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBefore * 0.5 * 0.5, EPSILON);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValue)
  {
    point_t centre{0.0, 0.0};

    BOOST_CHECK_THROW(Rectangle rectangle(centre, -2.7, 3.1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    point_t centre{0.0, 0.0};
    Rectangle rectangle(centre, 4.2, 3.3);
    BOOST_CHECK_THROW(rectangle.scale(-4.8), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircS)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    double areaBefore;
    rectangle_t circleBefore;
    point_t centre{3.0, -1.0};
    point_t newpos{8.0, 5.0};
    Circle circle(centre, 2.1);
    areaBefore = circle.getArea();
    circleBefore = circle.getFrameRect();
    circle.move(newpos);

    BOOST_CHECK_EQUAL(areaBefore, circle.getArea());
    BOOST_CHECK_EQUAL(circleBefore.height, circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(circleBefore.width, circle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(CompareMoveToXY)
  {
    double areaBefore;
    rectangle_t circleBefore;
    point_t centre{3.0, -1.0};
    Circle circle(centre, 1.3);
    areaBefore = circle.getArea();
    circleBefore = circle.getFrameRect();
    circle.move(4.5, -2.7);

    BOOST_CHECK_EQUAL(areaBefore, circle.getArea());
    BOOST_CHECK_EQUAL(circleBefore.height, circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(circleBefore.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, 7.5);
    BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, -3.7);
  }

  BOOST_AUTO_TEST_CASE(EnlargementOfArea)
  {
    double areaBefore;
    point_t centre{4.2, 6.4};
    Circle circle(centre, 1.0);
    areaBefore = circle.getArea();
    circle.scale(0.5);
    BOOST_CHECK_CLOSE(circle.getArea(), areaBefore * 0.5 * 0.5, EPSILON);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValue)
  {
    point_t centre{0.0, 0.0};
    BOOST_CHECK_THROW(Circle circle(centre, -2.7), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    point_t centre{0.0, 0.0};
    Circle circle(centre, 4.2);
    BOOST_CHECK_THROW(circle.scale(-4.8), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

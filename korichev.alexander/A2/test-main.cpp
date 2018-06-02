#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

using namespace korichev;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double h_before = test_rect.getFrameRect().height;
    double w_before = test_rect.getFrameRect().width;
    double a_before = test_rect.getArea();
    test_rect.move({2.0, 3.0});
    BOOST_CHECK_EQUAL(test_rect.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(test_rect.getFrameRect().pos.y, 3.0);
    BOOST_CHECK_EQUAL(a_before, test_rect.getArea());
    BOOST_CHECK_EQUAL(h_before, test_rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_rect.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(MoveByXY)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double h_before = test_rect.getFrameRect().height;
    double w_before = test_rect.getFrameRect().width;
    double a_before = test_rect.getArea();
    test_rect.move(2.0, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(test_rect.getFrameRect().pos.x, 5.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test_rect.getFrameRect().pos.y, 5.0, EPSILON);
    BOOST_CHECK_EQUAL(a_before, test_rect.getArea());
    BOOST_CHECK_EQUAL(h_before, test_rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_rect.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    BOOST_CHECK_THROW(test_rect.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double a_before = test_rect.getArea();
    test_rect.scale(3.0);
    BOOST_CHECK_CLOSE_FRACTION(3.0 * 3.0 * a_before, test_rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidInit)
  {
    BOOST_CHECK_THROW(Rectangle({3.0, 2.0}, 10.0, -10.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({3.0, 2.0}, -10.0, 10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double h_before = test_circle.getFrameRect().height;
    double w_before = test_circle.getFrameRect().width;
    double a_before = test_circle.getArea();
    test_circle.move({2.0, 3.0});
    BOOST_CHECK_EQUAL(test_circle.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(test_circle.getFrameRect().pos.y, 3.0);
    BOOST_CHECK_EQUAL(a_before, test_circle.getArea());
    BOOST_CHECK_EQUAL(h_before, test_circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_circle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(MoveByXY)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double h_before = test_circle.getFrameRect().height;
    double w_before = test_circle.getFrameRect().width;
    double a_before = test_circle.getArea();
    test_circle.move(2.0, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(test_circle.getFrameRect().pos.x, 5.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test_circle.getFrameRect().pos.y, 5.0, EPSILON);
    BOOST_CHECK_EQUAL(a_before, test_circle.getArea());
    BOOST_CHECK_EQUAL(h_before, test_circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_circle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    BOOST_CHECK_THROW(test_circle.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double a_before = test_circle.getArea();
    test_circle.scale(3.0);
    BOOST_CHECK_CLOSE_FRACTION(3.0 * 3.0 * a_before, test_circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidInit)
  {
    BOOST_CHECK_THROW(Circle({3.0, 2.0}, -10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

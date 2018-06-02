#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

const double EPSILON = 0.001;

using namespace semakina;

BOOST_AUTO_TEST_SUITE(TestsForRectangle)

  BOOST_AUTO_TEST_CASE(MoveTo)
  {
    Rectangle rect({0, 0}, 50, 10);
    rectangle_t initialValueRect = rect.getFrameRect();
    double initialValueArea = rect.getArea();
    rect.move({60, 60});
    BOOST_CHECK_EQUAL(initialValueRect.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(initialValueRect.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(initialValueArea, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    Rectangle rect({0, 0}, 50, 10);
    rectangle_t initialValueRect = rect.getFrameRect();
    double initialValueArea = rect.getArea();
    rect.move(30, 20);
    BOOST_CHECK_EQUAL(initialValueRect.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(initialValueRect.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(initialValueArea, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Rectangle rect({0, 0}, 50, 10);
    double initialValueArea = rect.getArea();
    double coefficient = 2;
    rect.scale(coefficient);
    BOOST_CHECK_CLOSE(initialValueArea * coefficient * coefficient, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Parameters)
  {
    BOOST_CHECK_THROW(Rectangle({0, 0}, -50, -10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Rectangle rect({0, 0}, 50, 10);
    BOOST_CHECK_THROW(rect.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestsForCircle)

  BOOST_AUTO_TEST_CASE(MoveTo)
  {
    Circle circ({0, 0}, 50);
    rectangle_t initialValueRect = circ.getFrameRect();
    double initialValueArea = circ.getArea();
    circ.move({60, 60});
    BOOST_CHECK_EQUAL(initialValueRect.width, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(initialValueRect.height, circ.getFrameRect().height);
    BOOST_CHECK_EQUAL(initialValueArea, circ.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    Circle circ({0, 0}, 50);
    rectangle_t initialValueRect = circ.getFrameRect();
    double initialValueArea = circ.getArea();
    circ.move(30, 20);
    BOOST_CHECK_EQUAL(initialValueRect.width, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(initialValueRect.height, circ.getFrameRect().height);
    BOOST_CHECK_EQUAL(initialValueArea, circ.getArea());
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Circle circ({0, 0}, 50);
    double initialValueArea = circ.getArea();
    double coefficient = 2;
    circ.scale(coefficient);
    BOOST_CHECK_CLOSE(initialValueArea * coefficient * coefficient, circ.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Parameters)
  {
    BOOST_CHECK_THROW(Circle({0,0}, -50), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Circle circ({0,0}, 50);
    BOOST_CHECK_THROW(circ.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

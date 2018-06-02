#define BOOST_TEST_MODULE MAIN

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double epsilon = 1e-4;
const double ratio = 3;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    babintseva::Rectangle rect({4, 4}, 5, 9);
    const double widthBefore = rect.getWidth();
    const double heightBefore = rect.getHeight();
    const double areaBefore = rect.getArea();

    rect.move(8, 1);

    BOOST_CHECK_CLOSE(rect.getArea(), areaBefore, epsilon);
    BOOST_CHECK_CLOSE(rect.getWidth(), widthBefore, epsilon);
    BOOST_CHECK_CLOSE(rect.getHeight(), heightBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(InvalidWidth)
  {
    BOOST_CHECK_THROW(babintseva::Rectangle rect({5, 5}, -7, 3), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidHeight)
  {
    BOOST_CHECK_THROW(babintseva::Rectangle rect({5, 5}, 7, -3), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    babintseva::Rectangle rect({5, 5}, 6, 7);
    const double widthBefore = rect.getWidth();
    const double heightBefore = rect.getHeight();
    const double areaBefore = rect.getArea();

    rect.move({4, 3});

    BOOST_CHECK_CLOSE(rect.getArea(), areaBefore, epsilon);
    BOOST_CHECK_CLOSE(rect.getWidth(), widthBefore, epsilon);
    BOOST_CHECK_CLOSE(rect.getHeight(), heightBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameters)
  {
    babintseva::Rectangle rect({4, 4}, 5, 9);
    BOOST_CHECK_THROW(rect.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    babintseva::Rectangle rect({4, 4}, 5, 9);
    babintseva::rectangle_t rectBeforeScaling = rect.getFrameRect();
    const double areaBefore = rect.getArea();

    rect.scale(ratio);

    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, rectBeforeScaling.pos.x, epsilon);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, rectBeforeScaling.pos.y, epsilon);
    BOOST_CHECK_CLOSE(rect.getArea(), areaBefore * ratio * ratio, epsilon);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    babintseva::Circle cir({5, 5}, 2);
    const double cirBefore = cir.getRadius();
    const double areaBefore = cir.getArea();

    cir.move(7, 9);

    BOOST_CHECK_CLOSE(cir.getArea(), areaBefore, epsilon);
    BOOST_CHECK_CLOSE(cir.getRadius(), cirBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    BOOST_CHECK_THROW (babintseva::Circle cir({5, 5}, -2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    babintseva::Circle cir({5, 5}, 2);
    const double cirBefore = cir.getRadius();
    const double areaBefore = cir.getArea();

    cir.move({6, 6});

    BOOST_CHECK_CLOSE(cir.getArea(), areaBefore, epsilon);
    BOOST_CHECK_CLOSE(cir.getRadius(), cirBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameters)
  {
    babintseva::Circle cir({5, 5}, 2);
    BOOST_CHECK_THROW(cir.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    babintseva::Circle cir({5, 5}, 2);
    babintseva::rectangle_t cirBeforeScaling = cir.getFrameRect();
    const double areaBefore = cir.getArea();

    cir.scale(ratio);

    BOOST_CHECK_CLOSE(cir.getArea(), areaBefore * ratio * ratio, epsilon);
    BOOST_CHECK_CLOSE(cir.getFrameRect().pos.x, cirBeforeScaling.pos.x, epsilon);
    BOOST_CHECK_CLOSE(cir.getFrameRect().pos.y, cirBeforeScaling.pos.y, epsilon);
  }

BOOST_AUTO_TEST_SUITE_END()

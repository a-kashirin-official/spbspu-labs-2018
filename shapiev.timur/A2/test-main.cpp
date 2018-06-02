#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(RectangleSuite)

  const double EPSILON = 0.00001;

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    shapiev::Rectangle rect (3.5, 4.8, {4.3, 3.4});
    double widthBefore = rect.getFrameRect().width;
    double heightBefore = rect.getFrameRect().height;

    rect.move ({25,10});

    BOOST_CHECK_EQUAL(widthBefore, rect.getFrameRect().width);

    BOOST_CHECK_EQUAL(heightBefore, rect.getFrameRect().height);

  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    shapiev::Rectangle rect (3.5, 4.8, {4.3, 3.4});

    double widthBefore = rect.getFrameRect().width;
    double heightBefore = rect.getFrameRect().height;

    rect.move (15,5);

    BOOST_CHECK_EQUAL(widthBefore, rect.getFrameRect().width);

    BOOST_CHECK_EQUAL(heightBefore, rect.getFrameRect().height);

  }

  BOOST_AUTO_TEST_CASE(MovingToPointArea)
  {
    shapiev::Rectangle rect (3.5, 4.8, {4.3, 3.4});
    double areaBefore = rect.getArea();

    rect.move ({25,10});

    BOOST_CHECK_EQUAL(areaBefore, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(MovingOnPointArea)
  {
    shapiev::Rectangle rect (3.5, 4.8, {4.3, 3.4});
    double areaBefore = rect.getArea();

    rect.move (15,5);

    BOOST_CHECK_EQUAL(areaBefore, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    const double ratio = 3.3;

    shapiev::Rectangle rect (3.5, 4.8, {4.3, 3.4});
    double areaBeforeScaling = rect.getArea();

    rect.scale(ratio);

    BOOST_CHECK_CLOSE(ratio * ratio * areaBeforeScaling, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    shapiev::Rectangle rect (3.5, 4.8, { 4.3, 3.4 });
    BOOST_CHECK_THROW (rect.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW( shapiev::Rectangle rect (3.5, -4.8, {4.3, 3.4}), std::invalid_argument );
    BOOST_CHECK_THROW( shapiev::Rectangle rect (-3.5, 4.8, {4.3, 3.4}), std::invalid_argument );
    BOOST_CHECK_THROW( shapiev::Rectangle rect (-3.5, -4.8, {4.3, 3.4}), std::invalid_argument );
  }

  BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

  const double EPSILON = 0.00001;

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    shapiev::Circle circle ({5.9, 7.1}, 3.0);
    double widthBefore = circle.getFrameRect().width;
    double heightBefore = circle.getFrameRect().height;


    circle.move ({20,10});

    BOOST_CHECK_EQUAL(widthBefore, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBefore, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    shapiev::Circle circle ({5.9, 7.1}, 3.0);
    double widthBefore = circle.getFrameRect().width;
    double heightBefore = circle.getFrameRect().height;

    circle.move (10,5);

    BOOST_CHECK_EQUAL(widthBefore, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBefore, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MovingToPointArea)
  {
    shapiev::Circle circle ({5.9, 7.1}, 3.0);
    double areaBefore = circle.getArea();


    circle.move ({20,10});

    BOOST_CHECK_EQUAL(areaBefore, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(MovingOnPointArea)
  {
    shapiev::Circle circle ({5.9, 7.1}, 3.0);
    double areaBefore = circle.getArea();


    circle.move (10,5);

    BOOST_CHECK_EQUAL(areaBefore, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    const double ratio = 3.3;

    shapiev::Circle circle ({5.9, 7.1}, 3.0);
    double areaBeforeScaling = circle.getArea();

    circle.scale(ratio);

    BOOST_CHECK_CLOSE(ratio * ratio * areaBeforeScaling, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    shapiev::Circle circle ({ 5.9, 7.1 }, 3.0);
    BOOST_CHECK_THROW(circle.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW( shapiev::Circle circle ({5.9, 7.1}, -3.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_SUITE_END()

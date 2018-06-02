#define BOOST_TEST_MODULE Main

#include "rectangle.hpp"
#include "circle.hpp"
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

using namespace sokolova;
const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    point_t centre{2.0, 4.0};
    Rectangle rect(centre, 5.0, 6.0);
    rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();

    point_t newpos{5.0, 2.0};
    rect.move(newpos);
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    point_t centre{2.0,4.0};
    Rectangle rect(centre, 5.0, 6.0) ;
    rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();

    rect.move(-10.0, 50.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, -8.0);
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, 54.0);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    point_t centre{2.0, 4.0};
    Rectangle rect(centre, 5.0, 6.0);
    double areaBeforeScaling = rect.getArea();
    const double factor = 3.3;

    rect.scale(factor);
    BOOST_CHECK_CLOSE(factor * factor * areaBeforeScaling, rect.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    point_t centre{10.0, 20.0};
    BOOST_CHECK_THROW( Rectangle rect(centre, 10.0, -15.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    point_t centre{2.0, 4.0};
    Rectangle rect(centre, 5.0, 6.0);
    BOOST_CHECK_THROW( rect.scale(-1.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    point_t centre{5.0, 3.0};
    Circle circle(centre, 22.0);
    rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();

    point_t newpos{15.0, 20.0};
    circle.move(newpos);
    BOOST_CHECK_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width/2, circle.getFrameRect().width/2);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height/2, circle.getFrameRect().height/2);

  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    point_t centre{5.0, 3.0};
    Circle circle(centre, 22.0);
    rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();

    circle.move(-10.0, 50.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width/2, circle.getFrameRect().width/2);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height/2, circle.getFrameRect().height/2);
    BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, -5.0);
    BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, 53.0);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    point_t centre{5.0, 3.0};
    Circle circle(centre, 22.0);
    double areaBeforeScaling = circle.getArea();
    const double factor = 3.3;

    circle.scale(factor);
    BOOST_CHECK_CLOSE(factor * factor * areaBeforeScaling, circle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    point_t centre{10.0, 20.0};
    BOOST_CHECK_THROW(Circle circle(centre, -15.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    point_t centre{5.0, 3.0};
    Circle circle(centre, 22.0);
    BOOST_CHECK_THROW( circle.scale(-1.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()


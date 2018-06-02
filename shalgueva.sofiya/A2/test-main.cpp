#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"

const double EPSILON = 1e-8;

BOOST_AUTO_TEST_SUITE(Rectangl)

BOOST_AUTO_TEST_CASE(InvalidArgumentsConstructor)
{
  BOOST_CHECK_THROW( shalgueva::Rectangle({-7.0, 21.0, {10.0, 20.0}}), std::invalid_argument );
  BOOST_CHECK_THROW( shalgueva::Rectangle({7.0, -21.0, {10.0, 20.0}}), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(InvalidArgumentScale)
{
  shalgueva::Rectangle rect{ {5.0, 6.0, {2.0, 4.0}} };
  BOOST_CHECK_THROW( rect.scale(-1.0), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(MoveToPoint)
{
  shalgueva::Rectangle rect{ { 5.0, 6.0, {2.0, 4.0}} };
  shalgueva::rectangle_t rectBeforeMoving = rect.getFrameRect();
  double areaBeforeMoving = rect.getArea();
  shalgueva::point_t positionBeforeMoving = {2.0, 4.0};
  BOOST_CHECK_CLOSE(areaBeforeMoving, rect.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(positionBeforeMoving.x, rect.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(positionBeforeMoving.y, rect.getFrameRect().pos.y);
  BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);

  shalgueva::point_t positionAfterMoving = {21.0, 21.0};
  rect.move(positionAfterMoving);
  BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
  BOOST_CHECK_EQUAL(positionAfterMoving.x, rect.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(positionAfterMoving.y, rect.getFrameRect().pos.y);
  BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(MoveByAxes)
{
  shalgueva::Rectangle rect{ {5.0, 6.0, {2.0, 4.0}} };
  shalgueva::rectangle_t rectBeforeMoving = rect.getFrameRect();
  double areaBeforeMoving = rect.getArea();
  shalgueva::point_t positionBeforeMoving = {2.0, 4.0};
  BOOST_CHECK_CLOSE(areaBeforeMoving, rect.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(positionBeforeMoving.x, rect.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(positionBeforeMoving.y, rect.getFrameRect().pos.y);
  BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);

  shalgueva::point_t positionAfterMoving = {-5.0, 25.0};
  rect.move(-7.0, 21.0);
  BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
  BOOST_CHECK_CLOSE(positionAfterMoving.x, rect.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(positionAfterMoving.y, rect.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(Scale)
{
  shalgueva::Rectangle rect{ {5.0, 6.0, {2.0, 4.0}} };
  double areaBeforeScaling = rect.getArea();
  BOOST_CHECK_CLOSE(areaBeforeScaling, rect.getArea(), EPSILON);

  const double coeff = 2.0;
  rect.scale(coeff);
  BOOST_CHECK_CLOSE(coeff * coeff * areaBeforeScaling, rect.getArea(), EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle)

BOOST_AUTO_TEST_CASE(InvalidArgumentsConstructor)
{
  BOOST_CHECK_THROW(shalgueva::Circle({10.0, 20.0}, -15.0), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(InvalidArgumentScale)
{
  shalgueva::Circle circle{ {5.0, 3.0}, 22.0 };
  BOOST_CHECK_THROW( circle.scale(-1.0), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(MoveToPoint)
 {
  shalgueva::Circle circle{ {5.0, 3.0}, 22.0 };
  shalgueva::rectangle_t rectBeforeMoving = circle.getFrameRect();
  double areaBeforeMoving = circle.getArea();
  shalgueva::point_t positionBeforeMoving = {5.0, 3.0};
  BOOST_CHECK_EQUAL(positionBeforeMoving.x, circle.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(positionBeforeMoving.y, circle.getFrameRect().pos.y);
  BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);

  shalgueva::point_t positionAfterMoving = {15.0, 20.0};
  circle.move({15.0, 20.0});
  BOOST_CHECK_EQUAL(positionAfterMoving.x, circle.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(positionAfterMoving.y, circle.getFrameRect().pos.y);
  BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(MoveByAxes)
{
  shalgueva::Circle circle{ {5.0, 3.0}, 22.0 };
  shalgueva::rectangle_t rectBeforeMoving = circle.getFrameRect();
  double areaBeforeMoving = circle.getArea();
  shalgueva::point_t positionBeforeMoving = {5.0, 3.0};
  BOOST_CHECK_EQUAL(positionBeforeMoving.x, circle.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(positionBeforeMoving.y, circle.getFrameRect().pos.y);
  BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);

  shalgueva::point_t positionAfterMoving = {-5.0, 53.0};
  circle.move(-10.0, 50.0);
  BOOST_CHECK_CLOSE(positionAfterMoving.x, circle.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(positionAfterMoving.y, circle.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);
}

 BOOST_AUTO_TEST_CASE(Scale)
{
  shalgueva::Circle circle{ {5.0, 3.0}, 22.0 };
  double areaBeforeScaling = circle.getArea();
  BOOST_CHECK_CLOSE(areaBeforeScaling, circle.getArea(), EPSILON);

  const double coeff = 3.3;
  circle.scale(coeff);
  BOOST_CHECK_CLOSE(coeff * coeff * areaBeforeScaling, circle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

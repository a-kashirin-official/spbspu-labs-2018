#define BOOST_TEST_MODULE

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double POGR = 1e-8;

BOOST_AUTO_TEST_SUITE(Rectangle)

  BOOST_AUTO_TEST_CASE(InvalidArgumentsConstructor)
  {
    BOOST_CHECK_THROW( gerastyonok::Rectangle({-3.0, 88.5, {0.0, 0.0}}), std::invalid_argument );
    BOOST_CHECK_THROW( gerastyonok::Rectangle({7.0, -21.0, {0.0, 0.0}}), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScale)
  {
    gerastyonok::Rectangle rect{ {3.0, 7.0, {0.0, 0.0}} };
    BOOST_CHECK_THROW( rect.scale(-1.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    gerastyonok::Rectangle rect{ { 5.0, 6.0, {0.0, 0.0}} };
    gerastyonok::rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();
    gerastyonok::point_t positionBeforeMoving = {0.0, 0.0};
    BOOST_CHECK_CLOSE(areaBeforeMoving, rect.getArea(), POGR);
    BOOST_CHECK_EQUAL(positionBeforeMoving.x, rect.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(positionBeforeMoving.y, rect.getFrameRect().pos.y);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);

    gerastyonok::point_t positionAfterMoving = {3.0, 3.0};
    rect.move(positionAfterMoving);
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(positionAfterMoving.x, rect.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(positionAfterMoving.y, rect.getFrameRect().pos.y);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MoveByAxes)
  {
    gerastyonok::Rectangle rect{ {5.0, 6.0, {0.0, 0.0}} };
    gerastyonok::rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();
    gerastyonok::point_t positionBeforeMoving = {0.0, 0.0};
    BOOST_CHECK_CLOSE(areaBeforeMoving, rect.getArea(), POGR);
    BOOST_CHECK_EQUAL(positionBeforeMoving.x, rect.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(positionBeforeMoving.y, rect.getFrameRect().pos.y);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);

    gerastyonok::point_t positionAfterMoving = {-7.0, 3.0};
    rect.move(-7.0, 3.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_CLOSE(positionAfterMoving.x, rect.getFrameRect().pos.x, POGR);
    BOOST_CHECK_CLOSE(positionAfterMoving.y, rect.getFrameRect().pos.y, POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    gerastyonok::Rectangle rect{ {5.0, 6.0, {0.0, 0.0}} };
    double areaBeforeScaling = rect.getArea();
    BOOST_CHECK_CLOSE(areaBeforeScaling, rect.getArea(), POGR);

    const double k = 2.0;
    rect.scale(k);
    BOOST_CHECK_CLOSE(k * k * areaBeforeScaling, rect.getArea(), POGR);
  }

  BOOST_AUTO_TEST_SUITE_END()

  BOOST_AUTO_TEST_SUITE(Circle)

  BOOST_AUTO_TEST_CASE(InvalidArgumentsConstructor)
  {
    BOOST_CHECK_THROW(gerastyonok::Circle(-37.0, {00.0, 00.0}), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScale)
  {
    gerastyonok::Circle circle{ 7.0, {0.0, 0.0}};
    BOOST_CHECK_THROW( circle.scale(-1.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    gerastyonok::Circle circle{ 3.0, {0.0, 0.0} };
    gerastyonok::rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();
    gerastyonok::point_t positionBeforeMoving = {0.0, 0.0};
    BOOST_CHECK_EQUAL(positionBeforeMoving.x, circle.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(positionBeforeMoving.y, circle.getFrameRect().pos.y);
    BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);

    gerastyonok::point_t positionAfterMoving = {3.0, 7.0};
    circle.move({3.0, 7.0});
    BOOST_CHECK_EQUAL(positionAfterMoving.x, circle.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(positionAfterMoving.y, circle.getFrameRect().pos.y);
    BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MoveByAxes)
  {
    gerastyonok::Circle circle{ 3.0, {0.0, 0.0} };
    gerastyonok::rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();
    gerastyonok::point_t positionBeforeMoving = {0.0, 0.0};
    BOOST_CHECK_EQUAL(positionBeforeMoving.x, circle.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(positionBeforeMoving.y, circle.getFrameRect().pos.y);
    BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);

    gerastyonok::point_t positionAfterMoving = {-5.0, 3.0};
    circle.move(-5.0, 3.0);
    BOOST_CHECK_CLOSE(positionAfterMoving.x, circle.getFrameRect().pos.x, POGR);
    BOOST_CHECK_CLOSE(positionAfterMoving.y, circle.getFrameRect().pos.y, POGR);
    BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);
  }

 BOOST_AUTO_TEST_CASE(Scale)
 {
   gerastyonok::Circle circle{ 3.0, {0.0, 0.0} };
   double areaBeforeScaling = circle.getArea();
   BOOST_CHECK_CLOSE(areaBeforeScaling, circle.getArea(), POGR);

   const double k = 7.7;
   circle.scale(k);
   BOOST_CHECK_CLOSE(k * k * areaBeforeScaling, circle.getArea(), POGR);
 }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Triangle)

  BOOST_AUTO_TEST_CASE(MoveByAxes)
  {
    gerastyonok::Triangle triangle({ 1.0, 1.0 }, { 2.0, 10.0 }, { 0.0, 0.0 });
    gerastyonok::rectangle_t rectBeforeMoving = triangle.getFrameRect();
    double areaBeforeMoving = triangle.getArea();
    gerastyonok::point_t positionBeforeMoving = { 1.0, 5.0 };
    BOOST_CHECK_EQUAL(positionBeforeMoving.x, triangle.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(positionBeforeMoving.y, triangle.getFrameRect().pos.y);
    BOOST_CHECK_CLOSE(areaBeforeMoving, triangle.getArea(), POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, triangle.getFrameRect().width);  
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, triangle.getFrameRect().height);

    gerastyonok::point_t positionAfterMoving = { -4.0, 6.6666666666666661 };
    triangle.move(-5.0, 3.0);
    BOOST_CHECK_CLOSE(positionAfterMoving.x, triangle.getCenter().x, POGR);
    BOOST_CHECK_CLOSE(positionAfterMoving.y, triangle.getCenter().y, POGR);
    BOOST_CHECK_CLOSE(areaBeforeMoving, triangle.getArea(), POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, triangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, triangle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    gerastyonok::Triangle triangle({1.0, 1.0}, {2.0, 10.0}, {0.0, 0.0});
    gerastyonok::rectangle_t rectBeforeMoving = triangle.getFrameRect();
    double areaBeforeMoving = triangle.getArea();
    gerastyonok::point_t positionBeforeMoving = {1.0, 3.6666666666666665 };
    BOOST_CHECK_EQUAL(positionBeforeMoving.x, triangle.getCenter().x);
    BOOST_CHECK_EQUAL(positionBeforeMoving.y, triangle.getCenter().y);
    BOOST_CHECK_CLOSE(areaBeforeMoving, triangle.getArea(), POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, triangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, triangle.getFrameRect().height);

    gerastyonok::point_t positionAfterMoving = {1.0, 2.0};
    triangle.move({1.0, 2.0});
    BOOST_CHECK_EQUAL(positionAfterMoving.x, triangle.getCenter().x);
    BOOST_CHECK_EQUAL(positionAfterMoving.y, triangle.getCenter().y);
    BOOST_CHECK_CLOSE(areaBeforeMoving, triangle.getArea(), POGR);
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, triangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, triangle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    gerastyonok::Triangle triangle({1.0, 1.0}, {2.0, 10.0}, {0.0, 0.0});
    double areaBeforeScaling = triangle.getArea();
    BOOST_CHECK_CLOSE(areaBeforeScaling, triangle.getArea(), POGR);

    const double k = 3.3;
    triangle.scale(k);
    BOOST_CHECK_CLOSE(k * k * areaBeforeScaling, triangle.getArea(), POGR);
  }

  BOOST_AUTO_TEST_SUITE_END()

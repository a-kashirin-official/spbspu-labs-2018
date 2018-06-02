#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double EPSILON = 10e-6;

using namespace hvetsckovich;

BOOST_AUTO_TEST_SUITE(RectangleTests)
  BOOST_AUTO_TEST_CASE(testRectangleSizesImmutabilityWhenMoveInNewPosition)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    double rectangleWidthBeforeMove = rectangle.getFrameRect().width;
    double rectangleHeightBeforeMove = rectangle.getFrameRect().height;
    double rectangleAreaBeforeMove = rectangle.getArea();

    rectangle.move({ 10.0, -10.0 });

    BOOST_REQUIRE_EQUAL(rectangleWidthBeforeMove, rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleHeightBeforeMove, rectangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(rectangleAreaBeforeMove, rectangle.getArea());
  }

  BOOST_AUTO_TEST_CASE(testRectangleSizesImmutabilityWhenMoveByOffset)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    double rectangleWidthBeforeMove = rectangle.getFrameRect().width;
    double rectangleHeightBeforeMove = rectangle.getFrameRect().height;
    double rectangleAreaBeforeMove = rectangle.getArea();

    rectangle.move(-5.0, 5.0);

    BOOST_REQUIRE_EQUAL(rectangleWidthBeforeMove, rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleHeightBeforeMove, rectangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(rectangleAreaBeforeMove, rectangle.getArea());
  }

  BOOST_AUTO_TEST_CASE(testRectangleQuadraticAreaChangeAfterScale)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    double rectangleAreaBeforeScale = rectangle.getArea();
    double factor = 2.0;
    rectangle.scale(factor);

    BOOST_CHECK_CLOSE(factor * factor * rectangleAreaBeforeScale, rectangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(testRectangleConstructorExceptions)
  {
    BOOST_REQUIRE_THROW(Rectangle({ 5.0, 0.0 }, -10.0, 5.0), std::invalid_argument);
    BOOST_REQUIRE_THROW(Rectangle({ 5.0, 0.0 }, 10.0, -5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(testRectangleScaleException)
  {
    Rectangle rectangle({ 5.0, 0.0 }, 10.0, 5.0);

    BOOST_REQUIRE_THROW(rectangle.scale(-3.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTests)
  BOOST_AUTO_TEST_CASE(testCircleSizesImmutabilityWhenMoveInNewPosition)
  {
    Circle circle({ -1.0, 13.0 }, 5.0);
    double circleWidthBeforeMove = circle.getFrameRect().width;
    double circleHeightBeforeMove = circle.getFrameRect().height;
    double circleAreaBeforeMove = circle.getArea();

    circle.move({ 10.0, 10.0 });

    BOOST_REQUIRE_EQUAL(circleWidthBeforeMove, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(circleHeightBeforeMove, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(circleAreaBeforeMove, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(testCircleSizesImmutabilityWhenMoveByOffset)
  {
    Circle circle({ -1.0, 13.0 }, 5.0);
    double circleWidthBeforeMove = circle.getFrameRect().width;
    double circleHeightBeforeMove = circle.getFrameRect().height;
    double circleAreaBeforeMove = circle.getArea();

    circle.move(-5.0, 5.0);

    BOOST_REQUIRE_EQUAL(circleWidthBeforeMove, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(circleHeightBeforeMove, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(circleAreaBeforeMove, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(testCircleQuadraticAreaChangeAfterScale)
  {
    Circle circle({ -1.0, 13.0 }, 5.0);
    double circleAreaBeforeScale = circle.getArea();
    double ratio = 2.0;

    circle.scale(ratio);

    BOOST_CHECK_CLOSE(ratio * ratio * circleAreaBeforeScale, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(testCircleConstructorExceptions)
  {
    BOOST_CHECK_THROW(Circle({ -5.0, 5.0 }, -2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(testCircleScaleException)
  {
    Circle circle({ -5.0, -5.0 }, 2.0);

    BOOST_CHECK_THROW(circle.scale(-3.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TriangleTests)
  BOOST_AUTO_TEST_CASE(testTriangleSizesImmutabilityWhenMoveInNewPosition)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    double triangleWidthBeforeMove = triangle.getFrameRect().width;
    double triangleHeightBeforeMove = triangle.getFrameRect().height;
    double triangleAreaBeforeMove = triangle.getArea();

    triangle.move({ 10.0, 10.0 });

    BOOST_REQUIRE_EQUAL(triangleWidthBeforeMove, triangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(triangleHeightBeforeMove, triangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(triangleAreaBeforeMove, triangle.getArea());
  }

  BOOST_AUTO_TEST_CASE(testTriangleSizesImmutabilityWhenMoveByOffset)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    double circleWidthBeforeMove = triangle.getFrameRect().width;
    double circleHeightBeforeMove = triangle.getFrameRect().height;
    double circleAreaBeforeMove = triangle.getArea();

    triangle.move(-5.0, 5.0);

    BOOST_REQUIRE_EQUAL(circleWidthBeforeMove, triangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(circleHeightBeforeMove, triangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(circleAreaBeforeMove, triangle.getArea());
  }

  BOOST_AUTO_TEST_CASE(testTriangleQuadraticAreaChangeAfterScale)
  {
    Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
    double circleAreaBeforeScale = triangle.getArea();
    double ratio = 4.0;

    triangle.scale(ratio);

    BOOST_CHECK_CLOSE(ratio * ratio * circleAreaBeforeScale, triangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(testTriangleCenterImmutabilityAfterScale)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    point_t oldPos = triangle.getPos();
    double ratio = 4.0;

    triangle.scale(ratio);

    BOOST_REQUIRE_EQUAL(oldPos.x, triangle.getPos().x);
    BOOST_REQUIRE_EQUAL(oldPos.y, triangle.getPos().y);
  }

  BOOST_AUTO_TEST_CASE(testTriangleScaleException)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });

    BOOST_CHECK_THROW(triangle.scale(-3.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

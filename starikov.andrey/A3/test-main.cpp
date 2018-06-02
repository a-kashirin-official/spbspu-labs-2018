#define BOOST_TEST_MODULE mainTests
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace starikov;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(InvariabilityCircleAfterCentreMove)
  {
    starikov::Circle objCircle(8.32, {23.01, 45.21});
    double heightBeforeMove = objCircle.getFrameRect().height;
    double widthBeforeMove = objCircle.getFrameRect().width;
    objCircle.move(3.12, 7.75);
    BOOST_REQUIRE_CLOSE(objCircle.getFrameRect().width, widthBeforeMove, EPSILON);
    BOOST_REQUIRE_CLOSE(objCircle.getFrameRect().height, heightBeforeMove, EPSILON);
    BOOST_REQUIRE_CLOSE((objCircle.getFrameRect().width / 2), 8.32, EPSILON);
    BOOST_REQUIRE_CLOSE(objCircle.getArea(), (M_PI * 8.32 * 8.32), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvariabilityCircleAfterAxisMove)
  {
    starikov::Circle objCircle(8.32, {23.01, 45.21});
    double heightBeforeMove = objCircle.getFrameRect().height;
    double widthBeforeMove = objCircle.getFrameRect().width;
    objCircle.move(43.21,54.22);
    BOOST_REQUIRE_CLOSE(objCircle.getFrameRect().width, widthBeforeMove, EPSILON);
    BOOST_REQUIRE_CLOSE(objCircle.getFrameRect().height, heightBeforeMove, EPSILON);
    BOOST_REQUIRE_CLOSE((objCircle.getFrameRect().width / 2), 8.32, EPSILON);
    BOOST_REQUIRE_CLOSE(objCircle.getArea(), (M_PI * 8.32 * 8.32), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CircleQuadraticChangeAreaAfterScale)
  {
    starikov::Circle objCircle(8.32, {23.01, 45.21});
    objCircle.scale(7.0);
    BOOST_REQUIRE_CLOSE(objCircle.getArea(), (M_PI * 8.32 * 8.32 * pow(7,2)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CircleCheckIncorrectParametrs)
  {
    BOOST_CHECK_THROW(starikov::Circle objCircle(-5.0,{23.01,45.21}),std::invalid_argument);
    starikov::Circle objCircle(8.32, {23.01, 45.21});
    BOOST_CHECK_THROW(objCircle.scale(-9.0),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(InvariabilityRectangleAfterCentreMove)
  {
    starikov::Rectangle objRectangle({14.21, 43.11, 30.54, 55.98});
    objRectangle.move(3.12, 7.75);
    BOOST_REQUIRE_CLOSE((objRectangle.getFrameRect().width), 14.21, EPSILON);
    BOOST_REQUIRE_CLOSE((objRectangle.getFrameRect().height), 43.11, EPSILON);
    BOOST_REQUIRE_CLOSE(objRectangle.getArea(), (14.21 * 43.11), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvariabilityRectangleAfterAxisMove)
  {
    starikov::Rectangle objRectangle({14.21, 43.11, 30.54, 55.98});
    objRectangle.move(43.21,54.22);
    BOOST_REQUIRE_CLOSE((objRectangle.getFrameRect().width), 14.21, EPSILON);
    BOOST_REQUIRE_CLOSE((objRectangle.getFrameRect().height), 43.11, EPSILON);
    BOOST_REQUIRE_CLOSE(objRectangle.getArea(), (14.21 * 43.11), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RectangleQuadraticChangeAreaAfterScale)
  {
    starikov::Rectangle objRectangle({14.21, 43.11, 30.54, 55.98});
    objRectangle.scale(7.0);
    BOOST_REQUIRE_CLOSE(objRectangle.getArea(), (14.21 * 43.11 * pow(7,2)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RectangleCheckIncorrectParametrs)
  {
    BOOST_CHECK_THROW(starikov::Rectangle objRectangle({-8.0, 43.11, 30.54, 55.98}),std::invalid_argument);
    BOOST_CHECK_THROW(starikov::Rectangle objRectangle({14.21, -10.0, 30.54, 55.98}),std::invalid_argument);
    BOOST_CHECK_THROW(starikov::Rectangle objRectangle({-20.0, -11.0, 30.54, 55.98}),std::invalid_argument);
    starikov::Rectangle objRectangle({14.21, 43.11, 30.54, 55.98});
    BOOST_CHECK_THROW(objRectangle.scale(-9.0),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeTests)

BOOST_AUTO_TEST_CASE(InvariabilityCompositeShapeAfterCentreMove)
{
  starikov::Rectangle rect({14.21, 43.11, 30.54, 55.98});
  std::shared_ptr <starikov::Shape> rectanglePtr = std::make_shared <starikov::Rectangle> (rect);
  starikov::CompositeShape objComposite(rectanglePtr);
  objComposite.move(3.12, 7.75);
  BOOST_REQUIRE_CLOSE((objComposite.getFrameRect().width), 14.21, EPSILON);
  BOOST_REQUIRE_CLOSE((objComposite.getFrameRect().height), 43.11, EPSILON);
  BOOST_REQUIRE_CLOSE(objComposite.getArea(), (14.21 * 43.11), EPSILON);
}

BOOST_AUTO_TEST_CASE(InvariabilityCompositeAfterAxisMove)
{
  starikov::Rectangle rect({14.21, 43.11, 30.54, 55.98});
  std::shared_ptr <starikov::Shape> rectanglePtr = std::make_shared <starikov::Rectangle> (rect);
  starikov::CompositeShape objComposite(rectanglePtr);
  BOOST_REQUIRE_CLOSE((objComposite.getFrameRect().width), 14.21, EPSILON);
  BOOST_REQUIRE_CLOSE((objComposite.getFrameRect().height), 43.11, EPSILON);
  BOOST_REQUIRE_CLOSE(objComposite.getArea(), (14.21 * 43.11), EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeQuadraticChangeAreaAfterScale)
{
  starikov::Rectangle rect({14.21, 43.11, 30.54, 55.98});
  std::shared_ptr <starikov::Shape> rectanglePtr = std::make_shared <starikov::Rectangle> (rect);
  starikov::CompositeShape objComposite(rectanglePtr);
  double area = objComposite.getArea();
  objComposite.scale(7.0);
  BOOST_REQUIRE_CLOSE((objComposite.getShapeInfo().width * objComposite.getShapeInfo().height), (area * pow(7,2)), EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

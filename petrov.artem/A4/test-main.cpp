#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPS_TEST = 1e-7;

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(ImmutableRadiusMoveByDeltaTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.move( 5.27, 18.9 );
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height / 2, 4.3);
  }

  BOOST_AUTO_TEST_CASE(ImmutableRadiusMoveToPosTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.move( { 5.27, 18.9 } );
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height / 2, 4.3);
  }

  BOOST_AUTO_TEST_CASE(ImmutableAreaMoveByDeltaTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.move( 5.27, 18.9 );
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 4.3 * 4.3 * M_PI, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(ImmutableAreaMoveToPosTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.move( { 5.27, 18.9 } );
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 4.3 * 4.3 * M_PI, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(CircleRotate)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.move( 5.27, 18.9 );
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 4.3 * 4.3 * M_PI, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.scale(5.0);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 4.3 * 4.3 * M_PI * 5.0 * 5.0, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentInCircleConstructorTest)
  {
    BOOST_CHECK_THROW(petrov::Circle( { 15.32, 1.23 }, -1.0 ), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentInCircleScaleTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    BOOST_CHECK_THROW(circle.scale(-1), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(ImmutableHeightMoveByDeltaTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.move( 5.27, 18.9 );
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 10.79);
  }

  BOOST_AUTO_TEST_CASE(ImmutableHeightMoveToPosTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.move( { 5.27, 18.9 } );
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 10.79);
  }

  BOOST_AUTO_TEST_CASE(ImmutableWidthMoveByDeltaTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.move( 5.27, 18.9 );
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 7.0);
  }

  BOOST_AUTO_TEST_CASE(ImmutableWidthMoveToPosTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.move( { 5.27, 18.9 } );
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 7.0);
  }

  BOOST_AUTO_TEST_CASE(ImmutableAreaMoveByDeltaTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.move( 5.27, 18.9 );
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 7.0 * 10.79, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(ImmutableAreaMoveToPosTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.move( { 5.27, 18.9 } );
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 7.0 * 10.79, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.scale(5.0);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 7.0 * 10.79 * 5.0 * 5.0, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentInRectangleConstructorTest)
  {
    BOOST_CHECK_THROW(petrov::Rectangle( { 15.32, 16.23 }, -3.26, 7.15 ), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentInRectangleScaleTest)
  {
    petrov::Rectangle rectangle{ { 15.32, 16.23 }, 6.21, 8.0 };
    BOOST_CHECK_THROW(rectangle.scale(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ChangeFrameRectRotateTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 16.0 };
    rectangle.rotate(90);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().width, 16.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().height, 7.0, EPS_TEST);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(ImmutableAreaMoveByDeltaTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.move( 1.37, 22.7 );
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), circle.getArea() + rectangle.getArea(), EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(ImmutableAreaMoveToPosTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.move( { 1.0, 2.0 } );
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), circle.getArea() + rectangle.getArea(), EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), (circle.getArea() + rectangle.getArea()) * 2.0 * 2.0,
      EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(RemoveShapeTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.removeShape(1);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, rectangle.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, rectangle.getFrameRect().pos.y);
    BOOST_REQUIRE_EQUAL(compositeShape.getArea(), rectangle.getArea());
    BOOST_REQUIRE_EQUAL(compositeShape.getSize(), 1);
  }

  BOOST_AUTO_TEST_CASE(ImmutableCentreScale)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    petrov::rectangle_t frameRect = compositeShape.getFrameRect();
    compositeShape.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.x, frameRect.pos.x, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.y, frameRect.pos.y, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(ImmutableHeightMoveByDeltaTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    petrov::rectangle_t frameRect = compositeShape.getFrameRect();
    compositeShape.move( 1.3, 2.5 );
    BOOST_REQUIRE_EQUAL(frameRect.height, compositeShape.getFrameRect().height);

  }

  BOOST_AUTO_TEST_CASE(ImmutableHeightMoveToPosTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    petrov::rectangle_t frameRect = compositeShape.getFrameRect();
    compositeShape.move( { 0.0, 2.3 } );
    BOOST_REQUIRE_EQUAL(frameRect.height, compositeShape.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(ImmutableWidthMoveByDeltaTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    petrov::rectangle_t frameRect = compositeShape.getFrameRect();
    compositeShape.move( 1.3, 2.5 );
    BOOST_REQUIRE_EQUAL(frameRect.width, compositeShape.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(ImmutableWidthMoveToPosTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    petrov::rectangle_t frameRect = compositeShape.getFrameRect();
    compositeShape.move( { 0.0, 2.3 } );
    BOOST_REQUIRE_EQUAL(frameRect.width, compositeShape.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(DeleteShapesTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.deleteShapes();
    BOOST_REQUIRE_EQUAL(compositeShape.getSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleFactor)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    petrov::CompositeShape compositeShape(circlePtr);
    BOOST_CHECK_THROW(compositeShape.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidIdenticalShapeTest)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    petrov::CompositeShape compositeShape(circlePtr);
    BOOST_CHECK_THROW(compositeShape.addShape(circlePtr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidShapeNumberRemove)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    petrov::CompositeShape compositeShape(circlePtr);
    BOOST_CHECK_THROW(compositeShape.removeShape(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(InvalidRemoveInCompositeShape)
  {
    petrov::Circle circle{ { 15.32, 1.23 }, 4.3 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    petrov::CompositeShape compositeShape(circlePtr);
    compositeShape.deleteShapes();
    BOOST_CHECK_THROW(compositeShape.removeShape(1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(ChangeFrameRectRotateTest)
  {
    petrov::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 16.0 };
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
    petrov::CompositeShape compositeShape(rectanglePtr);
    compositeShape.rotate(90);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().width, 16.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().height, 7.0, EPS_TEST);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTests)

  BOOST_AUTO_TEST_CASE(MatrixSplitting)
  {
    petrov::Circle circleM{ { -2.0, -2.0 }, 2.0 };
    petrov::Rectangle rectangleM1{ { -2.0, 0.0 }, 2.0, 2.0 };
    petrov::Rectangle rectangleM2{ { 1.0, 1.0 }, 6.0, 3.0 };
    petrov::Rectangle rectangleM3{ { 3.0, 1.0 }, 2.0, 4.0 };
    petrov::Rectangle rectangleM4{ { 3.0, 3.0 }, 4.0, 4.0 };

    std::shared_ptr< petrov::Shape > circlePtrM = std::make_shared< petrov::Circle >(circleM);
    std::shared_ptr< petrov::Shape > rectanglePtrM1 = std::make_shared< petrov::Rectangle >(rectangleM1);
    std::shared_ptr< petrov::Shape > rectanglePtrM2 = std::make_shared< petrov::Rectangle >(rectangleM2);
    std::shared_ptr< petrov::Shape > rectanglePtrM3 = std::make_shared< petrov::Rectangle >(rectangleM3);
    std::shared_ptr< petrov::Shape > rectanglePtrM4 = std::make_shared< petrov::Rectangle >(rectangleM4);

    petrov::Matrix matrix(circlePtrM);
    matrix.addShape(rectanglePtrM1);
    matrix.addShape(rectanglePtrM2);
    matrix.addShape(rectanglePtrM3);
    matrix.addShape(rectanglePtrM4);

    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > layer3 = matrix[2];

    BOOST_CHECK(layer1[0] == circlePtrM);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, -2.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.x, 3.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.x, -2.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(layer2[1]->getFrameRect().pos.x, 3.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(layer3[0]->getFrameRect().pos.x, 1.0, EPS_TEST);

    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, -2.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.y, 1.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.y, 0.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(layer2[1]->getFrameRect().pos.y, 3.0, EPS_TEST);
    BOOST_CHECK_CLOSE_FRACTION(layer3[0]->getFrameRect().pos.y, 1.0, EPS_TEST);
  }
BOOST_AUTO_TEST_SUITE_END()

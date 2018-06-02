#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>  
#include <stdexcept>
#include <cmath>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPSILON = 1e-7;

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(ConstantRadiusMoveToPointTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.move({ 5.5, 5.5 });
    BOOST_REQUIRE_EQUAL(testCircle.getRadius(), 13.33);
  }

  BOOST_AUTO_TEST_CASE(ConstantRadiusMoveByDeltaTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.move(0.5, 5.0);
    BOOST_REQUIRE_EQUAL(testCircle.getRadius(), 13.33);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveToPointTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.move({ 5.5, 5.5 });
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), M_PI * 13.33 * 13.33, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveByDeltaTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.move(0.5, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), M_PI * 13.33 * 13.33, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaByScaleTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), M_PI * 13.33 * 5 * 13.33 * 5, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RotateTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.rotate(144.5);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getAngle(), 144.5, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentRadiusTest)
  {
    BOOST_CHECK_THROW(satyukov::Circle testCircle ({ 5.0, 0.5 }, -13.33), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScaleCoefficientTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    BOOST_CHECK_THROW(testCircle.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(ConstantWidthMoveToPointTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move({ 5.5, 5.5 });
    BOOST_REQUIRE_EQUAL(testRectangle.getWidth(), 3.33);
  }

  BOOST_AUTO_TEST_CASE(ConstantHeightMoveToPointTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move({ 5.5, 5.5 });
    BOOST_REQUIRE_EQUAL(testRectangle.getHeight(), 10.0);
  }

  BOOST_AUTO_TEST_CASE(ConstantWidthMoveByDeltaTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move(0.5, 5.0);
    BOOST_REQUIRE_EQUAL(testRectangle.getWidth(), 3.33);
  }

  BOOST_AUTO_TEST_CASE(ConstantHeightMoveByDeltaTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move(0.5, 5.0);
    BOOST_REQUIRE_EQUAL(testRectangle.getHeight(), 10.0);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveToPointTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move({ 5.5, 5.5 });
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 3.33 * 10.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveByDeltaTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move(0.5, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 3.33 * 10.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaByScaleTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.scale(20);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 3.33 * 20 * 10.0 * 20, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RotateTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.rotate(90.0);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getAngle(), 90.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().width, 10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().height, 3.33, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentWidthTest)
  {
    BOOST_CHECK_THROW(satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, -3.33, 10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentHeightTest)
  {
    BOOST_CHECK_THROW(satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, -10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScaleCoefficientTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    BOOST_CHECK_THROW(testRectangle.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(FrameRectTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().x, 50.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().y, 10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getFrameRect().width, 120.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getFrameRect().height, 40.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(GetShapeTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    BOOST_REQUIRE_EQUAL(testCompositeShape.getShape(0), circlePtr);
    BOOST_REQUIRE_EQUAL(testCompositeShape.getShape(1), rectanglePtr); 
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    testCompositeShape.move({ 0.0, 50.0 });
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().x, 0.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().y, 50.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getCoordinates().x, 100.0 + (0.0 - 50.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getCoordinates().y, 0.0 + (50.0 - 10.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getCoordinates().x, 0.0 + (0.0 - 50.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getCoordinates().y, 10.0 + (50.0 - 10.0), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveByDeltaTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    testCompositeShape.move(-50.0, 40.0);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().x, 0.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().y, 50.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getCoordinates().x, 100.0 + (0.0 - 50.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getCoordinates().y, 0.0 + (50.0 - 10.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getCoordinates().x, 0.0 + (0.0 - 50.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getCoordinates().y, 10.0 + (50.0 - 10.0), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveToPointTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    testCompositeShape.move({ 0.0, 50.0 });
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getArea(), testCircle.getArea() + testRectangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveByDeltaTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    testCompositeShape.move(-50.0, 40.0);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getArea(), testCircle.getArea() + testRectangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    testCompositeShape.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getArea(), 
        2 * 2 * testCircle.getArea() + 2 * 2 * testRectangle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().x, 50.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().y, 10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getFrameRect().width, 2 * 120.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getFrameRect().height, 2 * 40.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getCoordinates().x, 50.0 + 2 * (100.0 - 50.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getCoordinates().y, 10.0 + 2 * (0.0 - 10.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getCoordinates().x, 50.0 + 2 * (0.0 - 50.0), EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getCoordinates().y, 10.0 + 2 * (10.0 - 10.0), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RotateTest)
  {
    satyukov::Circle testCircle ({ 20.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 0.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    testCompositeShape.rotate(90.0);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().x, 10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getCoordinates().y, 0.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getAngle(), 90.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getFrameRect().width, 40.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getFrameRect().height, 40.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getAngle(), 90.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getAngle(), 90.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getCoordinates().x, 10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(0)->getCoordinates().y, 10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getCoordinates().x, 10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getCoordinates().y, -10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getFrameRect().width, 40.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape.getShape(1)->getFrameRect().height, 20.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ChangeSizeTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    BOOST_REQUIRE_EQUAL(testCompositeShape.getSize(), 1);
    testCompositeShape.addShape(rectanglePtr);
    BOOST_REQUIRE_EQUAL(testCompositeShape.getSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(RemoveShapeTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    testCompositeShape.removeShape(0);
    BOOST_REQUIRE_EQUAL(testCompositeShape.getSize(), 1);
    BOOST_REQUIRE_EQUAL(testCompositeShape.getShape(0), rectanglePtr);
  }

  BOOST_AUTO_TEST_CASE(ClearTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.addShape(rectanglePtr);
    testCompositeShape.clear();
    BOOST_REQUIRE_EQUAL(testCompositeShape.getSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(CreateCompositeShapeWithNullptrTest)
  {
    BOOST_CHECK_THROW(satyukov::CompositeShape testCompositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScaleCoefficientTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    BOOST_CHECK_THROW(testCompositeShape.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(AddNullptrTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    BOOST_CHECK_THROW(testCompositeShape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(AddShapeThatIsAlreadyAddedTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    BOOST_CHECK_THROW(testCompositeShape.addShape(circlePtr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(GetShapeFromEmptyCompositeShapeTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.clear();
    BOOST_CHECK_THROW(testCompositeShape.getShape(0), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(GetShapeWithIncorrectIndexTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    BOOST_CHECK_THROW(testCompositeShape.getShape(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RemoveShapeFromEmptyCompositeShapeTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.clear();
    BOOST_CHECK_THROW(testCompositeShape.removeShape(0), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(RemoveShapeWithIncorrectIndexTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::CompositeShape testCompositeShape(circlePtr);
    BOOST_CHECK_THROW(testCompositeShape.removeShape(1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape1(circlePtr);
    testCompositeShape1.addShape(rectanglePtr);
    testCompositeShape1.rotate(90.0);
    satyukov::CompositeShape testCompositeShape2(testCompositeShape1);
    BOOST_REQUIRE_EQUAL(testCompositeShape2.getSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape2.getAngle(), 90.0, EPSILON);
    BOOST_CHECK(testCompositeShape2.getShape(0) == circlePtr);
    BOOST_CHECK(testCompositeShape2.getShape(1) == rectanglePtr);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape1(circlePtr);
    testCompositeShape1.addShape(rectanglePtr);
    testCompositeShape1.rotate(90.0);
    satyukov::CompositeShape testCompositeShape2(std::move(testCompositeShape1));
    BOOST_REQUIRE_EQUAL(testCompositeShape2.getSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape2.getAngle(), 90.0, EPSILON);
    BOOST_CHECK(testCompositeShape2.getShape(0) == circlePtr);
    BOOST_CHECK(testCompositeShape2.getShape(1) == rectanglePtr);
    BOOST_REQUIRE_EQUAL(testCompositeShape1.getSize(), 0);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape1.getAngle(), 0.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CopyOperatorTest)
  {
    satyukov::Circle testCircle1 ({ 100.0, 0.0 }, 10.0);
    satyukov::Circle testCircle2 ({ 0.0, 100.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr1 = std::make_shared < satyukov::Circle > (testCircle1);
    std::shared_ptr < satyukov::Shape > circlePtr2 = std::make_shared < satyukov::Circle > (testCircle2);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape1(circlePtr1);
    satyukov::CompositeShape testCompositeShape2(circlePtr2);
    testCompositeShape1.addShape(rectanglePtr);
    testCompositeShape1.rotate(90.0);
    testCompositeShape2 = testCompositeShape1;
    BOOST_REQUIRE_EQUAL(testCompositeShape2.getSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape2.getAngle(), 90.0, EPSILON);
    BOOST_CHECK(testCompositeShape2.getShape(0) == circlePtr1);
    BOOST_CHECK(testCompositeShape2.getShape(1) == rectanglePtr);
  }

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    satyukov::Circle testCircle1 ({ 100.0, 0.0 }, 10.0);
    satyukov::Circle testCircle2 ({ 0.0, 100.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr1 = std::make_shared < satyukov::Circle > (testCircle1);
    std::shared_ptr < satyukov::Shape > circlePtr2 = std::make_shared < satyukov::Circle > (testCircle2);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape1(circlePtr1);
    satyukov::CompositeShape testCompositeShape2(circlePtr2);
    testCompositeShape1.addShape(rectanglePtr);
    testCompositeShape1.rotate(90.0);
    testCompositeShape2 = std::move(testCompositeShape1);
    BOOST_REQUIRE_EQUAL(testCompositeShape2.getSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape2.getAngle(), 90.0, EPSILON);
    BOOST_CHECK(testCompositeShape2.getShape(0) == circlePtr1);
    BOOST_CHECK(testCompositeShape2.getShape(1) == rectanglePtr);
    BOOST_REQUIRE_EQUAL(testCompositeShape1.getSize(), 0);
    BOOST_CHECK_CLOSE_FRACTION(testCompositeShape1.getAngle(), 0.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(EqualOperatorTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape1(circlePtr);
    satyukov::CompositeShape testCompositeShape2(circlePtr);
    testCompositeShape1.addShape(rectanglePtr);
    testCompositeShape1.rotate(90.0);
    testCompositeShape2.addShape(rectanglePtr);
    testCompositeShape2.rotate(90.0);    
    bool equality = (testCompositeShape1 == testCompositeShape2);
    BOOST_CHECK(equality == true);
  }

  BOOST_AUTO_TEST_CASE(NonequalOperatorTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangle ({ 0.0, 10.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
    satyukov::CompositeShape testCompositeShape1(circlePtr);
    satyukov::CompositeShape testCompositeShape2(rectanglePtr);
    bool nonequality = (testCompositeShape1 != testCompositeShape2);
    BOOST_CHECK(nonequality == true);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTests)

  BOOST_AUTO_TEST_CASE(MatrixCorrectnessTest)
  {
    satyukov::Circle testCircleM1 ({ -10.0, 0.0 }, 10.0);
    satyukov::Circle testCircleM2 ({ 40.0, 30.0 }, 20.0);
    satyukov::Rectangle testRectangleM1 ({ 20.0, 30.0 }, 20.0, 40.0);
    satyukov::Rectangle testRectangleM2 ({ 30.0, 0.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtrM1 = std::make_shared < satyukov::Circle > (testCircleM1);
    std::shared_ptr < satyukov::Shape > circlePtrM2 = std::make_shared < satyukov::Circle > (testCircleM2);
    std::shared_ptr < satyukov::Shape > rectanglePtrM1 = std::make_shared < satyukov::Rectangle > (testRectangleM1);
    std::shared_ptr < satyukov::Shape > rectanglePtrM2 = std::make_shared < satyukov::Rectangle > (testRectangleM2);
    satyukov::Matrix testMatrix(circlePtrM1);
    testMatrix.addShape(rectanglePtrM1);
    testMatrix.addShape(rectanglePtrM2);
    testMatrix.addShape(circlePtrM2);
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer0 = testMatrix[0];
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer1 = testMatrix[1];
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer2 = testMatrix[2];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_CHECK(layer1[1] == nullptr);
    BOOST_CHECK(layer2[0] == circlePtrM2);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getFrameRect().pos.x, -10.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getFrameRect().pos.x, 20.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, 30.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.x, 40.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getFrameRect().pos.y, 0.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getFrameRect().pos.y, 30.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, 0.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.y, 30.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    satyukov::Circle testCircleM ({ -10.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangleM1 ({ 20.0, 30.0 }, 20.0, 40.0);
    satyukov::Rectangle testRectangleM2 ({ 30.0, 0.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtrM = std::make_shared < satyukov::Circle > (testCircleM);
    std::shared_ptr < satyukov::Shape > rectanglePtrM1 = std::make_shared < satyukov::Rectangle > (testRectangleM1);
    std::shared_ptr < satyukov::Shape > rectanglePtrM2 = std::make_shared < satyukov::Rectangle > (testRectangleM2);
    satyukov::Matrix testMatrix1(circlePtrM);
    testMatrix1.addShape(rectanglePtrM1);
    testMatrix1.addShape(rectanglePtrM2);
    satyukov::Matrix testMatrix2(testMatrix1);
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer0 = testMatrix2[0];
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);   
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    satyukov::Circle testCircleM ({ -10.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangleM1 ({ 20.0, 30.0 }, 20.0, 40.0);
    satyukov::Rectangle testRectangleM2 ({ 30.0, 0.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtrM = std::make_shared < satyukov::Circle > (testCircleM);
    std::shared_ptr < satyukov::Shape > rectanglePtrM1 = std::make_shared < satyukov::Rectangle > (testRectangleM1);
    std::shared_ptr < satyukov::Shape > rectanglePtrM2 = std::make_shared < satyukov::Rectangle > (testRectangleM2);
    satyukov::Matrix testMatrix1(circlePtrM);
    testMatrix1.addShape(rectanglePtrM1);
    testMatrix1.addShape(rectanglePtrM2);
    satyukov::Matrix testMatrix2(std::move(testMatrix1));
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer0 = testMatrix2[0];
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayersNumber(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayerSize(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(CopyOperatorTest)
  {
    satyukov::Circle testCircleM1 ({ -10.0, 0.0 }, 10.0);
    satyukov::Circle testCircleM2 ({ 40.0, 30.0 }, 20.0);
    satyukov::Rectangle testRectangleM1 ({ 20.0, 30.0 }, 20.0, 40.0);
    satyukov::Rectangle testRectangleM2 ({ 30.0, 0.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtrM1 = std::make_shared < satyukov::Circle > (testCircleM1);
    std::shared_ptr < satyukov::Shape > circlePtrM2 = std::make_shared < satyukov::Circle > (testCircleM2);
    std::shared_ptr < satyukov::Shape > rectanglePtrM1 = std::make_shared < satyukov::Rectangle > (testRectangleM1);
    std::shared_ptr < satyukov::Shape > rectanglePtrM2 = std::make_shared < satyukov::Rectangle > (testRectangleM2);
    satyukov::Matrix testMatrix1(circlePtrM1);
    testMatrix1.addShape(rectanglePtrM1);
    testMatrix1.addShape(rectanglePtrM2);
    satyukov::Matrix testMatrix2(circlePtrM2);
    testMatrix2 = testMatrix1;
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer0 = testMatrix2[0];
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    satyukov::Circle testCircleM1 ({ -10.0, 0.0 }, 10.0);
    satyukov::Circle testCircleM2 ({ 40.0, 30.0 }, 20.0);
    satyukov::Rectangle testRectangleM1 ({ 20.0, 30.0 }, 20.0, 40.0);
    satyukov::Rectangle testRectangleM2 ({ 30.0, 0.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtrM1 = std::make_shared < satyukov::Circle > (testCircleM1);
    std::shared_ptr < satyukov::Shape > circlePtrM2 = std::make_shared < satyukov::Circle > (testCircleM2);
    std::shared_ptr < satyukov::Shape > rectanglePtrM1 = std::make_shared < satyukov::Rectangle > (testRectangleM1);
    std::shared_ptr < satyukov::Shape > rectanglePtrM2 = std::make_shared < satyukov::Rectangle > (testRectangleM2);
    satyukov::Matrix testMatrix1(circlePtrM1);
    testMatrix1.addShape(rectanglePtrM1);
    testMatrix1.addShape(rectanglePtrM2);
    satyukov::Matrix testMatrix2(circlePtrM2);
    testMatrix2 = std::move(testMatrix1);
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer0 = testMatrix2[0];
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayersNumber(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayerSize(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(EqualOperatorTest)
  {
    satyukov::Circle testCircleM ({ -10.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangleM ({ 20.0, 30.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtrM = std::make_shared < satyukov::Circle > (testCircleM);
    std::shared_ptr < satyukov::Shape > rectanglePtrM = std::make_shared < satyukov::Rectangle > (testRectangleM);
    satyukov::Matrix testMatrix1(circlePtrM);
    testMatrix1.addShape(rectanglePtrM);
    satyukov::Matrix testMatrix2(circlePtrM);
    testMatrix2.addShape(rectanglePtrM);
    bool equality = (testMatrix1 == testMatrix2);
    BOOST_CHECK(equality == true);
  }

  BOOST_AUTO_TEST_CASE(NonequalOperatorTest)
  {
    satyukov::Circle testCircleM ({ -10.0, 0.0 }, 10.0);
    satyukov::Rectangle testRectangleM ({ 20.0, 30.0 }, 20.0, 40.0);
    std::shared_ptr < satyukov::Shape > circlePtrM = std::make_shared < satyukov::Circle > (testCircleM);
    std::shared_ptr < satyukov::Shape > rectanglePtrM = std::make_shared < satyukov::Rectangle > (testRectangleM);
    satyukov::Matrix testMatrix1(circlePtrM);
    satyukov::Matrix testMatrix2(rectanglePtrM);
    bool nonequality = (testMatrix1 != testMatrix2);
    BOOST_CHECK(nonequality == true);
  }
  
  BOOST_AUTO_TEST_CASE(CreateMatrixWithNullptrTest)
  {
    BOOST_CHECK_THROW(satyukov::Matrix testMatrix(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(GetLayerFromEmptyMatrixTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::Matrix testMatrix(circlePtr);
    testMatrix.~Matrix();
    BOOST_CHECK_THROW(testMatrix[0], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(GetLayerWithIncorrectIndexTest)
  {
    satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);
    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    satyukov::Matrix testMatrix(circlePtr);
    BOOST_CHECK_THROW(testMatrix[-1], std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

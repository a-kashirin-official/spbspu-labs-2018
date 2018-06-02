#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>  
#include <stdexcept>
#include <cmath>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

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

BOOST_AUTO_TEST_SUITE_END()

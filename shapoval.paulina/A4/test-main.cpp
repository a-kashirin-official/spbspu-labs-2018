#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPSILON_TEST = 0.00001;

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(MoveToXYTest)
  {
    shapoval::Circle new_circle({0,0},10);
    new_circle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().pos.x, 10, EPSILON_TEST); 
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().pos.y, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().height / 2 , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTest)
  {
    shapoval::Circle new_circle({0,0},10);
    new_circle.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().pos.y, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().height / 2 , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    shapoval::Circle new_circle({0,0},10);
    new_circle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI * 2 * 2, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(RotationTest)
  {
    shapoval::Circle new_circle({0,0},10);
    new_circle.rotate(90);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getAngle(), 90, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleTest)
  {
    BOOST_CHECK_THROW(shapoval::Circle({0,0},-10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleScaleTest)
  {
    shapoval::Circle new_circle ({0,0},10);
    BOOST_CHECK_THROW(new_circle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(MoveToXYTest)
  {
    shapoval::Rectangle new_rectangle({10,20}, 40, 20);
    new_rectangle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.y, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().height , 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().width , 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 40 * 20 , EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTest)
  {
    shapoval::Rectangle new_rectangle({10,20}, 40, 20);
    new_rectangle.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.y, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().height , 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().width , 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 40 * 20 , EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    shapoval::Rectangle new_rectangle({10,20}, 40, 20);
    new_rectangle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 40 * 2 * 20 * 2 , EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(RotationTest)
  {
    shapoval::Rectangle new_rectangle({10,20}, 40, 20);
    new_rectangle.rotate(45);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.y, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().height , 42.4264, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().width , 42.4264, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getAngle(), 45, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleHeightTest)
  {
    BOOST_CHECK_THROW(shapoval::Rectangle({0,0}, -10, 20), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleWigthTest)
  {
    BOOST_CHECK_THROW(shapoval::Rectangle({0,0}, 10, -20), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleScaleTest)
  {
    shapoval::Rectangle new_rectangle ({0,0}, 10, 20);
    BOOST_CHECK_THROW(new_rectangle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(GetFrameRectTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, 10, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToXYTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    new_compositeshape.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, 30, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getArea(), new_circle.getArea() + new_rectangle.getArea(), EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    new_compositeshape.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getArea(), new_circle.getArea() + new_rectangle.getArea(), EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveInformationConstructorTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    shapoval::CompositeShape compositeshape1 = std::move(new_compositeshape);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape1.getFrameRect().height, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape1.getFrameRect().width, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape1.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape1.getFrameRect().pos.y, 10, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveInformationOperatorTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    shapoval::CompositeShape new_compositeshape1(new_rectanglePtr);
    new_compositeshape = std::move(new_compositeshape1);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape1.getFrameRect().height, 0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape1.getFrameRect().width, 0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape1.getFrameRect().pos.x, 0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape1.getFrameRect().pos.y, 0, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(CopyInformationConstructorTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    shapoval::CompositeShape new_compositeshape1 = new_compositeshape;
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape1.getFrameRect().height, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape1.getFrameRect().width, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape1.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape1.getFrameRect().pos.y, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, new_compositeshape1.getFrameRect().height, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, new_compositeshape1.getFrameRect().width, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, new_compositeshape1.getFrameRect().pos.x, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, new_compositeshape1.getFrameRect().pos.y, EPSILON_TEST);
  }

BOOST_AUTO_TEST_CASE(CopyInformationOperatorTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    shapoval::CompositeShape new_compositeshape1(new_rectanglePtr);
    new_compositeshape = new_compositeshape1;
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, 40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, new_compositeshape1.getFrameRect().height, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, new_compositeshape1.getFrameRect().width, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, new_compositeshape1.getFrameRect().pos.x, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, new_compositeshape1.getFrameRect().pos.y, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    new_compositeshape.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, 200, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, 200, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getShape(0)->getFrameRect().pos.x, -40, EPSILON_TEST); 
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getShape(0)->getFrameRect().pos.y, -40, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getShape(1)->getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getShape(1)->getFrameRect().pos.y, 60, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getArea(), (new_circle.getArea() + new_rectangle.getArea()) * 5 * 5, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(RotationTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({40, 0}, 20, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    new_compositeshape.rotate(90);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, 0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().height, 60, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().width, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getShape(0)->getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getShape(0)->getFrameRect().pos.y, -20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getShape(1)->getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getShape(1)->getFrameRect().pos.y, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getArea(), (new_circle.getArea() + new_rectangle.getArea()), EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getAngle(), 90, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(RemoveShapeTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    new_compositeshape.removeShape(1);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getArea(), new_rectangle.getArea(), EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, new_rectangle.getFrameRect().pos.x, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, new_rectangle.getFrameRect().pos.y, EPSILON_TEST);
    BOOST_REQUIRE_EQUAL(new_compositeshape.getSize(), 1);
  }

  BOOST_AUTO_TEST_CASE(DeleteShapesTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    new_compositeshape.deleteShapes();
    BOOST_REQUIRE_EQUAL(new_compositeshape.getSize(), 0);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getArea(), 0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.x, 0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_compositeshape.getFrameRect().pos.y, 0, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidCompositeShapeScaleTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    BOOST_CHECK_THROW(new_compositeshape.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRemovingShapeNumberTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    BOOST_CHECK_THROW(new_compositeshape.removeShape(-5), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(EmptyCompositeShapeWhenRemovingTest)
  {
    shapoval::Circle new_circle({0, 0}, 10);
    shapoval::Rectangle new_rectangle({10, 20}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::CompositeShape new_compositeshape(new_circlePtr);
    new_compositeshape.addShape(new_rectanglePtr);
    new_compositeshape.deleteShapes();
    BOOST_CHECK_THROW(new_compositeshape.removeShape(1), std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTests)

  BOOST_AUTO_TEST_CASE(MatrixConstructorTest)
  {
    shapoval::Circle new_circle({50,0}, 20);
    shapoval::Rectangle new_rectangle({10,20}, 40, 80);
    shapoval::Rectangle new_rectangle2({70,70}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr2 = std::make_shared <shapoval::Rectangle> (new_rectangle2);
    shapoval::Matrix new_matrix(new_circlePtr);
    new_matrix.addShape(new_rectanglePtr);
    new_matrix.addShape(new_rectanglePtr2);
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer1 = new_matrix[0];
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer2 = new_matrix[1];
    BOOST_CHECK(new_layer1[0] == new_circlePtr);
    BOOST_CHECK(new_layer1[1] == new_rectanglePtr2);
    BOOST_CHECK(new_layer2[0] == new_rectanglePtr);
    BOOST_CHECK(new_layer2[1] == nullptr);
    BOOST_CHECK_CLOSE_FRACTION(new_layer1[0]->getFrameRect().pos.x, 50, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_layer1[0]->getFrameRect().pos.y, 0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_layer1[1]->getFrameRect().pos.x, 70, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_layer1[1]->getFrameRect().pos.y, 70, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_layer2[0]->getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_layer2[0]->getFrameRect().pos.y, 20, EPSILON_TEST);
    BOOST_REQUIRE_EQUAL(new_matrix.getLayerSize(1), 1);
  }

BOOST_AUTO_TEST_CASE(MatrixCompositeShapeConstructorTest)
{
  shapoval::Circle new_circle({50,0}, 20);
  shapoval::Rectangle new_rectangle({10,20}, 40, 80);
  shapoval::Rectangle new_rectangle2({70,70}, 40, 20);
  std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
  std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
  std::shared_ptr <shapoval::Shape> new_rectanglePtr2 = std::make_shared <shapoval::Rectangle> (new_rectangle2);
  shapoval::CompositeShape new_compositeshape(new_circlePtr);
  new_compositeshape.addShape(new_rectanglePtr);
  new_compositeshape.addShape(new_rectanglePtr2);
  shapoval::Matrix new_matrix(new_compositeshape);
  std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer1 = new_matrix[0];
  std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer2 = new_matrix[1];
  BOOST_CHECK(new_layer1[0] == new_circlePtr);
  BOOST_CHECK(new_layer1[1] == new_rectanglePtr2);
  BOOST_CHECK(new_layer2[0] == new_rectanglePtr);
  BOOST_CHECK(new_layer2[1] == nullptr);
  BOOST_CHECK_CLOSE_FRACTION(new_layer1[0]->getFrameRect().pos.x, 50, EPSILON_TEST);
  BOOST_CHECK_CLOSE_FRACTION(new_layer1[0]->getFrameRect().pos.y, 0, EPSILON_TEST);
  BOOST_CHECK_CLOSE_FRACTION(new_layer1[1]->getFrameRect().pos.x, 70, EPSILON_TEST);
  BOOST_CHECK_CLOSE_FRACTION(new_layer1[1]->getFrameRect().pos.y, 70, EPSILON_TEST);
  BOOST_CHECK_CLOSE_FRACTION(new_layer2[0]->getFrameRect().pos.x, 10, EPSILON_TEST);
  BOOST_CHECK_CLOSE_FRACTION(new_layer2[0]->getFrameRect().pos.y, 20, EPSILON_TEST);
}

  BOOST_AUTO_TEST_CASE(CopyInformationConstructorTest)
  {
    shapoval::Circle new_circle({50,0}, 20);
    shapoval::Rectangle new_rectangle({10,20}, 40, 80);
    shapoval::Rectangle new_rectangle2({70,70}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr2 = std::make_shared <shapoval::Rectangle> (new_rectangle2);
    shapoval::Matrix new_matrix(new_circlePtr);
    new_matrix.addShape(new_rectanglePtr);
    new_matrix.addShape(new_rectanglePtr2);
    shapoval::Matrix new_matrix1(new_matrix);
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new1_layer1 = new_matrix1[0];
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new1_layer2 = new_matrix1[1];
    BOOST_CHECK(new1_layer1[0] == new_circlePtr);
    BOOST_CHECK(new1_layer1[1] == new_rectanglePtr2);
    BOOST_CHECK(new1_layer2[0] == new_rectanglePtr);
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer1 = new_matrix[0];
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer2 = new_matrix[1];
    BOOST_CHECK(new1_layer1[0] == new_layer1[0]);
    BOOST_CHECK(new1_layer1[1] == new_layer1[1]);
    BOOST_CHECK(new1_layer2[0] == new_layer2[0]);
  }

  BOOST_AUTO_TEST_CASE(CopyInformationOperatorTest)
  {
    shapoval::Circle new_circle({50,0}, 20);
    shapoval::Rectangle new_rectangle({10,20}, 40, 80);
    shapoval::Rectangle new_rectangle2({70,70}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr2 = std::make_shared <shapoval::Rectangle> (new_rectangle2);
    shapoval::Matrix new_matrix(new_circlePtr);
    new_matrix.addShape(new_rectanglePtr);
    shapoval::Matrix new_matrix1(new_rectanglePtr2);
    new_matrix1 = new_matrix;
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new1_layer1 = new_matrix1[0];
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new1_layer2 = new_matrix1[1];
    BOOST_CHECK(new1_layer1[0] == new_circlePtr);
    BOOST_CHECK(new1_layer2[0] == new_rectanglePtr);
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer1 = new_matrix[0];
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer2 = new_matrix[1];
    BOOST_CHECK(new1_layer1[0] == new_layer1[0]);
    BOOST_CHECK(new1_layer2[0] == new_layer2[0]);
  }

  BOOST_AUTO_TEST_CASE(MoveInformationConstructorTest)
  {
    shapoval::Circle new_circle({50,0}, 20);
    shapoval::Rectangle new_rectangle({10,20}, 40, 80);
    shapoval::Rectangle new_rectangle2({70,70}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr2 = std::make_shared <shapoval::Rectangle> (new_rectangle2);
    shapoval::Matrix new_matrix(new_circlePtr);
    new_matrix.addShape(new_rectanglePtr);
    new_matrix.addShape(new_rectanglePtr2);
    shapoval::Matrix new_matrix1(std::move(new_matrix));
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer1 = new_matrix1[0];
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer2 = new_matrix1[1];
    BOOST_CHECK(new_layer1[0] == new_circlePtr);
    BOOST_CHECK(new_layer1[1] == new_rectanglePtr2);
    BOOST_CHECK(new_layer2[0] == new_rectanglePtr);
    BOOST_REQUIRE_EQUAL(new_matrix.getLayersNumber(), 0);
    BOOST_REQUIRE_EQUAL(new_matrix.getMaxLayerSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(MoveInformationOperatorTest)
  {
    shapoval::Circle new_circle({50,0}, 20);
    shapoval::Rectangle new_rectangle({10,20}, 40, 80);
    shapoval::Rectangle new_rectangle2({70,70}, 40, 20);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr2 = std::make_shared <shapoval::Rectangle> (new_rectangle2);
    shapoval::Matrix new_matrix(new_circlePtr);
    new_matrix.addShape(new_rectanglePtr);
    shapoval::Matrix new_matrix1(new_rectanglePtr2);
    new_matrix1 = std::move(new_matrix);
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer1 = new_matrix1[0];
    std::unique_ptr <std::shared_ptr<shapoval::Shape>[] > new_layer2 = new_matrix1[1];
    BOOST_CHECK(new_layer1[0] == new_circlePtr);
    BOOST_CHECK(new_layer2[0] == new_rectanglePtr);
    BOOST_REQUIRE_EQUAL(new_matrix.getLayersNumber(), 0);
    BOOST_REQUIRE_EQUAL(new_matrix.getMaxLayerSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(EqualityOperatorTest)
  {
    shapoval::Circle new_circle({50,0}, 20);
    shapoval::Rectangle new_rectangle({10,20}, 40, 80);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::Matrix new_matrix(new_circlePtr);
    new_matrix.addShape(new_rectanglePtr);
    shapoval::Matrix new_matrix1(new_circlePtr);
    new_matrix1.addShape(new_rectanglePtr);
    bool equal = (new_matrix == new_matrix1);
    BOOST_CHECK(equal == true);
  }

  BOOST_AUTO_TEST_CASE(NonEqualityOperatorTest)
  {
    shapoval::Circle new_circle({50,0}, 20);
    shapoval::Rectangle new_rectangle({10,20}, 40, 80);
    std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
    std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
    shapoval::Matrix new_matrix(new_circlePtr);
    shapoval::Matrix new_matrix1(new_rectanglePtr);
    bool notequal = (new_matrix != new_matrix1);
    BOOST_CHECK(notequal == true);
  }

BOOST_AUTO_TEST_SUITE_END()

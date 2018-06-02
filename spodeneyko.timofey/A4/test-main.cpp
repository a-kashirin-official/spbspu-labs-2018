#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPS = 0.0001;

BOOST_AUTO_TEST_SUITE(Rotate_Tests)

  BOOST_AUTO_TEST_CASE(RectangleTest)
  {
    spodeneyko::Rectangle rectangle({24.0, 48.0, {128.0, 256.0}});
    rectangle.rotate(90.0);
    spodeneyko::rectangle_t shapeFrameRect = rectangle.getFrameRect();
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.width, 48.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.height, 24.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.pos.x, 128.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.pos.y, 256.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr1
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({20.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr1);
    std::shared_ptr<spodeneyko::Shape> rectPtr2
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {200.0, 256.0}}));
    comp_shape.addShape(rectPtr2);
    comp_shape.rotate(90.0);
    spodeneyko::rectangle_t shapeFrameRect = comp_shape.getFrameRect();
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.width, 120.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.height, 166.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.pos.x, 164.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.pos.y, 255.0, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_Tests)

  BOOST_AUTO_TEST_CASE(AddShapeTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr1
         = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({20.0, 48.0, {128.0, 256.0}}));
    spodeneyko::MatrixShape matrix_shape(rectPtr1);
    std::shared_ptr<spodeneyko::Shape> rectPtr2
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {150.0, 256.0}}));
    matrix_shape.addShape(rectPtr2);
    std::shared_ptr<spodeneyko::Shape> circlePtr
        = std::make_shared<spodeneyko::Circle>(spodeneyko::Circle(10.0, {130.0, 256.0}));
    matrix_shape.addShape(circlePtr);
    BOOST_REQUIRE_EQUAL(matrix_shape[0][0], rectPtr1);
    BOOST_REQUIRE_EQUAL(matrix_shape[0][1], rectPtr2);
    BOOST_REQUIRE_EQUAL(matrix_shape[1][0], circlePtr);
  }

  BOOST_AUTO_TEST_CASE(AddCompositeShapeTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr1
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({20.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr1);
    spodeneyko::MatrixShape matrix_shape(rectPtr1);
    std::shared_ptr<spodeneyko::Shape> rectPtr2
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {200.0, 256.0}}));
    comp_shape.addShape(rectPtr2);
    matrix_shape.addShape(rectPtr2);
    std::shared_ptr<spodeneyko::Shape> compPtr
        = std::make_shared<spodeneyko::CompositeShape>(comp_shape);
    matrix_shape.addShape(compPtr);
    BOOST_REQUIRE_EQUAL(matrix_shape[0][0], rectPtr1);
    BOOST_REQUIRE_EQUAL(matrix_shape[0][1], rectPtr2);
    BOOST_REQUIRE_EQUAL(matrix_shape[1][0], compPtr);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentConstructorTest)
  { 
    BOOST_REQUIRE_THROW(spodeneyko::MatrixShape matrix_shape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentAddShapeTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr1
         = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({20.0, 48.0, {128.0, 256.0}}));
    spodeneyko::MatrixShape matrix_shape(rectPtr1);
    BOOST_REQUIRE_THROW(matrix_shape.addShape(nullptr), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

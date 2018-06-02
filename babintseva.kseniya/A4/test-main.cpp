#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"
#include <stdexcept>

const double epsilon = 1e-4;;

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(ConstancyOfRadius)
  {
    babintseva::Circle circle({0,0},6);
    const double radiusBefore = circle.getRadius();
    circle.move({15,15});
    circle.move(-20,25);
    BOOST_CHECK_CLOSE(circle.getRadius(), radiusBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(ConstancyOfArea)
  {
    babintseva::Circle circle({4,-2},10);
    double area = circle.getArea();
    circle.move({-4,-6});
    circle.move(3,-2);
    BOOST_CHECK_CLOSE(circle.getArea(), area, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    babintseva::Circle circle({12,-9},3);
    BOOST_CHECK_THROW(circle.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ParametersAfterRotating)
  {
    babintseva::Rectangle rectangle({0, 10}, 5, 8);
    rectangle.rotate(90);

    const double widthBefore = rectangle.getWidth();
    const double heightBefore = rectangle.getHeight();

    BOOST_CHECK_CLOSE(rectangle.getWidth(), widthBefore, epsilon);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), heightBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(AreaAfterRotating)
  {
    babintseva::Rectangle rectangle({0, 0}, 2, 3);
    rectangle.rotate(120);

    const double areaBefore = rectangle.getArea();

    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBefore, epsilon);
  }
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(WidthAfterMoving)
  {
    babintseva::Rectangle rectangle({0,0},7,3);

    const double widthBefore = rectangle.getWidth();

    rectangle.move({6,56});
    rectangle.move(3,-9);

    BOOST_CHECK_CLOSE(rectangle.getWidth(), widthBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(HeightAfterMoving)
  {
    babintseva::Rectangle rectangle({0,0},7,3);

    const double heightBefore = rectangle.getHeight();

    rectangle.move({-4,-6});
    rectangle.move(-5,5);

    BOOST_CHECK_CLOSE(rectangle.getHeight(), heightBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(AreaAfterMoving)
  {
    babintseva::Rectangle rectangle({0,0},5,4);

    double areaBefore = rectangle.getArea();

    rectangle.move({-4,-6});
    rectangle.move(-5,5);

    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    babintseva::Rectangle rectangle({3,6},3,2);
    BOOST_CHECK_THROW(rectangle.scale(-1), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(ParametersAfterRotating)
  {
    babintseva::Rectangle rectangle({0, 10}, 5, 8);

    const double widthBefore = rectangle.getWidth();
    const double heightBefore = rectangle.getHeight();

    rectangle.rotate(90);

    BOOST_CHECK_CLOSE(rectangle.getWidth(), widthBefore, epsilon);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), heightBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(AreaAfterRotating)
  {
    babintseva::Rectangle rectangle({0, 0}, 2, 3);
    rectangle.rotate(120);

    const double areaBefore = rectangle.getArea();

    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBefore, epsilon);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testCompositeShape)

  BOOST_AUTO_TEST_CASE(widthAfterMoving)
  {
    std::shared_ptr<babintseva::Shape> shape1 = std::make_shared<babintseva::Rectangle>(babintseva::Rectangle({0,0},5,2));
    std::shared_ptr<babintseva::Shape> shape2 = std::make_shared<babintseva::Circle>(babintseva::Circle({5,2},1));

    babintseva::CompositeShape compositeShape(shape1);

    compositeShape.addShape(shape2);

    const double widthBefore = compositeShape.getFrameRect().width;

    compositeShape.move({3,-2});
    compositeShape.move(3,-2);

    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, widthBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(HeightAfterMoving)
  {
    std::shared_ptr<babintseva::Shape> shape1 = std::make_shared<babintseva::Rectangle>(babintseva::Rectangle({0,0},5,2));
    std::shared_ptr<babintseva::Shape> shape2 = std::make_shared<babintseva::Circle>(babintseva::Circle({5,2},1));

    babintseva::CompositeShape compositeShape(shape1);

    compositeShape.addShape(shape2);

    const double heightBefore = compositeShape.getFrameRect().height;

    compositeShape.move({3,-2});
    compositeShape.move(3,-2);

    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, heightBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(AreaAfterMoving)
  {
    std::shared_ptr<babintseva::Shape> shape1 = std::make_shared<babintseva::Rectangle>(babintseva::Rectangle({0,0},5,2));
    std::shared_ptr<babintseva::Shape> shape2 = std::make_shared<babintseva::Circle>(babintseva::Circle({5,2},1));

    babintseva::CompositeShape compositeShape(shape1);

    compositeShape.addShape(shape2);

    const double areaBefore = shape1->getArea()+shape2->getArea();

    compositeShape.move({3,-2});
    compositeShape.move(3,-2);

    BOOST_CHECK_CLOSE(compositeShape.getArea(), areaBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    std::shared_ptr<babintseva::Shape> shape1 = std::make_shared<babintseva::Rectangle>(babintseva::Rectangle({0,0},5,2));
    babintseva::CompositeShape compositeShape(shape1);

    BOOST_CHECK_THROW(compositeShape.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rotating)

  BOOST_AUTO_TEST_CASE(rectangle)
  {
    babintseva::Rectangle rectangle({10, 0}, 3, 3);
    rectangle.rotate(-45);

    babintseva::rectangle_t frame_rect = rectangle.getFrameRect();

    BOOST_CHECK_CLOSE(frame_rect.pos.x, 10, epsilon);
    BOOST_CHECK_CLOSE(frame_rect.pos.y, 0, epsilon);
    BOOST_CHECK_CLOSE(frame_rect.width, 3 * sqrt(2), epsilon);
    BOOST_CHECK_CLOSE(frame_rect.height, 3 * sqrt(2), epsilon);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTest)

BOOST_AUTO_TEST_CASE(new_rows)
{
  auto rectangle1 = std::make_shared<babintseva::Rectangle>(babintseva::point_t{-3, -1}, 4, 4);
  auto circle = std::make_shared<babintseva::Circle>(babintseva::point_t{-1, 0}, 2);
  auto rectangle2 = std::make_shared<babintseva::Rectangle>(babintseva::point_t{3, 3}, 4, 2);

  babintseva::MatrixShape matrix_shape(rectangle1);
  matrix_shape.addShape(circle);
  matrix_shape.addShape(rectangle2);

  BOOST_CHECK(matrix_shape[1][0] == circle);
}

BOOST_AUTO_TEST_CASE(new_columns)
{
  auto rectangle_1 = std::make_shared<babintseva::Rectangle>(babintseva::point_t{1, -1}, 2, 2);
  auto rectangle_2 = std::make_shared<babintseva::Rectangle>(babintseva::point_t{0, 0}, 2, 2);
  auto rectangle_3 = std::make_shared<babintseva::Rectangle>(babintseva::point_t{2, -2}, 2, 2);

  babintseva::MatrixShape matrix_shape(rectangle_1);
  matrix_shape.addShape(rectangle_2);
  matrix_shape.addShape(rectangle_3);

  BOOST_CHECK(matrix_shape[0][0] == rectangle_1);
  BOOST_CHECK(matrix_shape[1][0] == rectangle_2);
  BOOST_CHECK(matrix_shape[1][1] == rectangle_3);
}

BOOST_AUTO_TEST_CASE(add_one_shape)
{
  auto rect = std::make_shared<babintseva::Rectangle>(babintseva::point_t{-2, 2}, 2, 2);
  babintseva::MatrixShape matrix_shape(rect);

  BOOST_CHECK(matrix_shape[0][0] == rect);
}

BOOST_AUTO_TEST_CASE(add_composite_shape)
{
  auto rectangle_1 = std::make_shared<babintseva::Rectangle>(babintseva::point_t{0, 3}, 4, 2);
  auto rectangle_2 = std::make_shared<babintseva::Rectangle>(babintseva::point_t{-1, -1}, 2, 2);
  auto circle = std::make_shared<babintseva::Circle>(babintseva::point_t{0, 2}, 2);

  auto composite_shape_1 = std::make_shared<babintseva::CompositeShape>(rectangle_1);
  composite_shape_1->addShape(circle);

  auto composite_shape_2 = std::make_shared<babintseva::CompositeShape>(composite_shape_1);

  babintseva::MatrixShape matrix_shape(composite_shape_1);
  matrix_shape.addShape(composite_shape_2);

  BOOST_CHECK(matrix_shape[0][0] == composite_shape_1 && matrix_shape[1][0] == composite_shape_2);
}

BOOST_AUTO_TEST_CASE(invalid_constructor)
{
  BOOST_CHECK_THROW(babintseva::MatrixShape matrix_shape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

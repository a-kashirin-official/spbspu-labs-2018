#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace khodyreva;

const double EPSILON = 1e-6;

BOOST_AUTO_TEST_SUITE(RotateTests)

  BOOST_AUTO_TEST_CASE(RotateRectangle180)
  {
    Rectangle rectangle ({4.0, 7.0}, 6.0, 3.0);
    rectangle_t frameRect = rectangle.getFrameRect();
    double area = rectangle.getArea();
    rectangle.rotate(180.0);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.width, rectangle.getFrameRect().width, EPSILON);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.height, rectangle.getFrameRect().height, EPSILON);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.pos.x, rectangle.getFrameRect().pos.x, EPSILON);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.pos.y, rectangle.getFrameRect().pos.y, EPSILON);
    BOOST_REQUIRE_CLOSE_FRACTION(area, rectangle.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_CASE(RotateRectangle45)
 {
   Rectangle rectangle({0.0, 0.0}, 5.0, 5.0);
   rectangle.rotate(45.0);
   rectangle_t frameRect = rectangle.getFrameRect();
   BOOST_REQUIRE_CLOSE(frameRect.width, 7.0710678118654755, EPSILON);
   BOOST_REQUIRE_CLOSE(frameRect.height, 7.0710678118654755, EPSILON);
   BOOST_REQUIRE_CLOSE(frameRect.pos.x, rectangle.getFrameRect().pos.x, EPSILON);
   BOOST_REQUIRE_CLOSE(frameRect.pos.y, rectangle.getFrameRect().pos.y, EPSILON);
 }

  BOOST_AUTO_TEST_CASE(CompositeShapeRotate)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));

    for (size_t i = -180; i < 180; i++)
    {
      std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
      CompositeShape cSh2(rect2);
      cSh2.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));

      cSh2.rotate(i);

      BOOST_CHECK_CLOSE(cSh.getFrameRect().pos.x, cSh2.getFrameRect().pos.x, EPSILON);
      BOOST_CHECK_CLOSE(cSh.getFrameRect().pos.y, cSh2.getFrameRect().pos.y, EPSILON);
      BOOST_CHECK_CLOSE(cSh.getArea(), cSh2.getArea(), EPSILON);
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_Shape_Tests)

  BOOST_AUTO_TEST_CASE(New_Columns)
  {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({9.0, 0.0}, 1.0));
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    std::shared_ptr<Shape> circle3 = std::make_shared<Circle>(Circle({-9.0, 0.0}, 1.0));

    Matrix matrix(circle1);
    matrix.addShape(circle2);
    matrix.addShape(circle3);

    BOOST_CHECK(matrix[0][0] == circle1);
    BOOST_CHECK(matrix[0][1] == circle2);
    BOOST_CHECK(matrix[0][2] == circle3);

  }

  BOOST_AUTO_TEST_CASE(New_Rows)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({-2.0, 2.0}, 2.0, 2.0));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({0.0, 0.0}, 3.0, 3.0));

    Matrix matrix(rect1);
    matrix.addShape(rect2);

    BOOST_CHECK(matrix[0][0] == rect1);
    BOOST_CHECK(matrix[1][0] == rect2);
  }

  BOOST_AUTO_TEST_CASE(Copy_Constructor_Test)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    Matrix matrix(rect);
    Matrix matrix2(matrix);
    BOOST_CHECK(matrix[0][0] == matrix2[0][0]);
  }

  BOOST_AUTO_TEST_CASE(Copy_Operator_Test)
  {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 5.0));
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    Matrix matrix(circle1);
    Matrix matrix2(circle2);
    matrix2 = matrix;
    BOOST_CHECK(matrix[0][0] == matrix2[0][0]);
  }

  BOOST_AUTO_TEST_CASE(Moving_Constructor_Test)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    Matrix matrix(rect);
    Matrix matrix2(matrix);
    Matrix matrix3(std::move(matrix));
    BOOST_CHECK(matrix2[0][0] == matrix3[0][0]);
  }

  BOOST_AUTO_TEST_CASE(Moving_Operator_Test)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4.0, 3.0}, 7.0, 5.0));
    Matrix matrix(rect);
    Matrix matrix2(matrix);
    Matrix matrix3(rect2);
    matrix3 = std::move(matrix);
    BOOST_CHECK(matrix2[0][0] == matrix3[0][0]);
  }

  BOOST_AUTO_TEST_CASE(addFromCSh)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 4.0, 4.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({2.0, 4.0}, 2.0));
    CompositeShape cSh(rect1);
    cSh.addShape(circle1);
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({-4.0, -3.0}, 4.0, 4.0));
    Matrix matrix(rect2);
    matrix.addFromCShape(cSh);
    BOOST_CHECK(matrix[0][0] == rect2);
    BOOST_CHECK(matrix[0][1] == rect1);
    BOOST_CHECK(matrix[1][0] == circle1);
  }

  BOOST_AUTO_TEST_CASE(matrix_after_rotate)
  {
    Rectangle rectangle1({0.0, 0.0}, 4.0, 2.0);
    Rectangle rectangle2({3.0, 0.0}, 4.0, 2.0);
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(rectangle1);
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(rectangle2);
    Matrix matrix(rect1);
    matrix.addShape(rect2);
    BOOST_CHECK(matrix[0][0] == rect1);
    BOOST_CHECK(matrix[0][1] == rect2);
    rectangle1.rotate(45.0);
    rectangle2.rotate(45.0);
    std::shared_ptr<Shape> newrect1 = std::make_shared<Rectangle>(rectangle1);
    std::shared_ptr<Shape> newrect2 = std::make_shared<Rectangle>(rectangle2);
    Matrix matrix2(newrect1);
    matrix2.addShape(newrect2);
    BOOST_CHECK(matrix2.getRows() == 2);
    BOOST_CHECK(matrix2[0][0] == newrect1);
    BOOST_CHECK(matrix2[1][0] == newrect2);
  }

BOOST_AUTO_TEST_SUITE_END()

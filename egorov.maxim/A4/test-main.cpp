#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

using namespace egorov;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Invalid_Initialization)
  {
    BOOST_CHECK_THROW(Circle(-4, {0, 0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle circle(5, {5, 3});
    double tmpHeight = circle.getFrameRect().height;
    double tmpWidth = circle.getFrameRect().width;
    double tmpArea = circle.getArea();
    circle.move({10, 12});
    BOOST_CHECK(circle.getFrameRect().pos.x == 10 && circle.getFrameRect().pos.y == 12);
    BOOST_CHECK_CLOSE(tmpArea, circle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, circle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, circle.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(DeltaMove)
  {
    Circle circle(5, {0, 0});
    double tmpHeight = circle.getFrameRect().height;
    double tmpWidth = circle.getFrameRect().width;
    double tmpArea = circle.getArea();
    circle.move(1, 2);
    BOOST_CHECK(circle.getFrameRect().pos.x == 1 && circle.getFrameRect().pos.y == 2);
    BOOST_CHECK_CLOSE(tmpArea, circle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, circle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, circle.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Circle circle(5, {0, 0});
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Circle_Scale)
  {
    Circle circle(5, {0, 0});
    double tmpArea = circle.getArea();
    const double coefficent2 = 2;
    circle.scale(coefficent2);
    BOOST_CHECK_CLOSE(coefficent2 * coefficent2 * tmpArea, circle.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rectangle_Test)

  BOOST_AUTO_TEST_CASE(Invalid_Initialization)
  {
    BOOST_CHECK_THROW(Rectangle({-5, -5, {0, 0}}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({-5, 5, {0, 0}}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({5, -5, {0, 0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rectangle({2, 4, {1, 1}});
    double tmpHeight = rectangle.getFrameRect().height;
    double tmpWidth = rectangle.getFrameRect().width;
    double tmpArea = rectangle.getArea();
    rectangle.move({5, 5});
    BOOST_CHECK(rectangle.getFrameRect().pos.x == 5 && rectangle.getFrameRect().pos.y);
    BOOST_CHECK_CLOSE(tmpArea, rectangle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, rectangle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, rectangle.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(DeltaMove)
  {
    Rectangle rectangle({2, 4, {1, 1}});
    double tmpHeight = rectangle.getFrameRect().height;
    double tmpWidth = rectangle.getFrameRect().width;
    double tmpArea = rectangle.getArea();
    rectangle.move(1, 2);
    BOOST_CHECK(rectangle.getFrameRect().pos.x == 2 && rectangle.getFrameRect().pos.y == 3);
    BOOST_CHECK_CLOSE(tmpArea, rectangle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, rectangle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, rectangle.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Rectangle rectangle({5, 5, {1, 1}});
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_Scale)
  {
    Rectangle rectangle({5, 5, {1, 1}});
    double tmpArea = rectangle.getArea();
    const double coefficent2 = 2;
    rectangle.scale(coefficent2);
    BOOST_CHECK_CLOSE(coefficent2 * coefficent2 * tmpArea, rectangle.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Composite_Shape_Tests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({10.0, 10.0, {2.0, 4.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(5.0, {0.0, 0.0}));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double tmpHeight = compositeShape.getFrameRect().height;
    double tmpWidth = compositeShape.getFrameRect().width;
    double tmpArea = compositeShape.getArea();
    compositeShape.move({5.0, 5.0});
    BOOST_CHECK(compositeShape.getFrameRect().pos.x == 5.0 && compositeShape.getFrameRect().pos.y == 5.0);
    BOOST_CHECK_CLOSE(tmpHeight, compositeShape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, compositeShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(tmpArea, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(DeltaMove)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({5.0, 5.0, {2.0, 3.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(5.0, {0.0, 0.0}));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double tmpHeight = compositeShape.getFrameRect().height;
    double tmpWidth = compositeShape.getFrameRect().width;
    double tmpArea = compositeShape.getArea();
    compositeShape.move(3.0, 2.0);
    BOOST_CHECK_CLOSE(tmpHeight, compositeShape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, compositeShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(tmpArea, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({5.0, 5.0, {1.0, 1.0}}));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(5.0, {1.0, 1.0}));
    compositeShape.addShape(circle1);
    BOOST_CHECK_THROW(compositeShape.scale(-2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CompositeShape_Scale)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({5.0, 5.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(5.0, {1.0, 1.0}));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double tmpArea = compositeShape.getArea();
    compositeShape.scale(2.0);
    BOOST_CHECK_CLOSE(2.0 * 2.0 * tmpArea, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Check_Add)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({5.0, 5.0, {1.0, 1.0}}));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(5.0, {1.0, 1.0}));
    compositeShape.addShape(circle1);
    BOOST_CHECK_EQUAL(compositeShape.getQuantity(), 2);
  }

  BOOST_AUTO_TEST_CASE(Check_Remove)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({25.0, 5.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(5.0, {1.0, 1.0}));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    compositeShape.removeShape(1);
    BOOST_CHECK_EQUAL(compositeShape.getQuantity(), 1);
  }

  BOOST_AUTO_TEST_CASE(Check_Remove_Index)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({25.0, 5.0, {1.0, 1.0}}));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    BOOST_CHECK_THROW(compositeShape.removeShape(1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Check_Recourse_Index)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({25.0, 5.0, {1.0, 1.0}}));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    BOOST_CHECK_THROW(compositeShape[3], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Empty_Composite_Shape)
  {
    CompositeShape compositeShape;
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().width, 0);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().height, 0);
  }

  BOOST_AUTO_TEST_CASE(Copy_TEST)
  {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(5.0, {0.0, 0.0}));
    std::shared_ptr<Shape> circle2(circle1);

    BOOST_CHECK_EQUAL(circle1->getFrameRect().pos.x, circle2->getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(circle1->getFrameRect().pos.y, circle2->getFrameRect().pos.y);
    BOOST_CHECK_EQUAL(circle1->getArea(), circle2->getArea());
  }


  BOOST_AUTO_TEST_CASE(Rotate_Test)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({25.0, 5.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(2.0, {0.0, 0.0}));

    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);

    for (size_t i = -180; i < 180; i++)
    {
      std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(Rectangle({25.0, 5.0, {1.0, 1.0}}));
      std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle(2.0, {0.0, 0.0}));

      CompositeShape compositeShape2;
      compositeShape2.addShape(rectangle2);
      compositeShape2.addShape(circle2);

      compositeShape2.rotate(i);

      BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, compositeShape2.getFrameRect().pos.x, EPSILON);
      BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, compositeShape2.getFrameRect().pos.y, EPSILON);
      BOOST_CHECK_CLOSE(compositeShape.getArea(), compositeShape2.getArea(), EPSILON);
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_Shape_Tests)

  BOOST_AUTO_TEST_CASE(New_Rows)
  {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(1.0, {-10.0, 0.0}));
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    std::shared_ptr<Shape> circle3 = std::make_shared<Circle>(Circle(1.0, {10.0, 0.0}));

    MatrixShape ms;
    ms.addShape(circle1);
    ms.addShape(circle2);
    ms.addShape(circle3);

    BOOST_CHECK(ms[0][0] == circle1);
    BOOST_CHECK(ms[0][1] == circle2);
    BOOST_CHECK(ms[0][2] == circle3);

  }

  BOOST_AUTO_TEST_CASE(New_Columns)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({10.0, 20.0, {0.0, 0.0}}));
    std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(Rectangle({10.0, 20.0, {2.0, 1.0}}));

    MatrixShape ms;
    ms.addShape(rectangle1);
    ms.addShape(rectangle2);

    BOOST_CHECK(ms[0][0] == rectangle1);
    BOOST_CHECK(ms[1][0] == rectangle2);

  }

  BOOST_AUTO_TEST_CASE(Copy_Constructor_Test)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({10.0, 20.0, {1.0, 2.0}}));
    MatrixShape matrixShape;
    matrixShape.addShape(rect);
    MatrixShape matrixShape2(matrixShape);
    BOOST_CHECK(matrixShape[0][0] == matrixShape2[0][0]);
  }

  BOOST_AUTO_TEST_CASE(Copy_Operator_Test)
  {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(5.0, {0.0, 0.0}));
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    MatrixShape matrixShape;
    MatrixShape matrixShape2;
    matrixShape.addShape(circle1);
    matrixShape2.addShape(circle2);
    matrixShape2 = matrixShape;
    BOOST_CHECK(matrixShape[0][0] == matrixShape2[0][0]);
  }

BOOST_AUTO_TEST_SUITE_END()

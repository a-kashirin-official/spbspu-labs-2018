#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "../A1/base-types.hpp"

using namespace lashchenov;

//Testing class Circle
BOOST_AUTO_TEST_SUITE(CircleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(lashchenov::Circle circle(-3.3, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(lashchenov::Circle circle(-3.3, 1, 2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    lashchenov::Circle circle{3.3, {1, 2}};
    circle.move({4, 5});
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.3, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    lashchenov::Circle circle1{3.3, {1, 2}};
    circle1.move(4, 5);
    BOOST_CHECK_CLOSE(circle1.getFrameRect().height / 2, 3.3, Accuracy);
    BOOST_CHECK_CLOSE(circle1.getFrameRect().pos.x, 5, Accuracy);
    BOOST_CHECK_CLOSE(circle1.getFrameRect().pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    lashchenov::Circle circle{3.3, {1, 2}};
    BOOST_CHECK_CLOSE(circle.getArea(), 34.21194399, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    lashchenov::Circle circle{3.3, {1, 2}};
    circle.scale(1.5);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 4.95, Accuracy);
    BOOST_CHECK_CLOSE(circle.getArea(), 76.97687399, Accuracy);
    BOOST_CHECK_THROW(circle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

//Testing class Rectangle
BOOST_AUTO_TEST_SUITE(RectangleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(lashchenov::Rectangle rectangle(-5, 7.5, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(lashchenov::Rectangle rectangle(-5, 7.5, 1, 2), std::invalid_argument);
    BOOST_CHECK_THROW(lashchenov::Rectangle rectangle(5, -7.5, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(lashchenov::Rectangle rectangle(5, -7.5, 1, 2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    lashchenov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move({4, 5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    lashchenov::Rectangle rectangle1(5, 7.5, {1, 2});
    rectangle1.move(4, 5);
    BOOST_CHECK_CLOSE(rectangle1.getFrameRect().width, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle1.getFrameRect().height, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle1.getFrameRect().pos.x, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle1.getFrameRect().pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    lashchenov::Rectangle rectangle(5, 7.5, {1, 2});
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    lashchenov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.scale(1.5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 11.25, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 84.375, Accuracy);
    BOOST_CHECK_THROW(rectangle.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    lashchenov::Rectangle rectangle(4, 2, {4, 3});
    for (int i = -90; i < 91; ++i) {
      lashchenov::Rectangle rectangle1(rectangle);
      rectangle.rotate(i);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, rectangle1.getFrameRect().pos.x, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, rectangle1.getFrameRect().pos.y, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.getArea(), rectangle1.getArea(), Accuracy);
    }
  }

BOOST_AUTO_TEST_SUITE_END()

//Testing class CompositeShape
BOOST_AUTO_TEST_SUITE(CompositeShapeTests)
  const double Accuracy = 0.0001;

  BOOST_AUTO_TEST_CASE(Constructor_Copying)
  {
    CompositeShape compositeShape;
    compositeShape.add(lashchenov::Rectangle(3, 4, {5, 6}));
    compositeShape.add(lashchenov::Rectangle(7, 8, {9, 1}));
    compositeShape.add(lashchenov::Circle(11, {12, 13}));
    compositeShape.add(lashchenov::Rectangle(4, 1, {6, 7}));

    CompositeShape compositeShape1(compositeShape);
    for (size_t i = 0; i < compositeShape.size(); ++i) {
      rectangle_t rectangle = compositeShape[i].getFrameRect();
      rectangle_t rectangle1 = compositeShape1[i].getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
      BOOST_CHECK((&compositeShape[i]) != (&compositeShape1[i]));
    }
  }

  BOOST_AUTO_TEST_CASE(Constructor_Moving)
  {
    CompositeShape compositeShape;
    compositeShape.add(lashchenov::Rectangle(3, 4, {5, 6}));
    compositeShape.add(lashchenov::Rectangle(7, 8, {9, 1}));
    compositeShape.add(lashchenov::Circle(11, {12, 13}));
    compositeShape.add(lashchenov::Rectangle(4, 1, {6, 7}));
    CompositeShape compositeShape1(compositeShape);

    CompositeShape compositeShape2(std::move(compositeShape));
    for (size_t i = 0; i < compositeShape2.size(); ++i) {
      rectangle_t rectangle = compositeShape1[i].getFrameRect();
      rectangle_t rectangle1 = compositeShape2[i].getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
      BOOST_CHECK((&compositeShape2[i]) != (&compositeShape1[i]));
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Copy)//copying operator=
  {
    CompositeShape compositeShape;
    compositeShape.add(lashchenov::Rectangle(3, 4, {5, 6}));
    compositeShape.add(lashchenov::Rectangle(7, 8, {9, 1}));
    compositeShape.add(lashchenov::Circle(11, {12, 13}));
    compositeShape.add(lashchenov::Rectangle(4, 1, {6, 7}));

    CompositeShape compositeShape1 = compositeShape;
    for (size_t i = 0; i < compositeShape.size(); ++i) {
      rectangle_t rectangle = compositeShape[i].getFrameRect();
      rectangle_t rectangle1 = compositeShape1[i].getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
      BOOST_CHECK((&compositeShape[i]) != (&compositeShape1[i]));
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Move)//moving operator=
  {
    CompositeShape compositeShape;
    compositeShape.add(lashchenov::Rectangle(3, 4, {5, 6}));
    compositeShape.add(lashchenov::Rectangle(7, 8, {9, 1}));
    compositeShape.add(lashchenov::Circle(11, {12, 13}));
    compositeShape.add(lashchenov::Rectangle(4, 1, {6, 7}));
    CompositeShape compositeShape1(compositeShape);

    CompositeShape compositeShape2 = std::move(compositeShape);
    for (size_t i = 0; i < compositeShape2.size(); ++i) {
      rectangle_t rectangle = compositeShape1[i].getFrameRect();
      rectangle_t rectangle1 = compositeShape2[i].getFrameRect();
      BOOST_CHECK_CLOSE(rectangle.height, rectangle1.height, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.width, rectangle1.width, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.pos.x, rectangle1.pos.x, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.pos.y, rectangle1.pos.y, Accuracy);
      BOOST_CHECK((&compositeShape2[i]) != (&compositeShape1[i]));
    }
  }

  BOOST_AUTO_TEST_CASE(Taking_by_index)//operator[]
  {
    CompositeShape compositeShape;
    compositeShape.add(lashchenov::Rectangle(3, 4, {5, 6}));
    BOOST_CHECK_THROW(compositeShape[1], std::out_of_range);
  }


  BOOST_AUTO_TEST_CASE(remove)
  {
    CompositeShape compositeShape;
    BOOST_REQUIRE_THROW(compositeShape.remove(0), std::invalid_argument);
    compositeShape.add(lashchenov::Rectangle(3, 4, {5, 6}));
    compositeShape.add(lashchenov::Rectangle(7, 8, {9, 1}));
    compositeShape.add(lashchenov::Circle(11, {12, 13}));
    compositeShape.add(lashchenov::Rectangle(4, 1, {6, 7}));
    BOOST_REQUIRE_THROW(compositeShape.remove(5), std::out_of_range);

    compositeShape.remove(2);
    rectangle_t rectangle = compositeShape[2].getFrameRect();
    BOOST_CHECK_CLOSE(rectangle.width, 4, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.height, 1, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.pos.x, 6, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getFrameRect)
  {
    CompositeShape compositeShape(lashchenov::Rectangle(1, 2, 3, 4));
    compositeShape.add(Circle(6, {2, 3}));
    compositeShape.add(lashchenov::Rectangle(9, 8, {7, 6}));
    compositeShape.add(Circle(5, {4, 7}));

    BOOST_CHECK_CLOSE(compositeShape.getArea(), 265.637151868, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 15, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 15.5, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, 3.75, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, 4.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    CompositeShape compositeShape(lashchenov::Rectangle(1, 2, 3, 4));
    compositeShape.add(Circle(6, {2, 3}));
    compositeShape.add(lashchenov::Rectangle(9, 8, {7, 6}));
    compositeShape.add(Circle(5, {4, 7}));

    CompositeShape compositeShape1 = compositeShape;
    compositeShape.move(5, 7);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), 265.637151868, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 15, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 15.5, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, 8.75, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, 11.5, Accuracy);

    for (size_t i = 0; i < compositeShape.size(); ++i) {
      rectangle_t rectangle = compositeShape[i].getFrameRect();
      rectangle_t rectangle1 = compositeShape1[i].getFrameRect();
      BOOST_CHECK_CLOSE(rectangle.height, rectangle1.height, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.width, rectangle1.width, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.pos.x, rectangle1.pos.x + 5, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.pos.y, rectangle1.pos.y + 7, Accuracy);
    }
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    CompositeShape compositeShape;
    compositeShape.add(lashchenov::Rectangle(10, 10, {5, 6}));
    compositeShape.add(lashchenov::Rectangle(10, 10, {9, 1}));
    compositeShape.add(lashchenov::Rectangle(10, 10, {12, 13}));
    compositeShape.add(lashchenov::Rectangle(10, 10, {6, 7}));

    CompositeShape compositeShape1 = compositeShape;
    double area = compositeShape1.getArea();
    rectangle_t rectangle = compositeShape1.getFrameRect();
    compositeShape.scale(2);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), area * 4, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, rectangle.height * 2, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, rectangle.width * 2, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, rectangle.pos.x, Accuracy);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, rectangle.pos.y, Accuracy);

    for (size_t i = 0; i < compositeShape.size(); ++i) {
      rectangle_t rectangle2 = compositeShape[i].getFrameRect();
      rectangle_t rectangle1 = compositeShape1[i].getFrameRect();
      const point_t pos = {rectangle.pos.x + (rectangle1.pos.x - rectangle.pos.x) * 2,
                           rectangle.pos.y + (rectangle1.pos.y - rectangle.pos.y) * 2};
      BOOST_CHECK_CLOSE(rectangle2.height, rectangle1.height * 2, Accuracy);
      BOOST_CHECK_CLOSE(rectangle2.width, rectangle1.width * 2, Accuracy);
      BOOST_CHECK_CLOSE(rectangle2.pos.x, pos.x, Accuracy);
      BOOST_CHECK_CLOSE(rectangle2.pos.y, pos.y, Accuracy);
    }
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    CompositeShape compositeShape;
    compositeShape.add(lashchenov::Rectangle(10, 10, {5, 6}));
    compositeShape.add(lashchenov::Rectangle(10, 10, {9, 1}));
    compositeShape.add(lashchenov::Rectangle(10, 10, {12, 13}));
    compositeShape.add(lashchenov::Rectangle(10, 10, {6, 7}));
    BOOST_CHECK_CLOSE(compositeShape.getArea(), 400, Accuracy);

    compositeShape.scale(2);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), 1600, Accuracy);

    compositeShape.move(2.3, 4.6);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), 1600, Accuracy);

    compositeShape.move({22.1, 21.5});
    BOOST_CHECK_CLOSE(compositeShape.getArea(), 1600, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    CompositeShape cShape1;
    cShape1.add(lashchenov::Rectangle(4, 3, {3, 2.5}));
    cShape1.add(lashchenov::Rectangle(2, 4, {11, 0}));
    cShape1.add(Circle(2, {8, 6}));
    CompositeShape cShape2(cShape1);
    cShape2.rotate(70);
    BOOST_CHECK_CLOSE(cShape1.getArea(), cShape2.getArea(), Accuracy);
    for (int i = 0; i < 3; ++i) {
      BOOST_CHECK_CLOSE(cShape1[i].getArea(), cShape2[i].getArea(), Accuracy);
    }
  }

  BOOST_AUTO_TEST_CASE(rotatePoint)
  {
    point_t p1 = {1, 1};
    point_t p2 = {5, 2};
    CompositeShape cShape;
    BOOST_CHECK_CLOSE_FRACTION(cShape.rotatePoint(p1, p2, 45).x,
                               p1.x + (5 - 1) * sqrt(2) / 2 - (2 - 1) * sqrt(2) / 2, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(cShape.rotatePoint(p1, p2, 45).y,
                               p1.y + (5 - 1) * sqrt(2) / 2 + (2 - 1) * sqrt(2) / 2, Accuracy);

    BOOST_CHECK_CLOSE_FRACTION(cShape.rotatePoint(p1, p2, 0).x, 5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(cShape.rotatePoint(p1, p2, 0).y, 2, Accuracy);

    BOOST_CHECK_CLOSE_FRACTION(cShape.rotatePoint(p1, p2, 360).x, 5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(cShape.rotatePoint(p1, p2, 360).y, 2, Accuracy);

    BOOST_CHECK_CLOSE_FRACTION(cShape.rotatePoint(p1, p2, -60).x,
                               p1.x + (5 - 1) * 1 / 2 - (2 - 1) * (-sqrt(3) / 2), Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(cShape.rotatePoint(p1, p2, -60).y,
                               p1.y + (5 - 1) * (-sqrt(3) / 2) + (2 - 1) * (0.5), Accuracy);
  }

BOOST_AUTO_TEST_SUITE_END()

//Testing class Matrix
BOOST_AUTO_TEST_SUITE(MatrixTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(addElementsFromCShape)
  {
    CompositeShape cShape1;
    lashchenov::Rectangle rectangle1(4, 2, {3, -3});
    Circle circle1(1, {10, -10});
    lashchenov::Rectangle rectangle2(2, 2, {10, -10});
    cShape1.add(rectangle1);
    cShape1.add(circle1);
    cShape1.add(rectangle2);

    Matrix matrix;
    matrix.addElementsFromCShape(cShape1);
    rectangle_t FrameRectangle[3];
    FrameRectangle[0] = rectangle1.getFrameRect();
    FrameRectangle[1] = circle1.getFrameRect();
    FrameRectangle[2] = rectangle2.getFrameRect();

    BOOST_CHECK_EQUAL(matrix.getLayerCount(), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(0), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(1), 1);
    for (size_t i = 0; i < matrix.getLayerCount(); ++i) {
      for (size_t j = 0; j < matrix.getLayerSize(i); ++j) {
        rectangle_t rectangle = matrix[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, FrameRectangle[i * 2 + j].pos.x, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.pos.y, FrameRectangle[i * 2 + j].pos.y, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.width, FrameRectangle[i * 2 + j].width, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.height, FrameRectangle[i * 2 + j].height, Accuracy);
      }
    }

  }
  BOOST_AUTO_TEST_CASE(add)
  {
    CompositeShape cShape1;
    lashchenov::Rectangle rectangle1(4, 2, {3, -3});
    Circle circle1(1, {7, -3});
    cShape1.add(rectangle1);
    cShape1.add(circle1);
    lashchenov::Rectangle rectangle2(2, 4, {2, 1});
    Circle circle2(1, {5, 3});

    Matrix matrix;
    matrix.addElementsFromCShape(cShape1);
    matrix.add(rectangle2);
    matrix.add(circle2);
    matrix.addElementsFromCShape(cShape1);

    rectangle_t FrameRectangle[6];
    FrameRectangle[0] = rectangle1.getFrameRect();
    FrameRectangle[1] = circle1.getFrameRect();
    FrameRectangle[2] = rectangle2.getFrameRect();
    FrameRectangle[3] = circle2.getFrameRect();
    FrameRectangle[4] = rectangle1.getFrameRect();
    FrameRectangle[5] = circle1.getFrameRect();

    BOOST_CHECK_EQUAL(matrix.getLayerCount(), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(0), 4);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(1), 2);
    for (size_t i = 0; i < matrix.getLayerCount(); ++i) {
      for (size_t j = 0; j < matrix.getLayerSize(i); ++j) {
        rectangle_t rectangle = matrix[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, FrameRectangle[i * 4 + j].pos.x, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.pos.y, FrameRectangle[i * 4 + j].pos.y, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.width, FrameRectangle[i * 4 + j].width, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.height, FrameRectangle[i * 4 + j].height, Accuracy);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(Taking_by_index)//operator[]
  {
    CompositeShape cShape1;
    cShape1.add(lashchenov::Rectangle(4, 2, {3, -3}));
    cShape1.add(Circle(1, {7, -3}));
    lashchenov::Rectangle rectangle1(2, 4, {2, 1});
    Circle circle1(1, {5, 3});

    Matrix matrix;
    matrix.addElementsFromCShape(cShape1);
    matrix.add(rectangle1);
    matrix.add(circle1);
    matrix.addElementsFromCShape(cShape1);

    BOOST_REQUIRE_EQUAL(matrix[0][2].getFrameRect().pos.x, rectangle1.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(matrix[0][2].getFrameRect().pos.y, rectangle1.getFrameRect().pos.y);
    BOOST_REQUIRE_THROW(matrix[3][0], std::out_of_range);
    BOOST_REQUIRE_THROW(matrix[0][4], std::out_of_range);

  }

  BOOST_AUTO_TEST_CASE(remove)
  {
    CompositeShape cShape1;
    lashchenov::Rectangle rectangle1(4, 2, {3, -3});
    Circle circle1(1, {7, -3});
    cShape1.add(rectangle1);
    cShape1.add(circle1);
    lashchenov::Rectangle rectangle2(2, 4, {2, 1});
    Circle circle2(1, {5, 3});

    Matrix matrix;
    matrix.addElementsFromCShape(cShape1);
    matrix.add(rectangle2);
    matrix.add(circle2);
    matrix.addElementsFromCShape(cShape1);

    rectangle_t FrameRectangle[5];
    FrameRectangle[0] = circle1.getFrameRect();
    FrameRectangle[1] = rectangle2.getFrameRect();
    FrameRectangle[2] = circle2.getFrameRect();
    FrameRectangle[3] = rectangle1.getFrameRect();
    FrameRectangle[4] = circle1.getFrameRect();

    matrix.remove(0, 0);
    BOOST_REQUIRE_THROW(matrix.remove(50, 0), std::out_of_range);
    BOOST_REQUIRE_THROW(matrix.remove(0, 50), std::out_of_range);
    BOOST_CHECK_EQUAL(matrix.getLayerCount(), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(0), 4);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(1), 1);
    for (size_t i = 0; i < matrix.getLayerCount(); ++i) {
      for (size_t j = 0; j < matrix.getLayerSize(i); ++j) {
        rectangle_t rectangle = matrix[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, FrameRectangle[i * 4 + j].pos.x, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.pos.y, FrameRectangle[i * 4 + j].pos.y, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.width, FrameRectangle[i * 4 + j].width, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.height, FrameRectangle[i * 4 + j].height, Accuracy);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(Constructor_Copy)
  {
    CompositeShape cShape1;
    cShape1.add(lashchenov::Rectangle(4, 2, {3, -3}));
    cShape1.add(Circle(1, {7, -3}));
    Matrix matrix;
    matrix.add(lashchenov::Rectangle(2, 4, {2, 1}));
    matrix.add(Circle(1, {5, 3}));
    matrix.addElementsFromCShape(cShape1);
    matrix.addElementsFromCShape(cShape1);

    Matrix matrix1(matrix);
    BOOST_CHECK_EQUAL(matrix.getLayerCount(), matrix1.getLayerCount());
    for (size_t i = 0; i < matrix.getLayerCount(); ++i) {
      BOOST_CHECK_EQUAL(matrix.getLayerSize(i), matrix1.getLayerSize(i));
      for (size_t j = 0; j < matrix.getLayerSize(i); ++j) {
        rectangle_t rectangle = matrix[i][j].getFrameRect();
        rectangle_t rectangle1 = matrix1[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, rectangle1.pos.x, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.pos.y, rectangle1.pos.y, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.width, rectangle1.width, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.height, rectangle1.height, Accuracy);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Copy)//copying operator=
  {
    CompositeShape cShape1;
    cShape1.add(lashchenov::Rectangle(4, 2, {3, -3}));
    cShape1.add(Circle(1, {7, -3}));
    Matrix matrix;
    matrix.add(lashchenov::Rectangle(2, 4, {2, 1}));
    matrix.add(Circle(1, {5, 3}));
    matrix.addElementsFromCShape(cShape1);
    matrix.addElementsFromCShape(cShape1);

    Matrix matrix1 = matrix;
    BOOST_CHECK_EQUAL(matrix.getLayerCount(), matrix1.getLayerCount());
    for (size_t i = 0; i < matrix.getLayerCount(); ++i) {
      BOOST_CHECK_EQUAL(matrix.getLayerSize(i), matrix1.getLayerSize(i));
      for (size_t j = 0; j < matrix.getLayerSize(i); ++j) {
        rectangle_t rectangle = matrix[i][j].getFrameRect();
        rectangle_t rectangle1 = matrix1[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, rectangle1.pos.x, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.pos.y, rectangle1.pos.y, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.width, rectangle1.width, Accuracy);
        BOOST_CHECK_CLOSE(rectangle.height, rectangle1.height, Accuracy);
      }
    }
  }

BOOST_AUTO_TEST_SUITE_END()

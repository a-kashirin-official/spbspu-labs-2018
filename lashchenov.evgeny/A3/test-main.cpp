#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

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

BOOST_AUTO_TEST_SUITE_END()

//Testing class CompositeShape
BOOST_AUTO_TEST_SUITE(CompositeShapeTests)
  const double Accuracy = 0.00001;

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

  BOOST_AUTO_TEST_CASE(Index_capture)//operator[]
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
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, 8.75, Accuracy);//3.75
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, 11.5, Accuracy);//4.5

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

BOOST_AUTO_TEST_SUITE_END()

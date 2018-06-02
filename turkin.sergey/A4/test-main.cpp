

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "polygon.hpp"
#include "matrix.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(CircleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(turkin::Circle circle(-3.3, {1, 2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    turkin::Circle circle{3.3, {1, 2}};
    circle.move({4, 5});
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.3, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    turkin::Circle circle{3.3, {1, 2}};
    circle.move(4, 5);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.3, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 5, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    turkin::Circle circle{3, {1, 2}};
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 9, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    turkin::Circle circle{3, {1, 2}};
    circle.scale(2);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 6, Accuracy);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 36, Accuracy);
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


//Testing class Rectangle
BOOST_AUTO_TEST_SUITE(RectangleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(turkin::Rectangle rectangle(-5, 7.5, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(turkin::Rectangle rectangle(5, -7.5, {1, 2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    turkin::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move({4, 5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    turkin::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move(4, 5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    turkin::Rectangle rectangle(5, 7.5, {1, 2});
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    turkin::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.scale(1.5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 11.25, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 84.375, Accuracy);
    BOOST_CHECK_THROW(rectangle.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    turkin::Rectangle rectangle(4, 2, {4, 3});
    turkin::Rectangle rectangle1(rectangle);
    for (int i = 0; i < 361; ++i) {
      rectangle.rotate(i);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, rectangle1.getFrameRect().pos.x, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, rectangle1.getFrameRect().pos.y, Accuracy);
      BOOST_CHECK_CLOSE(rectangle.getArea(), rectangle1.getArea(), Accuracy);
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TriangleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    turkin::Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.move({4.0, 5.0});
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 7, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 5.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    turkin::Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.move(4.0, 5.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 7, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 7, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 11.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    turkin::Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    BOOST_CHECK_CLOSE(triangle.getArea(), 6, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    turkin::Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.scale(2.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 4, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 14, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 3, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 7, Accuracy);
    BOOST_CHECK_THROW(triangle.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    turkin::Triangle triangle({4, 2}, {1, 1}, {4, 3});
    turkin::Triangle triangle1(triangle);
    for (int i = 0; i < 361; ++i) {
      triangle.rotate(i);
      BOOST_CHECK_CLOSE(triangle.getCenter().x, triangle1.getCenter().x, Accuracy);
      BOOST_CHECK_CLOSE(triangle.getCenter().y, triangle1.getCenter().y, Accuracy);
      BOOST_CHECK_CLOSE(triangle.getArea(), triangle1.getArea(), Accuracy);
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(turkin::CompositeShape testCompositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Constructor_Copying)
  {
    turkin::Rectangle rect1(3, 4, {5, 6});
    turkin::Rectangle rect2(7, 8, {9, 1});
    turkin::Circle circ(11, {12, 13});
    turkin::Rectangle rect3(4, 1, {6, 7});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> circPtr = std::make_shared<turkin::Circle>(circ);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(circPtr);
    testcompositeShape.add(rectPtr3);

    turkin::CompositeShape testcompositeShape1(testcompositeShape);
    for (size_t i = 0; i < testcompositeShape.getSize(); ++i) {
      turkin::rectangle_t rectangle = testcompositeShape[i]->getFrameRect();
      turkin::rectangle_t rectangle1 = testcompositeShape1[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Constructor_Moving)
  {
    turkin::Rectangle rect1(3, 4, {5, 6});
    turkin::Rectangle rect2(7, 8, {9, 1});
    turkin::Circle circ(11, {12, 13});
    turkin::Rectangle rect3(4, 1, {6, 7});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> circPtr = std::make_shared<turkin::Circle>(circ);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(circPtr);
    testcompositeShape.add(rectPtr3);
    turkin::CompositeShape testcompositeShape1(testcompositeShape);
    turkin::CompositeShape testcompositeShape2(std::move(testcompositeShape));
    for (size_t i = 0; i < testcompositeShape2.getSize(); ++i) {
      turkin::rectangle_t rectangle = testcompositeShape1[i]->getFrameRect();
      turkin::rectangle_t rectangle1 = testcompositeShape2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Copy)
  {
    turkin::Rectangle rect1(3, 4, {5, 6});
    turkin::Rectangle rect2(7, 8, {9, 1});
    turkin::Circle circ(11, {12, 13});
    turkin::Rectangle rect3(4, 1, {6, 7});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> circPtr = std::make_shared<turkin::Circle>(circ);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(circPtr);
    testcompositeShape.add(rectPtr3);
    turkin::CompositeShape testcompositeShape1(rectPtr1);
    testcompositeShape1 = testcompositeShape;
    for (size_t i = 0; i < testcompositeShape.getSize(); ++i) {
      turkin::rectangle_t rectangle = testcompositeShape[i]->getFrameRect();
      turkin::rectangle_t rectangle1 = testcompositeShape1[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Move)
  {
    turkin::Rectangle rect1(3, 4, {5, 6});
    turkin::Rectangle rect2(7, 8, {9, 1});
    turkin::Circle circ(11, {12, 13});
    turkin::Rectangle rect3(4, 1, {6, 7});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> circPtr = std::make_shared<turkin::Circle>(circ);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(circPtr);
    testcompositeShape.add(rectPtr3);
    turkin::CompositeShape testcompositeShape1(testcompositeShape);
    turkin::CompositeShape testcompositeShape2(rectPtr1);
    testcompositeShape2 = std::move(testcompositeShape);
    for (size_t i = 0; i < testcompositeShape2.getSize(); ++i) {
      turkin::rectangle_t rectangle = testcompositeShape1[i]->getFrameRect();
      turkin::rectangle_t rectangle1 = testcompositeShape2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Move_Test)
  {
    turkin::Rectangle rect1(1, 1, {1.5, 1.5});
    turkin::Rectangle rect2(1, 1, {2.5, 2.5});
    turkin::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testCompositeShape(rectPtr1);
    testCompositeShape.add(rectPtr2);
    testCompositeShape.add(rectPtr3);
    testCompositeShape.move({15, 10});
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.x, 15, Accuracy);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.y, 10, Accuracy);
  }


  BOOST_AUTO_TEST_CASE(Relative_Move_Test_CS)
  {
    turkin::Rectangle rect1(1, 1, {1.5, 1.5});
    turkin::Rectangle rect2(1, 1, {2.5, 2.5});
    turkin::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    testcompositeShape.move(-1, 1);
    BOOST_CHECK_CLOSE(testcompositeShape.getFrameRect().pos.x, 1.5, Accuracy);
    BOOST_CHECK_CLOSE(testcompositeShape.getFrameRect().pos.y, 3.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_CS)
  {
    turkin::Rectangle rect1(1, 1, {1.5, 1.5});
    turkin::Rectangle rect2(1, 1, {2.5, 2.5});
    turkin::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    BOOST_REQUIRE_EQUAL(testcompositeShape.getArea(), 3);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Move_CS)
  {
    turkin::Rectangle rect1(1, 1, {1.5, 1.5});
    turkin::Rectangle rect2(1, 1, {2.5, 2.5});
    turkin::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    testcompositeShape.move(5, 5);
    BOOST_CHECK_EQUAL(testcompositeShape.getArea(), 3);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_CS)
  {
    turkin::Rectangle rect1(1, 1, {1.5, 1.5});
    turkin::Rectangle rect2(1, 1, {2.5, 2.5});
    turkin::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 3, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_CS)
  {
    turkin::Rectangle rect1(1, 1, {1.5, 1.5});
    turkin::Rectangle rect2(1, 1, {2.5, 2.5});
    turkin::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    testcompositeShape.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getArea(), 48, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 12, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 12, Accuracy);

  }


  BOOST_AUTO_TEST_CASE(Remove_Element_Test_CS)
  {
    turkin::Rectangle rect1(1, 1, {1.5, 1.5});
    turkin::Rectangle rect2(1, 1, {2.5, 2.5});
    turkin::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    testcompositeShape.del(0);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 2, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 2, Accuracy);
  }


  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_CS)
  {
    turkin::Circle circ(10, {0, 0});
    std::shared_ptr<turkin::Shape> circPtr = std::make_shared<turkin::Circle>(circ);
    turkin::CompositeShape testcompositeShape(circPtr);
    BOOST_CHECK_THROW(testcompositeShape.scale(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_RemoveShape_Test_CS)
  {
    turkin::Circle circ(10, {0, 0});
    std::shared_ptr<turkin::Shape> circPtr = std::make_shared<turkin::Circle>(circ);
    turkin::CompositeShape testcompositeShape(circPtr);
    BOOST_CHECK_THROW(testcompositeShape.del(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Clear_Test_CS)
  {
    turkin::Circle circ1(10, {0, 0});
    turkin::Circle circ2(20, {10, 10});
    turkin::Circle circ3(30, {20, 20});
    std::shared_ptr<turkin::Shape> circPtr1 = std::make_shared<turkin::Circle>(circ1);
    std::shared_ptr<turkin::Shape> circPtr2 = std::make_shared<turkin::Circle>(circ2);
    std::shared_ptr<turkin::Shape> circPtr3 = std::make_shared<turkin::Circle>(circ3);
    turkin::CompositeShape testcompositeShape(circPtr1);
    testcompositeShape.add(circPtr2);
    testcompositeShape.add(circPtr3);
    testcompositeShape.del(2);
    BOOST_REQUIRE_EQUAL(testcompositeShape.getSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(Out_Of_Range_Error_Get_Element_Test_CS)
  {
    turkin::Circle circ(10, {0, 0});
    std::shared_ptr<turkin::Shape> circPtr = std::make_shared<turkin::Circle>(circ);
    turkin::CompositeShape testcompositeShape(circPtr);
    BOOST_CHECK_THROW(testcompositeShape[2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    turkin::Rectangle rect1(3, 4, {5, 6});
    turkin::Rectangle rect2(7, 8, {9, 1});
    turkin::Circle circ(11, {12, 13});
    turkin::Rectangle rect3(4, 1, {6, 7});
    std::shared_ptr<turkin::Shape> rectPtr1 = std::make_shared<turkin::Rectangle>(rect1);
    std::shared_ptr<turkin::Shape> rectPtr2 = std::make_shared<turkin::Rectangle>(rect2);
    std::shared_ptr<turkin::Shape> circPtr = std::make_shared<turkin::Circle>(circ);
    std::shared_ptr<turkin::Shape> rectPtr3 = std::make_shared<turkin::Rectangle>(rect3);
    turkin::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(circPtr);
    testcompositeShape.add(rectPtr3);

    turkin::CompositeShape testcompositeShape1(testcompositeShape);
    testcompositeShape1.rotate(70);
    BOOST_CHECK_CLOSE(testcompositeShape.getArea(), testcompositeShape1.getArea(), Accuracy);
    for (int i = 0; i < 3; ++i) {
      BOOST_CHECK_CLOSE(testcompositeShape[i]->getArea(), testcompositeShape1[i]->getArea(), Accuracy);
    }

  }


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PolegonTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor_Area)
  {

    size_t size = 4;
    turkin::point_t ver[size] = {{0, 0},
                                 {0, 0},
                                 {0, 0},
                                 {0, 0}};
    std::unique_ptr<turkin::point_t[]> array(new turkin::point_t[size]);
    for (int i = 0; i < 4; ++i) {
      array[i] = ver[i];
    }
    BOOST_CHECK_THROW(turkin::Polygon pol(array, size), std::invalid_argument);


  }

  BOOST_AUTO_TEST_CASE(Constructor_size)
  {
    size_t size = 3;
    turkin::point_t ver[size] = {{0, 1},
                                 {1, 0},
                                 {3, 3}};
    std::unique_ptr<turkin::point_t[]> array(new turkin::point_t[size]);
    for (int i = 0; i < 3; ++i) {
      array[i] = ver[i];
    }
    BOOST_CHECK_THROW(turkin::Polygon pol(array, size), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Constructor_convex)
  {
    size_t size = 4;
    turkin::point_t ver[size] = {{-2, 1},
                                 {-5, 1},
                                 {-3, 2},
                                 {-2, 4}};
    std::unique_ptr<turkin::point_t[]> array(new turkin::point_t[size]);
    for (int i = 0; i < 4; ++i) {
      array[i] = ver[i];
    }
    BOOST_CHECK_THROW(turkin::Polygon pol(array, size), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    size_t size = 4;
    turkin::point_t ver[size] = {{0, 0},
                                 {2, 2},
                                 {4, 2},
                                 {2, 0}};
    std::unique_ptr<turkin::point_t[]> array(new turkin::point_t[size]);
    for (int i = 0; i < 4; ++i) {
      array[i] = ver[i];
    }
    turkin::Polygon pol(array, size);
    pol.move({4.0, 5.0});
    BOOST_CHECK_CLOSE(pol.getFrameRect().width, 4, Accuracy);
    BOOST_CHECK_CLOSE(pol.getFrameRect().height, 2, Accuracy);
    BOOST_CHECK_CLOSE(pol.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(pol.getFrameRect().pos.y, 5, Accuracy);
    BOOST_CHECK_CLOSE(pol.getArea(), 4, Accuracy);
  }


  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    size_t size = 4;
    turkin::point_t ver[size] = {{0, 0},
                                 {2, 2},
                                 {4, 2},
                                 {2, 0}};
    std::unique_ptr<turkin::point_t[]> array(new turkin::point_t[size]);
    for (int i = 0; i < 4; ++i) {
      array[i] = ver[i];
    }
    turkin::Polygon pol(array, size);
    pol.move(4.0, 5.0);
    BOOST_CHECK_CLOSE(pol.getFrameRect().width, 4, Accuracy);
    BOOST_CHECK_CLOSE(pol.getFrameRect().height, 2, Accuracy);
    BOOST_CHECK_CLOSE(pol.getFrameRect().pos.x, 6, Accuracy);
    BOOST_CHECK_CLOSE(pol.getFrameRect().pos.y, 6, Accuracy);
    BOOST_CHECK_CLOSE(pol.getArea(), 4, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    size_t size = 4;
    turkin::point_t ver[size] = {{0, 0},
                                 {2, 2},
                                 {4, 2},
                                 {2, 0}};
    std::unique_ptr<turkin::point_t[]> array(new turkin::point_t[size]);
    for (int i = 0; i < 4; ++i) {
      array[i] = ver[i];
    }
    turkin::Polygon pol(array, size);
    BOOST_CHECK_CLOSE(pol.getArea(), 4, Accuracy);
  }


  BOOST_AUTO_TEST_CASE(scale)
  {
    size_t size = 4;
    turkin::point_t ver[size] = {{0, 0},
                                 {2, 2},
                                 {4, 2},
                                 {2, 0}};
    std::unique_ptr<turkin::point_t[]> array(new turkin::point_t[size]);
    for (int i = 0; i < 4; ++i) {
      array[i] = ver[i];
    }
    turkin::Polygon pol(array, size);
    pol.scale(2);
    BOOST_CHECK_CLOSE(pol.getArea(), 16, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    size_t size = 4;
    turkin::point_t ver[size] = {{0, 0},
                                 {2, 2},
                                 {4, 2},
                                 {2, 0}};
    std::unique_ptr<turkin::point_t[]> array(new turkin::point_t[size]);
    for (int i = 0; i < 4; ++i) {
      array[i] = ver[i];
    }
    turkin::Polygon pol1(array, size);
    turkin::Polygon pol2(array, size);
    for (int i = 0; i < 361; ++i) {
      pol1.rotate(i);
      BOOST_CHECK_CLOSE(pol1.getFrameRect().pos.x, pol2.getFrameRect().pos.x, Accuracy);
      BOOST_CHECK_CLOSE(pol1.getFrameRect().pos.y, pol2.getFrameRect().pos.y, Accuracy);
      BOOST_CHECK_CLOSE(pol1.getArea(), pol2.getArea(), Accuracy);
    }
  }


BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(MatrixTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor1)
  {
    BOOST_CHECK_THROW(turkin::Matrix testMatrix(nullptr), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(Constructor2)
  {
    turkin::Circle testCircle(10.0, {100.0, 0.0});
    std::shared_ptr<turkin::Shape> circlePtr = std::make_shared<turkin::Circle>(testCircle);
    turkin::Matrix testMatrix(circlePtr);
    BOOST_CHECK_THROW(testMatrix[-1], std::invalid_argument);
  }


  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    turkin::Circle testCircleM(10.0, {-10.0, 0.0});
    turkin::Rectangle testRectangleM1(20.0, 40.0, {20.0, 30.0});
    turkin::Rectangle testRectangleM2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr<turkin::Shape> circlePtrM = std::make_shared<turkin::Circle>(testCircleM);
    std::shared_ptr<turkin::Shape> rectanglePtrM1 = std::make_shared<turkin::Rectangle>(testRectangleM1);
    std::shared_ptr<turkin::Shape> rectanglePtrM2 = std::make_shared<turkin::Rectangle>(testRectangleM2);
    turkin::Matrix testMatrix1(circlePtrM);
    testMatrix1.addShape(rectanglePtrM1);
    testMatrix1.addShape(rectanglePtrM2);
    turkin::Matrix testMatrix2(testMatrix1);
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer0 = testMatrix2[0];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    turkin::Circle testCircleM(10.0, {-10.0, 0.0});
    turkin::Rectangle testRectangleM1(20.0, 40.0, {20.0, 30.0});
    turkin::Rectangle testRectangleM2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr<turkin::Shape> circlePtrM = std::make_shared<turkin::Circle>(testCircleM);
    std::shared_ptr<turkin::Shape> rectanglePtrM1 = std::make_shared<turkin::Rectangle>(testRectangleM1);
    std::shared_ptr<turkin::Shape> rectanglePtrM2 = std::make_shared<turkin::Rectangle>(testRectangleM2);
    turkin::Matrix testMatrix1(circlePtrM);
    testMatrix1.addShape(rectanglePtrM1);
    testMatrix1.addShape(rectanglePtrM2);
    turkin::Matrix testMatrix2(std::move(testMatrix1));
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer0 = testMatrix2[0];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer1 = testMatrix2[1];
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
    turkin::Circle testCircleM2(20.0, {40.0, 30.0});
    turkin::Circle testCircleM1(10.0, {-10.0, 0.0});
    turkin::Rectangle testRectangleM1(20.0, 40.0, {20.0, 30.0});
    turkin::Rectangle testRectangleM2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr<turkin::Shape> circlePtrM1 = std::make_shared<turkin::Circle>(testCircleM1);
    std::shared_ptr<turkin::Shape> circlePtrM2 = std::make_shared<turkin::Circle>(testCircleM2);
    std::shared_ptr<turkin::Shape> rectanglePtrM1 = std::make_shared<turkin::Rectangle>(testRectangleM1);
    std::shared_ptr<turkin::Shape> rectanglePtrM2 = std::make_shared<turkin::Rectangle>(testRectangleM2);
    turkin::Matrix testMatrix1(circlePtrM1);
    testMatrix1.addShape(rectanglePtrM1);
    testMatrix1.addShape(rectanglePtrM2);
    turkin::Matrix testMatrix2(circlePtrM2);
    testMatrix2 = testMatrix1;
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer0 = testMatrix2[0];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    turkin::Circle testCircleM2(20.0, {40.0, 30.0});
    turkin::Circle testCircleM1(10.0, {-10.0, 0.0});
    turkin::Rectangle testRectangleM1(20.0, 40.0, {20.0, 30.0});
    turkin::Rectangle testRectangleM2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr<turkin::Shape> circlePtrM1 = std::make_shared<turkin::Circle>(testCircleM1);
    std::shared_ptr<turkin::Shape> circlePtrM2 = std::make_shared<turkin::Circle>(testCircleM2);
    std::shared_ptr<turkin::Shape> rectanglePtrM1 = std::make_shared<turkin::Rectangle>(testRectangleM1);
    std::shared_ptr<turkin::Shape> rectanglePtrM2 = std::make_shared<turkin::Rectangle>(testRectangleM2);
    turkin::Matrix testMatrix1(circlePtrM1);
    testMatrix1.addShape(rectanglePtrM1);
    testMatrix1.addShape(rectanglePtrM2);
    turkin::Matrix testMatrix2(circlePtrM2);
    testMatrix2 = std::move(testMatrix1);
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer0 = testMatrix2[0];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayersNumber(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayerSize(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MatrixGetFramerectTest)
  {
    turkin::Circle testCircle1(10.0, {-10.0, 0.0});
    turkin::Circle testCircle2(20.0, {40.0, 30.0});
    turkin::Rectangle testRectangle1(20.0, 40.0, {20.0, 30.0});
    turkin::Rectangle testRectangle2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr<turkin::Shape> circlePtr1 = std::make_shared<turkin::Circle>(testCircle1);
    std::shared_ptr<turkin::Shape> circlePtr2 = std::make_shared<turkin::Circle>(testCircle2);
    std::shared_ptr<turkin::Shape> rectanglePtr1 = std::make_shared<turkin::Rectangle>(testRectangle1);
    std::shared_ptr<turkin::Shape> rectanglePtr2 = std::make_shared<turkin::Rectangle>(testRectangle2);
    turkin::Matrix testMatrix(circlePtr1);
    testMatrix.addShape(rectanglePtr1);
    testMatrix.addShape(rectanglePtr2);
    testMatrix.addShape(circlePtr2);
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer0 = testMatrix[0];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer1 = testMatrix[1];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer2 = testMatrix[2];
    BOOST_CHECK(layer0[0] == circlePtr1);
    BOOST_CHECK(layer0[1] == rectanglePtr1);
    BOOST_CHECK(layer1[0] == rectanglePtr2);
    BOOST_CHECK(layer1[1] == nullptr);
    BOOST_CHECK(layer2[0] == circlePtr2);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getFrameRect().pos.x, -10.0, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getFrameRect().pos.x, 20.0, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, 30.0, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.x, 40.0, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getFrameRect().pos.y, 0.0, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getFrameRect().pos.y, 30.0, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, 0.0, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.y, 30.0, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(addCs)
  {
    turkin::Circle testCircle1(10.0, {-10.0, 0.0});
    turkin::Circle testCircle2(20.0, {40.0, 30.0});
    turkin::Rectangle testRectangle1(20.0, 40.0, {20.0, 30.0});
    turkin::Rectangle testRectangle2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr<turkin::Shape> circlePtr1 = std::make_shared<turkin::Circle>(testCircle1);
    std::shared_ptr<turkin::Shape> circlePtr2 = std::make_shared<turkin::Circle>(testCircle2);
    std::shared_ptr<turkin::Shape> rectanglePtr1 = std::make_shared<turkin::Rectangle>(testRectangle1);
    std::shared_ptr<turkin::Shape> rectanglePtr2 = std::make_shared<turkin::Rectangle>(testRectangle2);
    turkin::CompositeShape testCompasiteShape(rectanglePtr1);
    testCompasiteShape.add(rectanglePtr2);
    testCompasiteShape.add(circlePtr2);

    size_t size = testCompasiteShape.getSize();
    std::shared_ptr<turkin::CompositeShape> array = std::make_shared<turkin::CompositeShape>(testCompasiteShape);
    turkin::Matrix testMatrix(circlePtr1);
    testMatrix.addFromShape(array, size);

    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer0 = testMatrix[0];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer1 = testMatrix[1];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer2 = testMatrix[2];
    BOOST_CHECK(layer0[0] == circlePtr1);
    BOOST_CHECK(layer0[1] == rectanglePtr1);
    BOOST_CHECK(layer1[0] == rectanglePtr2);
    BOOST_CHECK(layer1[1] == nullptr);
    BOOST_CHECK(layer2[0] == circlePtr2);
    BOOST_CHECK(layer2[1] == nullptr);
  }

BOOST_AUTO_TEST_SUITE_END()

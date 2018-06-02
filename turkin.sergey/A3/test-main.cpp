

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
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
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
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


BOOST_AUTO_TEST_SUITE_END()

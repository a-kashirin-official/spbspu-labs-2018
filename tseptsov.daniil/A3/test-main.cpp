#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "boost/test/included/unit_test.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

using namespace tseptsov;

const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(tseptsov::Rectangle rectangle(-5, 7.5, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(tseptsov::Rectangle rectangle(5, -7.5, {1, 2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_byAxes)
  {
    tseptsov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move(4, 5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 7, EPS);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, EPS);

  }

  BOOST_AUTO_TEST_CASE(Move_topoint)
  {
    tseptsov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move({4, 5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 4, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, EPS);

  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    tseptsov::Rectangle rectangle(5, 7.5, {1, 2});
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, EPS);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    tseptsov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.scale(1.5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 7.5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 11.25, EPS);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 84.375, EPS);
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(Circle circle(-3.3, {1, 2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    Circle circle{3.0, {1, 2}};
    circle.move(4, 5);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.0, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 5, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 7, EPS);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 9.0, EPS);

  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    Circle circle{3.0, {1, 2}};
    circle.move({4, 5});
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.0, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 4, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 5, EPS);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 9.0, EPS);

  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Circle circle{3, {1, 2}};
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 9, EPS);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Circle circle{3, {1, 2}};
    circle.scale(2);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 6, EPS);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 36, EPS);
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TriangleTests)

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.move(4.0, 5.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 7, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 7, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 11.5, EPS);
    BOOST_CHECK_CLOSE(triangle.getArea(), 6, EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.move({4.0, 5.0});
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 7, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 4, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 5.5, EPS);
    BOOST_CHECK_CLOSE(triangle.getArea(), 6, EPS);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    BOOST_CHECK_CLOSE(triangle.getArea(), 6, EPS);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.scale(2.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 4, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 14, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 3, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 7, EPS);
    BOOST_CHECK_CLOSE(triangle.getArea(), 6 * 4, EPS);
    BOOST_CHECK_THROW(triangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape)

  BOOST_AUTO_TEST_CASE(Constructor_Test)
  {
    BOOST_CHECK_THROW(tseptsov::CompositeShape compositeshape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Constructor_Copying)
  {
    tseptsov::Rectangle rect1(3, 4, {5, 6});
    tseptsov::Rectangle rect2(7, 8, {9, 1});
    tseptsov::Circle circ1(11, {12, 13});
    tseptsov::Circle circ2(12, {13, 14});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > circPtr1 = std::make_shared < tseptsov::Circle >(circ1);
    std::shared_ptr < tseptsov::Shape > circPtr2 = std::make_shared < tseptsov::Circle >(circ2);
    tseptsov::CompositeShape compositeShape(rectPtr1);
    compositeShape.add(rectPtr2);
    compositeShape.add(circPtr1);
    compositeShape.add(circPtr2);

    tseptsov::CompositeShape compositeShape1(compositeShape);
    for (size_t i = 0; i < compositeShape.getSize(); ++i) {
      tseptsov::rectangle_t rectangle = compositeShape[i]->getFrameRect();
      tseptsov::rectangle_t rectangle1 = compositeShape1[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Constructor_Moving)
  {
    tseptsov::Rectangle rect1(3, 4, {5, 6});
    tseptsov::Rectangle rect2(7, 8, {9, 1});
    tseptsov::Circle circ1(11, {12, 13});
    tseptsov::Circle circ2(12, {13, 14});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > circPtr = std::make_shared < tseptsov::Circle >(circ1);
    std::shared_ptr < tseptsov::Shape > circPtr2 = std::make_shared < tseptsov::Circle >(circ2);
    tseptsov::CompositeShape compositeShape(rectPtr1);
    compositeShape.add(rectPtr2);
    compositeShape.add(circPtr);
    compositeShape.add(circPtr2);
    tseptsov::CompositeShape compositeShape1(compositeShape);
    tseptsov::CompositeShape compositeShape2(std::move(compositeShape));
    for (size_t i = 0; i < compositeShape2.getSize(); ++i) {
      tseptsov::rectangle_t rectangle = compositeShape1[i]->getFrameRect();
      tseptsov::rectangle_t rectangle1 = compositeShape2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }


  BOOST_AUTO_TEST_CASE(Assignment_Copy)
  {
    tseptsov::Rectangle rect1(3, 4, {5, 6});
    tseptsov::Rectangle rect2(7, 8, {9, 1});
    tseptsov::Circle circl(11, {12, 13});
    tseptsov::Circle circ2(12, {13, 14});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > circPtr1 = std::make_shared < tseptsov::Circle >(circl);
    std::shared_ptr < tseptsov::Shape > circPtr2 = std::make_shared < tseptsov::Circle >(circ2);
    tseptsov::CompositeShape compositeShape(rectPtr1);
    compositeShape.add(rectPtr2);
    compositeShape.add(circPtr1);
    compositeShape.add(circPtr2);
    tseptsov::CompositeShape compositeShape1(rectPtr1);
    compositeShape1 = compositeShape;
    for (size_t i = 0; i < compositeShape.getSize(); ++i) {
      tseptsov::rectangle_t rectangle = compositeShape[i]->getFrameRect();
      tseptsov::rectangle_t rectangle1 = compositeShape1[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Move)
  {
    tseptsov::Rectangle rectang1(3, 4, {5, 6});
    tseptsov::Rectangle rectang2(7, 8, {9, 1});
    tseptsov::Circle circ1(11, {12, 13});
    tseptsov::Circle circ2(12, {13, 14});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rectang1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rectang2);
    std::shared_ptr < tseptsov::Shape > circPtr1 = std::make_shared < tseptsov::Circle >(circ1);
    std::shared_ptr < tseptsov::Shape > circPtr2 = std::make_shared < tseptsov::Circle >(circ2);
    tseptsov::CompositeShape compositeShape(rectPtr1);
    compositeShape.add(rectPtr2);
    compositeShape.add(circPtr1);
    compositeShape.add(circPtr2);
    tseptsov::CompositeShape compositeShape1(compositeShape);
    tseptsov::CompositeShape compositeShape2(circPtr1);
    compositeShape2 = std::move(compositeShape1);
    for (size_t i = 0; i < compositeShape2.getSize(); ++i) {
      tseptsov::rectangle_t rectangle = compositeShape[i]->getFrameRect();
      tseptsov::rectangle_t rectangle1 = compositeShape2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Moving_Test)
  {
    tseptsov::Rectangle rect1(10, 13, {11.5, 11.5});
    tseptsov::Rectangle rect2(10, 13, {12.5, 12.5});
    tseptsov::Rectangle rect3(10, 13, {13.5, 13.5});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > rectPtr3 = std::make_shared < tseptsov::Rectangle >(rect3);
    tseptsov::CompositeShape compositeShape(rectPtr1);
    compositeShape.add(rectPtr2);
    compositeShape.add(rectPtr3);
    compositeShape.move({1, 3});
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, 1, EPS);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, 3, EPS);
  }

  BOOST_AUTO_TEST_CASE(Relative_Moving_Test)
  {
    tseptsov::Rectangle rect1(10, 13, {11.5, 11.5});
    tseptsov::Rectangle rect2(10, 13, {12.5, 12.5});
    tseptsov::Rectangle rect3(10, 13, {13.5, 13.5});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > rectPtr3 = std::make_shared < tseptsov::Rectangle >(rect3);
    tseptsov::CompositeShape compositeShape(rectPtr1);
    compositeShape.add(rectPtr2);
    compositeShape.add(rectPtr3);
    compositeShape.move(-2, 2);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, 10.5, EPS);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, 14.5, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test)
  {
    tseptsov::Rectangle rect1(10, 13, {11.5, 11.5});
    tseptsov::Rectangle rect2(10, 13, {12.5, 12.5});
    tseptsov::Rectangle rect3(10, 13, {13.5, 13.5});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > rectPtr3 = std::make_shared < tseptsov::Rectangle >(rect3);
    tseptsov::CompositeShape compositeshape(rectPtr1);
    compositeshape.add(rectPtr2);
    compositeshape.add(rectPtr3);
    BOOST_REQUIRE_EQUAL(compositeshape.getArea(), 390);
  }

  BOOST_AUTO_TEST_CASE(Moving_Test_Area)
  {
    tseptsov::Rectangle rect1(10, 13, {11.5, 11.5});
    tseptsov::Rectangle rect2(10, 13, {12.5, 12.5});
    tseptsov::Rectangle rect3(10, 13, {13.5, 13.5});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > rectPtr3 = std::make_shared < tseptsov::Rectangle >(rect3);
    tseptsov::CompositeShape compositeshape(rectPtr1);
    compositeshape.add(rectPtr2);
    compositeshape.add(rectPtr3);
    compositeshape.move(5, 5);
    BOOST_REQUIRE_EQUAL(compositeshape.getArea(), 390);
  }

  BOOST_AUTO_TEST_CASE(FrameRect_Test)
  {
    tseptsov::Rectangle rect1(10, 13, {11.5, 11.5});
    tseptsov::Rectangle rect2(10, 13, {12.5, 12.5});
    tseptsov::Rectangle rect3(10, 13, {13.5, 13.5});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > rectPtr3 = std::make_shared < tseptsov::Rectangle >(rect3);
    tseptsov::CompositeShape compositeshape(rectPtr1);
    compositeshape.add(rectPtr2);
    compositeshape.add(rectPtr3);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().pos.x, 12.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().pos.y, 12.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().width, 12, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().height, 15, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scaling_Test_Area)
  {
    tseptsov::Rectangle rect1(10, 13, {11.5, 11.5});
    tseptsov::Rectangle rect2(10, 13, {12.5, 12.5});
    tseptsov::Rectangle rect3(10, 13, {13.5, 13.5});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > rectPtr3 = std::make_shared < tseptsov::Rectangle >(rect3);
    tseptsov::CompositeShape compositeshape(rectPtr1);
    compositeshape.add(rectPtr2);
    compositeshape.add(rectPtr3);
    compositeshape.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getArea(), 6240, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scaling_Test_FrameRect)
  {
    tseptsov::Rectangle rect1(1.0, 1.0, {1.5, 1.5});
    tseptsov::Rectangle rect2(1.0, 1.0, {2.5, 2.5});
    tseptsov::Rectangle rect3(1.0, 1.0, {3.5, 3.5});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > rectPtr3 = std::make_shared < tseptsov::Rectangle >(rect3);
    tseptsov::CompositeShape compositeshape(rectPtr1);
    compositeshape.add(rectPtr2);
    compositeshape.add(rectPtr3);
    compositeshape.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().pos.x, 2.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().pos.y, 2.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().width, 6, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().height, 6, EPS);
  }

  BOOST_AUTO_TEST_CASE(Remove_Element_Test)
  {
    tseptsov::Rectangle rect1(10, 13, {11.5, 11.5});
    tseptsov::Rectangle rect2(10, 13, {12.5, 12.5});
    tseptsov::Rectangle rect3(10, 13, {13.5, 13.5});
    std::shared_ptr < tseptsov::Shape > rectPtr1 = std::make_shared < tseptsov::Rectangle >(rect1);
    std::shared_ptr < tseptsov::Shape > rectPtr2 = std::make_shared < tseptsov::Rectangle >(rect2);
    std::shared_ptr < tseptsov::Shape > rectPtr3 = std::make_shared < tseptsov::Rectangle >(rect3);
    tseptsov::CompositeShape compositeshape(rectPtr1);
    compositeshape.add(rectPtr2);
    compositeshape.add(rectPtr3);
    compositeshape.remove(0);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().pos.x, 13, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().pos.y, 13, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().width, 11, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getFrameRect().height, 14, EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Of_Scaling)
  {
    Circle circ(10.0, {0.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circPtr = std::make_shared < tseptsov::Circle >(circ);
    tseptsov::CompositeShape compositeshape(circPtr);
    BOOST_CHECK_THROW(compositeshape.scale(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Of_Removing)
  {
    Circle circ(10.0, {0.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circPtr = std::make_shared < tseptsov::Circle >(circ);
    tseptsov::CompositeShape compositeshape(circPtr);
    BOOST_CHECK_THROW(compositeshape.remove(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Get_Size)
  {
    Circle circ1(1.0, {1.0, 1.0});
    Circle circ2(2.0, {2.0, 2.0});
    Circle circ3(3.0, {3.0, 3.0});
    std::shared_ptr < tseptsov::Shape > circPtr1 = std::make_shared < tseptsov::Circle >(circ1);
    std::shared_ptr < tseptsov::Shape > circPtr2 = std::make_shared < tseptsov::Circle >(circ2);
    std::shared_ptr < tseptsov::Shape > circPtr3 = std::make_shared < tseptsov::Circle >(circ3);
    tseptsov::CompositeShape compositeshape(circPtr1);
    compositeshape.add(circPtr2);
    compositeshape.add(circPtr3);
    compositeshape.remove(1);
    BOOST_REQUIRE_EQUAL(compositeshape.getSize(),2);
  }

  BOOST_AUTO_TEST_CASE(Out_Of_Range)
  {
    Circle circ(10.0, {0.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circPtr = std::make_shared < tseptsov::Circle >(circ);
    tseptsov::CompositeShape compositeshape(circPtr);
    BOOST_CHECK_THROW(compositeshape[2], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()



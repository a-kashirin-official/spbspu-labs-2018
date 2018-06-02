#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "boost/test/included/unit_test.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "polygon.hpp"
#include "matrix.hpp"

using namespace tseptsov;

const double EPS = 0.0001;

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

  BOOST_AUTO_TEST_CASE(rotate)
  {
    tseptsov::Rectangle rectangle(4, 2, {4, 3});
    tseptsov::Rectangle rectangle1(rectangle);
    for (int i = 0; i < 361; ++i) {
      rectangle.rotate(i);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, rectangle1.getFrameRect().pos.x, EPS);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, rectangle1.getFrameRect().pos.y, EPS);
      BOOST_CHECK_CLOSE(rectangle.getArea(), rectangle1.getArea(), EPS);
    }
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

  BOOST_AUTO_TEST_CASE(rotate)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    Triangle triangle1(triangle);
    for(int i = -181; i < 181; ++i){
      triangle1.rotate(i);
      BOOST_CHECK_CLOSE(triangle.getCenter().x, triangle1.getCenter().x, EPS);
      BOOST_CHECK_CLOSE(triangle.getCenter().y, triangle1.getCenter().y, EPS);
      BOOST_CHECK_CLOSE(triangle.getArea(), triangle1.getArea() , EPS);
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape)

  BOOST_AUTO_TEST_CASE(Constructor_Test)
  {
    BOOST_CHECK_THROW(tseptsov::CompositeShape compositeShape(nullptr), std::invalid_argument);
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
    tseptsov::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(circPtr1);
    testcompositeShape.add(circPtr2);
    tseptsov::CompositeShape testcompositeShape1(testcompositeShape);
    tseptsov::CompositeShape testcompositeShape2(rectPtr1);
    testcompositeShape2 = std::move(testcompositeShape);
    for (size_t i = 0; i < testcompositeShape2.getSize(); ++i) {
      tseptsov::rectangle_t rectangle = testcompositeShape1[i]->getFrameRect();
      tseptsov::rectangle_t rectangle1 = testcompositeShape2[i]->getFrameRect();
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

  BOOST_AUTO_TEST_CASE(Scaling_Test)
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
    BOOST_CHECK_CLOSE_FRACTION(compositeshape.getArea(), 12, EPS);
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
    BOOST_REQUIRE_EQUAL(compositeshape.getSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(Out_Of_Range)
  {
    Circle circ(10.0, {0.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circPtr = std::make_shared < tseptsov::Circle >(circ);
    tseptsov::CompositeShape compositeshape(circPtr);
    BOOST_CHECK_THROW(compositeshape[2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    tseptsov::Rectangle rect1(3, 4, {5, 6});
    tseptsov::Rectangle rect2(7, 8, {9, 1});
    tseptsov::Circle circ(11, {12, 13});
    tseptsov::Rectangle rect3(4, 1, {6, 7});
    std::shared_ptr<tseptsov::Shape> rectPtr1 = std::make_shared<tseptsov::Rectangle>(rect1);
    std::shared_ptr<tseptsov::Shape> rectPtr2 = std::make_shared<tseptsov::Rectangle>(rect2);
    std::shared_ptr<tseptsov::Shape> circPtr = std::make_shared<tseptsov::Circle>(circ);
    std::shared_ptr<tseptsov::Shape> rectPtr3 = std::make_shared<tseptsov::Rectangle>(rect3);
    tseptsov::CompositeShape compositeshape(rectPtr1);
    compositeshape.add(rectPtr2);
    compositeshape.add(circPtr);
    compositeshape.add(rectPtr3);

    tseptsov::CompositeShape compositeshape1(compositeshape);
    compositeshape1.rotate(70);
    BOOST_CHECK_CLOSE(compositeshape.getArea(), compositeshape1.getArea(), EPS);
    for (int i = 0; i < 3; ++i) {
      BOOST_CHECK_CLOSE(compositeshape[i]->getArea(), compositeshape1[i]->getArea(), EPS);
    }

  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_Polygon)

  BOOST_AUTO_TEST_CASE(test_throw)
  {
    BOOST_CHECK_THROW(tseptsov::Polygon polygon({{0, 0}, {1, 1}}), std::range_error);
    BOOST_CHECK_THROW(tseptsov::Polygon polygon({{0, 0}, {0, 10}, {1, 1}, {5, 5}, {10, 0}}), std::invalid_argument);
    BOOST_CHECK_THROW(tseptsov::Polygon polygon({{0, 0}, {1, 0}, {2, 0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scaling_Test)
  {
    tseptsov::Polygon polygon({{0, 0}, {0, 10}, {4, 10}, {4, 0}});
    polygon.scale(2);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().pos.x, 2);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().pos.y, 5);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().width, 8);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().height, 20);
    BOOST_CHECK_EQUAL(polygon.getArea(), 160);
  }

  BOOST_AUTO_TEST_CASE(Moving_test)
  {
    tseptsov::Polygon polygon({{0, 0}, {0, 10}, {4, 10}, {10, 0}});
    polygon.move({-1, -2});
    BOOST_CHECK_EQUAL(polygon.getFrameRect().pos.x, 0.5);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().pos.y, -2);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().width, 10);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().height, 10);
    BOOST_CHECK_EQUAL(polygon.getArea(), 70);
    polygon.move(4, 5);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().pos.x, 4.5);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().pos.y, 3);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().width, 10);
    BOOST_CHECK_EQUAL(polygon.getFrameRect().height, 10);
    BOOST_CHECK_EQUAL(polygon.getArea(), 70);
  }

  BOOST_AUTO_TEST_CASE(Rotate_Test)
  {
    tseptsov::Polygon polygon({{0, 0}, {0, 10}, {4, 10}, {10, 0}});
    polygon.rotate(90);
    BOOST_CHECK_CLOSE(polygon.getFrameRect().width, 10, EPS);
    BOOST_CHECK_CLOSE(polygon.getFrameRect().height, 10, EPS);
    BOOST_CHECK_CLOSE(polygon.getFrameRect().pos.x, 3.5, EPS);
    BOOST_CHECK_CLOSE(polygon.getFrameRect().pos.y, 6.5, EPS);
    BOOST_CHECK_CLOSE(polygon.getArea(), 70, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTests)

  BOOST_AUTO_TEST_CASE(Constructor_Test1)
  {
    BOOST_CHECK_THROW(tseptsov::Matrix matrix(nullptr), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(Constructor_Test2)
  {
    tseptsov::Circle circle(10.0, {-10.0, 0.0});
    std::shared_ptr<tseptsov::Shape> circlePtr = std::make_shared<tseptsov::Circle>(circle);
    tseptsov::Matrix matrix(circlePtr);
    BOOST_CHECK_THROW(matrix[-1], std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MatrixCorrectnessTest)
  {
    tseptsov::Circle circle1 ( 10.0, {-10.0 , 0.0});
    tseptsov::Circle circle2 ( 20.0, {40.0 , 30.0});
    tseptsov::Rectangle rectangle1 ( 20.0, 40.0 ,{20.0, 30.0});
    tseptsov::Rectangle rectangle2 ( 20.0, 40.0 , {30.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circlePtrM1 = std::make_shared < tseptsov::Circle > (circle1);
    std::shared_ptr < tseptsov::Shape > circlePtrM2 = std::make_shared < tseptsov::Circle > (circle2);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM1 = std::make_shared < tseptsov::Rectangle > (rectangle1);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM2 = std::make_shared < tseptsov::Rectangle > (rectangle2);
    tseptsov::Matrix testmatrix(circlePtrM1);
    testmatrix.addShape(rectanglePtrM1);
    testmatrix.addShape(rectanglePtrM2);
    testmatrix.addShape(circlePtrM2);
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer0 = testmatrix[0];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer1 = testmatrix[1];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer2 = testmatrix[2];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_CHECK(layer1[1] == nullptr);
    BOOST_CHECK(layer2[0] == circlePtrM2);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getFrameRect().pos.x, -10.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getFrameRect().pos.x, 20.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, 30.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.x, 40.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getFrameRect().pos.y, 0.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getFrameRect().pos.y, 30.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, 0.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.y, 30.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getArea(), M_PI * 100, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getArea(), 800.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getArea(), 800.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getArea(), M_PI * 400, EPS);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    tseptsov::Circle circle ( 10.0, {-10.0 , 0.0});
    tseptsov::Rectangle rectangle1 ( 20.0, 40.0 ,{20.0, 30.0});
    tseptsov::Rectangle rectangle2 ( 20.0, 40.0 , {30.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circlePtrM1 = std::make_shared < tseptsov::Circle > (circle);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM1 = std::make_shared < tseptsov::Rectangle > (rectangle1);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM2 = std::make_shared < tseptsov::Rectangle > (rectangle2);
    tseptsov::Matrix testmatrix1(circlePtrM1);
    testmatrix1.addShape(rectanglePtrM1);
    testmatrix1.addShape(rectanglePtrM2);
    tseptsov::Matrix testmatrix2(testmatrix1);
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer0 = testmatrix2[0];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer1 = testmatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testmatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testmatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    tseptsov::Circle circle1 ( 10.0, {-10.0 , 0.0});
    tseptsov::Rectangle rectangle1 ( 20.0, 40.0 ,{20.0, 30.0});
    tseptsov::Rectangle rectangle2 ( 20.0, 40.0 , {30.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circlePtrM1 = std::make_shared < tseptsov::Circle > (circle1);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM1 = std::make_shared < tseptsov::Rectangle > (rectangle1);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM2 = std::make_shared < tseptsov::Rectangle > (rectangle2);
    tseptsov::Matrix testmatrix1(circlePtrM1);
    testmatrix1.addShape(rectanglePtrM1);
    testmatrix1.addShape(rectanglePtrM2);
    tseptsov::Matrix testmatrix2(std::move(testmatrix1));
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer0 = testmatrix2[0];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer1 = testmatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testmatrix1.getLayersNumber(), 0);
    BOOST_REQUIRE_EQUAL(testmatrix1.getLayerSize(), 0);
    BOOST_REQUIRE_EQUAL(testmatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testmatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(CopyOperatorTest)
  {
    tseptsov::Circle circle1 ( 10.0, {-10.0 , 0.0});
    tseptsov::Circle circle2 ( 20.0, {40.0 , 30.0});
    tseptsov::Rectangle rectangle1 ( 20.0, 40.0 ,{20.0, 30.0});
    tseptsov::Rectangle rectangle2 ( 20.0, 40.0 , {30.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circlePtrM1 = std::make_shared < tseptsov::Circle > (circle1);
    std::shared_ptr < tseptsov::Shape > circlePtrM2 = std::make_shared < tseptsov::Circle > (circle2);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM1 = std::make_shared < tseptsov::Rectangle > (rectangle1);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM2 = std::make_shared < tseptsov::Rectangle > (rectangle2);
    tseptsov::Matrix testmatrix1(circlePtrM1);
    testmatrix1.addShape(rectanglePtrM1);
    testmatrix1.addShape(rectanglePtrM2);
    tseptsov::Matrix testmatrix2(circlePtrM2);
    testmatrix2 = testmatrix1;
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer0 = testmatrix2[0];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer1 = testmatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testmatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testmatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    tseptsov::Circle circle1 ( 10.0, {-10.0 , 0.0});
    tseptsov::Circle circle2 ( 20.0, {40.0 , 30.0});
    tseptsov::Rectangle rectangle1 ( 20.0, 40.0 ,{20.0, 30.0});
    tseptsov::Rectangle rectangle2 ( 20.0, 40.0 , {30.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circlePtrM1 = std::make_shared < tseptsov::Circle > (circle1);
    std::shared_ptr < tseptsov::Shape > circlePtrM2 = std::make_shared < tseptsov::Circle > (circle2);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM1 = std::make_shared < tseptsov::Rectangle > (rectangle1);
    std::shared_ptr < tseptsov::Shape > rectanglePtrM2 = std::make_shared < tseptsov::Rectangle > (rectangle2);
    tseptsov::Matrix testmatrix1(circlePtrM1);
    testmatrix1.addShape(rectanglePtrM1);
    testmatrix1.addShape(rectanglePtrM2);
    tseptsov::Matrix testmatrix2(circlePtrM2);
    testmatrix2 = std::move(testmatrix1);
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer0 = testmatrix2[0];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer1 = testmatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testmatrix1.getLayersNumber(), 0);
    BOOST_REQUIRE_EQUAL(testmatrix1.getLayerSize(), 0);
    BOOST_REQUIRE_EQUAL(testmatrix2.getLayersNumber(), 2);
    BOOST_REQUIRE_EQUAL(testmatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(addCompositeShape)
  {
    tseptsov::Circle circle1(10.0, {-10.0, 0.0});
    tseptsov::Circle circle2(20.0, {40.0, 30.0});
    tseptsov::Circle circle3(30.0, {50.0, 40.0});
    tseptsov::Rectangle rectangle1(20.0, 40.0, {20.0, 30.0});
    tseptsov::Rectangle rectangle2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr<tseptsov::Shape> circlePtr1 = std::make_shared<tseptsov::Circle>(circle1);
    std::shared_ptr<tseptsov::Shape> circlePtr2 = std::make_shared<tseptsov::Circle>(circle2);
    std::shared_ptr<tseptsov::Shape> circlePtr3 = std::make_shared<tseptsov::Circle>(circle3);
    std::shared_ptr<tseptsov::Shape> rectanglePtr1 = std::make_shared<tseptsov::Rectangle>(rectangle1);
    std::shared_ptr<tseptsov::Shape> rectanglePtr2 = std::make_shared<tseptsov::Rectangle>(rectangle2);
    tseptsov::CompositeShape compositeshape(circlePtr2);
    compositeshape.add(circlePtr3);
    compositeshape.add(rectanglePtr1);
    compositeshape.add(rectanglePtr2);
    size_t size = compositeshape.getSize();
    std::shared_ptr<tseptsov::CompositeShape> array = std::make_shared<tseptsov::CompositeShape>(compositeshape);
    tseptsov::Matrix matrix(circlePtr1);
    matrix.addFromCShape(array, size);
    std::unique_ptr<std::shared_ptr<tseptsov::Shape>[]> layer0 = matrix[0];
    std::unique_ptr<std::shared_ptr<tseptsov::Shape>[]> layer1 = matrix[1];
    std::unique_ptr<std::shared_ptr<tseptsov::Shape>[]> layer2 = matrix[2];
    std::unique_ptr<std::shared_ptr<tseptsov::Shape>[]> layer3 = matrix[3];
    BOOST_CHECK(layer0[0] == circlePtr1);
    BOOST_CHECK(layer0[1] == circlePtr2);
    BOOST_CHECK(layer1[0] == circlePtr3);
    BOOST_CHECK(layer1[1] == nullptr);
    BOOST_CHECK(layer2[0] == rectanglePtr1);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK(layer3[0] == rectanglePtr2);
    BOOST_CHECK(layer3[1] == nullptr);
  }

BOOST_AUTO_TEST_SUITE_END()


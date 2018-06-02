#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace ponomarev;

const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rect({5.0, 5.0}, 5.0, 5.0);
    double heightBeforeChange = rect.getFrameRect().height;
    double widthBeforeChange = rect.getFrameRect().width;
    double areaBeforeChange = rect.getArea();
    rect.move({-3.0, 4.0});
    BOOST_CHECK(rect.getFrameRect().pos.x == -3.0 && rect.getFrameRect().pos.y == 4.0);
    BOOST_CHECK_CLOSE(areaBeforeChange, rect.getArea(), EPS);
    BOOST_CHECK_CLOSE(heightBeforeChange, rect.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, rect.getFrameRect().width, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(MoveAxis)
  {
    Rectangle rect({0.0, 0.0}, 4.0, 3.0);
    double heightBeforeChange = rect.getFrameRect().height;
    double widthBeforeChange = rect.getFrameRect().width;
    double areaBeforeChange = rect.getArea();
    rect.move(5.0, 6.0);
    BOOST_CHECK(rect.getFrameRect().pos.x == 5.0 && rect.getFrameRect().pos.y == 6.0);
    BOOST_CHECK_CLOSE(areaBeforeChange, rect.getArea(), EPS);
    BOOST_CHECK_CLOSE(heightBeforeChange, rect.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, rect.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Rectangle rect({0.0, 0.0}, 4.0, 2.0);
    BOOST_CHECK_THROW(rect.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Rect)
  {
    Rectangle rect({0.0, 0.0}, 4.0, 4.0);
    double areaBeforeChange = rect.getArea();
    rect.scale(4.0);
    BOOST_CHECK_CLOSE(4.0 * 4.0 * areaBeforeChange, rect.getArea(), EPS);
  }


BOOST_AUTO_TEST_SUITE_END()
 
BOOST_AUTO_TEST_SUITE(Circle_Tests)
  
  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle circle({1.0, 4.0}, 5.0);
    double heightBeforeChange = circle.getFrameRect().height;
    double widthBeforeChange = circle.getFrameRect().width;
    double areaBeforeChange = circle.getArea();
    circle.move({22.0, 12.2});
    BOOST_CHECK(circle.getFrameRect().pos.x == 22.0 && circle.getFrameRect().pos.y == 12.2);
    BOOST_CHECK_CLOSE(areaBeforeChange, circle.getArea(), EPS);
    BOOST_CHECK_CLOSE(heightBeforeChange, circle.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, circle.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveAxis)
  {
    Circle circle({0.0, 0.0}, 4.0);
    double heightBeforeChange = circle.getFrameRect().height;
    double widthBeforeChange = circle.getFrameRect().width;
    double areaBeforeChange = circle.getArea();
    circle.move(5.0, 6.0);
    BOOST_CHECK(circle.getFrameRect().pos.x == 5.0 && circle.getFrameRect().pos.y == 6.0);
    BOOST_CHECK_CLOSE(areaBeforeChange, circle.getArea(), EPS);
    BOOST_CHECK_CLOSE(heightBeforeChange, circle.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, circle.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Circle circle({0.0, 0.0}, 4.0);
    BOOST_CHECK_THROW(circle.scale(-13.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Rect)
  {
    Circle circle({0.0, 0.0}, 4.0);
    double areaBeforeChange = circle.getArea();
    circle.scale(4.0);
    BOOST_CHECK_CLOSE(4.0 * 4.0 * areaBeforeChange, circle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Initialization)
  {
    BOOST_CHECK_THROW(Rectangle({0.0, 0.0}, 10.0, -10.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({0.0, 0.0}, -10.0, 10.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({0.0, 0.0}, -10.0, -10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Composite_Shape_Tests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 2.0, 3.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double heightBeforeChange = compositeShape.getFrameRect().height;
    double widthBeforeChange = compositeShape.getFrameRect().width;
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.move({3.0, 2.0});
    BOOST_CHECK(compositeShape.getFrameRect().pos.x == 3.0 && compositeShape.getFrameRect().pos.y == 2.0);
    BOOST_CHECK_CLOSE(heightBeforeChange, compositeShape.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, compositeShape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveAxis)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 2.0, 3.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double heightBeforeChange = compositeShape.getFrameRect().height;
    double widthBeforeChange = compositeShape.getFrameRect().width;
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.move(3.0, 2.0);
    BOOST_CHECK_CLOSE(heightBeforeChange, compositeShape.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, compositeShape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 2.0, 3.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    BOOST_CHECK_THROW(compositeShape.scale(-2.9), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_CompositeShape)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 2.0, 3.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.scale(3.0);
    BOOST_CHECK_CLOSE(3.0 * 3.0 * areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(Check_Add)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 2.0, 3.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    BOOST_CHECK_EQUAL(compositeShape.getQuantity(), 2);
  }

  BOOST_AUTO_TEST_CASE(Check_Remove)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 2.0, 3.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    compositeShape.removeShape(1);
    BOOST_CHECK_EQUAL(compositeShape.getQuantity(), 1);
  }

 BOOST_AUTO_TEST_CASE(Add_nullptr)
  {
    std::shared_ptr<Shape> circle = nullptr;
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    CompositeShape compositeShape;
    compositeShape.addShape(circle1);
    BOOST_CHECK_THROW(compositeShape.addShape(circle), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Out_of_range_error)
  {
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(Circle({0, 0}, 10));
    CompositeShape compositeShape;
    compositeShape.addShape(circle);
    BOOST_CHECK_THROW(compositeShape[2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Empty_Shape_)
  {
    CompositeShape compositeShape;
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().width, 0);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().height, 0);
  }

  BOOST_AUTO_TEST_CASE(Constructor_Copy)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 2.0, 3.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({10.0, 0.0}, 1.0));
    std::shared_ptr<Shape> circle2(circle1);

    BOOST_CHECK_EQUAL(circle1->getFrameRect().pos.x, circle2->getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(circle1->getFrameRect().pos.y, circle2->getFrameRect().pos.y);
    BOOST_CHECK_EQUAL(circle1->getArea(), circle2->getArea());
  }

  BOOST_AUTO_TEST_CASE(Assignment_operator)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 2.0, 3.0));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({10.0, 0.0}, 1.0));
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle({23.1, 22.0}, 9.0));
    circle2 = circle1;

    BOOST_CHECK_EQUAL(circle2->getFrameRect().pos.x, circle1->getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(circle2->getFrameRect().pos.y, circle1->getFrameRect().pos.y);
    BOOST_CHECK_EQUAL(circle2->getArea(), circle1->getArea());
  }

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"
#include <stdexcept>
#include "composite-shape.hpp"

const double ACCURACY = 1E-5;
const double FACTOR_POS = 2.0;
const double FACTOR_NEG = -3.5;
const double EPS = 0.00001;
using namespace koryakin;

BOOST_AUTO_TEST_SUITE(TestRectangle)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    point_t pnt = { 14.0, 19.0 };
    Rectangle rect = Rectangle(pnt, 3.0, 5.0);
    rectangle_t frame = rect.getFrameRect();
    double area = rect.getArea();
    //Move to point
    rect.move({ 60.8, 71.0 });
    //Check
    BOOST_CHECK_EQUAL(frame.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(frame.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(area, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(RelativeMove) 
  {
    point_t pnt = { 14.0, 19.0 };
    Rectangle rect = Rectangle(pnt, 3.0, 5.0);
    rectangle_t frame = rect.getFrameRect();
    double area = rect.getArea();
    //Relative move
    rect.move(30.1, -5.2);
    //Check
    BOOST_CHECK_EQUAL(frame.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(frame.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(area, rect.getArea());
  }
  
  BOOST_AUTO_TEST_CASE(Scale)
    {
      point_t pnt = { 14.0, 19.0 };
      Rectangle rect = Rectangle(pnt, 3.0, 5.0);
      double area = rect.getArea();
      //Scale
      rect.scale(FACTOR_POS);
      //Check
      BOOST_CHECK_CLOSE(area * FACTOR_POS * FACTOR_POS, rect.getArea(), ACCURACY);
    }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
      point_t pnt = { 14.0, 19.0 };
      BOOST_CHECK_THROW(Rectangle({ 14.0, 19.0 }, -3.0, 5.0), std::invalid_argument);
      BOOST_CHECK_THROW(Rectangle({ 14.0, 19.0 },  3.0,-5.0), std::invalid_argument);
      BOOST_CHECK_THROW(Rectangle({ 14.0, 19.0 }, -3.0, -5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingFactor)
  {
    point_t pnt = { 14.0, 19.0 };
    Rectangle rect = Rectangle(pnt, 3.0, 5.0);
    BOOST_CHECK_THROW(rect.scale(FACTOR_NEG), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)
  
  BOOST_AUTO_TEST_CASE(MoveToPoint) 
  {
    point_t pnt = { 40.0, 90.0 };
    Circle circle = Circle(pnt, 20.0);
    rectangle_t frame = circle.getFrameRect();
    double area = circle.getArea();
    //Move to point
    circle.move({ -92.2, 68.0 });
    //Check
    BOOST_CHECK_EQUAL(frame.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(frame.height, circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(area, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(RelativeMove) 
  {
    point_t pnt = { 40.0, 90.0 };
    Circle circle = Circle(pnt, 20.0); 
    rectangle_t frame = circle.getFrameRect();
    double area = circle.getArea();
    //Move to point
    circle.move(-64.3, 15.2);
    //Check
    BOOST_CHECK_EQUAL(frame.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(frame.height, circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(area, circle.getArea());
  }
  
  BOOST_AUTO_TEST_CASE(Scale)
  {
    point_t pnt = { 40.0, 90.0 };
    Circle circle = Circle(pnt, 20.0);
    double area = circle.getArea();
    //Scale
    circle.scale(FACTOR_POS);
    //Check
    BOOST_CHECK_CLOSE(area * FACTOR_POS * FACTOR_POS, circle.getArea(), ACCURACY);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    BOOST_CHECK_THROW(Circle({ 40.0, 90.0 }, -90), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingFactor)
  {
    point_t pnt = { 40.0, 90.0 };
    Circle circle = Circle(pnt, 20.0);

    BOOST_CHECK_THROW(circle.scale(FACTOR_NEG), std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(CompositeShape_Test)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    cs.move({15, 10});
    BOOST_CHECK_CLOSE(cs.getFrameRect().pos.x, 15, EPS); 
    BOOST_CHECK_CLOSE(cs.getFrameRect().pos.y, 10, EPS);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    cs.move(-1, 1);
    BOOST_CHECK_CLOSE(cs.getFrameRect().pos.x, 1.5, EPS);
    BOOST_CHECK_CLOSE(cs.getFrameRect().pos.y, 3.5, EPS);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Area_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    BOOST_REQUIRE_EQUAL(cs.getArea(), 3);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Move_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    cs.move(5, 5);
    BOOST_REQUIRE_EQUAL(cs.getArea(), 3);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Count_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    BOOST_REQUIRE_EQUAL(cs.getCount(), 3);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 2.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 2.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 3, EPS);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Scale_Area_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    cs.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(cs.getArea(), 48, EPS);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Scale_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    cs.scale(2);

    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 2.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 2.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 3*2, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 3*2, EPS);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Remove_Element_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    cs.removeShape(0);
    BOOST_REQUIRE_EQUAL(cs.getCount(), 2);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 2, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 2, EPS);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Get_Element_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    Shape * shape = cs[0];
    BOOST_REQUIRE_EQUAL(shape->getFrameRect().pos.x, 1.5);
    BOOST_REQUIRE_EQUAL(shape->getFrameRect().pos.y, 1.5);
    BOOST_REQUIRE_EQUAL(shape->getFrameRect().width, 1);
    BOOST_REQUIRE_EQUAL(shape->getFrameRect().height, 1);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Equal_Test_CS)
  {
    Rectangle rect1({1.5, 1.5}, 1, 1);
    Rectangle rect2({2.5, 2.5}, 1, 1);
    Rectangle rect3({3.5, 3.5}, 1, 1);
    CompositeShape cs(&rect1);
    cs.addShape(&rect2);
    cs.addShape(&rect3);
    CompositeShape shape(&rect1);
    shape = cs;
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, 2.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, 2.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 3, EPS);
    cs.clear();
    shape.clear();
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_CS)
  {
    Circle circ({0, 0}, 10);
    CompositeShape cs(&circ);
    BOOST_CHECK_THROW(cs.scale(-1), std::invalid_argument);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_RemoveShape_Test_CS)
  {
    Circle circ({0, 0}, 10);
    CompositeShape cs(&circ);
    BOOST_CHECK_THROW(cs.removeShape(2), std::out_of_range);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Clear_Test_CS)
  {
    Circle circ1({0, 0}, 10);
    Circle circ2({10, 10}, 20);
    Circle circ3({20, 20}, 30);
    CompositeShape cs(&circ1);
    cs.addShape(&circ2);
    cs.addShape(&circ3);
    cs.clear();

    BOOST_REQUIRE_EQUAL(cs.getCount(), 0);
  }

  BOOST_AUTO_TEST_CASE(Out_Of_Range_Error_Get_Element_Test_CS)
  {
    Circle circ({0, 0}, 10);
    CompositeShape cs(&circ);
    BOOST_CHECK_THROW(cs[2], std::out_of_range);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Add_Nullptr_Invalid_Argument_Error_Test_CS)
  {
    Circle circ({0, 0}, 10);
    CompositeShape cs(&circ);
    BOOST_CHECK_THROW(cs.addShape(nullptr), std::invalid_argument);
    cs.clear();
  }

BOOST_AUTO_TEST_SUITE_END() // koryakin 13534/6

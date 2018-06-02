#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

using namespace korichev;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double h_before = test_rect.getFrameRect().height;
    double w_before = test_rect.getFrameRect().width;
    double a_before = test_rect.getArea();
    test_rect.move({2.0, 3.0});
    BOOST_CHECK_EQUAL(test_rect.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(test_rect.getFrameRect().pos.y, 3.0);
    BOOST_CHECK_EQUAL(a_before, test_rect.getArea());
    BOOST_CHECK_EQUAL(h_before, test_rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_rect.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(MoveByXY)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double h_before = test_rect.getFrameRect().height;
    double w_before = test_rect.getFrameRect().width;
    double a_before = test_rect.getArea();
    test_rect.move(2.0, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(test_rect.getFrameRect().pos.x, 5.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test_rect.getFrameRect().pos.y, 5.0, EPSILON);
    BOOST_CHECK_EQUAL(a_before, test_rect.getArea());
    BOOST_CHECK_EQUAL(h_before, test_rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_rect.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    BOOST_CHECK_THROW(test_rect.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double a_before = test_rect.getArea();
    test_rect.scale(3.0);
    BOOST_CHECK_CLOSE_FRACTION(3.0 * 3.0 * a_before, test_rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidInit)
  {
    BOOST_CHECK_THROW(Rectangle({3.0, 2.0}, 10.0, -10.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({3.0, 2.0}, -10.0, 10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double h_before = test_circle.getFrameRect().height;
    double w_before = test_circle.getFrameRect().width;
    double a_before = test_circle.getArea();
    test_circle.move({2.0, 3.0});
    BOOST_CHECK_EQUAL(test_circle.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(test_circle.getFrameRect().pos.y, 3.0);
    BOOST_CHECK_EQUAL(a_before, test_circle.getArea());
    BOOST_CHECK_EQUAL(h_before, test_circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_circle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(MoveByXY)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double h_before = test_circle.getFrameRect().height;
    double w_before = test_circle.getFrameRect().width;
    double a_before = test_circle.getArea();
    test_circle.move(2.0, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(test_circle.getFrameRect().pos.x, 5.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test_circle.getFrameRect().pos.y, 5.0, EPSILON);
    BOOST_CHECK_EQUAL(a_before, test_circle.getArea());
    BOOST_CHECK_EQUAL(h_before, test_circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_circle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    BOOST_CHECK_THROW(test_circle.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double a_before = test_circle.getArea();
    test_circle.scale(3.0);
    BOOST_CHECK_CLOSE_FRACTION(3.0 * 3.0 * a_before, test_circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidInit)
  {
    BOOST_CHECK_THROW(Circle({3.0, 2.0}, -10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.move({10, 5});
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 10, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 5, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(MoveByXY)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.move(-2, 3);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 1.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 6.0, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(AreaTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    BOOST_CHECK_EQUAL(cs.getArea(), 3);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(AreaTestMoveByXY)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.move(5, 5);
    BOOST_CHECK_EQUAL(cs.getArea(), 3);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(CheckListSize)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    BOOST_CHECK_EQUAL(cs.getListSize(), 3);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(FrameRectTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 3.0, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(ScaleAreaTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(cs.getArea(), 48, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(FrameRectScaleTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.scale(2);

    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 8.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 8.0, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(RemoveElementTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.dispose(0);
    BOOST_REQUIRE_EQUAL(cs.getListSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 3.5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 3.5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 2, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(OperatorTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    CompositeShape shape;
    shape = cs;
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, 3, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, 3, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 3, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 3, EPSILON);
    cs.clean();
    shape.clean();
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    BOOST_CHECK_THROW(cs.scale(-1), std::invalid_argument);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(InvalidRemoveTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    BOOST_CHECK_THROW(cs.dispose(2), std::invalid_argument);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(CleanTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.clean();

    BOOST_CHECK_EQUAL(cs.getListSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(Add_Nullptr_Invalid_Argument_Error_Test_CS)
  {
    CompositeShape cs;
    BOOST_CHECK_THROW(cs.add(nullptr), std::invalid_argument);
    cs.clean();
  }

BOOST_AUTO_TEST_SUITE_END()

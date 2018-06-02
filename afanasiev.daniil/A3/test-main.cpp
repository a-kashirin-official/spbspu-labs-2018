#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPS = 0.00001;

using namespace afanasiev;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_Rect)
  {
    Rectangle rect(10.9, 5.5, { 11.1, 15.6 } );
    rect.move( { 53.3, 20.4 } );
    BOOST_CHECK((rect.getPos().x == 53.3) && (rect.getPos().y == 20.4));
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_Rect)
  {
    Rectangle rect(10.9, 5.5, { 11.1, 15.6 } );
    rect.move(-10.1, 0.4);
    BOOST_CHECK_CLOSE_FRACTION(rect.getPos().x, 1.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(rect.getPos().y, 16.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Rect)
  {
    Rectangle rect(5, 5, { 11.1, 15.6 } );
    BOOST_REQUIRE_EQUAL(rect.getArea(), 25);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_With_Move_Rect)
  {
    Rectangle rect(5, 5, { 11.1, 15.6 } );
    rect.move(10, 5);
    BOOST_REQUIRE_EQUAL(rect.getArea(), 25);
  }

  BOOST_AUTO_TEST_CASE(Height_Test_Rect)
  {
    Rectangle rect(5, 5, { 11.1, 15.6 } );
    rect.move(10, 0);
    BOOST_REQUIRE_EQUAL(rect.getHeight(), 5);
  }

  BOOST_AUTO_TEST_CASE(Widht_Test_Rect)
  {
    Rectangle rect(5, 5, { 11.1, 15.6 } );
    rect.move(10, 0);
    BOOST_REQUIRE_EQUAL(rect.getWidth(), 5);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Rect)
  {
    Rectangle rect(5, 5, { 11.1, 15.6 } );
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().width, 5);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().height, 5);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.x, 11.1);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.y, 15.6);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Rect)
  {
    Rectangle rect(5, 5, { 0, 0 } );
    rect.scale(10);
    BOOST_REQUIRE_EQUAL(rect.getArea(), 25 * 100);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Rect)
  {
    BOOST_CHECK_THROW(Rectangle(-1, -1, { 0, 0 } ), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Rect)
  {
    Rectangle rect(5, 5, { 0, 0 } );
    BOOST_CHECK_THROW(rect.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_Circle)
  {
    Circle circ( { 10, 0 }, 10);
    circ.move( { 15, 20} );
    BOOST_CHECK(circ.getPos().x == 15 && circ.getPos().y == 20);
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_Circle)
  {
    Circle circ( { 10, 0 }, 10);
    circ.move(-5, 8);
    BOOST_CHECK_CLOSE_FRACTION(circ.getPos().x, 5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(circ.getPos().y, 8, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Circle)
  {
    Circle circ( { 10, 0 }, 10);
    BOOST_REQUIRE_EQUAL(circ.getArea(), 100 * M_PI);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_With_Move_Circle)
  {
    Circle circ( { 10, 0 }, 10);
    circ.move(10, 5);
    BOOST_REQUIRE_EQUAL(circ.getArea(), 100 * M_PI);
  }

  BOOST_AUTO_TEST_CASE(Radius_Test_Circle)
  {
    Circle circ( { 10, 0 }, 10);
    circ.move(0, 10);
    BOOST_REQUIRE_EQUAL(circ.getRadius(), 10);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Circle)
  {
    Circle circ( { 10, 0 }, 10);
    circ.scale(2);
    BOOST_REQUIRE_EQUAL(circ.getArea(), 100 * M_PI * 4);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Circle)
  {
    Circle circ( { 3, 0 }, 15);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().width, 30);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().height, 30);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().pos.x, 3);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().pos.y, 0);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Circle)
  {
    BOOST_CHECK_THROW(Circle( { 0, 0 }, -1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Circle)
  {
    Circle circ( { 0, 0 }, 10);
    BOOST_CHECK_THROW(circ.scale(-1), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(Area_Test_Move_CS)
  {
    Circle circle({ 15.32, 1.23 }, 4.3 );
    Rectangle rectangle(7.0, 10.79, { 19.64, 8.35 });
    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(circle);
    std::shared_ptr<Shape> rectanglePtr = std::make_shared<Rectangle>(rectangle);
    CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.move( 1.37, 22.7 );
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), circle.getArea() + rectangle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(Scale_Area_Test_CS)
  {
    Circle circle({ 15.32, 1.23 }, 4.3 );
    Rectangle rectangle(7.0, 10.79, { 19.64, 8.35 });
    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(circle);
    std::shared_ptr<Shape> rectanglePtr = std::make_shared<Rectangle>(rectangle);
    CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), (circle.getArea() + rectangle.getArea()) * 2.0 * 2.0,
      EPS);
  }

  BOOST_AUTO_TEST_CASE(Remove_Element_Test_CS)
  {
    Circle circle({ 15.32, 1.23 }, 4.3 );
    Rectangle rectangle(7.0, 10.79, { 19.64, 8.35 });
    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(circle);
    std::shared_ptr<Shape> rectanglePtr = std::make_shared<Rectangle>(rectangle);
    CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.removeShape(1);
    BOOST_REQUIRE_EQUAL(compositeShape.getPos().x, circle.getPos().x);
    BOOST_REQUIRE_EQUAL(compositeShape.getPos().y, circle.getPos().y);
    BOOST_REQUIRE_EQUAL(compositeShape.getArea(), circle.getArea());
    BOOST_REQUIRE_EQUAL(compositeShape.getCount(), 1);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Scale_Test_CS)
  {
    Circle circle({ 15.32, 1.23 }, 4.3 );
    Rectangle rectangle(7.0, 10.79, { 19.64, 8.35 });
    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(circle);
    std::shared_ptr<Shape> rectanglePtr = std::make_shared<Rectangle>(rectangle);
    CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    rectangle_t frameRect = compositeShape.getFrameRect();
    compositeShape.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getPos().x, frameRect.pos.x, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getPos().y, frameRect.pos.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(Clear_Test_CS)
  {
    Circle circle({ 15.32, 1.23 }, 4.3 );
    Rectangle rectangle(7.0, 10.79, { 19.64, 8.35 });
    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(circle);
    std::shared_ptr<Shape> rectanglePtr = std::make_shared<Rectangle>(rectangle);
    CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    compositeShape.clear();
    BOOST_REQUIRE_EQUAL(compositeShape.getCount(), 0);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_CS)
  {
    Circle circle( { 15.32, 1.23 }, 4.3 );
    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(circle);
    CompositeShape compositeShape(circlePtr);
    BOOST_CHECK_THROW(compositeShape.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_RemoveShape_Test_CS)
  {
    Circle circle( { 15.32, 1.23 }, 4.3 );
    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(circle);
    CompositeShape compositeShape(circlePtr);
    BOOST_CHECK_THROW(compositeShape.removeShape(2), std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()


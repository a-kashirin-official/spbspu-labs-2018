#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <memory>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double DELTA = 0.001;

using namespace krasilnikov;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test)
  {
  Rectangle rect(11.9, 11.8, {17, 18} );
  rect.move({13.1, -2.1});
  BOOST_REQUIRE_EQUAL(rect.getPosition().x, 13.1);
  BOOST_REQUIRE_EQUAL(rect.getPosition().y, -2.1);
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Rectangle)
  {
    Rectangle rect(11.9, 11.8, {17.1, 18.2} );
    rect.move(-16.1, -0.2);
    BOOST_CHECK_CLOSE_FRACTION(rect.getPosition().x, 1.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(rect.getPosition().y, 18.0, DELTA);
  }

  BOOST_AUTO_TEST_CASE(Area_Rectangle)
  {
    Rectangle rect(7, 7, {12.4, 13.2});
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), 49, DELTA);
  }

  BOOST_AUTO_TEST_CASE(Area_Move_Rectangle)
  {
    Rectangle rect(7, 7, {12.4, 13.2});
    rect.move(13, 7);
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), 49, DELTA);
  }

  BOOST_AUTO_TEST_CASE(Height_Rectangle)
  {
    Rectangle rect(7, 7, {12.4, 13.2});
    rect.move(13, 0);
    BOOST_REQUIRE_EQUAL(rect.getHeight(), 7);
  }

  BOOST_AUTO_TEST_CASE(Width_Rectangle)
  {
    Rectangle rect(7, 7, {12.4, 13.2});
    rect.move(13, 0);
    BOOST_REQUIRE_EQUAL(rect.getWidth(), 7);
  }

  BOOST_AUTO_TEST_CASE(FrameRect_Rectangle)
  {
    Rectangle rect(7, 7, {12.4, 13.2});
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().height, 7);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().width, 7);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.x, 12.4);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.y, 13.2);
  }

  BOOST_AUTO_TEST_CASE(Scale_Rectangle)
  {
    Rectangle rect(7, 7, {0, 0});
    rect.scale(5);
    BOOST_REQUIRE_EQUAL(rect.getArea(), 49 * 25);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Constructor_Rectangle)
  {
    BOOST_CHECK_THROW(Rectangle(-1, 1, {0, 0}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle(1, -1, {0, 0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Rectangle)
  {
    Rectangle rect(7, 7, {0, 0});
    BOOST_CHECK_THROW(rect.scale(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_SUITE_END()

  BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Circle)
  {
    Circle circ( {13, 7}, 10);
    circ.move( {7, 13});
    BOOST_REQUIRE_EQUAL(circ.getPosition().x, 7);
    BOOST_REQUIRE_EQUAL(circ.getPosition().y, 13);
  }

  BOOST_AUTO_TEST_CASE(Realtive_Move_Circle)
  {
    Circle circ( {13, 7}, 10);
    circ.move(7, 13);
    BOOST_CHECK_CLOSE_FRACTION(circ.getPosition().x, 20, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(circ.getPosition().y, 20, DELTA);
  }

  BOOST_AUTO_TEST_CASE(Area_Circle)
  {
    Circle circ( {13, 7}, 10);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 100 * M_PI, DELTA);
  }

  BOOST_AUTO_TEST_CASE(Area_Move_Circle)
  {
    Circle circ( {13, 7}, 10);
    circ.move(7, 13);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 100 * M_PI, DELTA);
  }

  BOOST_AUTO_TEST_CASE(Radius_Circle)
  {
    Circle circ( {13, 7}, 10);
    circ.move(7, 13);
    BOOST_REQUIRE_EQUAL(circ.getRadius(), 10);
  }

  BOOST_AUTO_TEST_CASE(Scale_Circle)
  {
    Circle circ( {13, 7}, 10);
    circ.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 100 * M_PI * 25, DELTA);
  }

  BOOST_AUTO_TEST_CASE(FrameRect_Circle)
  {
    Circle circ( {13, 7}, 10);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().height, 20);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().width, 20);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().pos.x, 13);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().pos.y, 7);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Constructor_Circle)
  {
    BOOST_CHECK_THROW(Circle( {0, 0}, -1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Circle)
  {
    Circle circ( {0, 0}, 10);
    BOOST_CHECK_THROW(circ.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_Tests)

  BOOST_AUTO_TEST_CASE(Absolute_Move_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    cs.move({13, 13});
    BOOST_CHECK_CLOSE(cs.getPosition().x, 13, DELTA);
    BOOST_CHECK_CLOSE(cs.getPosition().y, 13, DELTA);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    cs.move(1, -1);
    BOOST_CHECK_CLOSE(cs.getPosition().x, 5, DELTA);
    BOOST_CHECK_CLOSE(cs.getPosition().y, 3, DELTA);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Area_Move_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    cs.move(13, 13);
    BOOST_REQUIRE_EQUAL(cs.getArea(), 3);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Count_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    BOOST_REQUIRE_EQUAL(cs.getCount(), 3);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(FrameRect_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 4.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 4.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 5.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 5.0, DELTA);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Scale_Area_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    cs.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(cs.getArea(), 12, DELTA);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(FrameRect_Scale_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    cs.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 4.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 4.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 5*2, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 5*2, DELTA);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Remove_Element_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    cs.removeShape(0);
    BOOST_REQUIRE_EQUAL(cs.getCount(), 2);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 5.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 5.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 3.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 3.0, DELTA);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Get_Element_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    std::shared_ptr< Shape > shape = cs[0];
    BOOST_REQUIRE_EQUAL(shape->getPosition().x, 2.0);
    BOOST_REQUIRE_EQUAL(shape->getPosition().y, 2.0);
    BOOST_REQUIRE_EQUAL(shape->getFrameRect().height, 1);
    BOOST_REQUIRE_EQUAL(shape->getFrameRect().width, 1);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Equal_CS)
  {
    Rectangle rect1(1, 1, {2.0, 2.0});
    Rectangle rect2(1, 1, {4.0, 4.0});
    Rectangle rect3(1, 1, {6.0, 6.0});
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rectPtr2 = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > rectPtr3 = std::make_shared< Rectangle >(rect3);
    CompositeShape cs(rectPtr1);
    cs.addShape(rectPtr2);
    cs.addShape(rectPtr3);
    CompositeShape shape(rectPtr1);
    shape = cs;
    BOOST_CHECK_CLOSE_FRACTION(shape.getPosition().x, 4.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(shape.getPosition().y, 4.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 5.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 5.0, DELTA);
    cs.clear();
    shape.clear();
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_CS)
  {
    Circle circ({7, 7}, 13);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    CompositeShape cs(circPtr);
    BOOST_CHECK_THROW(cs.removeShape(2), std::out_of_range);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Clear_CS)
  {
    Circle circ1({0, 0}, 3);
    Circle circ2({3, 3}, 5);
    Circle circ3({7, 7}, 13);
    std::shared_ptr< Shape > circPtr1 = std::make_shared< Circle >(circ1);
    std::shared_ptr< Shape > circPtr2 = std::make_shared< Circle >(circ2);
    std::shared_ptr< Shape > circPtr3 = std::make_shared< Circle >(circ3);
    CompositeShape cs(circPtr1);
    cs.addShape(circPtr2);
    cs.addShape(circPtr3);
    cs.clear();
    BOOST_REQUIRE_EQUAL(cs.getCount(), 0);
  }

  BOOST_AUTO_TEST_CASE(Out_Of_Range_CS)
  {
    Circle circ({7, 7}, 13);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    CompositeShape cs(circPtr);
    BOOST_CHECK_THROW(cs[2], std::out_of_range);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_CS)
  {
    Circle circ({7, 7}, 13);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    CompositeShape cs(circPtr);
    BOOST_CHECK_THROW(cs.addShape(nullptr), std::invalid_argument);
    cs.clear();
  }

BOOST_AUTO_TEST_SUITE_END()

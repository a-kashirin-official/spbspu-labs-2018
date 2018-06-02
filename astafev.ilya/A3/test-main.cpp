#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPS = 0.00001;

using namespace astafev;

BOOST_AUTO_TEST_SUITE(CompositeShape_Test)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    cs.move({7, -3});
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 7, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, -3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getArea(), 15,EPS);
    BOOST_REQUIRE_EQUAL(cs.getSize(), 3);
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    cs.move(-1, 1);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 0.25, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 2, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getArea(), 15,EPS);
    BOOST_REQUIRE_EQUAL(cs.getSize(), 3);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 1.25, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 9.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 9, EPS);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    cs.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(cs.getArea(), 240, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 1.25, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 9.5*4, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 9*4, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs[0]->getFrameRect().pos.x, 0.25, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs[0]->getFrameRect().pos.y, 1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs[1]->getFrameRect().pos.x, 12.25, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs[1]->getFrameRect().pos.y, 13, EPS);
  }

  BOOST_AUTO_TEST_CASE(Remove_Element_Test_CS_1)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    cs.deleteElement(0);
    BOOST_REQUIRE_EQUAL(cs.getSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 1.25, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 9.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 9, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(Remove_Element_Test_CS_2)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    cs.deleteElement(1);
    BOOST_REQUIRE_EQUAL(cs.getSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, -0.75, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, -1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 5.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 5, EPS);
  }

  BOOST_AUTO_TEST_CASE(Copy_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    CompositeShape shape(cs);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, shape.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, shape.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, shape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, shape.getFrameRect().height, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(Move_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    CompositeShape shape(std::move(cs));
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, 1.25, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, 1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 9.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 9, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(Operator_Move_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    CompositeShape shape(rect1);
    shape=std::move(cs);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, 1.25, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, 1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 9.5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 9, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(Operator_Copy_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    CompositeShape shape(rect1);
    shape=cs;
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, shape.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, shape.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, shape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, shape.getFrameRect().height, EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_CS)
  {
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle({130, 130}, 30));
    CompositeShape cs(circ);
    BOOST_CHECK_THROW(cs.scale(-1), std::invalid_argument);
    cs.clear();
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_deleteElement_Test_CS)
  {
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle({130, 130}, 30));
    CompositeShape cs(circ);
    BOOST_CHECK_THROW(cs.deleteElement(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Clear_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));
    CompositeShape cs(rect1);
    cs.addElement(rect2);
    cs.addElement(rect3);
    cs.clear();
    BOOST_REQUIRE_EQUAL(cs.getSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(Out_Of_Range_Error_Get_Element_Test_CS)
  {
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle({130, 130}, 30));
    CompositeShape cs(circ);
    BOOST_CHECK_THROW(cs[2], std::out_of_range);
    cs.clear();
  }
  
BOOST_AUTO_TEST_SUITE_END()


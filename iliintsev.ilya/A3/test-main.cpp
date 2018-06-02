#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPSILON = 1e-5;

using namespace iliintsev;

BOOST_AUTO_TEST_SUITE(CompositeShape_Test)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 2, 2));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    testComp.move({15, -7});
    BOOST_CHECK_CLOSE_FRACTION(testComp.getCenter().x, 15, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getCenter().y, -7, EPSILON);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    testComp.move(-1, 1);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getCenter().x, 0.25, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getCenter().y, 2, EPSILON);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Move_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    double areaBefore = testComp.getArea();

    testComp.move(5, 5);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getArea(), areaBefore , EPSILON);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(Count_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    BOOST_REQUIRE_EQUAL(testComp.getSize(), 3);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().pos.x, 1.25, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().pos.y, 1, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().width, 9.5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().height, 9, EPSILON);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(Scale_Area_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    testComp.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getArea(), 240, EPSILON);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Scale_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    testComp.scale(2);

    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().pos.x, 1.25, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().pos.y, 1, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().width, 9.5*2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().height, 9*2, EPSILON);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(clear_Element_Test_CS_1)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    testComp.remove(0);

    BOOST_REQUIRE_EQUAL(testComp.getSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().pos.x, 1.25, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().pos.y, 1, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().width, 9.5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().height, 9, EPSILON);
    testComp.clear();
  }
  
  BOOST_AUTO_TEST_CASE(clear_Element_Test_CS_2)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    testComp.remove(1);

    BOOST_REQUIRE_EQUAL(testComp.getSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().pos.x, -0.75, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().pos.y, -1, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().width, 5.5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testComp.getFrameRect().height, 5, EPSILON);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(Equal_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    CompositeShape shape = testComp;
    BOOST_CHECK_CLOSE_FRACTION(shape.getCenter().x, 1.25, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getCenter().y, 1, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 9.5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 9, EPSILON);
    testComp.clear();
    shape.clear();
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_CS)
  {
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle({130, 130}, 30));
    CompositeShape testComp(circ);
    BOOST_CHECK_THROW(testComp.scale(-1), std::invalid_argument);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_remove_Test_CS)
  {
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle({130, 130}, 30));
    CompositeShape testComp(circ);
    BOOST_CHECK_THROW(testComp.remove(2), std::invalid_argument);
    testComp.clear();
  }

  BOOST_AUTO_TEST_CASE(clear_Test_CS)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({4, 4}, 4, 3));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({-3, -3}, 1, 1));

    CompositeShape testComp(rect1);
    testComp.add(rect2);
    testComp.add(rect3);
    testComp.clear();

    BOOST_REQUIRE_EQUAL(testComp.getSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(Out_Of_Range_Error_Get_Element_Test_CS)
  {
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle({130, 130}, 30));
    CompositeShape testComp(circ);
    BOOST_CHECK_THROW(testComp[2], std::invalid_argument);
    testComp.clear();
  }


BOOST_AUTO_TEST_SUITE_END()


#define BOOST_TEST_MAIN

#include <stdexcept>
#include <math.h>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double Epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(CompositeShapeSuite)
  
  BOOST_AUTO_TEST_CASE(CopyCosntructor)
  {
    kudryakov::Rectangle rectangle({-2,0}, 2, 2);
    kudryakov::Circle circle({2,0}, 1);
    kudryakov::CompositeShape cs(&rectangle);
    cs.addShape(&circle);
    
    kudryakov::CompositeShape cs2(cs);
    BOOST_CHECK_CLOSE(cs2.getArea(), cs.getArea(), Epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(CopyOperator)
  {
    kudryakov::Rectangle rectangle({-2,0}, 2, 2);
    kudryakov::Circle circle({2,0}, 1);
    kudryakov::CompositeShape cs(&rectangle);
    cs.addShape(&circle);
    
    kudryakov::CompositeShape cs2;
    cs2 = cs;
    BOOST_CHECK_CLOSE(cs2.getArea(), cs.getArea(), Epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(MoveAssignmentOperator)
  {
    kudryakov::Rectangle rectangle({-2,0}, 2, 2);
    kudryakov::Circle circle({2,0}, 1);
    kudryakov::CompositeShape cs(&rectangle);
    cs.addShape(&circle);
    double initCSArea = cs.getArea();
    
    kudryakov::CompositeShape cs2;
    cs2 = std::move(cs);
    BOOST_CHECK_CLOSE(cs2.getArea(), initCSArea, Epsilon);
    BOOST_CHECK_CLOSE(cs.getArea(), 0.0, Epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(SquareBracketsOperator)
  {
    kudryakov::Rectangle rectangle({-2,0}, 2, 2);
    kudryakov::Circle circle({2,0}, 1);
    kudryakov::CompositeShape cs(&rectangle);
    cs.addShape(&circle);
    
    BOOST_CHECK_CLOSE(cs[0]->getArea(), 4.0, Epsilon);
    BOOST_CHECK_CLOSE(cs[1]->getArea(), M_PI, Epsilon);
    BOOST_CHECK_THROW(cs[2], std::out_of_range);
  }
  
  BOOST_AUTO_TEST_CASE(Move)
  {
    kudryakov::Rectangle rectangle({-2,0}, 2, 2);
    kudryakov::Circle circle({2,0}, 1);
    kudryakov::CompositeShape cs(&rectangle);
    cs.addShape(&circle);
    
    cs.move(1, 1);
    BOOST_CHECK_CLOSE(-1, rectangle.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(1, rectangle.getFrameRect().pos.y, Epsilon);
    BOOST_CHECK_CLOSE(3, circle.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(1, circle.getFrameRect().pos.y, Epsilon);
    
    BOOST_CHECK_CLOSE(2, rectangle.getFrameRect().width, Epsilon);
    BOOST_CHECK_CLOSE(2, rectangle.getFrameRect().height, Epsilon);
    BOOST_CHECK_CLOSE(4, rectangle.getArea(), Epsilon);
    BOOST_CHECK_CLOSE(2, circle.getFrameRect().width, Epsilon);
    BOOST_CHECK_CLOSE(2, circle.getFrameRect().height, Epsilon);
    BOOST_CHECK_CLOSE(M_PI, circle.getArea(), Epsilon);
    
    cs.move({0, 0});
    BOOST_CHECK_CLOSE(-2, rectangle.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(0, rectangle.getFrameRect().pos.y, Epsilon);
    BOOST_CHECK_CLOSE(2, circle.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(0, circle.getFrameRect().pos.y, Epsilon);
    
    BOOST_CHECK_CLOSE(2, rectangle.getFrameRect().width, Epsilon);
    BOOST_CHECK_CLOSE(2, rectangle.getFrameRect().height, Epsilon);
    BOOST_CHECK_CLOSE(4, rectangle.getArea(), Epsilon);
    BOOST_CHECK_CLOSE(2, circle.getFrameRect().width, Epsilon);
    BOOST_CHECK_CLOSE(2, circle.getFrameRect().height, Epsilon);
    BOOST_CHECK_CLOSE(M_PI, circle.getArea(), Epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    kudryakov::Rectangle rectangle({-2,0}, 2, 2);
    kudryakov::Circle circle({2,0}, 1);
    kudryakov::CompositeShape cs(&rectangle);
    cs.addShape(&circle);
    
    BOOST_CHECK_THROW(cs.scale(-2), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(Scale)
  {
    kudryakov::Rectangle rectangle({-2,0}, 2, 2);
    kudryakov::Circle circle({2,0}, 1);
    kudryakov::CompositeShape cs(&rectangle);
    cs.addShape(&circle);
    
    double rectInitArea = rectangle.getArea();
    double circInitArea = circle.getArea();
    kudryakov::rectangle_t compositeShapeInitRectangle = cs.getFrameRect();
    
    cs.scale(2);
    BOOST_CHECK_CLOSE(rectInitArea*4, rectangle.getArea(), Epsilon);
    BOOST_CHECK_CLOSE(circInitArea*4, circle.getArea(), Epsilon);
    BOOST_CHECK_CLOSE(compositeShapeInitRectangle.height*2, cs.getFrameRect().height, Epsilon);
    BOOST_CHECK_CLOSE(compositeShapeInitRectangle.width*2, cs.getFrameRect().width, Epsilon);
    BOOST_CHECK_CLOSE(compositeShapeInitRectangle.pos.x, cs.getFrameRect().pos.x, Epsilon);
    BOOST_CHECK_CLOSE(compositeShapeInitRectangle.pos.y, cs.getFrameRect().pos.y, Epsilon);
  }

BOOST_AUTO_TEST_SUITE_END()

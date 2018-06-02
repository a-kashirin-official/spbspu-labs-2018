#define BOOST_TEST_MAIN 
#define BOOST_TEST_DYN_LINK 
#include <stdexcept> 
#include <boost/test/included/unit_test.hpp> 
#include "circle.hpp" 
#include "rectangle.hpp" 

const double EPSILON = 0.000001; 

using namespace subtselnaya; 

BOOST_AUTO_TEST_SUITE(RectangleSuite) 

BOOST_AUTO_TEST_CASE(MoveToPoint) 
{ 
  Rectangle rect (3.5, 4.8, {4.3, 3.4}); 
  rectangle_t startRect = rect.getFrameRect(); 
  double startArea = rect.getArea(); 

  rect.move ({25, 10}); 
  BOOST_CHECK_EQUAL(startArea, rect.getArea()); 
  BOOST_CHECK_EQUAL(startRect.width, rect.getFrameRect().width); 
  BOOST_CHECK_EQUAL(startRect.height, rect.getFrameRect().height); 
} 

BOOST_AUTO_TEST_CASE(MoveByAxis) 
{ 
  Rectangle rect (3.5, 4.8, {4.3, 3.4}); 
  rectangle_t startRect = rect.getFrameRect(); 
  double startArea = rect.getArea(); 

  rect.move (15,5); 
  BOOST_CHECK_EQUAL(startArea, rect.getArea()); 
  BOOST_CHECK_EQUAL(startRect.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(startRect.height, rect.getFrameRect().height); 
} 

BOOST_AUTO_TEST_CASE(Scaling) 
{ 
  Rectangle rect (3.5, 4.8, {4.3, 3.4}); 
  double startArea = rect.getArea(); 
  const double value = 3.3; 

  rect.scale(value); 
  BOOST_CHECK_CLOSE(value * value * startArea, rect.getArea(), EPSILON); 
} 

BOOST_AUTO_TEST_CASE(InvalidScaleParameter) 
{ 
  Rectangle rect (3.5, 4.8, { 4.3, 3.4 }); 
  BOOST_CHECK_THROW (rect.scale(-1.0), std::invalid_argument); 
} 

BOOST_AUTO_TEST_SUITE_END() 


BOOST_AUTO_TEST_SUITE(CircleSuite) 

BOOST_AUTO_TEST_CASE(MoveToPoint) 
{ 
  Circle circ ({5.9, 7.1}, 3.0); 
  rectangle_t startRect = circ.getFrameRect(); 
  double startArea = circ.getArea(); 

  circ.move ({20,10}); 
  BOOST_CHECK_EQUAL(startArea, circ.getArea()); 
  BOOST_CHECK_EQUAL(startRect.width, circ.getFrameRect().width); 
  BOOST_CHECK_EQUAL(startRect.height, circ.getFrameRect().height); 
} 

BOOST_AUTO_TEST_CASE(MoveByAxis) 
{ 
  Circle circ ({5.9, 7.1}, 3.0); 
  rectangle_t startRect = circ.getFrameRect(); 
  double startArea = circ.getArea(); 

  circ.move (10,5); 
  BOOST_CHECK_EQUAL(startArea, circ.getArea()); 
  BOOST_CHECK_EQUAL(startRect.width, circ.getFrameRect().width); 
  BOOST_CHECK_EQUAL(startRect.height, circ.getFrameRect().height); 
} 

BOOST_AUTO_TEST_CASE(Scaling) 
{ 
  Circle circ ({5.9, 7.1}, 3.0); 
  double startArea = circ.getArea(); 
  const double value = 3.3; 

  circ.scale(value); 
  BOOST_CHECK_CLOSE(value * value * startArea, circ.getArea(), EPSILON); 
} 

BOOST_AUTO_TEST_CASE(InvalidScaleParameter) 
{ 
  Circle circ ({5.9, 7.1}, 3.0); 
  BOOST_CHECK_THROW(circ.scale(-1.0), std::invalid_argument); 
} 

BOOST_AUTO_TEST_SUITE_END()

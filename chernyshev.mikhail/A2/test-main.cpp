#define BOOST_TEST_MODULE mainTest
#include <stdexcept>
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace chernyshev;

const double delta = 1;

BOOST_AUTO_TEST_SUITE(testCircle)
  
  BOOST_AUTO_TEST_CASE(getFrameRect)
  {
    Circle circle(5,{10,15});
    BOOST_CHECK_CLOSE(5*2,circle.getFrameRect().height,delta);
    BOOST_CHECK_CLOSE(5*2,circle.getFrameRect().width,delta);
    BOOST_CHECK_CLOSE(10,circle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(15,circle.getFrameRect().pos.y,delta);
  }
   
  BOOST_AUTO_TEST_CASE(Area)
  {
    Circle circle(5,{10,15});
    BOOST_CHECK_CLOSE(M_PI*5*5,circle.getArea(),delta);
  }
  BOOST_AUTO_TEST_CASE(Moving)
  {
    Circle circle(5,{10,15});
    circle.Move(20,30);
    BOOST_CHECK_CLOSE(30,circle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(45,circle.getFrameRect().pos.y,delta);
    circle.Move({5,10});
    BOOST_CHECK_CLOSE(5,circle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(10,circle.getFrameRect().pos.y,delta);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Circle circle(5,{10,15});
    circle.scale(1.5);
    BOOST_CHECK_CLOSE(M_PI*56.25,circle.getArea(),delta);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidSCale)
  {
    Circle circle(5,{10,15});
    BOOST_CHECK_THROW(circle.scale(-100),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(Circle circle(-5,{10,15}),std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()
        
BOOST_AUTO_TEST_SUITE(testRectangle)
  
  BOOST_AUTO_TEST_CASE(getFrameRect)
  {
    Rectangle rectangle(5,10,{10,10});
    BOOST_CHECK_CLOSE(5,rectangle.getFrameRect().height,delta);
    BOOST_CHECK_CLOSE(10,rectangle.getFrameRect().width,delta);
    BOOST_CHECK_CLOSE(10,rectangle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(10,rectangle.getFrameRect().pos.y,delta);
  }
   
  BOOST_AUTO_TEST_CASE(Area)
  {
    Rectangle rectangle(5,10,{10,10});
    BOOST_CHECK_CLOSE(50,rectangle.getArea(),delta);
  }
  BOOST_AUTO_TEST_CASE(Moving)
  {
    Rectangle rectangle(5,10,{10,10});
    rectangle.Move(20,30);
    BOOST_CHECK_CLOSE(30,rectangle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(40,rectangle.getFrameRect().pos.y,delta);
    rectangle.Move({5,10});
    BOOST_CHECK_CLOSE(5,rectangle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(10,rectangle.getFrameRect().pos.y,delta);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rectangle(5,10,{10,10});
    rectangle.scale(1.5);
    BOOST_CHECK_CLOSE(112.5,rectangle.getArea(),delta);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidSCale)
  {
    Rectangle rectangle(5,10,{10,15});
    BOOST_CHECK_THROW(rectangle.scale(-100),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(Rectangle rectangle(-5,-10,{10,15}),std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()
 

BOOST_AUTO_TEST_SUITE(testTriangle)
  
  BOOST_AUTO_TEST_CASE(getFrameRect)
  {
    Triangle triangle({10,10},{15,15},{20,10});
    BOOST_CHECK_CLOSE(5,triangle.getFrameRect().height,delta);
    BOOST_CHECK_CLOSE(10,triangle.getFrameRect().width,delta);
    BOOST_CHECK_CLOSE(15,triangle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(10+(5/3),triangle.getFrameRect().pos.y,delta);
  }
   
  BOOST_AUTO_TEST_CASE(Area)
  {
    Triangle triangle({10,10},{15,15},{20,10});
    BOOST_CHECK_CLOSE(25,triangle.getArea(),delta);
  }
  BOOST_AUTO_TEST_CASE(Moving)
  {
    Triangle triangle({10,10},{15,15},{20,10});
    triangle.Move(20,30);
    BOOST_CHECK_CLOSE(15+20,triangle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(10+(5/3)+30,triangle.getFrameRect().pos.y,delta);
    triangle.Move({5,10});
    BOOST_CHECK_CLOSE(5,triangle.getFrameRect().pos.x,delta);
    BOOST_CHECK_CLOSE(10,triangle.getFrameRect().pos.y,delta);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Triangle triangle({10,10},{15,15},{20,10});
    triangle.scale(1.5);
    BOOST_CHECK_CLOSE(69.525,triangle.getArea(),delta);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidSCale)
  {
    Triangle triangle({10,10},{15,15},{20,10});
    BOOST_CHECK_THROW(triangle.scale(-100),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

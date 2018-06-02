#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"

const double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(InitRectangleTest)
  {
    BOOST_CHECK_THROW(maikenova::Rectangle({15.32, 1.23}, -9, 9), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_toPoint_Tests)
  {
    maikenova::Rectangle myRectangle({80.31, 72.68}, 3.0, 10.0);

    double widthBefore = myRectangle.getFrameRect().width;
    double heightBefore = myRectangle.getFrameRect().height;
    double areaBefore = myRectangle.getArea();
    myRectangle.move({20.0, 20.0});

    //checking sides of the rectangle
    BOOST_CHECK_EQUAL(widthBefore, myRectangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBefore, myRectangle.getFrameRect().height);

    //checking area of the rectangle
    BOOST_CHECK_EQUAL(areaBefore, myRectangle.getArea());

    //checking position of the rectangle
    BOOST_CHECK_EQUAL(20.0, myRectangle.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(20.0, myRectangle.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_CASE(Move_shift_Tests)
  {
    maikenova::Rectangle myRectangle({80.31, 72.68}, 3.0, 10.0);

    double widthBefore = myRectangle.getFrameRect().width;
    double heightBefore = myRectangle.getFrameRect().height;
    double xBefore = myRectangle.getFrameRect().pos.x;
    double yBefore = myRectangle.getFrameRect().pos.y;
    double areaBefore = myRectangle.getArea();
    myRectangle.move(100.0, 100.0);

    //checking sides of the rectangle
    BOOST_CHECK_EQUAL(widthBefore, myRectangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBefore,myRectangle.getFrameRect().height);

    //checking area of the rectangle
    BOOST_CHECK_EQUAL(areaBefore, myRectangle.getArea());

    //checking position of the rectangle
    BOOST_CHECK_CLOSE(xBefore + 100.0, myRectangle.getFrameRect().pos.x, epsilon);
    BOOST_CHECK_CLOSE(yBefore + 100.0, myRectangle.getFrameRect().pos.y, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scale_Tests)
  {
    maikenova::Rectangle myRectangle({173.82, 163.43}, 8.99, 20.0);
    BOOST_CHECK_THROW(myRectangle.scale(-9.0), std::invalid_argument);

    double xBefore = myRectangle.getFrameRect().pos.x;
    double yBefore = myRectangle.getFrameRect().pos.y;
    double areaBefore = myRectangle.getArea();
    myRectangle.scale(2.0);

    //checking position after scaling
    BOOST_CHECK_EQUAL(xBefore, myRectangle.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(yBefore, myRectangle.getFrameRect().pos.y);

    //checking area after scaling
    BOOST_CHECK_EQUAL(areaBefore * 4.0, myRectangle.getArea());
  }
BOOST_AUTO_TEST_SUITE_END()

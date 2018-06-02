#include <boost/test/unit_test.hpp>
#include "circle.hpp"

const double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(Circle_Tests)

  BOOST_AUTO_TEST_CASE(Init_Circle_Test)
  {
    BOOST_CHECK_THROW(maikenova::Circle({173.82, 163.43}, -8.99), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_toPoint_Tests)
  {
    maikenova::Circle myCircle({173.82, 163.43}, 8.99);

    double frameH = myCircle.getFrameRect().height;
    double frameW = myCircle.getFrameRect().width;
    double areaBefore = myCircle.getArea();
    myCircle.move({10.0, 72.0});

    //checking that framed rectangle didn't change, therefore radius is the same
    BOOST_CHECK_EQUAL(frameH, myCircle.getFrameRect().height);
    BOOST_CHECK_EQUAL(frameW, myCircle.getFrameRect().width);

    //checking area after moving
    BOOST_CHECK_EQUAL(areaBefore, myCircle.getArea());

    //checking position
    BOOST_CHECK_EQUAL(10.0, myCircle.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(72.0, myCircle.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_CASE(Move_shift_Tests)
  {
    maikenova::Circle myCircle({173.82, 163.43}, 8.99);

    double frameH = myCircle.getFrameRect().height;
    double frameW = myCircle.getFrameRect().width;
    double areaBefore = myCircle.getArea();
    double xBefore = myCircle.getFrameRect().pos.x;
    double yBefore = myCircle.getFrameRect().pos.y;
    myCircle.move(100.0, 100.0);

    //checking framed rectangle
    BOOST_CHECK_EQUAL(frameH, myCircle.getFrameRect().height);
    BOOST_CHECK_EQUAL(frameW, myCircle.getFrameRect().width);

    //checking area
    BOOST_CHECK_EQUAL(areaBefore, myCircle.getArea());

    //checking position
    BOOST_CHECK_CLOSE(xBefore + 100.0, myCircle.getFrameRect().pos.x, epsilon);
    BOOST_CHECK_CLOSE(yBefore + 100.0, myCircle.getFrameRect().pos.y, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scale_Tests)
  {
    maikenova::Circle myCircle({173.82, 163.43}, 8.99);
    BOOST_CHECK_THROW(myCircle.scale(-9.0), std::invalid_argument);

    double xBefore = myCircle.getFrameRect().pos.x;
    double yBefore = myCircle.getFrameRect().pos.y;
    double areaBefore = myCircle.getArea();
    myCircle.scale(2.0);

    //checking position
    BOOST_CHECK_EQUAL(xBefore, myCircle.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(yBefore, myCircle.getFrameRect().pos.y);

    //checking area
    BOOST_CHECK_CLOSE(areaBefore * 4.0, myCircle.getArea(), epsilon);
  }
BOOST_AUTO_TEST_SUITE_END()

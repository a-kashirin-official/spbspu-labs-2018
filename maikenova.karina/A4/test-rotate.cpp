#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "rotateMtrx.hpp"
#include <cmath>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tests_CompositeShape)

const double epsilon = 0.00001;

BOOST_AUTO_TEST_CASE(rotateMatrix_Test)
{
  const maikenova::point_t p1 = {1.0, 1.0};
  const maikenova::point_t p2 = {2.0, 2.0};
  maikenova::point_t p3;

  p3 = rotateMtrx(p1, p2, 45.0);
  BOOST_CHECK_CLOSE(p3.x, 1.0, epsilon);
  BOOST_CHECK_CLOSE(p3.y, 1+sqrt(2), epsilon);

  p3 = rotateMtrx(p1, p2, 315.0);
  BOOST_CHECK_CLOSE(p3.x, 1+sqrt(2), epsilon);
  BOOST_CHECK_CLOSE(p3.y, 1.0, epsilon);

  p3 = rotateMtrx(p1, p2, 135.0);
  BOOST_CHECK_CLOSE(p3.x, 1 - sqrt(2), epsilon);
  BOOST_CHECK_CLOSE(p3.y, 1.0, epsilon);

  p3 = rotateMtrx(p1, p2, -45.0);
  BOOST_CHECK_CLOSE(p3.x, 1 + sqrt(2), epsilon);
  BOOST_CHECK_CLOSE(p3.y, 1.0, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_rotation_Test)
{
  maikenova::Circle myCircle({0.0, 0.0}, 3.0);
  myCircle.rotate(90.0);

  BOOST_CHECK_CLOSE(myCircle.getFrameRect().height, 6.0, epsilon);
  BOOST_CHECK_CLOSE(myCircle.getFrameRect().width, 6.0, epsilon);
  BOOST_CHECK_CLOSE(myCircle.getFrameRect().pos.x, 0.0, epsilon);
  BOOST_CHECK_CLOSE(myCircle.getFrameRect().pos.y, 0.0, epsilon);

  myCircle.rotate(-90.0);
  BOOST_CHECK_CLOSE(myCircle.getFrameRect().height, 6.0, epsilon);
  BOOST_CHECK_CLOSE(myCircle.getFrameRect().width, 6.0, epsilon);
  BOOST_CHECK_CLOSE(myCircle.getFrameRect().pos.x, 0.0, epsilon);
  BOOST_CHECK_CLOSE(myCircle.getFrameRect().pos.y, 0.0, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_rotation_Test)
{
  maikenova::Rectangle myRectangle({5.0, 5.0}, 4.0, 2.0);
  myRectangle.rotate(45.0);
  double wAfter = 3*sqrt(2);
  double hAfter = 3*sqrt(2);

  BOOST_CHECK_CLOSE(myRectangle.getFrameRect().height, hAfter, epsilon);
  BOOST_CHECK_CLOSE(myRectangle.getFrameRect().width, wAfter, epsilon);
  BOOST_CHECK_CLOSE(myRectangle.getFrameRect().pos.x, 5.0, epsilon);
  BOOST_CHECK_CLOSE(myRectangle.getFrameRect().pos.y, 5.0, epsilon);

  myRectangle.rotate(-45.0);
  BOOST_CHECK_CLOSE(myRectangle.getFrameRect().pos.x, 5.0, epsilon);
  BOOST_CHECK_CLOSE(myRectangle.getFrameRect().pos.y, 5.0, epsilon);


  BOOST_CHECK_CLOSE(myRectangle.getFrameRect().width, 4.0, epsilon);
  BOOST_CHECK_CLOSE(myRectangle.getFrameRect().height, 2.0, epsilon);
}

BOOST_AUTO_TEST_CASE(CompositeShape_rotation_Test)
{
  maikenova::Circle myCircle({2.0, 2.0}, 2.0);
  maikenova::Rectangle myRectangle({6.0, 7.0}, 2.0, 4.0);
  maikenova::CompositeShape compShape;
  compShape.pushBack(& myCircle);
  compShape.pushBack(& myRectangle);

  compShape.rotate(90.0);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.x, 6.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.y, 3.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.x, 1.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.y, 7.0, epsilon);

  compShape.rotate(-90.0);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, 3.5, epsilon);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, 4.5, epsilon);
  
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.x, 2.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.y, 2.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.x, 6.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.y, 7.0, epsilon);

  compShape.rotate(180.0);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.x, 5.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.y, 7.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.x, 1.0, epsilon);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.y, 2.0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()


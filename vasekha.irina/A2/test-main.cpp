#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace vasekha;

const double epsilon = 1e-4;

BOOST_AUTO_TEST_SUITE(TestRectangle)

BOOST_AUTO_TEST_CASE(testMoveToPoint)
{
  Rectangle rect{{2.0,3.0},4.0,4.0};
  const rectangle_t frameBefore = rect.getFrameRect();
  const double areaBefore = rect.getArea();
  rect.move({5.6,5.8});
  BOOST_CHECK_EQUAL(frameBefore.height, rect.getFrameRect().height);
  BOOST_CHECK_EQUAL(frameBefore.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, rect.getArea());
}

BOOST_AUTO_TEST_CASE(testRelativeMove)
{
  Rectangle rect{{1.0,5.0},6.0,5.6};
  const rectangle_t frameBefore = rect.getFrameRect();
  const double areaBefore = rect.getArea();
  rect.move(5.6,5.8);
  BOOST_CHECK_EQUAL(frameBefore.height, rect.getFrameRect().height);
  BOOST_CHECK_EQUAL(frameBefore.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, rect.getArea());
}

BOOST_AUTO_TEST_CASE(testAreaAfterScaling)
{
  Rectangle rect{{2.4,3.6},3.1,6.7};
  const double areaBefore = rect.getArea();
  const double factor = 4.0;
  rect.scale(factor);
  BOOST_CHECK_CLOSE(areaBefore*factor*factor, rect.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(testScaleParametr)
{
  Rectangle rect{{2.4,3.6},23.4,54.3};
  BOOST_CHECK_THROW(rect.scale(-1.0),std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testConstructorParametrs)
{
  BOOST_CHECK_THROW(Rectangle({0.0,3.6},-2.0,6.0),std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle({0.0,3.6},2.0,-6.0),std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle({0.0,3.6},-2.0,-6.0),std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)

BOOST_AUTO_TEST_CASE(testMoveToPoint)
{
  Circle cir{{2.0,3.0},2.0};
  const rectangle_t frame = cir.getFrameRect();
  const double areaBefore = cir.getArea();
  cir.move({5.6,5.8});
  BOOST_CHECK_EQUAL(frame.width, cir.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, cir.getArea());
}

BOOST_AUTO_TEST_CASE(testRelativeMove)
{
  Circle cir{{1.76,3.0},2.434};
  const rectangle_t frame = cir.getFrameRect();
  const double areaBefore = cir.getArea();
  cir.move(5.6,5.232);
  BOOST_CHECK_EQUAL(frame.width, cir.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, cir.getArea());
}

BOOST_AUTO_TEST_CASE(testAreaAfterScaling)
{
  Circle cir{{2.4,3.6},4.0};
  const double areaBefore = cir.getArea();
  const double factor = 4.0;
  cir.scale(factor);
  BOOST_CHECK_CLOSE(areaBefore*factor*factor, cir.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(testScaleParametr)
{
  Circle cir{{2.4,3.6},4.0};
  BOOST_CHECK_THROW(cir.scale(-1.0),std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testConstructorParametrs)
{
  BOOST_CHECK_THROW(Circle({0.0,3.6},-5.0),std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestTriangle)

BOOST_AUTO_TEST_CASE(testMoveToPoint)
{
  Triangle tr{{2.0,3.0},{0.0,4.0},{1.0,5.0}};
  const rectangle_t frame = tr.getFrameRect();
  const double areaBefore = tr.getArea();
  tr.move({5.6,5.8});
  BOOST_CHECK_EQUAL(frame.height, tr.getFrameRect().height);
  BOOST_CHECK_EQUAL(frame.width, tr.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, tr.getArea());
}

BOOST_AUTO_TEST_CASE(testRelativeMove)
{
  Triangle tr{{2.0,3.0},{0.0,4.0},{1.0,5.0}};
  const rectangle_t frame = tr.getFrameRect();
  const double areaBefore = tr.getArea();
  tr.move(5.6,5.8);
  BOOST_CHECK_EQUAL(frame.height, tr.getFrameRect().height);
  BOOST_CHECK_EQUAL(frame.width, tr.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, tr.getArea());
}

BOOST_AUTO_TEST_CASE(testAreaAfterScaling)
{
  Triangle tr{{2.4,3.6},{1.5,5.4},{3.3,5.4}};
  const double areaBefore = tr.getArea();
  const double factor = 5.0;
  tr.scale(factor);
  BOOST_CHECK_CLOSE(areaBefore*factor*factor, tr.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(testScaleParametr)
{
  Triangle tr{{2.4,3.6},{1.5,5.4},{3.3,5.4}};
  BOOST_CHECK_THROW(tr.scale(-4.0),std::invalid_argument);

}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
using namespace vasekha;

const double epsilon = 1e-1;

BOOST_AUTO_TEST_SUITE(TestRectangle)

BOOST_AUTO_TEST_CASE(testRotate)
{
  Rectangle rect{{2.0,3.0},4.0,4.0};
  const rectangle_t frameBefore = rect.getFrameRect();
  const double areaBefore = rect.getArea();  
  rect.rotate(-180.0);
  BOOST_CHECK_EQUAL(frameBefore.height, rect.getFrameRect().height);
  BOOST_CHECK_EQUAL(frameBefore.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, rect.getArea());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)

BOOST_AUTO_TEST_CASE(testRotate)
{
  Circle cir{{2.0,3.0},2.0};
  const rectangle_t frame = cir.getFrameRect();
  const double areaBefore = cir.getArea();
  cir.rotate(54.0);
  BOOST_CHECK_EQUAL(frame.width, cir.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, cir.getArea());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestTriangle)

BOOST_AUTO_TEST_CASE(testRotate)
{
  Triangle tr{{2.0,3.0},{0.0,4.0},{1.0,5.0}};
  const rectangle_t frame = tr.getFrameRect();
  const double areaBefore = tr.getArea();
  tr.rotate(6.0);
  BOOST_CHECK_CLOSE_FRACTION(frame.height, tr.getFrameRect().height,epsilon);
  BOOST_CHECK_CLOSE_FRACTION(frame.width, tr.getFrameRect().width,epsilon);
  BOOST_CHECK_EQUAL(areaBefore, tr.getArea());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCompositeShape)

BOOST_AUTO_TEST_CASE(testRotate)
{
  CompositeShape compSh;
  compSh.add(std::make_shared<Rectangle>(Rectangle{{2.0,3.0},4.0,4.0}));
  compSh.add(std::make_shared<Circle>(Circle{{2.4,3.6},4.0}));
  compSh.add(std::make_shared<Triangle>(Triangle{{2.4,3.6},{1.5,5.4},{3.3,5.4}}));
  const rectangle_t frameBefore = compSh.getFrameRect();
  const double areaBefore = compSh.getArea();
  compSh.rotate(50.0);
  BOOST_CHECK_EQUAL(frameBefore.height, compSh.getFrameRect().height);
  BOOST_CHECK_EQUAL(frameBefore.width, compSh.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBefore, compSh.getArea());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestMatrix)

BOOST_AUTO_TEST_CASE(testLayering)
{
  Circle cir{{1.0,1.0},5.0};
  Circle cir1{{3.0,-9.0},1.0};
  Rectangle rect{{4.5,9.0},3.0,2.0};
  Rectangle rect1{{3.0,7.0},4.0,4.0};
  Triangle tr{{3.0,-3.0},{3.0,-9.0},{5.0,-9.0}};
  Rectangle rect2{{9.0,7.0},2.0,2.0};
  Circle cir2{{9.0,8.0},1.0};
  Rectangle rect3{{1.0,9.0},2.0,2.0};
  
  Shape::ptr_shape ptr_cir = std::make_shared<Circle>(cir);
  Shape::ptr_shape ptr_cir1 = std::make_shared<Circle>(cir1);
  Shape::ptr_shape ptr_rect = std::make_shared<Rectangle>(rect);
  Shape::ptr_shape ptr_rect1 = std::make_shared<Rectangle>(rect1);
  Shape::ptr_shape ptr_tr = std::make_shared<Triangle>(tr);
  Shape::ptr_shape ptr_rect2 = std::make_shared<Rectangle>(rect2);
  Shape::ptr_shape ptr_cir2 = std::make_shared<Circle>(cir2);
  Shape::ptr_shape ptr_rect3 = std::make_shared<Rectangle>(rect3);

  Matrix matrix;
  matrix.add(ptr_cir);
  matrix.add(ptr_cir1);
  matrix.add(ptr_rect);
  matrix.add(ptr_rect1);
  matrix.add(ptr_tr);
  matrix.add(ptr_rect2);
  matrix.add(ptr_cir2);
  matrix.add(ptr_rect3);

  std::unique_ptr<Shape::ptr_shape[]> layer1=matrix[0];
  std::unique_ptr<Shape::ptr_shape[]> layer2=matrix[1];
  std::unique_ptr<Shape::ptr_shape[]> layer3=matrix[2];

  BOOST_CHECK(layer1[0]==ptr_cir);
  BOOST_CHECK(layer1[1]==ptr_cir1);
  BOOST_CHECK(layer1[2]==ptr_rect);
  BOOST_CHECK(layer1[3]==ptr_rect2);
  BOOST_CHECK(layer2[0]==ptr_rect1);
  BOOST_CHECK(layer2[1]==ptr_tr);
  BOOST_CHECK(layer2[2]==ptr_cir2);
  BOOST_CHECK(layer3[0]==ptr_rect3);
}

BOOST_AUTO_TEST_SUITE_END()

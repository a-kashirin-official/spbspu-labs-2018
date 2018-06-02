#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace ivanov;

const double EPS = 0.0001;

BOOST_AUTO_TEST_SUITE(Composite_Shape_Tests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({7.9, 8.2, {-1.6, -2.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({3.2, 2.6}, 6.9));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double heightBeforeChange = compositeShape.getFrameRect().height;
    double widthBeforeChange = compositeShape.getFrameRect().width;
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.move({3.2, 1.0});
    BOOST_CHECK((compositeShape.getFrameRect().pos.x == 3.2));
    BOOST_CHECK_CLOSE(heightBeforeChange, compositeShape.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, compositeShape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveAxis)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({7.9, 8.2, {-1.6, -2.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({3.2, 2.6}, 6.9));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double heightBeforeChange = compositeShape.getFrameRect().height;
    double widthBeforeChange = compositeShape.getFrameRect().width;
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.move(3.0, 2.0);
    BOOST_CHECK_CLOSE(heightBeforeChange, compositeShape.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, compositeShape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(invalidScale)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({7.9, 8.2, {-1.6, -2.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({3.2, 2.6}, 6.9));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    BOOST_CHECK_THROW(compositeShape.scale(-2.9), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScale)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({7.9, 8.2, {-1.6, -2.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({3.2, 2.6}, 6.9));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.scale(3.0);
    BOOST_CHECK_CLOSE(3.0 * 3.0 * areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(TestaddShape)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({7.9, 8.2, {-1.6, -2.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({3.2, 2.6}, 6.9));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    BOOST_CHECK_EQUAL(compositeShape.getSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(TestdeleteShape)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({7.9, 8.2, {-1.6, -2.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({3.2, 2.6}, 6.9));
    CompositeShape compositeShape;
    compositeShape.addShape(rectangle1);
    compositeShape.addShape(circle1);
    compositeShape.deleteShape(1);
    BOOST_CHECK_EQUAL(compositeShape.getSize(), 1);
  }

 BOOST_AUTO_TEST_CASE(addNullPointer)
  {
    std::shared_ptr<Shape> circle = nullptr;
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({0.0, 0.0}, 1.0));
    CompositeShape compositeShape;
    compositeShape.addShape(circle1);
    BOOST_CHECK_THROW(compositeShape.addShape(circle), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(outOfRange)
  {
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(Circle({0, 0}, 10.3));
    CompositeShape compositeShape;
    compositeShape.addShape(circle);
    BOOST_CHECK_THROW(compositeShape[2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(emptyShape)
  {
    CompositeShape compositeShape;
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().width, 0);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().height, 0);
  }

  BOOST_AUTO_TEST_CASE(constructorTest)
  {
    std::shared_ptr<Shape> shape = nullptr;
    BOOST_CHECK_THROW(CompositeShape compositeShape(shape), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(copyingConstructor)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({5.0, 7.0, {3.0, 4.0}}));
    CompositeShape compositeShape1(rectangle1);
    compositeShape1.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    CompositeShape compositeShape2(compositeShape1);
    for (size_t i = 0; i < compositeShape1.getSize(); i++)
    {
      const rectangle_t rectangle1 = compositeShape1[i]->getFrameRect();
      const rectangle_t rectangle2 = compositeShape2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle1.height, rectangle2.height);
      BOOST_CHECK_EQUAL(rectangle1.width, rectangle2.width);
      BOOST_CHECK_EQUAL(rectangle1.pos.x, rectangle2.pos.x);
      BOOST_CHECK_EQUAL(rectangle1.pos.y, rectangle2.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(movingConstructor)
{
  std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({5.0, 7.0, {3.0, 4.0}}));
  CompositeShape compositeShape1(rectangle1);
  compositeShape1.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
  CompositeShape compositeShape2(compositeShape1);
  CompositeShape compositeShape3(std::move(compositeShape1));
  for (size_t i = 0; i < compositeShape1.getSize(); i++)
  {
    const rectangle_t rectangle2 = compositeShape2[i]->getFrameRect();
    const rectangle_t rectangle3 = compositeShape3[i]->getFrameRect();
    BOOST_CHECK_EQUAL(rectangle2.height, rectangle3.height);
    BOOST_CHECK_EQUAL(rectangle2.width, rectangle3.width);
    BOOST_CHECK_EQUAL(rectangle2.pos.x, rectangle3.pos.x);
    BOOST_CHECK_EQUAL(rectangle2.pos.y, rectangle3.pos.y);
  }
}

BOOST_AUTO_TEST_CASE(movingOperator)
{
  std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({5.0, 7.0, {3.0, 4.0}}));
  CompositeShape compositeShape1(rectangle1);
  compositeShape1.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
  CompositeShape compositeShape2(compositeShape1);
  std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(Rectangle({5.0, 7.0, {1.0, 5.0}}));
  CompositeShape compositeShape3(rectangle2);
  compositeShape3.addShape(std::make_shared<Circle>(Circle({6.0, 6.0}, 11.0)));
  compositeShape3 = std::move(compositeShape1);
  for (size_t i = 0; i < compositeShape1.getSize(); i++)
  {
    const rectangle_t rectangle2 = compositeShape2[i]->getFrameRect();
    const rectangle_t rectangle3 = compositeShape3[i]->getFrameRect();
    BOOST_CHECK_EQUAL(rectangle2.height, rectangle3.height);
    BOOST_CHECK_EQUAL(rectangle2.width, rectangle3.width);
    BOOST_CHECK_EQUAL(rectangle2.pos.x, rectangle3.pos.x);
    BOOST_CHECK_EQUAL(rectangle2.pos.y, rectangle3.pos.y);
  }
}

BOOST_AUTO_TEST_SUITE_END()

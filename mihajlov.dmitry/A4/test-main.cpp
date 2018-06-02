#define BOOST_TEST_MODULE testmain
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "matrix.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double precision = 1e-3;

mihajlov::Matrix matrix;
std::shared_ptr<mihajlov::Shape> rectangle(new mihajlov::Rectangle({10.0, 10.0}, 4.0, 5.0));
std::shared_ptr<mihajlov::Shape> circle(new mihajlov::Circle({0.0, -6.0}, 5.0));
std::shared_ptr<mihajlov::CompositeShape> composite(new mihajlov::CompositeShape(rectangle));

BOOST_AUTO_TEST_SUITE(MatrixTest)

  BOOST_AUTO_TEST_CASE(InvalidParamters)
  {
    BOOST_CHECK_THROW(matrix.addShape(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(matrix[-2], std::out_of_range);
    BOOST_CHECK_THROW(matrix[53], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(MatrixInitialize)
  {
    BOOST_CHECK_EQUAL(matrix.getLayersCount(), 0);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(MatrixElement1)
  {
    matrix.addShape(rectangle);
    BOOST_CHECK_EQUAL(matrix.getLayersCount(), 1);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(), 1);
  }

  BOOST_AUTO_TEST_CASE(MatrixElement2)
  {
    matrix.addShape(circle);
    BOOST_CHECK_EQUAL(matrix.getLayersCount(), 1);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MatrixElement3)
  {
    composite->addShape(circle);
    matrix.addShape(composite);
    BOOST_CHECK_EQUAL(matrix.getLayersCount(), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(), 2);
  }


BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(RotationTests)

  BOOST_AUTO_TEST_CASE(rotateRectangle1)
  {
    rectangle->rotate(90);
    BOOST_CHECK_EQUAL(rectangle->getFrameRect().width, 4.0);
    BOOST_CHECK_EQUAL(rectangle->getFrameRect().height, 5.0);

    rectangle->rotate(90);

    BOOST_CHECK_EQUAL(rectangle->getFrameRect().height, 4.0);
    BOOST_CHECK_EQUAL(rectangle->getFrameRect().width, 5.0);

    rectangle->rotate(-90);
  }

  BOOST_AUTO_TEST_CASE(rotateRectangle2)
  {
    rectangle->rotate(270);
    BOOST_CHECK_CLOSE_FRACTION(rectangle->getFrameRect().width, 5.0, precision);
    BOOST_CHECK_CLOSE_FRACTION(rectangle->getFrameRect().height, 4.0, precision);
  }

  BOOST_AUTO_TEST_CASE(rotateRectangle3)
  {
    rectangle->rotate(45);
    BOOST_CHECK_CLOSE_FRACTION(rectangle->getFrameRect().width, rectangle->getFrameRect().height, precision);
  }

  BOOST_AUTO_TEST_CASE(rotateRectangle4)
  {
    rectangle->rotate(55);
    BOOST_CHECK_EQUAL(rectangle->getFrameRect().pos.x, 10.0);
    BOOST_CHECK_EQUAL(rectangle->getFrameRect().pos.y, 10.0);
  }

  BOOST_AUTO_TEST_CASE(rotateCircle)
  {
    circle->rotate(45);
    BOOST_CHECK_EQUAL(circle->getFrameRect().width / 2, 5.0);
    BOOST_CHECK_EQUAL(circle->getFrameRect().height / 2, 5.0);
  }


BOOST_AUTO_TEST_SUITE_END()

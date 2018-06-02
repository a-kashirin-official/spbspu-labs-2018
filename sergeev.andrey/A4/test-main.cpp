#define BOOST_TEST_MAIN
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace sergeev;

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(RectangleTest)
  BOOST_AUTO_TEST_CASE(Rotate)
  {
    const rectangle_t s_rect = { {2.0, 5.0}, 7.0, 8.0 };
    const double angle = 135.0;
    Rectangle rect{ s_rect };

    rect.rotate(angle);

    rectangle_t Rotated = rect.getFrameRect();
    BOOST_CHECK_EQUAL(s_rect.pos.x, Rotated.pos.x);
    BOOST_CHECK_EQUAL(s_rect.pos.y, Rotated.pos.y);

    point_t rightUp = {s_rect.width / 2, s_rect.height / 2};
    point_t leftDown = {-s_rect.width / 2, -s_rect.height / 2};

    rightUp.rotate(angle);
    leftDown.rotate(angle);

    BOOST_CHECK_CLOSE(leftDown.x - rightUp.x, Rotated.width, EPSILON);
    
    point_t leftUp = {-s_rect.width / 2, s_rect.height / 2};
    point_t rightDown = {s_rect.width / 2, -s_rect.height / 2};

    leftUp.rotate(angle);
    rightDown.rotate(angle);

    BOOST_CHECK_CLOSE(rightDown.y - leftUp.y, Rotated.height, EPSILON);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)
  BOOST_AUTO_TEST_CASE(Rotate)
  {
    Circle circ{ {2.0, 3.0}, 5.0};

    circ.rotate(34.0);

    BOOST_CHECK_EQUAL(circ.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(circ.getFrameRect().pos.y, 3.0);
    BOOST_CHECK_CLOSE(circ.getFrameRect().width, 10.0, EPSILON);
    BOOST_CHECK_CLOSE(circ.getFrameRect().height, 10.0, EPSILON);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompostieShapeTest)
  BOOST_AUTO_TEST_CASE(Rotate)
  {
    CompositeShape c_shape;
    
    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {1.0, 2.0}, 5.0, 6.0 });
    c_shape.add(rect);
  
    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 6.0);
    c_shape.add(circle);

    rectangle_t constructed = c_shape.getFrameRect();

    c_shape.rotate(90.0);

    rectangle_t Rotated = c_shape.getFrameRect();

    BOOST_CHECK_CLOSE(constructed.pos.x, Rotated.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(constructed.pos.y, Rotated.pos.y, EPSILON);
    BOOST_CHECK_CLOSE(constructed.height, Rotated.width, EPSILON);
    BOOST_CHECK_CLOSE(constructed.width, Rotated.height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(devide)
  {
    CompositeShape c_shape;
    
    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {3.0, 2.0}, 5.0, 6.0 });
    c_shape.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 2.0);
    c_shape.add(circle);
  
    std::shared_ptr< Circle > circle1 = std::make_shared< Circle >(point_t{1.0, 2.0}, 6.0);
    c_shape.add(circle1);

    std::shared_ptr< Rectangle > rect1 = std::make_shared< Rectangle >(rectangle_t{ {4.0, 3.0}, 7.0, 8.0 });
    c_shape.add(rect1);

    Matrix mat = c_shape.devide();
    
    BOOST_CHECK_EQUAL(mat.getLayers(), 3);
    BOOST_CHECK_EQUAL(mat.getLayerSize(), 2);

    BOOST_CHECK_EQUAL(mat[0][0], rect);
    BOOST_CHECK_EQUAL(mat[0][1], circle);
    BOOST_CHECK_EQUAL(mat[1][0], circle1);
    BOOST_CHECK_EQUAL(mat[2][0], rect1);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTest)

  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    Matrix mat2;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {12.0, 15.0}, 10.0, 2.0 });
    mat2.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 9.0);
    mat2.add(circle);

    Matrix mat1{mat2};

    BOOST_CHECK_EQUAL(mat1.getLayers(), mat2.getLayers());
    BOOST_CHECK_EQUAL(mat1.getLayerSize(), mat2.getLayerSize());
    BOOST_CHECK_EQUAL(mat1[0][0], mat2[0][0]);
    BOOST_CHECK_EQUAL(mat1[1][0], mat2[1][0]);
  }

  BOOST_AUTO_TEST_CASE(MoveConstrucotr)
  {
    Matrix mat2;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {12.0, 15.0}, 10.0, 2.0 });
    mat2.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 9.0);
    mat2.add(circle);

    Matrix mat1{std::move(mat2)};

    BOOST_CHECK_EQUAL(mat1.getLayers(), 2);
    BOOST_CHECK_EQUAL(mat1.getLayerSize(), 1);
    BOOST_CHECK_EQUAL(mat2.getLayers(), 0);
    BOOST_CHECK_EQUAL(mat2.getLayerSize(), 0);

    BOOST_CHECK_EQUAL(mat1[0][0], rect);
    BOOST_CHECK_EQUAL(mat1[1][0], circle);

    BOOST_CHECK_THROW(mat2[0], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(AssignmentCopy)
  {
    Matrix mat2, mat1;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {12.0, 15.0}, 10.0, 2.0 });
    mat2.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 9.0);
    mat2.add(circle);

    mat1 = mat2;

    BOOST_CHECK_EQUAL(mat1.getLayers(), mat2.getLayers());
    BOOST_CHECK_EQUAL(mat1.getLayerSize(), mat2.getLayerSize());
    BOOST_CHECK_EQUAL(mat1[0][0], mat2[0][0]);
    BOOST_CHECK_EQUAL(mat1[1][0], mat2[1][0]);
  }

  BOOST_AUTO_TEST_CASE(AssignmentMove)
  {
    Matrix mat2, mat1;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {12.0, 15.0}, 10.0, 2.0 });
    mat2.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 9.0);
    mat2.add(circle);

    mat1 = std::move(mat2);

    BOOST_CHECK_EQUAL(mat1.getLayers(), 2);
    BOOST_CHECK_EQUAL(mat1.getLayerSize(), 1);
    BOOST_CHECK_EQUAL(mat2.getLayers(), 0);
    BOOST_CHECK_EQUAL(mat2.getLayerSize(), 0);

    BOOST_CHECK_EQUAL(mat1[0][0], rect);
    BOOST_CHECK_EQUAL(mat1[1][0], circle);

    BOOST_CHECK_THROW(mat2[0], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(InvalidIndexindOperator)
  {
    Matrix mat;
    BOOST_CHECK_THROW(mat[0], std::out_of_range);

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 2.0 });
    mat.add(rect);

    BOOST_CHECK_THROW(mat[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(clean)
  {
    Matrix mat;
    
    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 12.0 });
    mat.add(rect);

    mat.clean();
    BOOST_CHECK_EQUAL(mat.getLayers(), 0);
    BOOST_CHECK_EQUAL(mat.getLayerSize(), 0);
    BOOST_CHECK_THROW(mat[0], std::out_of_range);
  }
BOOST_AUTO_TEST_SUITE_END()

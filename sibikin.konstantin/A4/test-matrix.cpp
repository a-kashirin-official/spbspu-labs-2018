#include <boost/test/unit_test.hpp>
#include <iostream>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "matrix.hpp"

const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(Matrix_Test)

  struct PolyFixture
  {
    sibikin::Circle circle;
    sibikin::Rectangle rect;
    sibikin::CompositeShape comp;

    PolyFixture() :
      circle({0.0, 0.0}, 2.0),
      rect({15.0, 15.0}, 4.0, 5.0)
    {
      comp.addShape(&circle);
      comp.addShape(&rect);
    }

    ~PolyFixture() = default;
  };

  BOOST_FIXTURE_TEST_CASE(Matrix_Overlapping_Test, PolyFixture)
  {
    sibikin::Circle circle1({30.0, 30.0}, 3.0);
    sibikin::Rectangle rect1({0.0, 0.0}, 4.0, 5.0);
    sibikin::Matrix matrix{&circle, &rect};
    size_t size = 3;

    BOOST_CHECK_EQUAL(matrix.getShape(0, 0), &circle);
    BOOST_CHECK_EQUAL(matrix.getShape(0, 1), &rect);

    matrix.addShape(&comp);
    BOOST_CHECK_EQUAL(matrix.getShape(1, 0), &comp);

    matrix.addShape(&rect1);
    BOOST_CHECK_EQUAL(matrix.getShape(2, 0), &rect1);

    matrix.addShape(&circle1);
    BOOST_CHECK_EQUAL(matrix.getShape(0, 2), &circle1);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(0), size);
  }

  BOOST_FIXTURE_TEST_CASE(CreateMatrix_Overlapping_Test, PolyFixture)
  {
    sibikin::Rectangle rect1({0.0, 0.0}, 4.0, 5.0);
    sibikin::Circle circle1({30.0, 30.0}, 3.0);
    comp.addShape(&rect1);
    comp.addShape(&circle1);
    sibikin::Matrix matrix = matrix.createMatrix(comp);
    sibikin::Matrix matrix1{&circle, &rect, &rect1, &circle1};

    BOOST_CHECK_EQUAL(matrix.getShape(0, 0), matrix1.getShape(0, 0));
    BOOST_CHECK_EQUAL(matrix.getShape(0, 1), matrix1.getShape(0, 1));
    BOOST_CHECK_EQUAL(matrix.getShape(1, 0), matrix1.getShape(1, 0));
    BOOST_CHECK_EQUAL(matrix.getShape(0, 2), matrix1.getShape(0, 2));

  }

  BOOST_FIXTURE_TEST_CASE(Matrix_Copy_Operator_Test, PolyFixture)
  {
    sibikin::Matrix matrix;
    sibikin::Matrix matrix1{&circle,&rect};
    matrix = matrix1;

    BOOST_CHECK_EQUAL(matrix.getShape(0,0), matrix1.getShape(0,0));
    BOOST_CHECK_EQUAL(matrix.getShape(0,0), &circle);

    BOOST_CHECK_EQUAL(matrix.getShape(0,1), matrix1.getShape(0,1));
    BOOST_CHECK_EQUAL(matrix.getShape(0,1), &rect);
  }

  BOOST_FIXTURE_TEST_CASE(Copy_Constructor_Test, PolyFixture)
  {
    sibikin::Matrix matrix{&circle, &rect};
    sibikin::Matrix matrix1(matrix);

    BOOST_CHECK_EQUAL(matrix.getShape(0, 0), matrix1.getShape(0, 0));
    BOOST_CHECK_EQUAL(matrix.getShape(0, 0), &circle);

    BOOST_CHECK_EQUAL(matrix.getShape(0, 1), matrix1.getShape(0, 1));
    BOOST_CHECK_EQUAL(matrix.getShape(0, 1), &rect);
  }

  BOOST_FIXTURE_TEST_CASE(CreateMatrix_After_Rotation_Test, PolyFixture)
  {
    sibikin::Rectangle rect1({4.0, 4.0}, 4.0, 2.0);
    sibikin::Circle circle1({1.0, 1.0}, 2.0);
    sibikin::CompositeShape compShape;
    compShape.addShape(&circle1);
    compShape.addShape(&rect1);
    size_t size = 2;
    sibikin::Matrix matrix = matrix.createMatrix(compShape);
    BOOST_CHECK_EQUAL(matrix.getLayerCount(), size);
    size--;
    compShape.rotate(45.0);
    matrix = matrix.createMatrix(compShape);
    BOOST_CHECK_EQUAL(matrix.getLayerCount(), size);
  }


BOOST_AUTO_TEST_SUITE_END()



#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "matrix.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Matrix_Test)

BOOST_AUTO_TEST_CASE(Matrix_Overlapping_Test)
{
  maikenova::Circle myCircle({0.0, 0.0}, 2.0);
  maikenova::Circle myCircle1({30.0, 30.0}, 3.0);
  maikenova::Rectangle myRectangle({15.0, 15.0}, 4.0, 5.0);
  maikenova::Rectangle myRectangle1({0.0, 0.0}, 4.0, 5.0);
  maikenova::CompositeShape compShape;
  compShape.pushBack(& myCircle);
  compShape.pushBack(& myRectangle);
  maikenova::Matrix myMatrix{& myCircle, & myRectangle};
  size_t size = 3;

  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 0), & myCircle);
  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 1), & myRectangle);

  myMatrix.addShape(& compShape);
  BOOST_CHECK_EQUAL(myMatrix.getShape(1, 0), & compShape);

  myMatrix.addShape(& myRectangle1);
  BOOST_CHECK_EQUAL(myMatrix.getShape(2, 0), & myRectangle1);

  myMatrix.addShape(& myCircle1);
  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 2), & myCircle1);
  BOOST_CHECK_EQUAL(myMatrix.getLayerSize(0), size);
}

BOOST_AUTO_TEST_CASE(createMatrix_Overlapping_Test)
{
  maikenova::Circle myCircle({0.0, 0.0}, 2.0);
  maikenova::Rectangle myRectangle({15.0, 15.0}, 4.0, 5.0);
  maikenova::Rectangle myRectangle1({0.0, 0.0}, 4.0, 5.0);
  maikenova::Circle myCircle1({30.0, 30.0}, 3.0);
  maikenova::CompositeShape compShape;
  compShape.pushBack(& myCircle);
  compShape.pushBack(& myRectangle);
  compShape.pushBack(& myRectangle1);
  compShape.pushBack(& myCircle1);
  maikenova::Matrix myMatrix = myMatrix.createMatrix(compShape);
  maikenova::Matrix myMatrix1{& myCircle, & myRectangle, &myRectangle1, & myCircle1};
  
  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 0), myMatrix1.getShape(0, 0));
  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 1), myMatrix1.getShape(0, 1));
  BOOST_CHECK_EQUAL(myMatrix.getShape(1, 0), myMatrix1.getShape(1, 0));
  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 2), myMatrix1.getShape(0, 2));

}

BOOST_AUTO_TEST_CASE(createMatrix_after_rotation_Test)
{
  maikenova::Circle myCircle({1.0, 1.0}, 2.0);
  maikenova::Rectangle myRectangle({4.0, 4.0}, 4.0, 2.0);
  maikenova::CompositeShape compShape;
  compShape.pushBack(& myCircle);
  compShape.pushBack(& myRectangle);
  size_t size = 2;
  maikenova::Matrix myMatrix = myMatrix.createMatrix(compShape);
  BOOST_CHECK_EQUAL(myMatrix.getLayerNum(), size);
  size--;
  compShape.rotate(70.0);
  myMatrix = myMatrix.createMatrix(compShape);
  BOOST_CHECK_EQUAL(myMatrix.getLayerNum(), size);
}

BOOST_AUTO_TEST_CASE(matrix_Copy_Operator_Test)
{
  maikenova::Circle myCircle({0.0, 0.0}, 2.0);
  maikenova::Rectangle myRectangle({15.0, 15.0}, 4.0, 5.0);
  maikenova::Matrix myMatrix;
  maikenova::Matrix myMatrix1{& myCircle,& myRectangle};
  myMatrix = myMatrix1;

  BOOST_CHECK_EQUAL(myMatrix.getShape(0,0), myMatrix1.getShape(0,0));
  BOOST_CHECK_EQUAL(myMatrix.getShape(0,0), & myCircle);

  BOOST_CHECK_EQUAL(myMatrix.getShape(0,1), myMatrix1.getShape(0,1));
  BOOST_CHECK_EQUAL(myMatrix.getShape(0,1), & myRectangle);
}

BOOST_AUTO_TEST_CASE(Copy_Constructor_Test)
{
  maikenova::Circle myCircle({ 0.0, 0.0 }, 2.0);
  maikenova::Rectangle myRectangle({15.0, 15.0}, 4.0, 5.0);
  maikenova::Matrix myMatrix{& myCircle, & myRectangle};
  maikenova::Matrix myMatrix1(myMatrix);

  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 0), myMatrix1.getShape(0, 0));
  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 0), & myCircle);

  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 1), myMatrix1.getShape(0, 1));
  BOOST_CHECK_EQUAL(myMatrix.getShape(0, 1), & myRectangle);
}

BOOST_AUTO_TEST_SUITE_END()


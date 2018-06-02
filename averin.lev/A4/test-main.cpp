#define BOOST_TEST_MODULE mainTest
#include <stdexcept>
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace averin;

const double epsilon = 1e-3;

BOOST_AUTO_TEST_SUITE(CompositeShapeSuite)

  BOOST_AUTO_TEST_CASE(Moving)
  {
    Rectangle rec(3,3,10,15);
    CompositeShape shp(&rec);
    shp.move(30,50);
    BOOST_CHECK_CLOSE(3,shp.getFrameRect().height,epsilon);
    BOOST_CHECK_CLOSE(3,shp.getFrameRect().width,epsilon);
    BOOST_CHECK_CLOSE(3*3,shp.getArea(),epsilon);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rec(3,3,10,15);
    CompositeShape shp(&rec);
    Circle cir(10,5,7);
    shp.addShape(&cir);
    shp.scale(2);
    BOOST_CHECK_CLOSE(((3*3)+(10*10*M_PI))*2*2,shp.getArea(),epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidScaleParameters)
  {
    Rectangle rec(3,3,10,15);
    CompositeShape shp(&rec);
    BOOST_CHECK_THROW(shp.scale(-3),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW(CompositeShape shp(nullptr),std::invalid_argument );
  }
  
  BOOST_AUTO_TEST_CASE(InvalidAddParameters)
  {
    Rectangle rec(3,3,10,15);
    CompositeShape shp(&rec);
    BOOST_CHECK_THROW(shp.addShape(nullptr),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(Rotate)
  {
    Rectangle rec(3,3,10,15);
    Circle cir(3,10,15);
    CompositeShape shp(&rec);
    shp.addShape(&cir);
    shp.rotate(90);
    BOOST_CHECK_CLOSE((3*3)+(3*3*M_PI),shp.getArea(),epsilon);
  }
  
BOOST_AUTO_TEST_SUITE_END()
        
BOOST_AUTO_TEST_SUITE(MatrixSuite)

  BOOST_AUTO_TEST_CASE(Rows)
  {
    std::shared_ptr<Rectangle> rec = std::make_shared<Rectangle>(1,1,0,0);
    std::shared_ptr<Rectangle> rec2 = std::make_shared<Rectangle>(2,2,0,0);
    std::shared_ptr<Rectangle> rec3 = std::make_shared<Rectangle>(4,4,0,0);
    std::shared_ptr<Rectangle> rec4 = std::make_shared<Rectangle>(6,6,0,0);
    Matrix matrix;
    matrix.addShape(rec);
    matrix.addShape(rec2);
    matrix.addShape(rec3);
    matrix.addShape(rec4);
    BOOST_REQUIRE_EQUAL(4,matrix.getRows());
  }

  BOOST_AUTO_TEST_CASE(Columns)
  {
    std::shared_ptr<Rectangle> rec = std::make_shared<Rectangle>(1,1,1000,1000);
    std::shared_ptr<Rectangle> rec2 = std::make_shared<Rectangle>(2,2,0,0);
    Matrix matrix;
    matrix.addShape(rec);
    matrix.addShape(rec2);
    BOOST_REQUIRE_EQUAL(2,matrix.getColumns());
  }
        
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW(Matrix matrix(nullptr),std::invalid_argument );
  }
BOOST_AUTO_TEST_SUITE_END()

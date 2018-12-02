#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace kashirin;

const double dx = 0.000001;

BOOST_AUTO_TEST_SUITE(MatrixTest)

  BOOST_AUTO_TEST_CASE(MatrixSizeTest)
  {
    Rectangle rect{ 4.0, 4.0, { 2.5, 2.5} };
    Circle circ{ 1.0, { 6.0, 6.0 } };
    Triangle trian{ { 3.0, 3.0 }, { 5, 3 }, { 3, 5 } };
    Rectangle rect1{ 4.0, 4.0, { 6.0, 2.0 } };
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    std::shared_ptr< Shape > rect1Ptr = std::make_shared< Rectangle >(rect1);

    Matrix matrix(rectPtr);
    matrix.addShape(circPtr);
    matrix.addShape(trianPtr);
    matrix.addShape(rect1Ptr);

    BOOST_REQUIRE_EQUAL(matrix.getSize(), 2);
    BOOST_REQUIRE_EQUAL(matrix.getNumbers(), 3);
  }

  BOOST_AUTO_TEST_CASE(MatrixAddShapeTest)
  {
    Rectangle rect{ 4.0, 4.0, { 2.5, 2.5} };
    Circle circ{ 1.0, { 6.0, 6.0 } };
    Triangle trian{ { 3.0, 3.0 }, { 5.0, 3.0 }, { 3.0, 5.0 } };
    Rectangle rect1{ 4.0, 4.0, { 6.0, 2.0 } };
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    std::shared_ptr< Shape > rect1Ptr = std::make_shared< Rectangle >(rect1);

    Matrix matrix(rectPtr);
    matrix.addShape(circPtr);
    matrix.addShape(trianPtr);
    matrix.addShape(rect1Ptr);
    
    std::shared_ptr< Shape > layer1Shape0 = matrix[0][0];
    std::shared_ptr< Shape > layer1Shape1 = matrix[0][1];
    std::shared_ptr< Shape > layer2Shape0 = matrix[1][0];
    std::shared_ptr< Shape > layer3Shape0 = matrix[2][0];

    BOOST_REQUIRE_EQUAL(layer1Shape0, rectPtr);
    BOOST_REQUIRE_EQUAL(layer1Shape1, circPtr);
    BOOST_REQUIRE_EQUAL(layer2Shape0, trianPtr);
    BOOST_REQUIRE_EQUAL(layer3Shape0, rect1Ptr);
  }

  BOOST_AUTO_TEST_CASE(MatrixFrameRectTest)
  {
    Rectangle rect{ 4.0, 4.0, { 2.5, 2.5} };
    Circle circ{ 1.0, { 6.0, 6.0 } };
    Triangle trian{ { 3.0, 3.0 }, { 5.0, 3.0 }, { 3.0, 5.0 } };
    Rectangle rect1{ 4.0, 4.0, { 6.0, 2.0 } };
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    std::shared_ptr< Shape > rect1Ptr = std::make_shared< Rectangle >(rect1);

    Matrix matrix(rectPtr);
    matrix.addShape(circPtr);
    matrix.addShape(trianPtr);
    matrix.addShape(rect1Ptr);
    
    std::unique_ptr< std::shared_ptr< Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< Shape >[] > layer3 = matrix[2];

    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, 2.5, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, 2.5, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().height, 4, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().width, 4, dx);

    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.x, 6, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.y, 6, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().height, 2, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().width, 2, dx);

    BOOST_CHECK_CLOSE_FRACTION(layer3[0]->getFrameRect().pos.x, 6, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer3[0]->getFrameRect().pos.y, 2, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer3[0]->getFrameRect().height, 4, dx);
    BOOST_CHECK_CLOSE_FRACTION(layer3[0]->getFrameRect().width, 4, dx);
  }

  BOOST_AUTO_TEST_CASE(MatrixCopyConstTest)
  {
    Rectangle rect{ 4.0, 4.0, { 2.5, 2.5} };
    Circle circ{ 1.0, { 6.0, 6.0 } };
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);

    Matrix matrix(rectPtr);
    matrix.addShape(circPtr);

    Matrix matrix1(matrix);

    std::unique_ptr< std::shared_ptr< Shape >[] > layer1 = matrix1[0];
    BOOST_CHECK(layer1[0] == rectPtr);
    BOOST_CHECK(layer1[1] == circPtr);
    BOOST_REQUIRE_EQUAL(matrix1.getSize(), 2);
    BOOST_REQUIRE_EQUAL(matrix1.getNumbers(), 1);
  }

  BOOST_AUTO_TEST_CASE(MatrixCopyOperTest)
  {
    Rectangle rect{ 4, 4, { 2.5, 2.5} };
    Circle circ{ 1.0, { 6.0, 6.0 } };
    Circle circ1{ 2.0, { 6.0, 6.0 } };
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > circ1Ptr = std::make_shared< Circle >(circ1);

    Matrix matrix(rectPtr);
    matrix.addShape(circPtr);

    Matrix matrix1(circ1Ptr);
    
    matrix1 = matrix;

    std::unique_ptr< std::shared_ptr< Shape >[] > layer1 = matrix1[0];
    BOOST_CHECK(layer1[0] == rectPtr);
    BOOST_CHECK(layer1[1] == circPtr);
    BOOST_REQUIRE_EQUAL(matrix1.getSize(), 2);
    BOOST_REQUIRE_EQUAL(matrix1.getNumbers(), 1);
  }

  BOOST_AUTO_TEST_CASE(MatrixMoveConstTest)
  {
    Rectangle rect{ 4.0, 4.0, { 2.5, 2.5} };
    Circle circ{ 1.0, { 6.0, 6.0 } };
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);

    Matrix matrix(rectPtr);
    matrix.addShape(circPtr);

    Matrix matrix1(std::move(matrix));

    std::unique_ptr< std::shared_ptr< Shape >[] > layer1 = matrix1[0];
    BOOST_CHECK(layer1[0] == rectPtr);
    BOOST_CHECK(layer1[1] == circPtr);
    BOOST_REQUIRE_EQUAL(matrix.getSize(), 0);
    BOOST_REQUIRE_EQUAL(matrix.getNumbers(), 0);
    BOOST_REQUIRE_EQUAL(matrix1.getSize(), 2);
    BOOST_REQUIRE_EQUAL(matrix1.getNumbers(), 1);
  }

  BOOST_AUTO_TEST_CASE(MatrixMoveOperTest)
  {
    Rectangle rect{ 4.0, 4.0, { 2.5, 2.5} };
    Circle circ{ 1.0, { 6.0, 6.0 } };
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);

    Matrix matrix(rectPtr);
    matrix.addShape(circPtr);

    Matrix matrix1(circPtr);
    matrix1 = std::move(matrix);

    std::unique_ptr< std::shared_ptr< Shape >[] > layer1 = matrix1[0];
    BOOST_CHECK(layer1[0] == rectPtr);
    BOOST_CHECK(layer1[1] == circPtr);
    BOOST_REQUIRE_EQUAL(matrix.getSize(), 0);
    BOOST_REQUIRE_EQUAL(matrix.getNumbers(), 0);
    BOOST_REQUIRE_EQUAL(matrix1.getSize(), 2);
    BOOST_REQUIRE_EQUAL(matrix1.getNumbers(), 1);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testRect)

  BOOST_AUTO_TEST_CASE(testRectMove1)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    rect.move({ 11.3, 0.7 });
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, 11.3);
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, 0.7);
  }

  BOOST_AUTO_TEST_CASE(testRectMove2)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    rect.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.x, 18.5, dx);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.y, 8.5, dx);
  }

  BOOST_AUTO_TEST_CASE(testRectMoveWidth)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    rect.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().width, 5.3, dx);
  }

  BOOST_AUTO_TEST_CASE(testRectMoveHeight)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    rect.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().height, 6.9, dx);
  }

  BOOST_AUTO_TEST_CASE(testRectMoveArea)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    double area = rect.getArea();
    rect.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(area, rect.getArea(), dx);
  }

 BOOST_AUTO_TEST_CASE(testRectScale)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    double area = rect.getArea();
    rect.scale(2.5);
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), area * 2.5 * 2.5, dx);
  }

  BOOST_AUTO_TEST_CASE(RectRotateTest)
  {
    Rectangle rect(5.0, 10.0, { 3.0, 3.0 });
    const double area = rect.getArea(); 
    rect.rotate(44);
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), area, dx);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.x, 3.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.y, 3.0, dx);
  }

  BOOST_AUTO_TEST_CASE(testRectInit)
  {
    BOOST_CHECK_THROW(Rectangle rect1(-1.0, 3.0, { 3.0, 3.0 }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rect2(1.0, -3.0, { 3.0, 3.0 }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rect3(-1, -3, { 3.0, 3.0 }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rect4(0.0, 3.0, { 3.0, 3.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(testInitScale)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    BOOST_CHECK_THROW(rect.scale(-5), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(testCirc)

  BOOST_AUTO_TEST_CASE(testCircMove1)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    circ.move({ 11.3, 0.7 });
    BOOST_CHECK_EQUAL(circ.getFrameRect().pos.x, 11.3);
    BOOST_CHECK_EQUAL(circ.getFrameRect().pos.y, 0.7);
  }

  BOOST_AUTO_TEST_CASE(testCircMove2)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    circ.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.x, 19.1, dx);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.y, 7.0, dx);
  }

  BOOST_AUTO_TEST_CASE(testCircMoveRadius)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    circ.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().width/2, 5.0, dx);
  }

  BOOST_AUTO_TEST_CASE(testCircMoveArea)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    double area = circ.getArea();
    circ.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(area, circ.getArea(), dx);
  }

 BOOST_AUTO_TEST_CASE(testCircScaleArea)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    double area = circ.getArea();
    circ.scale(2.5);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), area * 2.5 * 2.5, dx);
  }

  BOOST_AUTO_TEST_CASE(CircRotateTest)
  {
    Circle circ(5.0, { 3.0, 3.0 });
    const double area = circ.getArea(); 
    circ.rotate(44);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), area, dx);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.x, 3.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.y, 3.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().width, 10.0, dx);
  }

  BOOST_AUTO_TEST_CASE(testCircInit)
  {
    BOOST_CHECK_THROW(Circle circ1(-1.0, { 3.0, 3.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(testCircInitScale)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    BOOST_CHECK_THROW(circ.scale(-5.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(CompositeShapeMove1Test)
  {
    Triangle trian({ 0.0, 0.0 }, { 4.0, 0.0 }, { 0.0, 2.0 });
    Circle circ(1.0, { 0.0, 0.0 });
    Rectangle rect(2.0, 4.0, { 1.0, 1.0 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    comp.move({ 1.0, 1.0 });
    BOOST_CHECK_CLOSE_FRACTION(comp.getArea(),circ.getArea() + rect.getArea() + trian.getArea(), dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.x, 1.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.y, 1.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().width, 5.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().height, 4.0, dx);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeMove2Test)
  {
    Triangle trian({ 0.0, 0.0 }, { 4.0, 0.0 }, { 0.0, 2.0 });
    Circle circ(1.0, { 0.0, 0.0});
    Rectangle rect(2.0, 4.0, { 1.0, 1.0 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    comp.move(5.5, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(comp.getArea(),circ.getArea() + rect.getArea() + trian.getArea(), dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.x, 7.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.y, 4.0, dx);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeScaleTest)
  {
    Triangle trian({ 0.0, 0.0 }, { 4.0, 0.0 }, { 0.0, 2.0 });
    Circle circ(1.0, { 0.0, 0.0});
    Rectangle rect(2.0, 4.0, { 1.0, 1.0 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    point_t center = comp.getFrameRect().pos;
    comp.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(comp.getArea(),(circ.getArea() + rect.getArea() + trian.getArea()) * 4.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.x, center.x, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.y, center.y, dx);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRemoveFigureTest)
  {
    Triangle trian({ 0.0, 0.0 }, { 4.0, 0.0 }, { 0.0, 2.0 });
    Circle circ(1.0, { 0.0, 0.0});
    Rectangle rect(2.0, 4.0, { 1.0, 1.0 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    comp.removeFigure(2);
    BOOST_CHECK_EQUAL(comp.getCount(), 2.0);
    BOOST_CHECK_EQUAL(comp.getArea(), rect.getArea() + trian.getArea());
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.y, 1.0);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRemoveAllTest)
  {
    Triangle trian({ 0.0, 0.0 }, { 4.0, 0.0 }, { 0.0, 2.0 });
    Circle circ(1.0, { 0.0, 0.0});
    Rectangle rect(2.0, 4.0, { 1.0, 1.0 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    comp.removeAll();
    BOOST_CHECK_EQUAL(comp.getCount(), 0.0);
    BOOST_CHECK_EQUAL(comp.getArea(), 0.0);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeScaleInvalidTest)
  {
    Triangle trian({ 0.0, 0.0 }, { 4.0, 0.0 }, { 0.0, 2.0 });
    Circle circ(1.0, { 0.0, 0.0});
    Rectangle rect(2.0, 4.0, { 1.0, 1.0 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    BOOST_CHECK_THROW(comp.scale(-2), std::invalid_argument);
    BOOST_CHECK_THROW(comp.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRemoveInvalidTest)
  {
    Triangle trian({ 0.0, 0.0 }, { 4.0, 0.0 }, { 0.0, 2.0 });
    Circle circ(1.0, { 0.0, 0.0});
    Rectangle rect(2.0, 4.0, { 1.0, 1.0 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    BOOST_CHECK_THROW(comp.removeFigure(11.0), std::out_of_range);
    BOOST_CHECK_THROW(comp.removeFigure(-1.0), std::out_of_range);
    comp.removeAll();
    BOOST_CHECK_THROW(comp.removeFigure(1.0), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeAddShapeInvalidTest)
  {
    Triangle trian({ 0.0, 0.0 }, { 4.0, 0.0 }, { 0.0, 2.0 });
    Circle circ(1.0, { 0.0, 0.0});
    Rectangle rect(2.0, 4.0, { 1.0, 1.0 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    BOOST_CHECK_THROW(comp.addShape(rectPtr), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testTrian)

  BOOST_AUTO_TEST_CASE(testTrianMove1)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 2.0, 4.0 });
    trian.move({ 11.3, 0.7 });
    BOOST_CHECK_EQUAL(trian.getCenter().x, 11.3);
    BOOST_CHECK_EQUAL(trian.getCenter().y, 0.7);
  }

  BOOST_AUTO_TEST_CASE(testTrianMove2)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 3.0, 6.0 });
    rectangle_t frame = trian.getFrameRect();
    trian.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(trian.getCenter().x, 21.1, dx);
    BOOST_CHECK_CLOSE_FRACTION(trian.getCenter().y, 9.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(trian.getFrameRect().width, frame.width, dx);
    BOOST_CHECK_CLOSE_FRACTION(trian.getFrameRect().height, frame.height, dx);
  }

  BOOST_AUTO_TEST_CASE(testTrianMoveArea)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 2.0, 4.0 });
    double area = trian.getArea();
    trian.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(area, trian.getArea(), dx);
  }

 BOOST_AUTO_TEST_CASE(testTrianScaleArea)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 2.0, 4.0 });
    double area = trian.getArea();
    trian.scale(2.5);
    BOOST_CHECK_CLOSE_FRACTION(trian.getArea(), area * 2.5 * 2.5, dx);
  }

  BOOST_AUTO_TEST_CASE(TrianRotateTest)
  {
    Triangle trian({ 5.0 , 10.0 }, { 0.0, 10.0 }, { 3.0, 3.0 });
    const double area = trian.getArea();
    const point_t center = trian.getCenter();
    trian.rotate(44.0);
    BOOST_CHECK_CLOSE_FRACTION(trian.getArea(), area, dx);
    BOOST_CHECK_CLOSE_FRACTION(trian.getCenter().x, center.x, dx);
    BOOST_CHECK_CLOSE_FRACTION(trian.getCenter().y, center.y, dx);
  }

  BOOST_AUTO_TEST_CASE(testTrianInitScale)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 2.0, 4.0 });
    BOOST_CHECK_THROW(trian.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(testTrianInit)
  {
    BOOST_CHECK_THROW(Triangle trian({ 1.0, 3.0 }, { 1.0, 3.0 }, { 1.0, 4.0 }), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

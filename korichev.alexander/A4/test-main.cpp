#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

using namespace korichev;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double h_before = test_rect.getFrameRect().height;
    double w_before = test_rect.getFrameRect().width;
    double a_before = test_rect.getArea();
    test_rect.move({2.0, 3.0});
    BOOST_CHECK_EQUAL(test_rect.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(test_rect.getFrameRect().pos.y, 3.0);
    BOOST_CHECK_EQUAL(a_before, test_rect.getArea());
    BOOST_CHECK_EQUAL(h_before, test_rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_rect.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(MoveByXY)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double h_before = test_rect.getFrameRect().height;
    double w_before = test_rect.getFrameRect().width;
    double a_before = test_rect.getArea();
    test_rect.move(2.0, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(test_rect.getFrameRect().pos.x, 5.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test_rect.getFrameRect().pos.y, 5.0, EPSILON);
    BOOST_CHECK_EQUAL(a_before, test_rect.getArea());
    BOOST_CHECK_EQUAL(h_before, test_rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_rect.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    BOOST_CHECK_THROW(test_rect.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Rectangle test_rect({3.0, 2.0}, 4.0, 5.0);
    double a_before = test_rect.getArea();
    test_rect.scale(3.0);
    BOOST_CHECK_CLOSE_FRACTION(3.0 * 3.0 * a_before, test_rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidInit)
  {
    BOOST_CHECK_THROW(Rectangle({3.0, 2.0}, 10.0, -10.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({3.0, 2.0}, -10.0, 10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double h_before = test_circle.getFrameRect().height;
    double w_before = test_circle.getFrameRect().width;
    double a_before = test_circle.getArea();
    test_circle.move({2.0, 3.0});
    BOOST_CHECK_EQUAL(test_circle.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(test_circle.getFrameRect().pos.y, 3.0);
    BOOST_CHECK_EQUAL(a_before, test_circle.getArea());
    BOOST_CHECK_EQUAL(h_before, test_circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_circle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(MoveByXY)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double h_before = test_circle.getFrameRect().height;
    double w_before = test_circle.getFrameRect().width;
    double a_before = test_circle.getArea();
    test_circle.move(2.0, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(test_circle.getFrameRect().pos.x, 5.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test_circle.getFrameRect().pos.y, 5.0, EPSILON);
    BOOST_CHECK_EQUAL(a_before, test_circle.getArea());
    BOOST_CHECK_EQUAL(h_before, test_circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(w_before, test_circle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    BOOST_CHECK_THROW(test_circle.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Circle test_circle({3.0, 2.0}, 4.0);
    double a_before = test_circle.getArea();
    test_circle.scale(3.0);
    BOOST_CHECK_CLOSE_FRACTION(3.0 * 3.0 * a_before, test_circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidInit)
  {
    BOOST_CHECK_THROW(Circle({3.0, 2.0}, -10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.move({10, 5});
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 10, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 5, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(MoveByXY)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.move(-2, 3);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 1.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 6.0, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(AreaTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    BOOST_CHECK_EQUAL(cs.getArea(), 3);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(AreaTestMoveByXY)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.move(5, 5);
    BOOST_CHECK_EQUAL(cs.getArea(), 3);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(CheckListSize)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    BOOST_CHECK_EQUAL(cs.getListSize(), 3);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(FrameRectTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 3.0, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(ScaleAreaTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(cs.getArea(), 48, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(FrameRectScaleTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.scale(2);

    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 8.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 8.0, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(RemoveElementTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.dispose(0);
    BOOST_REQUIRE_EQUAL(cs.getListSize(), 2);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.x, 3.5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().pos.y, 3.5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().width, 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(cs.getFrameRect().height, 2, EPSILON);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(OperatorTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    CompositeShape shape;
    shape = cs;
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, 3, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, 3, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 3, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 3, EPSILON);
    cs.clean();
    shape.clean();
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    BOOST_CHECK_THROW(cs.scale(-1), std::invalid_argument);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(InvalidRemoveTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    BOOST_CHECK_THROW(cs.dispose(2), std::invalid_argument);
    cs.clean();
  }

  BOOST_AUTO_TEST_CASE(CleanTest)
  {
    Rectangle rectangle1({2.0, 2.0} ,1, 1);
    Rectangle rectangle2({3.0, 3.0} ,1, 1);
    Rectangle rectangle3({4.0, 4.0} ,1, 1);
    CompositeShape cs;
    cs.add(std::make_shared< korichev::Rectangle> (rectangle1));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle2));
    cs.add(std::make_shared< korichev::Rectangle> (rectangle3));
    cs.clean();

    BOOST_CHECK_EQUAL(cs.getListSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(Add_Nullptr_Invalid_Argument_Error_Test_CS)
  {
    CompositeShape cs;
    BOOST_CHECK_THROW(cs.add(nullptr), std::invalid_argument);
    cs.clean();
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( A4rotateMatrix)

  BOOST_AUTO_TEST_CASE( RotateRectangle )
  {
    std::shared_ptr<korichev::Shape> rectangle( new Rectangle( { 0, 0 }, 5, 5 ) );

    rectangle_t orig_frame = rectangle->getFrameRect();
    double orig_area = rectangle->getArea();

    rectangle->rotate( 170 );

    BOOST_CHECK_CLOSE_FRACTION( orig_area, rectangle->getArea(), EPSILON );
    BOOST_CHECK_CLOSE_FRACTION( rectangle->getFrameRect().pos.x, orig_frame.pos.x, EPSILON );
    BOOST_CHECK_CLOSE_FRACTION( rectangle->getFrameRect().pos.y, orig_frame.pos.y, EPSILON );
  }

  BOOST_AUTO_TEST_CASE( RotateComposite )
  {
    std::shared_ptr<korichev::Shape> rect1(  new Rectangle( { 10, 10 }, 1, 1 ) );
    std::shared_ptr<korichev::Shape> rect2( new Rectangle( { -10, -10 }, 1, 1 ) );

    CompositeShape cs;
    cs.add( rect1 );
    cs.add( rect2 );

    rectangle_t orig_frame = cs.getFrameRect();
    double orig_area = cs.getArea();

    BOOST_CHECK_CLOSE_FRACTION( cs.getFrameRect().pos.x, 0.0, EPSILON );
    BOOST_CHECK_CLOSE_FRACTION( cs.getFrameRect().pos.y, 0.0, EPSILON );

    cs.rotate( 45 );

    BOOST_CHECK_CLOSE_FRACTION( orig_area, cs.getArea(), EPSILON );
    BOOST_CHECK_CLOSE_FRACTION( cs.getFrameRect().pos.x, orig_frame.pos.x, EPSILON );
    BOOST_CHECK_CLOSE_FRACTION( cs.getFrameRect().pos.y, orig_frame.pos.y, EPSILON );

    cs.rotate( -45 );

    BOOST_CHECK_CLOSE_FRACTION( cs.getFrameRect().width, orig_frame.width, EPSILON );
    BOOST_CHECK_CLOSE_FRACTION( cs.getFrameRect().height, orig_frame.height, EPSILON );

    cs.clean();
  }

  BOOST_AUTO_TEST_CASE( MatrixTest )
  {
    CompositeShape compositeshape;
    Matrix matrix;

    std::shared_ptr< korichev::Shape > rectangle1(new Rectangle(  { 1, 1 }, 6, 6  ) );
    std::shared_ptr< korichev::Shape > rectangle2(new Rectangle(  { 3, 3 }, 2, 2  ) );
    std::shared_ptr< korichev::Shape > rectangle3(new Rectangle(  { 7, 7 }, 1, 1  ) );
    std::shared_ptr< korichev::Shape > rectangle4(new Rectangle(  { 15 , 15 }, 6, 6 ));

    compositeshape.add( rectangle1 );
    compositeshape.add( rectangle2 );
    compositeshape.add( rectangle3 );
    compositeshape.add( rectangle4 );

    matrix = compositeshape.getMatrix();

    BOOST_REQUIRE(matrix[0][0] == rectangle1 );
    BOOST_REQUIRE(matrix[1][0] == rectangle2 );
    BOOST_REQUIRE(matrix[0][1] == rectangle3 );
    BOOST_REQUIRE(matrix[0][2] == rectangle4 );

    matrix.clear();
  }
  BOOST_AUTO_TEST_CASE( MatrixAndRotation )
  {
    Matrix matrix;
    CompositeShape compositeshape;

    std::shared_ptr< Shape > rectangle1(new Rectangle(  { 1, 1 }, 1, 1  ) );
    std::shared_ptr< Shape > rectangle2(new Rectangle(  { 3, 1 }, 1, 8  ) );

    compositeshape.add( rectangle1 );
    compositeshape.add( rectangle2 );

    matrix = compositeshape.getMatrix();

    BOOST_REQUIRE(matrix[0][0] == rectangle1 );
    BOOST_REQUIRE(matrix[1][0] == rectangle2 );

    rectangle2->rotate( 90 );

    matrix = compositeshape.getMatrix();

    BOOST_REQUIRE(matrix[0][0] == rectangle1 );
    BOOST_REQUIRE(matrix[0][1] == rectangle2 );
  }
  BOOST_AUTO_TEST_CASE( MatrixShifting )
  {
    Matrix matrix1;
    Matrix matrix2;
    CompositeShape compositeshape;

    std::shared_ptr<Shape> rectangle1( new Rectangle(  { 1, 1 }, 1, 1  ) );
    std::shared_ptr<Shape> rectangle2( new Rectangle(  { 3, 1 }, 1, 8  ) );

    compositeshape.add( rectangle1 );
    compositeshape.add( rectangle2 );

    matrix1 = compositeshape.getMatrix();

    compositeshape.move( 4, 4 );

    matrix2 = compositeshape.getMatrix();

    BOOST_REQUIRE(matrix2[0][0] == rectangle1 );
    BOOST_REQUIRE(matrix2[1][0] == rectangle2 );
  }
  BOOST_AUTO_TEST_CASE( MatrixCheck )
  {
    std::shared_ptr< Shape > rectangle1(new Rectangle(  { 1, 1 }, 1, 1  ) );
    std::shared_ptr< Shape > circle2( new Circle( { 9, 9 }, 2 ) );
    std::shared_ptr< Shape > rectangle3( new Rectangle(  { 1, 1 },2,2  ) );
    std::shared_ptr< Shape > circle4( new Circle( { -9, -9 }, 2) );

    CompositeShape compositeshape;
    std::shared_ptr< CompositeShape > compositeshape1(new CompositeShape);
    std::shared_ptr< CompositeShape > compositeshape2(new CompositeShape);
    Matrix matrix;
    compositeshape1->add(circle2);
    compositeshape2->add(compositeshape1);

    compositeshape.add(rectangle1);
    compositeshape.add(compositeshape2);
    compositeshape.add(rectangle3);
    compositeshape.add(circle4);

    matrix = compositeshape.getMatrix();

    BOOST_REQUIRE( matrix[0][0] == rectangle1 );
    BOOST_REQUIRE( matrix[0][1] == compositeshape2 );
    BOOST_REQUIRE( matrix[0][2] == circle4 );
    BOOST_REQUIRE( matrix[1][0] == rectangle3 );
  }
  BOOST_AUTO_TEST_CASE( MatrixAddElement )
  {
    std::shared_ptr< Shape > rectangle1(new Rectangle( { 5, 5 }, 1, 1 ) );
    std::shared_ptr< Shape > rectangle2(new Rectangle( { 1, 1 }, 2, 2 ) );
    std::shared_ptr< Shape > rectangle3(new Rectangle( { 1, 1 }, 2, 2 ) );

    CompositeShape compositeshape;
    compositeshape.add( rectangle1 );
    compositeshape.add( rectangle2 );
    Matrix matrix;
    matrix = compositeshape.getMatrix();

    matrix.add(rectangle3);

    BOOST_REQUIRE( matrix[0][0] == rectangle1);
    BOOST_REQUIRE( matrix[0][1] == rectangle2);
    BOOST_REQUIRE( matrix[1][0] == rectangle3);


  }

BOOST_AUTO_TEST_SUITE_END()

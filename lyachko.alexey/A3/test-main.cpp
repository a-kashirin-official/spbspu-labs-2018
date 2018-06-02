#define BOOST_TEST_MAIN
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double EPSILON = 0.0001;


BOOST_AUTO_TEST_SUITE( CompositeShape_test )

BOOST_AUTO_TEST_CASE( Invalid_Cmp_Constructor )
{
  lyachko::Shape * shape = nullptr;
  BOOST_CHECK_THROW( lyachko::CompositeShape compositeshape( shape ), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( MoveTo )
{
  lyachko::point_t cmp_original_coord = { 1, 1 };
  lyachko::point_t new_coord = { 4, 4 };

  lyachko::Rectangle rectangle( { cmp_original_coord, 3, 3 } );
  lyachko::CompositeShape compositeshape( &rectangle );

  double cmp_original_area = compositeshape.getArea();
  double cmp_original_width = compositeshape.getFrameRect().width;
  double cmp_original_height = compositeshape.getFrameRect().height;

  compositeshape.move( new_coord );

  BOOST_CHECK_CLOSE_FRACTION( cmp_original_area, compositeshape.getArea(), EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().pos.x, new_coord.x, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().pos.y, new_coord.y, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, cmp_original_width, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, cmp_original_height, EPSILON );
}

BOOST_AUTO_TEST_CASE( ShiftBy )
{
  lyachko::point_t cmp_original_coord = {1,1};
  double dx = 3;
  double dy = 3;

  lyachko::Rectangle rectangle( { cmp_original_coord, 3, 3 } );
  lyachko::CompositeShape compositeshape( &rectangle );

  double cmp_original_area = compositeshape.getArea();
  double cmp_original_width = compositeshape.getFrameRect().width;
  double cmp_original_height = compositeshape.getFrameRect().height;

  compositeshape.move( 3, 3 );

  BOOST_CHECK_CLOSE_FRACTION( cmp_original_area, compositeshape.getArea(), EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().pos.x, cmp_original_coord.x + dx, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().pos.y, cmp_original_coord.y + dy, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, cmp_original_width, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, cmp_original_height, EPSILON );
}

BOOST_AUTO_TEST_CASE(  Scale  )
{
  double scale_coef = -1.0;
  lyachko::point_t cmp_original_coord = { 1, 1 };

  lyachko::Rectangle rectangle( { cmp_original_coord, 3, 3 } );
  lyachko::CompositeShape compositeshape( &rectangle );

  double cmp_original_area = compositeshape.getArea();
  double cmp_original_width = compositeshape.getFrameRect().width;
  double cmp_original_height = compositeshape.getFrameRect().height;

  BOOST_CHECK_THROW( compositeshape.scale( scale_coef ), std::invalid_argument );

  scale_coef = 2.0; 

  compositeshape.scale( scale_coef );

  BOOST_CHECK_CLOSE_FRACTION( cmp_original_area * scale_coef * scale_coef, compositeshape.getArea(), EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().pos.x, cmp_original_coord.x, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().pos.y, cmp_original_coord.y, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, cmp_original_width * scale_coef, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, cmp_original_height * scale_coef, EPSILON );
}

BOOST_AUTO_TEST_CASE( Add ) //Note that this test does not work correctly with areas crossing each other forming one single area
{
  lyachko::Rectangle rectangle( { { 0, 0 }, 2, 2 } );
  lyachko::Circle circle1( { 4, 4 }, 1 );

  lyachko::Circle circle2( { -1, -1 }, 0 ); //two of these points form a rectangle 10 x 10
  lyachko::Circle circle3( { 9, 9 }, 0 );

  lyachko::CompositeShape compositeshape( &rectangle );

  double r_area = rectangle.getArea();
  double c_area = circle1.getArea();

  compositeshape.add( &circle1 );

  BOOST_CHECK_CLOSE_FRACTION( c_area + r_area, compositeshape.getArea(), EPSILON );

  compositeshape.add( &circle2 );
  compositeshape.add( &circle3 );

  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, 10.0, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, 10.0, EPSILON );

}

BOOST_AUTO_TEST_CASE( Remove ) //Note that this test does not work correctly with areas crossing each other forming one single area
{
  lyachko::Circle circle1( { 0, 0 }, 0 );//Two points form a square 10 x 10, and there is a crciel inside with its own area;
  lyachko::Circle circle2( { 3, 3 }, 1 );//Smallers squares should be 4 x 4 and 7 x 7;
  lyachko::Circle circle3( { 9, 9 }, 0 );//Bigger one 9 x 9. Lets check that.
  
  lyachko::CompositeShape compositeshape( &circle1 );

  BOOST_CHECK_CLOSE_FRACTION( circle1.getArea(), compositeshape.getArea(), EPSILON );

  compositeshape.add( &circle2 );

  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, 4.0, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, 4.0, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( circle1.getArea() + circle2.getArea(), compositeshape.getArea(), EPSILON );

  compositeshape.add( &circle3 );

  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, 9.0, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, 9.0, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( circle1.getArea() + circle2.getArea() + circle3.getArea(), compositeshape.getArea(), EPSILON );

  compositeshape.remove( 1 );

  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, 7.0, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, 7.0, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( circle3.getArea() + circle2.getArea(), compositeshape.getArea(), EPSILON );

  compositeshape.remove( 2 );

  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, circle2.getFrameRect().width, EPSILON  );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, circle2.getFrameRect().height, EPSILON  );
  BOOST_CHECK_CLOSE_FRACTION( circle2.getArea(), compositeshape.getArea(), EPSILON );

}

BOOST_AUTO_TEST_CASE( Shapecompositeshape )//Lets check if changing included shapes changes CompositeShape
{
  lyachko::Circle circle( { 0, 0 }, 1 );
  lyachko::CompositeShape compositeshape( &circle );
  circle.scale( 2 ); 

  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().width, circle.getFrameRect().width, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( compositeshape.getFrameRect().height, circle.getFrameRect().height, EPSILON );
  BOOST_CHECK_CLOSE_FRACTION( circle.getArea(), compositeshape.getArea(), EPSILON );

}

BOOST_AUTO_TEST_SUITE_END()

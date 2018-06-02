//
// Created by Yaroslav on 13.04.2018.
//

#define BOOST_TEST_MODULE testmain
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

erokhin::Rectangle rect({7, 17}, 3.7, 5.3);
erokhin:: point_t pos{45, 36};
const double dx = 0.000001;

BOOST_AUTO_TEST_SUITE(testRectangle)
    BOOST_AUTO_TEST_CASE(test_Rect_move1)
    {
        rect.move(13, 13);
        BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, 20);
        BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, 30);
    }
    BOOST_AUTO_TEST_CASE(test_Rect_move2)
    {
        rect.move(pos);
        BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, 45);
        BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, 36);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_move_width)
    {
        rect.move(13, 13);
        BOOST_CHECK_EQUAL(rect.getFrameRect().width, 3.7);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_move_height)
    {
        rect.move(13, 13);
        BOOST_CHECK_EQUAL(rect.getFrameRect().height, 5.3);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_move_area)
    {
        double area = rect.getArea();
        rect.move(pos);
        BOOST_CHECK_CLOSE_FRACTION(area, rect.getArea(), dx);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_scale_area)
    {
        double area = rect.getArea();
        rect.scale(6.7);
        BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), area * 6.7 * 6.7, dx);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_init_exception)
    {
        BOOST_CHECK_THROW(erokhin::Rectangle rect1({7, 7}, -3, 7), std::invalid_argument);
        BOOST_CHECK_THROW(erokhin::Rectangle rect2({7, 7}, 3, -7), std::invalid_argument);
        BOOST_CHECK_THROW(erokhin::Rectangle rect3({7, 7}, -3, -7), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_scale_exception)
    {
        BOOST_CHECK_THROW(rect.scale(-58), std::invalid_argument);
    }
BOOST_AUTO_TEST_SUITE_END();

erokhin::Circle circ({7, 7}, 3.7);

BOOST_AUTO_TEST_SUITE(testCircle)
    BOOST_AUTO_TEST_CASE(test_Circ_move_width)
    {
        circ.move(13, 13);
        BOOST_CHECK_EQUAL(circ.getFrameRect().width/2, 3.7);
    }

    BOOST_AUTO_TEST_CASE(test_Circ_move_area)
    {
        double area = circ.getArea();
        circ.move(pos);
        BOOST_CHECK_CLOSE_FRACTION(area, circ.getArea(), dx);
    }

    BOOST_AUTO_TEST_CASE(test_Circ_scale_area)
    {
        double area = circ.getArea();
        circ.scale(6.7);
        BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), area * 6.7 * 6.7, dx);
    }

    BOOST_AUTO_TEST_CASE(test_Circ_init_exception)
    {
        BOOST_CHECK_THROW(erokhin::Circle circ1({7, 7}, -3), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(test_circ_scale_exception)
    {
        BOOST_CHECK_THROW(circ.scale(-58), std::invalid_argument);
    }
BOOST_AUTO_TEST_SUITE_END()

//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <mml/mml.hh>

#define BOOST_TEST_MODULE Polygon
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  int next()
  {
    return sqrt(rand()) / 5;
  }

  typedef mml::Shape<mml::Num> Shape;
  typedef mml::Point<mml::Num> Point;
  typedef mml::Point<mml::Num> Vector;
  typedef mml::Rect<mml::Num> Rect;
  typedef mml::Polygon<mml::Num> Polygon;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(t0)
{
  srand(time(0));

  Point p0(next(), next());
  Point p1(next(), next());
  Point p2(next(), next());
  Point p3(next(), next());

  Polygon pp0;
  Polygon pp1(Shape::tetragon(p0, p1, p2, p3));
  Polygon pp2(pp1);

  BOOST_REQUIRE_EQUAL(pp0, Polygon());
  BOOST_REQUIRE_EQUAL(pp1, Shape::tetragon(p0, p1, p2, p3));
  BOOST_REQUIRE_EQUAL(pp2, pp1);

  BOOST_REQUIRE_EQUAL(pp0.size(), 0);
  BOOST_REQUIRE_EQUAL(pp1.size(), 4);
  BOOST_REQUIRE_EQUAL(pp2.size(), 4);
}

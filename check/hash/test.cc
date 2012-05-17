//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <mml/mml.hh>

#define BOOST_TEST_MODULE Hash
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  typedef mml::Shape<mml::Num> Shape;
  typedef mml::Point<mml::Num> Point;
  typedef mml::Line<mml::Num> Line;
  typedef mml::Rect<mml::Num> Rect;
  typedef mml::Polygon<mml::Num> Polygon;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(Hash_00)
{
  Shape p0 = Point(0, 0);
  Shape p1 = Point(1, 1);
  boost::hash<Shape> bh;

  BOOST_REQUIRE(bh(p0) != bh(p1));
  BOOST_REQUIRE(bh(p0) == bh(p0));
}

BOOST_AUTO_TEST_CASE(Hash_01)
{
  Point p0(0, 0);
  Point p1(1, 1);
  boost::hash<Point> bh;

  BOOST_REQUIRE(bh(p0) != bh(p1));
  BOOST_REQUIRE(bh(p0) == bh(p0));
}

BOOST_AUTO_TEST_CASE(Hash_02)
{
  Point p0(0, 0);
  Point p1(1, 1);
  Line l0(p0, p1);
  Line l1(p1, p0);
  boost::hash<Line> bh;

  BOOST_REQUIRE(bh(l0) != bh(l1));
  BOOST_REQUIRE(bh(l0) == bh(l0));
}

BOOST_AUTO_TEST_CASE(Hash_03)
{
  Point p0(0, 0);
  Point p1(1, 1);
  Point p2(2, 2);
  Rect r0(p0, p1);
  Rect r1(p0, p2);
  boost::hash<Rect> bh;

  BOOST_REQUIRE(bh(r0) != bh(r1));
  BOOST_REQUIRE(bh(r0) == bh(r0));
}

BOOST_AUTO_TEST_CASE(Hash_04)
{
  Point p0(0, 0);
  Point p1(1, 1);
  Point p2(2, 2);
  Polygon q0 = Shape::triangle(p0, p1, p2);
  Polygon q1 = Shape::triangle(p1, p2, p0);
  boost::hash<Polygon> bh;

  BOOST_REQUIRE(bh(q0) != bh(q1));
  BOOST_REQUIRE(bh(q0) == bh(q0));
}

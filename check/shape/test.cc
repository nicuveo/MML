//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <nauths/mml/shapes.hh>
#include <nauths/mml/tools.hh>
#include <nauths/mml/io.hh>

#define BOOST_TEST_MODULE Shape
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

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

// TODO debug::shape: check operations work when nearing INT_MAX



// shape: empty

BOOST_AUTO_TEST_CASE(EMPTY)
{
  Shape s0;

  BOOST_REQUIRE_EQUAL(s0.type(), mml::shape::EMPTY);
}



// shape: point

BOOST_AUTO_TEST_CASE(POINT)
{
  Shape s0(Point(next(), next()));
  Shape s1(s0);

  BOOST_REQUIRE_EQUAL(s0.type(), mml::shape::POINT);
  BOOST_REQUIRE_EQUAL(s1.type(), mml::shape::POINT);
  BOOST_REQUIRE_EQUAL(s0, s1);

  BOOST_REQUIRE_EQUAL(s0.center(), s0.point());

  int dx = next();
  int dy = next();

  s0.move_of(Vector(dx, dy));
  BOOST_REQUIRE_EQUAL(s0, s1.moved_of(Vector(dx, dy)));
  BOOST_REQUIRE_EQUAL(s0.moved_of(-dx, -dy), s1);
}



// shape: rect

BOOST_AUTO_TEST_CASE(RECT)
{
  int x0 = next();
  int x1 = next();
  int y0 = next();
  int y1 = next();

  Shape s0(Shape::rect(
             std::min(x0, x1), std::min(y0, y1),
             std::max(x0, x1), std::max(y0, y1)));
  Shape s1(s0);
  Shape s2(s0);

  BOOST_REQUIRE_EQUAL(s0.type(), mml::shape::RECT);
  BOOST_REQUIRE_EQUAL(s1.type(), mml::shape::RECT);
  BOOST_REQUIRE_EQUAL(s0, s1);

  int dx = next();
  int dy = next();
  Vector d(dx, dy);

  s1.move_of(dx, dy);
  s2.move_of(d);

  BOOST_REQUIRE_EQUAL(s0.rect().min() + Vector(dx, dy), s1.rect().min());
  BOOST_REQUIRE_EQUAL(s0.rect().max() + Vector(dx, dy), s1.rect().max());
  BOOST_REQUIRE_EQUAL(s0.rect().min(), s1.rect().min() - Vector(dx, dy));
  BOOST_REQUIRE_EQUAL(s0.rect().max(), s1.rect().max() - Vector(dx, dy));
  BOOST_REQUIRE_EQUAL(s0.moved_of(dx, dy), s1);

  BOOST_REQUIRE_EQUAL(s0.rect().min() + d, s2.rect().min());
  BOOST_REQUIRE_EQUAL(s0.rect().max() + d, s2.rect().max());
  BOOST_REQUIRE_EQUAL(s0.rect().min(), s2.rect().min() - d);
  BOOST_REQUIRE_EQUAL(s0.rect().max(), s2.rect().max() - d);
  BOOST_REQUIRE_EQUAL(s0.moved_of(d), s2);

  s1.move_to(0, 0);
  s2.move_to(Point(0, 0));

  BOOST_REQUIRE_EQUAL(s1.center(), Point(0, 0));
  BOOST_REQUIRE_EQUAL(s2.center(), Point(0, 0));
  BOOST_REQUIRE_EQUAL(s1, s2);
}



// shape: circle

BOOST_AUTO_TEST_CASE(CIRCLE)
{
  Shape s0 = Shape::circle(next(), next(), next());
  Shape s1(s0);

  BOOST_REQUIRE_EQUAL(s0.type(), mml::shape::CIRCLE);
  BOOST_REQUIRE_EQUAL(s1.type(), mml::shape::CIRCLE);
  BOOST_REQUIRE_EQUAL(s0, s1);
}



// shape: polygon

BOOST_AUTO_TEST_CASE(POLYGON)
{
  Shape s0 = Shape::hexagon(Point(-50,    0),
                            Point(-10,  -50),
                            Point( 10,  -50),
                            Point( 50,    0),
                            Point( 10,   50),
                            Point(-10,   50));
  Shape s1(s0);

  BOOST_REQUIRE_EQUAL(s0.type(), mml::shape::POLYGON);
  BOOST_REQUIRE_EQUAL(s1.type(), mml::shape::POLYGON);
  BOOST_REQUIRE_EQUAL(s0, s1);
}

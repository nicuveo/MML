//
// Copyright Antoine Leblanc 2010 - 2013
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
#include <nauths/mml/mml.hh>

#define BOOST_TEST_MODULE intersection
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  typedef mml::Shape<int>   Shape;
  typedef mml::Point<int>   Point;
  typedef mml::Line<int>    Line;
  typedef mml::Rect<int>    Rect;
  typedef mml::Circle<int>  Circle;
  typedef mml::Polygon<int> Polygon;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

// ------------------------------------------
// shape: rect x rect

BOOST_AUTO_TEST_CASE(RECT_RECT)
{
  Shape s1;
  Shape s2;


  s1 = Shape::rect( 0,  0, 10, 10);
  s2 = Shape::rect(10,  5, 20, 15);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::rect( 0,  0, 10, 10);
  s2 = Shape::rect( 5, 10, 15, 20);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::rect( 0,  0, 30, 30);
  s2 = Shape::rect(10, 10, 20, 20);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::rect( 0,  0, 10, 10);
  s2 = Shape::rect(10, 10, 20, 20);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::rect(10,  0, 20, 10);
  s2 = Shape::rect( 0, 10, 10, 20);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);


  s1 = Shape::rect( 0,  0, 10, 10);
  s2 = Shape::rect(11,  5, 21, 15);
  BOOST_CHECK_MESSAGE(not mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::rect( 0,  0, 10, 10);
  s2 = Shape::rect( 5, 11, 15, 21);
  BOOST_CHECK_MESSAGE(not mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::rect( 0,  0, 10, 10);
  s2 = Shape::rect(20, 20, 30, 30);
  BOOST_CHECK_MESSAGE(not mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::rect( 0,  0, 10, 10);
  s2 = Shape::rect(11, 11, 20, 20);
  BOOST_CHECK_MESSAGE(not mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::rect(11,  0, 20, 10);
  s2 = Shape::rect( 0, 11, 10, 20);
  BOOST_CHECK_MESSAGE(not mml::overlaps(s1, s2), s1 << ", " << s2);
}


// ------------------------------------------
// shape: rect x circle

BOOST_AUTO_TEST_CASE(RECT_CIRCLE)
{
  Shape c = Shape::circle(0, 0, 50);
  Shape r;

  r = Shape::rect(-60, -1, -50, 1);
  BOOST_CHECK_MESSAGE(mml::overlaps(c, r), c << ", " << r);

  r = Shape::rect(50, -1, 60, 1);
  BOOST_CHECK_MESSAGE(mml::overlaps(c, r), c << ", " << r);

  r = Shape::rect(-10, -10, 10, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(c, r), c << ", " << r);

  r = Shape::rect(-100, -100, 100, 100);
  BOOST_CHECK_MESSAGE(mml::overlaps(c, r), c << ", " << r);

  r = Shape::rect(-100, -1, 100, 1);
  BOOST_CHECK_MESSAGE(mml::overlaps(c, r), c << ", " << r);

  r = Shape::rect(-100, -1, 0, 1);
  BOOST_CHECK_MESSAGE(mml::overlaps(c, r), c << ", " << r);

  r = Shape::rect(40, 40, 50, 50);
  BOOST_CHECK_MESSAGE(not mml::overlaps(c, r), c << ", " << r);
}


// ------------------------------------------
// shape: rect x polygon

BOOST_AUTO_TEST_CASE(RECT_POLYGON)
{
  Shape p = Shape::tetragon(Point(-50,    0),
                            Point(  0,  -50),
                            Point( 50,    0),
                            Point(  0,   50));
  Shape r;

  r = Shape::rect(-60, 0, -51, 1);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-60, -1, -51, 1);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-60, 0, -50, 1);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-60, -1, -50, 1);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-60, -10, -40, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(51, 0, 60, 1);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(51, -1, 60, 1);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(50, 0, 60, 1);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(50, -1, 60, 1);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(40, -10, 60, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(0, -60, 1, -51);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-1, -60, 1, -51);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(0, -60, 1, -50);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-1, -60, 1, -50);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-10, -60, 10, -40);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(0, 51, 1, 60);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-1, 51, 1, 60);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(0, 50, 1, 60);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-1, 50, 1, 60);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-10, 40, 10, 60);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(-50, -50, -26, -26);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-50, -50, -25, -25);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-50, -50, -24, -24);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(26, 26, 50, 50);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(25, 25, 50, 50);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(24, 24, 50, 50);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(-50, 26, -26, 50);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-50, 25, -25, 50);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-50, 24, -24, 50);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(26, -50, 50, -26);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(25, -50, 50, -25);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(24, -50, 50, -24);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(-10, -10, 10, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);
  r = Shape::rect(-100, -100, 100, 100);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, r), p << ", " << r);

  r = Shape::rect(40, 40, 50, 50);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, r), p << ", " << r);
}


// ------------------------------------------
// shape: circle x line

BOOST_AUTO_TEST_CASE(CIRCLE_LINE)
{
  Circle c(500, 500, 200);

  Line l00(100, 100, 900, 100);
  Line l01(100, 300, 900, 300);
  Line l02(100, 500, 900, 500);
  Line l03(100, 700, 900, 700);
  Line l04(100, 900, 900, 900);
  Line l05(100, 100, 100, 900);
  Line l06(300, 100, 300, 900);
  Line l07(500, 100, 500, 900);
  Line l08(700, 100, 700, 900);
  Line l09(900, 100, 900, 900);
  Line l10(300, 500, 700, 500);
  Line l11(500, 300, 500, 700);
  Line l12(400, 500, 600, 500);
  Line l13(500, 400, 500, 600);
  Line l14(400, 400, 600, 400);
  Line l15(400, 600, 600, 600);
  Line l16(400, 400, 400, 600);
  Line l17(600, 400, 600, 600);

#define TL(c, l, r) BOOST_CHECK_MESSAGE(mml::overlaps(c, l) == r, c << ", " << l << " != " << r);

  TL(c, l00, false);
  TL(c, l01, true);
  TL(c, l02, true);
  TL(c, l03, true);
  TL(c, l04, false);
  TL(c, l05, false);
  TL(c, l06, true);
  TL(c, l07, true);
  TL(c, l08, true);
  TL(c, l09, false);
  TL(c, l10, true);
  TL(c, l11, true);
  TL(c, l12, true);
  TL(c, l13, true);
  TL(c, l14, true);
  TL(c, l15, true);
  TL(c, l16, true);
  TL(c, l17, true);

#undef TL

}


// ------------------------------------------
// shape: circle x circle

BOOST_AUTO_TEST_CASE(CIRCLE_CIRCLE)
{
  Shape s1;
  Shape s2;

  s1 = Shape::circle(10, 10, 10);
  s2 = Shape::circle(30, 10, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::circle(10, 10, 10);
  s2 = Shape::circle(10, 30, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::circle( 0,  0,  2);
  s2 = Shape::circle( 3,  4,  3);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::circle( 0,  0, 10);
  s2 = Shape::circle( 1,  1,  5);
  BOOST_CHECK_MESSAGE(mml::overlaps(s1, s2), s1 << ", " << s2);

  s1 = Shape::circle( 0,  0, 10);
  s2 = Shape::circle(10, 10,  2);
  BOOST_CHECK_MESSAGE(not mml::overlaps(s1, s2), s1 << ", " << s2);
}


// ------------------------------------------
// shape: circle x polygon

BOOST_AUTO_TEST_CASE(CIRCLE_POLYGON)
{
  Shape p = Shape::tetragon(Point(-50,    0),
                            Point(  0,  -50),
                            Point( 50,    0),
                            Point(  0,   50));
  Shape c;

  c = Shape::circle(-60, 0,  9);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(-60, 0, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(-60, 0, 11);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(0, -60,  9);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(0, -60, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(0, -60, 11);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(60, 0,  9);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(60, 0, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(60, 0, 11);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(0, 60,  9);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(0, 60, 10);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(0, 60, 11);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(-30, -30, 7);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(-30, -30, 8);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(-30, 30, 7);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(-30, 30, 8);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(30, -30, 7);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(30, -30, 8);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(30, 30, 7);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(30, 30, 8);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(0, 0, 20);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);
  c = Shape::circle(0, 0, 100);
  BOOST_CHECK_MESSAGE(mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(40, 40, 10);
  BOOST_CHECK_MESSAGE(not mml::overlaps(p, c), p << ", " << c);

  c = Shape::circle(800, 600, 500);
  Shape t1 = Shape::triangle(Point(1280,  920),
                             Point(1440,  920),
                             Point(1360, 1000));
  Shape t2 = Shape::triangle(Point(1280,  920),
                             Point(1360,  840),
                             Point(1440,  920));
  BOOST_CHECK_MESSAGE(not mml::overlaps(t1, c), t1 << ", " << c);
  BOOST_CHECK_MESSAGE(not mml::overlaps(t2, c), t2 << ", " << c);
}

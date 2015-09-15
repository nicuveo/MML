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
#include <iomanip>
#include <boost/test/unit_test.hpp>
#include "nauths/mml/mml.hh"



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

BOOST_AUTO_TEST_SUITE(contains)

BOOST_AUTO_TEST_CASE(line_point)
{
  static const int b = -42;
  static const int e =  42;

  Line l1(b, b, e, b);
  Line l2(b, b, b, e);
  Line l3(b, b, e, e);

  for (int x = b; x <= e; ++x)
    for (int y = b; y <= e; ++y)
    {
      Point p(x, y);
      bool b1 = mml::contains(l1, p);
      bool b2 = mml::contains(l2, p);
      bool b3 = mml::contains(l3, p);
      bool r1 = (y == b);
      bool r2 = (x == b);
      bool r3 = ((y - b) == (x - b));

      BOOST_CHECK_MESSAGE(b1 == r1, "t1: " << l1 << ",\t" << p << "\t: " << b1 << " != " << r1);
      BOOST_CHECK_MESSAGE(b2 == r2, "t2: " << l2 << ",\t" << p << "\t: " << b2 << " != " << r2);
      BOOST_CHECK_MESSAGE(b3 == r3, "t3: " << l3 << ",\t" << p << "\t: " << b3 << " != " << r3);
    }
}

BOOST_AUTO_TEST_CASE(line_line)
{
  static const int b = -42;
  static const int e =  42;

  Line l1(b, b, e, b);
  Line l2(b, b, b, e);
  Line l3(b, b, e, e);

  for (int d = 1; d <= e - b; ++d)
    for (int x = b; x <= e - d; ++x)
      for (int y = b; y <= e - d; ++y)
      {
        Line o1(x, y, x + d, y + 0);
        Line o2(x, y, x + 0, y + d);
        Line o3(x, y, x + d, y + d);
        bool b1 = mml::contains(l1, o1);
        bool b2 = mml::contains(l2, o2);
        bool b3 = mml::contains(l3, o3);
        bool r1 = (y == b);
        bool r2 = (x == b);
        bool r3 = ((y - b) == (x - b));

        BOOST_CHECK_MESSAGE(b1 == r1, "t1: " << l1 << ",\t" << o1 << "\t: " << b1 << " != " << r1);
        BOOST_CHECK_MESSAGE(b2 == r2, "t2: " << l2 << ",\t" << o2 << "\t: " << b2 << " != " << r2);
        BOOST_CHECK_MESSAGE(b3 == r3, "t3: " << l3 << ",\t" << o3 << "\t: " << b3 << " != " << r3);
      }
}

BOOST_AUTO_TEST_CASE(rect_point)
{
  Shape s0 = Shape::rect(-10, -10, 10, 10);
  for (int x = -20; x <= 20; ++x)
    for (int y = -20; y <= 20; ++y)
      BOOST_CHECK_MESSAGE(mml::contains(s0, Point(x, y)) ==
                          (x >= -10 and x <= 10 and
                           y >= -10 and y <= 10), s0 << ",\t" << Point(x, y));
}

BOOST_AUTO_TEST_CASE(rect_line)
{
  static const int rb =  -8;
  static const int re =   8;
  static const int pb = -10;
  static const int pe =  10;

  Rect r(rb, rb, re, re);
  for (int x1 = pb; x1 <= pe; ++x1)
    for (int y1 = pb; y1 <= pe; ++y1)
      for (int x2 = pb; x2 <= pe; ++x2)
        for (int y2 = pb; y2 <= pe; ++y2)
        {
          Point p1(x1, y1);
          Point p2(x2, y2);
          Line l12(p1, p2);

          BOOST_CHECK_MESSAGE(mml::contains(r, l12) == (mml::contains(r, p1) and
                                                        mml::contains(r, p2)),
                              r << ",\t" << l12);
        }
}

BOOST_AUTO_TEST_CASE(rect_rect)
{
  static const int rb =  -8;
  static const int re =   8;
  static const int pb = -10;
  static const int pe =  10;

  Rect r(rb, rb, re, re);
  for (int x1 = pb; x1 <= pe; ++x1)
    for (int y1 = pb; y1 <= pe; ++y1)
      for (int x2 = x1 + 1; x2 <= pe; ++x2)
        for (int y2 = y1 + 1; y2 <= pe; ++y2)
        {
          Point p1(x1, y1);
          Point p2(x2, y2);
          Rect r12(p1, p2);

          BOOST_CHECK_MESSAGE(mml::contains(r, r12) == (mml::contains(r, p1) and
                                                        mml::contains(r, p2)),
                              r << ",\t" << r12);
        }
}

BOOST_AUTO_TEST_CASE(rect_circle)
{
  static const int bb =  -8;
  static const int be =   8;
  static const int pb = -10;
  static const int pe =  10;
  static const int rb =   1;
  static const int re =  10;

  Rect b(bb, bb, be, be);
  for (int x = pb; x <= pe; ++x)
    for (int y = pb; y <= pe; ++y)
      for (int r = rb; r <= re; ++r)
      {
        Point p(x, y);
        Circle c(p, r);

        BOOST_CHECK_MESSAGE(mml::contains(b, c) == (mml::contains(b, p - Point(r, r)) and
                                                    mml::contains(b, p + Point(r, r))),
                            b << ",\t" << c);
      }
}

BOOST_AUTO_TEST_CASE(circle_point)
{
  Shape c = Shape::circle(0, 0, 10);
  for (int x = -20; x <= 20; ++x)
    for (int y = -20; y <= 20; ++y)
      BOOST_CHECK_MESSAGE(mml::contains(c, Point(x, y)) == (sqrt(x * x + y * y) <= 10),
                          c << ", " << Point(x, y));
}

BOOST_AUTO_TEST_CASE(circle_circle)
{
  static const int pb = -10;
  static const int pe =  10;
  static const int rb =   1;
  static const int re =  10;

  Circle b(0, 0, 10);

  for (int x = pb; x <= pe; ++x)
    for (int y = pb; y <= pe; ++y)
      for (int r = rb; r <= re; ++r)
      {
        Circle c(x, y, r);
        x = std::abs(x) + r;
        y = std::abs(y) + r;

        bool ref = (x * x + y * y <= 100);
        BOOST_CHECK_MESSAGE(mml::contains(b, c) == ref, b << ", " << c << " != " << ref);
      }
}

BOOST_AUTO_TEST_CASE(polygon_point)
{
  static int xs[5] = { 100, 200, 400, 600, 700 };
  static int ys[5] = { 100, 200, 400, 600, 700 };

#define P(x, y) Point(xs[x], ys[y])

  Shape o = Shape::octagon(P(0, 2), P(1, 3), P(2, 4), P(3, 3),
                           P(4, 2), P(3, 1), P(2, 0), P(1, 1));

  BOOST_CHECK_MESSAGE(mml::contains(o, P(0, 0)) == false, o << ",\t" << P(0, 0));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(0, 1)) == false, o << ",\t" << P(0, 1));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(0, 2)) == true,  o << ",\t" << P(0, 2));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(0, 3)) == false, o << ",\t" << P(0, 3));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(0, 4)) == false, o << ",\t" << P(0, 4));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(1, 0)) == false, o << ",\t" << P(1, 0));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(1, 1)) == true,  o << ",\t" << P(1, 1));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(1, 2)) == true,  o << ",\t" << P(1, 2));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(1, 3)) == true,  o << ",\t" << P(1, 3));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(1, 4)) == false, o << ",\t" << P(1, 4));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(2, 0)) == true,  o << ",\t" << P(2, 0));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(2, 1)) == true,  o << ",\t" << P(2, 1));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(2, 2)) == true,  o << ",\t" << P(2, 2));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(2, 3)) == true,  o << ",\t" << P(2, 3));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(2, 4)) == true,  o << ",\t" << P(2, 4));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(3, 0)) == false, o << ",\t" << P(3, 0));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(3, 1)) == true,  o << ",\t" << P(3, 1));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(3, 2)) == true,  o << ",\t" << P(3, 2));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(3, 3)) == true,  o << ",\t" << P(3, 3));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(3, 4)) == false, o << ",\t" << P(3, 4));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(4, 0)) == false, o << ",\t" << P(4, 0));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(4, 1)) == false, o << ",\t" << P(4, 1));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(4, 2)) == true,  o << ",\t" << P(4, 2));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(4, 3)) == false, o << ",\t" << P(4, 3));
  BOOST_CHECK_MESSAGE(mml::contains(o, P(4, 4)) == false, o << ",\t" << P(4, 4));

  for (const Point& p : o.polygon().points())
    BOOST_CHECK_MESSAGE(mml::contains(o, p) == true, o << ",\t" << p);

  for (const Line& l : o.polygon().lines())
    BOOST_CHECK_MESSAGE(mml::contains(o, l.center()) == true, o << ",\t" << l.center());

#undef P

}

BOOST_AUTO_TEST_CASE(polygon_line)
{
  static int xs[5] = { 100, 200, 400, 600, 700 };
  static int ys[5] = { 100, 200, 400, 600, 700 };

#define P(x, y)           Point(xs[x], ys[y])
#define L(x1, y1, x2, y2) Line(xs[x1], ys[y1], xs[x2], ys[y2])

  Shape o = Shape::octagon(P(0, 2), P(1, 3), P(2, 4), P(3, 3),
                           P(4, 2), P(3, 1), P(2, 0), P(1, 1));

  Line l[28] = {
    L(0, 0, 4, 0), L(0, 1, 4, 1), L(0, 2, 4, 2), L(0, 3, 4, 3), L(0, 4, 4, 4),
    L(0, 0, 0, 4), L(1, 0, 1, 4), L(2, 0, 2, 4), L(3, 0, 3, 4), L(4, 0, 4, 4),
    L(1, 1, 3, 1), L(1, 2, 3, 2), L(1, 3, 3, 3),
    L(1, 1, 1, 3), L(2, 1, 2, 3), L(3, 1, 3, 3),
    L(0, 0, 4, 4), L(0, 4, 4, 0),
    L(1, 1, 3, 3), L(1, 3, 3, 1),
    L(0, 2, 1, 3), L(1, 3, 2, 4), L(2, 4, 3, 3), L(3, 3, 4, 2),
    L(4, 2, 3, 1), L(3, 1, 2, 0), L(2, 0, 1, 1), L(1, 1, 0, 2)
  };

  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 0]) == false, "\n" << o << "\n" << l[ 0]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 1]) == false, "\n" << o << "\n" << l[ 1]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 2]) == true,  "\n" << o << "\n" << l[ 2]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 3]) == false, "\n" << o << "\n" << l[ 3]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 4]) == false, "\n" << o << "\n" << l[ 4]);

  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 5]) == false, "\n" << o << "\n" << l[ 5]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 6]) == false, "\n" << o << "\n" << l[ 6]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 7]) == true,  "\n" << o << "\n" << l[ 7]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 8]) == false, "\n" << o << "\n" << l[ 8]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[ 9]) == false, "\n" << o << "\n" << l[ 9]);

  BOOST_CHECK_MESSAGE(mml::contains(o, l[10]) == true,  "\n" << o << "\n" << l[10]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[11]) == true,  "\n" << o << "\n" << l[11]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[12]) == true,  "\n" << o << "\n" << l[12]);

  BOOST_CHECK_MESSAGE(mml::contains(o, l[13]) == true,  "\n" << o << "\n" << l[13]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[14]) == true,  "\n" << o << "\n" << l[14]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[15]) == true,  "\n" << o << "\n" << l[15]);

  BOOST_CHECK_MESSAGE(mml::contains(o, l[16]) == false, "\n" << o << "\n" << l[16]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[17]) == false, "\n" << o << "\n" << l[17]);

  BOOST_CHECK_MESSAGE(mml::contains(o, l[18]) == true,  "\n" << o << "\n" << l[18]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[19]) == true,  "\n" << o << "\n" << l[19]);

  BOOST_CHECK_MESSAGE(mml::contains(o, l[20]) == true,  "\n" << o << "\n" << l[20]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[21]) == true,  "\n" << o << "\n" << l[21]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[22]) == true,  "\n" << o << "\n" << l[22]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[23]) == true,  "\n" << o << "\n" << l[23]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[24]) == true,  "\n" << o << "\n" << l[24]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[25]) == true,  "\n" << o << "\n" << l[25]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[26]) == true,  "\n" << o << "\n" << l[26]);
  BOOST_CHECK_MESSAGE(mml::contains(o, l[27]) == true,  "\n" << o << "\n" << l[27]);

#undef P
#undef L

}

BOOST_AUTO_TEST_CASE(polygon_line_advanced_1)
{
  Polygon p0 = Shape::hexagon(Point(100,   0), Point(200, 100),
                              Point(100, 200), Point( 50, 150),
                              Point(100, 100), Point( 50,  50));

  Line l00(Point( 50,   0), Point( 50,  50));
  Line l01(Point( 50,  50), Point( 50, 100));
  Line l02(Point( 50, 100), Point( 50, 150));
  Line l03(Point( 50, 150), Point( 50, 200));
  Line l04(Point( 50,   0), Point( 50, 100));
  Line l05(Point( 50,  50), Point( 50, 150));
  Line l06(Point( 50, 100), Point( 50, 200));
  Line l07(Point( 50,   0), Point( 50, 200));
  Line l10(Point( 75,   0), Point( 75,  50));
  Line l11(Point( 75,  50), Point( 75, 100));
  Line l12(Point( 75, 100), Point( 75, 150));
  Line l13(Point( 75, 150), Point( 75, 200));
  Line l14(Point( 75,   0), Point( 75, 100));
  Line l15(Point( 75,  50), Point( 75, 150));
  Line l16(Point( 75, 100), Point( 75, 200));
  Line l17(Point( 75,   0), Point( 75, 200));
  Line l20(Point(100,   0), Point(100,  50));
  Line l21(Point(100,  50), Point(100, 100));
  Line l22(Point(100, 100), Point(100, 150));
  Line l23(Point(100, 150), Point(100, 200));
  Line l24(Point(100,   0), Point(100, 100));
  Line l25(Point(100,  50), Point(100, 150));
  Line l26(Point(100, 100), Point(100, 200));
  Line l27(Point(100,   0), Point(100, 200));
  Line l30(Point(150,   0), Point(150,  50));
  Line l31(Point(150,  50), Point(150, 100));
  Line l32(Point(150, 100), Point(150, 150));
  Line l33(Point(150, 150), Point(150, 200));
  Line l34(Point(150,   0), Point(150, 100));
  Line l35(Point(150,  50), Point(150, 150));
  Line l36(Point(150, 100), Point(150, 200));
  Line l37(Point(150,   0), Point(150, 200));
  Line l40(Point(200,   0), Point(200,  50));
  Line l41(Point(200,  50), Point(200, 100));
  Line l42(Point(200, 100), Point(200, 150));
  Line l43(Point(200, 150), Point(200, 200));
  Line l44(Point(200,   0), Point(200, 100));
  Line l45(Point(200,  50), Point(200, 150));
  Line l46(Point(200, 100), Point(200, 200));
  Line l47(Point(200,   0), Point(200, 200));

#define LT(p, l, r) BOOST_CHECK_MESSAGE(mml::contains(p, l) == r, "\n" << p << "\n" << l)

  LT(p0, l00, false);
  LT(p0, l01, false);
  LT(p0, l02, false);
  LT(p0, l03, false);
  LT(p0, l04, false);
  LT(p0, l05, false);
  LT(p0, l06, false);
  LT(p0, l07, false);
  LT(p0, l10, false);
  LT(p0, l11, false);
  LT(p0, l12, false);
  LT(p0, l13, false);
  LT(p0, l14, false);
  LT(p0, l15, false);
  LT(p0, l16, false);
  LT(p0, l17, false);
  LT(p0, l20, true );
  LT(p0, l21, true );
  LT(p0, l22, true );
  LT(p0, l23, true );
  LT(p0, l24, true );
  LT(p0, l25, true );
  LT(p0, l26, true );
  LT(p0, l27, true );
  LT(p0, l30, false);
  LT(p0, l31, true );
  LT(p0, l32, true );
  LT(p0, l33, false);
  LT(p0, l34, false);
  LT(p0, l35, true );
  LT(p0, l36, false);
  LT(p0, l37, false);
  LT(p0, l40, false);
  LT(p0, l41, false);
  LT(p0, l42, false);
  LT(p0, l43, false);
  LT(p0, l44, false);
  LT(p0, l45, false);
  LT(p0, l46, false);
  LT(p0, l47, false);

#undef LT

}

BOOST_AUTO_TEST_CASE(polygon_line_advanced_2)
{
  Polygon p0 = Shape::tetragon(Point(100, 100), Point(200, 100),
                               Point(200, 200), Point(100, 200));

  Line l0(Point(100,   0), Point(100, 100));
  Line l1(Point(100, 100), Point(100, 200));
  Line l2(Point(100, 200), Point(100, 300));
  Line l3(Point(100,   0), Point(100, 150));
  Line l4(Point(100, 150), Point(100, 300));
  Line l5(Point(100, 100), Point(100, 140));
  Line l6(Point(100, 140), Point(100, 160));
  Line l7(Point(100, 160), Point(100, 200));

#define LT(p, l, r) BOOST_CHECK_MESSAGE(mml::contains(p, l) == r, "\n" << p << "\n" << l)

  LT(p0, l0, false);
  LT(p0, l1, true );
  LT(p0, l2, false);
  LT(p0, l3, false);
  LT(p0, l4, false);
  LT(p0, l5, true );
  LT(p0, l6, true );
  LT(p0, l7, true );

#undef LT
}

BOOST_AUTO_TEST_CASE(polygon_circle)
{
  static int xs[5] = { 100, 200, 400, 600, 700 };
  static int ys[5] = { 100, 200, 400, 600, 700 };

#define P(x, y)    Point(xs[x], ys[y])
#define C(x, y, r) Circle(P(x, y), r)

  Shape o = Shape::octagon(P(0, 2), P(1, 3), P(2, 4), P(3, 3),
                           P(4, 2), P(3, 1), P(2, 0), P(1, 1));

  Circle c[12] = {
    C(2, 2, 200), C(2, 2, 260),
    C(2, 2, 280), C(2, 2, 400),
    C(2, 1,  70), C(2, 1, 100),
    C(2, 3,  70), C(2, 3, 100),
    C(1, 2,  70), C(1, 2, 100),
    C(3, 2,  70), C(3, 2, 100),
  };

  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 0]) == true,  o << ",\t" << c[ 0]);
  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 1]) == true,  o << ",\t" << c[ 1]);
  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 2]) == false, o << ",\t" << c[ 2]);
  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 3]) == false, o << ",\t" << c[ 3]);

  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 4]) == true,  o << ",\t" << c[ 4]);
  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 5]) == false, o << ",\t" << c[ 5]);

  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 6]) == true,  o << ",\t" << c[ 6]);
  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 7]) == false, o << ",\t" << c[ 7]);

  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 8]) == true,  o << ",\t" << c[ 8]);
  BOOST_CHECK_MESSAGE(mml::contains(o, c[ 9]) == false, o << ",\t" << c[ 9]);

  BOOST_CHECK_MESSAGE(mml::contains(o, c[10]) == true,  o << ",\t" << c[10]);
  BOOST_CHECK_MESSAGE(mml::contains(o, c[11]) == false, o << ",\t" << c[11]);

#undef P
#undef C

}

BOOST_AUTO_TEST_CASE(polygon_polygon)
{
  static int xs[5] = { 100, 200, 400, 600, 700 };
  static int ys[5] = { 100, 200, 400, 600, 700 };

#define P(x, y) Point(xs[x], ys[y])
#define NP(s, x, y) p0.scaled(s).moved_of(x, y)

  Polygon p0 = Shape::octagon(P(0, 2), P(1, 3), P(2, 4), P(3, 3),
                              P(4, 2), P(3, 1), P(2, 0), P(1, 1));

  Polygon ps[15] = {
    NP(0.9, 0, 0), NP(1.0, 0, 0), NP(1.1, 0, 0),
    NP(0.5, -149,    0), NP(0.5, -150,    0), NP(0.5, -151,    0),
    NP(0.5,  149,    0), NP(0.5,  150,    0), NP(0.5,  151,    0),
    NP(0.5,    0, -149), NP(0.5,    0, -150), NP(0.5,    0, -151),
    NP(0.5,    0,  149), NP(0.5,    0,  150), NP(0.5,    0,  151)
  };

  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 0]) == true,  "\n" << p0 << "\n" << ps[ 0]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 1]) == true,  "\n" << p0 << "\n" << ps[ 1]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 2]) == false, "\n" << p0 << "\n" << ps[ 2]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 3]) == true,  "\n" << p0 << "\n" << ps[ 3]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 4]) == true,  "\n" << p0 << "\n" << ps[ 4]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 5]) == false, "\n" << p0 << "\n" << ps[ 5]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 6]) == true,  "\n" << p0 << "\n" << ps[ 6]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 7]) == true,  "\n" << p0 << "\n" << ps[ 7]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 8]) == false, "\n" << p0 << "\n" << ps[ 8]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[ 9]) == true,  "\n" << p0 << "\n" << ps[ 9]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[10]) == true,  "\n" << p0 << "\n" << ps[10]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[11]) == false, "\n" << p0 << "\n" << ps[11]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[12]) == true,  "\n" << p0 << "\n" << ps[12]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[13]) == true,  "\n" << p0 << "\n" << ps[13]);
  BOOST_CHECK_MESSAGE(mml::contains(p0, ps[14]) == false, "\n" << p0 << "\n" << ps[14]);

#undef P
#undef NP

}

BOOST_AUTO_TEST_SUITE_END()

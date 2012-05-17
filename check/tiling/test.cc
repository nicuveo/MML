//
// test.cc for mml
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <mml/mml.hh>

#define BOOST_TEST_MODULE Tiling
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

#define TEST_TILING(type, good_size)                            \
  {                                                             \
    Shape ref(Shape::circle(1000));                             \
                                                                \
    for (int a = 0; a < 360; a += 72)                           \
      for (int x = 1000; x <= 8000; x *= 2)                     \
        for (int y = 1000; y <= 8000; y *= 2)                   \
        {                                                       \
          double ra = (a * (2 * mml::pi()) / 360.);             \
          Tessellation tess(type, ref, x, y, ra);               \
          const std::vector<Shape>& pt = tess.pattern();        \
          const Vector& dh = tess.dh();                         \
          const Vector& dv = tess.dv();                         \
                                                                \
          std::set<Point, Less> points;                         \
                                                                \
          mml_foreach (const Shape& s, pt)                      \
            for (int dx = -1; dx <= 1; ++dx)                    \
              for (int dy = -1; dy <= 1; ++dy)                  \
              {                                                 \
                Shape rs = s.moved_of(dx * dh + dy * dv);       \
                mml_foreach (const Point& p,                    \
                             rs.polygon().points())             \
                  points.insert(p);                             \
              }                                                 \
                                                                \
          BOOST_CHECK_MESSAGE(points.size() == good_size,       \
                              "a: " << ra   << ", "             \
                              << "x: " << x    << ", "          \
                              << "y: " << y    << ": "          \
                              << points.size() << " != "        \
                              << good_size);                    \
        }                                                       \
  }                                                             \

#define TEST_LINKS(type)                                        \
  {                                                             \
    Shape ref(Shape::circle(1000));                             \
    Shape test(Shape::circle(500));                             \
    Tessellation tess(type, ref, 200);                          \
    Tessellation::iterator it;                                  \
    std::map<int, std::vector<int> > l;                         \
    unsigned n = tess.pattern().size();                         \
                                                                \
    for (it = tess.begin(false, true); it != tess.end(); ++it)  \
    {                                                           \
      l[it.index()] = it.links();                               \
      mml_foreach (int nid, it.links())                         \
        l[nid].push_back(it.index());                           \
    }                                                           \
                                                                \
    for (it = tess.begin(false); it != tess.end(); ++it)        \
      if (mml::overlaps(test, *it))                             \
        BOOST_CHECK_MESSAGE(l[it.index()].size() ==             \
                            it->polygon().size(),               \
                            "i1: " << it.index() << ": "        \
                            "i2: " << it.index() % n << ", "    \
                            << l[it.index()].size() << " != "   \
                            << it->polygon().size());           \
  }                                                             \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  typedef mml::Shape<mml::Num> Shape;
  typedef mml::Point<mml::Num> Point;
  typedef mml::Point<mml::Num> Vector;
  typedef mml::Polygon<mml::Num> Polygon;

  typedef mml::Tessellation<mml::Num> Tessellation;

  class Less
  {
    public:
      bool operator()(const Point& p1, const Point& p2)
      {
        return p1.x() == p2.x()
          ? p1.y() < p2.y()
          : p1.x() < p2.x();
      }
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(TRIANGULAR_TILING)
{
  TEST_TILING(mml::tiling::TRIANGULAR, 28);
}

BOOST_AUTO_TEST_CASE(SQUARE_TILING)
{
  TEST_TILING(mml::tiling::SQUARE, 16);
}

BOOST_AUTO_TEST_CASE(HEXAGONAL_TILING)
{
  TEST_TILING(mml::tiling::HEXAGONAL, 54);
}

BOOST_AUTO_TEST_CASE(SNUB_HEXAGONAL_TILING)
{
  TEST_TILING(mml::tiling::SNUB_HEXAGONAL, 831);
}

BOOST_AUTO_TEST_CASE(REFLECTED_SNUB_HEXAGONAL_TILING)
{
  TEST_TILING(mml::tiling::REFLECTED_SNUB_HEXAGONAL, 831);
}

BOOST_AUTO_TEST_CASE(TRI_HEXAGONAL_TILING)
{
  TEST_TILING(mml::tiling::TRI_HEXAGONAL, 78);
}

BOOST_AUTO_TEST_CASE(ELONGATED_TRIANGULAR_TILING)
{
  TEST_TILING(mml::tiling::ELONGATED_TRIANGULAR, 52);
}

BOOST_AUTO_TEST_CASE(SNUB_SQUARE_TILING)
{
  TEST_TILING(mml::tiling::SNUB_SQUARE, 96);
}

BOOST_AUTO_TEST_CASE(RHOMBITRIHEXAGONAL_TILING)
{
  TEST_TILING(mml::tiling::RHOMBITRIHEXAGONAL, 137);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_SQUARE_TILING)
{
  TEST_TILING(mml::tiling::TRUNCATED_SQUARE, 101);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_HEXAGONAL_TILING)
{
  TEST_TILING(mml::tiling::TRUNCATED_HEXAGONAL, 149);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_TRIHEXAGONAL_TILING)
{
  // FIXME check::tiling: numbers ought to be checked
  TEST_TILING(mml::tiling::TRUNCATED_TRIHEXAGONAL, 268);
}

BOOST_AUTO_TEST_CASE(TRIANGULAR_LINKS)
{
  TEST_LINKS(mml::tiling::TRIANGULAR);
}

BOOST_AUTO_TEST_CASE(SQUARE_LINKS)
{
  TEST_LINKS(mml::tiling::SQUARE);
}

BOOST_AUTO_TEST_CASE(HEXAGONAL_LINKS)
{
  TEST_LINKS(mml::tiling::HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(SNUB_HEXAGONAL_LINKS)
{
  TEST_LINKS(mml::tiling::SNUB_HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(REFLECTED_SNUB_HEXAGONAL_LINKS)
{
  TEST_LINKS(mml::tiling::REFLECTED_SNUB_HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(TRI_HEXAGONAL_LINKS)
{
  TEST_LINKS(mml::tiling::TRI_HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(ELONGATED_TRIANGULAR_LINKS)
{
  TEST_LINKS(mml::tiling::ELONGATED_TRIANGULAR);
}

BOOST_AUTO_TEST_CASE(SNUB_SQUARE_LINKS)
{
  TEST_LINKS(mml::tiling::SNUB_SQUARE);
}

BOOST_AUTO_TEST_CASE(RHOMBITRIHEXAGONAL_LINKS)
{
  TEST_LINKS(mml::tiling::RHOMBITRIHEXAGONAL);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_SQUARE_LINKS)
{
  TEST_LINKS(mml::tiling::TRUNCATED_SQUARE);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_HEXAGONAL_LINKS)
{
  TEST_LINKS(mml::tiling::TRUNCATED_HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_TRIHEXAGONAL_LINKS)
{
  TEST_LINKS(mml::tiling::TRUNCATED_TRIHEXAGONAL);
}

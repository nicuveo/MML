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
#include <nauths/mml/mml.hh>

#define BOOST_TEST_MODULE TilingRatios
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  typedef mml::Shape<mml::Num> Shape;
  typedef mml::Point<mml::Num> Point;
  typedef mml::Line<mml::Num> Line;
  typedef mml::Point<mml::Num> Vector;
  typedef mml::Polygon<mml::Num> Polygon;

  typedef mml::Tessellation<mml::Num> Tessellation;

  typedef std::map<int, Shape> ShapeMap;


  Line oriented(const Line& l)
  {
    return (l.x0() == l.x1()
            ? (l.y0() < l.y1()
               ? l
               : -l)
            : (l.x0() < l.x1()
               ? l
               : -l));
  }

  Line
  common_line(const Polygon& p1, const Polygon& p2)
  {
    // ugly
    for (const Line& l1 : p1.lines())
      for (const Line& l2 : p2.lines())
        if (oriented(l1) == oriented(l2))
          return oriented(l1);
    BOOST_CHECK(false);
    return Line();
  }

  void check_pair(const Polygon& p1, const Polygon& p2)
  {
    const Line& common = common_line(p1, p2);
    Line centers(p1.center(), p2.center());
    mml::Real n1;
    mml::Real n2;
    mml::Real d1;
    mml::Real d2;
    mml::il::lines_coeff(common, centers, n1, n2, d1, d2);

    BOOST_CHECK_NE(0, d1);
    BOOST_CHECK_NE(0, d2);
    BOOST_CHECK_LE(0, std::abs(n1));
    BOOST_CHECK_LE(0, std::abs(n2));
    BOOST_CHECK_LE(std::abs(n1), std::abs(d1));
    BOOST_CHECK_LE(std::abs(n2), std::abs(d2));

    double real = n2 / d2;
    double theoretical = mml::tiling::ratio(p1.size(), p2.size());
    double diff = std::abs(theoretical - real);

    std::cout << "real: " << std::setw(10) << real << " theo: " << theoretical << std::endl;
    BOOST_CHECK_LT(diff / theoretical, 0.05);
  }

  void check_tiling(mml::TilingType type)
  {
    Shape ref(Shape::square(20000));
    Tessellation tess(type, ref, 5000);
    Tessellation::iterator it;
    ShapeMap m;

    for (it = tess.begin(false, true); it != tess.end(); ++it)
    {
      m[it.index()] = *it;
      for (const Tessellation::Link& nid : it.links())
      {
        ShapeMap::iterator it2 = m.find(nid.first);
        if (it2 != m.end())
          check_pair(m[it.index()].polygon(), it2->second.polygon());
      }
    }
  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(TRIANGULAR_TILING)
{
  check_tiling(mml::tiling::TRIANGULAR);
}

BOOST_AUTO_TEST_CASE(SQUARE_TILING)
{
  check_tiling(mml::tiling::SQUARE);
}

BOOST_AUTO_TEST_CASE(HEXAGONAL_TILING)
{
  check_tiling(mml::tiling::HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(SNUB_HEXAGONAL_TILING)
{
  check_tiling(mml::tiling::SNUB_HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(REFLECTED_SNUB_HEXAGONAL_TILING)
{
  check_tiling(mml::tiling::REFLECTED_SNUB_HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(TRI_HEXAGONAL_TILING)
{
  check_tiling(mml::tiling::TRI_HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(ELONGATED_TRIANGULAR_TILING)
{
  check_tiling(mml::tiling::ELONGATED_TRIANGULAR);
}

BOOST_AUTO_TEST_CASE(SNUB_SQUARE_TILING)
{
  check_tiling(mml::tiling::SNUB_SQUARE);
}

BOOST_AUTO_TEST_CASE(RHOMBITRIHEXAGONAL_TILING)
{
  check_tiling(mml::tiling::RHOMBITRIHEXAGONAL);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_SQUARE_TILING)
{
  check_tiling(mml::tiling::TRUNCATED_SQUARE);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_HEXAGONAL_TILING)
{
  check_tiling(mml::tiling::TRUNCATED_HEXAGONAL);
}

BOOST_AUTO_TEST_CASE(TRUNCATED_TRIHEXAGONAL_TILING)
{
  check_tiling(mml::tiling::TRUNCATED_TRIHEXAGONAL);
}

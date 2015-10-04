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
#include <boost/test/unit_test.hpp>
#include "nauths/mml/mml.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  typedef mml::Shape<mml::Num> Shape;
  typedef mml::Point<mml::Num> Point;
  typedef mml::perlin<> Perlin;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_SUITE(perlin)

BOOST_AUTO_TEST_CASE(PERLIN_BASIC)
{
  Perlin::NoiseSum s = Perlin::harmonic_sum(1, 4, 0.25);

  BOOST_REQUIRE(s.size() == 4);

  for (int y = 0; y <= 100; ++y)
    for (int x = 0; x <= 100; ++x)
    {
      double noise = s(double(x) / 100, double(y) / 100);
      BOOST_REQUIRE_GE(noise, 0);
      BOOST_REQUIRE_LE(noise, 1.);
    }
}

BOOST_AUTO_TEST_SUITE_END()

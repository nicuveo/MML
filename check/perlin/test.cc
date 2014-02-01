//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <nauths/mml/mml.hh>

#define BOOST_TEST_MODULE Perlin
#include <boost/test/included/unit_test.hpp>



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

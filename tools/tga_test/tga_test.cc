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

#include <fstream>
#include <iomanip>
#include <iostream>
#include <nauths/mml/mml.hh>
#include "img/io/tga.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{


  typedef mml::shapes<int>::Shape Shape;
  typedef mml::shapes<int>::Point Point;
  typedef tools::Bitmap::size_type size_type;
  typedef tools::Bitmap Bitmap;
  typedef tools::Color Color;


  const int P_MIN   =  3;
  const int P_MAX   = 20;
  const int A_STEPS = 11;

  const size_type IMW  = 1200;
  const size_type IMH  =  900;
  const size_type SIZE =  400;


  void test_polygon(int points, int angle)
  {
    const char p1 = '0' + points / 10;
    const char p0 = '0' + points % 10;
    const char a1 = '0' + angle / 10;
    const char a0 = '0' + angle % 10;
    const char fn[] = { 'o', 'u', 't', '/', p1, p0, '_', a1, a0, '.', 't', 'g', 'a', 0 };
    const double rad_angle = (mml::tau() * angle) / A_STEPS;
    const Shape ref = Shape::reg_polygon(Point(IMW / 2, IMH / 2), SIZE, points, rad_angle);

    Bitmap buffer(IMW, IMH);

    for (size_type y = 0; y < IMH; ++y)
      for (size_type x = 0; x < IMW; ++x)
        buffer(x, y) = (mml::contains(ref, Point(x, y)) ? Color::green : Color::red);

    std::ofstream res_file(fn);
    if (not res_file.is_open())
      std::exit(1);

    res_file << tools::tga(buffer);
    res_file.close();
  }

  void test_polygon(int points)
  {
    for (int a = 0; a < A_STEPS; ++a)
      test_polygon(points, a);
  }


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

int main()
{
  for (int p = P_MIN; p <= P_MAX; ++p)
    test_polygon(p);

  return 0;
}

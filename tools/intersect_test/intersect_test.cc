//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <fstream>
#include <iomanip>
#include <iostream>
#include <mml/mml.hh>
#include "img/io/tga.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  // types

  typedef mml::shapes<int>::Shape Shape;
  typedef mml::shapes<int>::Point Point;
  typedef tools::Bitmap Bitmap;
  typedef tools::Color Color;
  typedef tools::Bitmap::size_type size_type;


  // constants

  const int IMW    = 800;
  const int IMH    = 600;
  const int DIA    = 280;

  const int STEP   =  10;
  const int SIZE   =   4;

  const int FACT   =   4;
  const int   AA   =   1;

  const char* OUT  = "out/out.tga";

  const Shape REF  = Shape::reg_heptagon(FACT * IMW / 2, FACT * IMH / 2, FACT * DIA, mml::pi() / 2);
  const Shape TEST = Shape::reg_hexagon(0, 0, FACT * SIZE);

#define C0 Color::black
#define C1 Color::green
#define C2 Color::blue
#define C3 Color::red


  // scale
  //   scales a bitmap, blending colours

  Bitmap scale(Bitmap const& in)
  {
    assert(in.width()  % FACT == 0);
    assert(in.height() % FACT == 0);
    assert(in.width()  == FACT * IMW);
    assert(in.height() == FACT * IMH);

    Bitmap res(IMW, IMH);
    const int r_min = -AA;
    const int r_max = FACT + AA;
    const float k = 1.f / std::pow(FACT + 2 * AA, 2);

    for (size_type y = 0; y < size_type(IMH); y += 1)
      for (size_type x = 0; x < size_type(IMW); x += 1)
      {
        float c[3] = { 0, 0, 0 };

        for (int dy = r_min; dy < r_max; ++dy)
          for (int dx = r_min; dx < r_max; ++dx)
          {
            size_type rx = std::max<size_type>(std::min<size_type>(FACT * x + dx, in.width()  - 1), 0);
            size_type ry = std::max<size_type>(std::min<size_type>(FACT * y + dy, in.height() - 1), 0);
            const Color& color = in.at(rx, ry);

            c[0] += color.rf() * k;
            c[1] += color.gf() * k;
            c[2] += color.bf() * k;
          }

        res(x, y) = Color::rgbf(c[0], c[1], c[2]);

        // Color color = Color::rgbf(c[0], c[1], c[2]);
        // std::cout << "res["
        //           << std::dec << std::setfill(' ') << std::setw(4) << x
        //           << ", "
        //           << std::dec << std::setfill(' ') << std::setw(4) << y
        //           << "]: <- #"
        //           << std::hex << std::setfill('0') << std::setw(2) << int(color.r())
        //           << std::hex << std::setfill('0') << std::setw(2) << int(color.g())
        //           << std::hex << std::setfill('0') << std::setw(2) << int(color.b())
        //           << std::endl;
      }

    return res;
  }


  // populate
  //   populates teh bitmap

  Bitmap populate()
  {
    const int d = FACT * STEP;
    Bitmap res(IMW * FACT, IMH * FACT);

    for (size_type y = 0; y < res.height(); y += d)
      for (size_type x = 0; x < res.width(); x += d)
      {
        Shape test = TEST.moved_to(x + d / 2, y + d / 2);
        bool over_ref = mml::overlaps(test, REF);

        for (int dy = 0; dy < d; ++dy)
          for (int dx = 0; dx < d; ++dx)
          {
            Point p(x + dx, y + dy);
            int value = (mml::contains(test, p)
                         ? (over_ref
                            ? 3
                            : 2)
                         : (mml::contains(REF, p)
                            ? 1
                            : 0));
            Color c;

            switch (value)
            {
              case 0: c = C0; break;
              case 1: c = C1; break;
              case 2: c = C2; break;
              case 3: c = C3; break;
              default: assert(false);
            }

            // std::cout << "buffer["
            //           << std::dec << std::setfill(' ') << std::setw(5) << p.x()
            //           << ", "
            //           << std::dec << std::setfill(' ') << std::setw(5) << p.y()
            //           << "]: ("
            //           << over_ref
            //           << ", " << mml::contains(REF, p)
            //           << ", " << mml::contains(test, p)
            //           << ", " << mml::overlaps(test, REF)
            //           << " => " << value << ") <- #"
            //           << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(c.r())
            //           << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(c.g())
            //           << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(c.b())
            //           << std::endl;

            res(p.x(), p.y()) = c;
          }
      }

    return res;
  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

int main()
{
  std::ofstream res_file(OUT);

  if (not res_file.is_open())
    return 1;

  res_file << tools::tga(scale(populate()));

  res_file.close();
}

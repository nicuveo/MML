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
  typedef mml::shapes<int>::Rect Rect;
  typedef mml::Tessellation<int> Tessellation;
  typedef tools::Bitmap Bitmap;
  typedef tools::Color Color;
  typedef tools::Bitmap::size_type size_type;


  // constants

  const int IMW = 1200;
  const int IMH =  900;
  const int DIA =  280;

  const int REF_SIZE = 380;
  const int MOT_SIZE = 100;

  const int FACT   =   4;
  const int   AA   =   1;

  const char* OUT  = "out/tess.tga";

//const Shape REF         = Shape::reg_heptagon(FACT * IMW / 2, FACT * IMH / 2, FACT * DIA, mml::pi() / 2);
  const Shape REF         = Shape::circle(FACT * IMW / 2, FACT * IMH / 2, FACT * REF_SIZE);
  const Tessellation TESS = Tessellation(mml::tiling::RHOMBITRIHEXAGONAL, REF, 150 * FACT, 240 * FACT, FACT * MOT_SIZE, 0.);


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


  // add
  //   add two rgb colors

  Color add(const Color& c1, const Color& c2)
  {
    return Color::rgb(
      std::min(int(c1.r()) + int(c2.r()), 255),
      std::min(int(c1.g()) + int(c2.g()), 255),
      std::min(int(c1.b()) + int(c2.b()), 255));
  }


  // draw_shape
  //   draws a shape on the bitmap

  void draw_shape(Bitmap& b, const Shape& s, const Color& c)
  {
    const Rect bb = s.bounding_rect();
    const size_type xmin = std::max<size_type>(bb.x_min(), 0);
    const size_type ymin = std::max<size_type>(bb.y_min(), 0);
    const size_type xmax = std::min<size_type>(bb.x_max(), b.width()  - 1);
    const size_type ymax = std::min<size_type>(bb.y_max(), b.height() - 1);

    for (size_type y = ymin; y <= ymax; ++y)
      for (size_type x = xmin; x <= xmax; ++x)
        if (mml::contains(s, Point(x, y)))
          b(x, y) = add(b(x, y), c);
  }


  // draw_point
  //   draws a point on the bitmap

  void draw_point(Bitmap& b, const Point& p, const Color& c)
  {
    const int d = 1 * FACT;

    draw_shape(b, Shape::rect(p - Point(d, d), p + Point(d, d)), c);
  }


  // populate
  //   populates teh bitmap

  Bitmap populate()
  {
    Bitmap res(IMW * FACT, IMH * FACT, Color::black);

    for (Tessellation::iterator it = TESS.begin(false, false); it != TESS.end(); ++it)
    {
      Shape const& s = *it;

      Color c;
      switch (it.index() % TESS.pattern().size() % 18)
      {
        case  0: c = Color::rgb(  0,   0, 200); break;
        case  1: c = Color::rgb(  0, 200,   0); break;
        case  2: c = Color::rgb(  0, 200, 200); break;
        case  3: c = Color::rgb(200,   0,   0); break;
        case  4: c = Color::rgb(200,   0, 200); break;
        case  5: c = Color::rgb(200, 200,   0); break;
        case  6: c = Color::rgb(  0, 100, 200); break;
        case  7: c = Color::rgb(  0, 200, 100); break;
        case  8: c = Color::rgb(100,   0, 200); break;
        case  9: c = Color::rgb(100, 200,   0); break;
        case 10: c = Color::rgb(200,   0, 100); break;
        case 11: c = Color::rgb(200, 100,   0); break;
        case 12: c = Color::rgb(  0,   0, 100); break;
        case 13: c = Color::rgb(  0, 100,   0); break;
        case 14: c = Color::rgb(  0, 100, 100); break;
        case 15: c = Color::rgb(100,   0,   0); break;
        case 16: c = Color::rgb(100,   0, 100); break;
        case 17: c = Color::rgb(100, 100,   0); break;
      }

      draw_shape(res, s, c);
    }

    return res;
  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

int main()
{
  Shape draw(REF.circle().polygonize(1024 * FACT));
  Bitmap res = populate();


  mml_foreach (const Point& p, draw.polygon().points_data())
    draw_point(res, p, Color::white);
  draw_point(res, REF.center(), Color::white);


  std::ofstream res_file(OUT);

  if (not res_file.is_open())
    return 1;

  res_file << tools::tga(scale(res));

  res_file.close();
}

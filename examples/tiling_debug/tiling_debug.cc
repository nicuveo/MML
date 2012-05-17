//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <mml/mml.hh>
#include "tools/img/tga.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{


  // types

  typedef mml::shapes<int>::Shape Shape;
  typedef mml::shapes<int>::Point Point;
  typedef mml::shapes<int>::Vector Vector;
  typedef mml::shapes<int>::Line Line;
  typedef mml::shapes<int>::Rect Rect;
  typedef mml::Tessellation<int> Tessellation;
  typedef tools::Bitmap Bitmap;
  typedef tools::Color Color;
  typedef tools::Bitmap::size_type size_type;


  // constants

  const int IMW      = 1600;
  const int IMH      = 1200;
  const int REF_SIZE =  503;

  const int FACT     =   2;
  const int   AA     =   0;

  const Shape REF    = Shape::circle(FACT * IMW / 2, FACT * IMH / 2, FACT * REF_SIZE);


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


  // mul
  //   multiplies a rgb color by a scalar k

  Color mul(const Color& c, float k)
  {
    return Color::rgbf(mml::clamp(c.rf() * k, 0.f, 1.f),
                       mml::clamp(c.gf() * k, 0.f, 1.f),
                       mml::clamp(c.bf() * k, 0.f, 1.f));
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

  void draw_point(Bitmap& b, const Point& p, const Color& c, int k = 1)
  {
    const int d = k * FACT;

    draw_shape(b, Shape::rect(p - Point(d, d), p + Point(d, d)), c);
  }


  // draw_line
  //   draws a line on the bitmap

  void draw_line(Bitmap& b, const Line& l, const Color& c, int k = 0)
  {
    Vector v = l.delta();
    int steps = l.length();
    for (int i = 0; i <= steps; ++i)
      draw_point(b, l[0] + (float(i) / steps) * v, c, k);
  }


  // out
  //   outputs file name

  std::string out(int t, int a, int x)
  {
    std::ostringstream oss;

    oss << "out/t_"
        << std::dec << std::setw(2) << std::setfill('0') << t
        << "_"
        << std::dec << std::setw(3) << std::setfill('0') << a
        << "_"
        << std::dec << std::setw(3) << std::setfill('0') << x
        << ".tga";

    return oss.str();
  }


  // populate
  //   populates teh bitmap

  Bitmap populate(mml::TilingType type, int a, int x)
  {
    Shape draw(REF.circle().polygonize(1024 * FACT));
    Bitmap res(IMW * FACT, IMH * FACT, Color::black);

    Tessellation tess(type, REF, FACT * x, 0, (a * (2 * mml::pi()) / 360.));
    std::map<unsigned, Point> links_ref;

    for (Tessellation::iterator it = tess.begin(true, true); it != tess.end(); ++it)
    {
      Point center = it->center();
      links_ref[it.index()] = center;
      Color c;

      switch ((it.index() / (tess.pattern().size())) % 6)
      {
        case  0: c = Color::rgb(  0,   0, 200); break;
        case  1: c = Color::rgb(  0, 200,   0); break;
        case  2: c = Color::rgb(  0, 200, 200); break;
        case  3: c = Color::rgb(200,   0,   0); break;
        case  4: c = Color::rgb(200,   0, 200); break;
        case  5: c = Color::rgb(200, 200,   0); break;
      }

      int i = (it.index() % tess.pattern().size()) + 1;
      c = mul(c, 0.2 + 0.8 * (i / float(tess.pattern().size())));

      draw_shape(res, *it, c);

      mml_foreach (unsigned nid, it.links())
      {
        if (links_ref.find(nid) != links_ref.end())
          draw_line(res, Line(center, links_ref[nid]), Color::white);
      }
    }

    mml_foreach (const Point& p, draw.polygon().points_data())
      draw_point(res, p, Color::white);
    draw_point(res, REF.center(), Color::white);

    return res;
  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

int main()
{
  mml::TilingType tts[] =
  {
    mml::tiling::TRIANGULAR,
    mml::tiling::SQUARE,
    mml::tiling::HEXAGONAL,

    mml::tiling::SNUB_HEXAGONAL,
    mml::tiling::REFLECTED_SNUB_HEXAGONAL,
    mml::tiling::TRI_HEXAGONAL,
    mml::tiling::ELONGATED_TRIANGULAR,
    mml::tiling::SNUB_SQUARE,
    mml::tiling::RHOMBITRIHEXAGONAL,
    mml::tiling::TRUNCATED_SQUARE,
    mml::tiling::TRUNCATED_HEXAGONAL,
    mml::tiling::TRUNCATED_TRIHEXAGONAL
  };

  for (unsigned t = 0; t < (sizeof (tts) / sizeof (mml::TilingType)); ++t)
    for (int a = 0; a < 360; a += 90)
      for (int x = 50; x <= 200; x += 50)
      {
        Bitmap res = populate(tts[t], a, x);

        std::string ofn = out(t, a, x);
        std::ofstream res_file(ofn.c_str());
        if (not res_file.is_open())
          std::exit(1);

        res_file << tools::tga(scale(res));
        res_file.close();

        std::cout << ">>> " << ofn << std::endl;
      }
}

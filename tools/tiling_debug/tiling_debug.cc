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

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <nauths/mml/mml.hh>
#include "img/io/tga.hh"



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


  // next color
  //  picks a color according to a key

  template <typename Key>
  Color next_color(Key k)
  {
    static Color colors[] = { Color::red,
                              Color::green,
                              Color::blue,
                              Color::yellow,
                              Color::cyan,
                              Color::magenta,
                              Color::cyan,
                              Color::yellow,
                              Color::blue,
                              Color::green };

    static int size = sizeof(colors) / sizeof(Color);
    static int current = 0;
    static std::map<Key, int> color_indices;

    static bool first = true;

    if (first)
    {
      first = false;
      std::cout << size << ", " << sizeof(colors) << ", " << sizeof(Color) << std::endl;
    }

    typename std::map<Key, int>::const_iterator it = color_indices.find(k);

    if (it != color_indices.end())
      return colors[it->second];

    const Color& c = colors[current % size];
    std::cout << current << ": ("
              << std::right << std::setw(3) << int(c.r())
              << ", "
              << std::right << std::setw(3) << int(c.g())
              << ", "
              << std::right << std::setw(3) << int(c.b())
              << ")" <<std::endl;

    color_indices[k] = current % size;
    return colors[current++ % size];
  }


  // draw_shape
  //   draws a shape on the bitmap

  void draw_shape(Bitmap& b, const Shape& s, const Color& c, bool override = false)
  {
    const Rect bb = s.bounding_rect();
    const size_type xmin = std::max<size_type>(bb.x_min(), 0);
    const size_type ymin = std::max<size_type>(bb.y_min(), 0);
    const size_type xmax = std::min<size_type>(bb.x_max(), b.width()  - 1);
    const size_type ymax = std::min<size_type>(bb.y_max(), b.height() - 1);

    for (size_type y = ymin; y <= ymax; ++y)
      for (size_type x = xmin; x <= xmax; ++x)
        if (mml::contains(s, Point(x, y)))
        {
          if (override)
            b(x, y) = c;
          else
            b(x, y) = add(b(x, y), c);
        }
  }


  // draw_point
  //   draws a point on the bitmap

  void draw_point(Bitmap& b, const Point& p, const Color& c, int k = 1, bool override = false)
  {
    const int d = k * FACT;

    draw_shape(b, Shape::rect(p - Point(d, d), p + Point(d, d)), c, override);
  }


  // draw_line
  //   draws a line on the bitmap

  void draw_line(Bitmap& b, const Line& l, const Color& c, int k = 0, bool override = false)
  {
    Vector v = l.delta();
    int steps = l.length();
    for (int i = 0; i <= steps; ++i)
      draw_point(b, l[0] + (float(i) / steps) * v, c, k, override);
  }


  // out
  //   outputs file name

  std::string out(int t, int a, int x, int m)
  {
    std::ostringstream oss;

    oss << "out/t_"
        << std::dec << std::setw(2) << std::setfill('0') << t
        << "_"
        << std::dec << std::setw(3) << std::setfill('0') << a
        << "_"
        << std::dec << std::setw(3) << std::setfill('0') << x
        << "_"
        << m
        << ".tga";

    return oss.str();
  }


  // populate
  //   populates teh bitmap

  Bitmap populate(mml::TilingType type, int a, int x, int m)
  {
    Shape draw(REF);
    Bitmap res(IMW * FACT, IMH * FACT, Color::black);
    std::set<double> dbs;

    Tessellation tess(type, REF, FACT * x, (a * (2 * mml::pi()) / 360.));
    std::map<unsigned, Point> links_ref;

    for (Tessellation::iterator it = tess.begin(true, true); it != tess.end(); ++it)
    {
      Point center = it->center();
      links_ref[it.index()] = center;
      Color c;

      switch ((it.index() / (tess.pattern().size())) % 6)
      {
        case  0: c = Color::rgb(  0,   0, 220); break;
        case  1: c = Color::rgb(  0, 220,   0); break;
        case  2: c = Color::rgb(  0, 220, 220); break;
        case  3: c = Color::rgb(220,   0,   0); break;
        case  4: c = Color::rgb(220,   0, 220); break;
        case  5: c = Color::rgb(220, 220,   0); break;
      }

      int i = (it.index() % tess.pattern().size()) + 1;
      c = mul(c, 0.4 + 0.6 * (i / float(tess.pattern().size())));

      if (m == 0 or m == 4)
        draw_shape(res, *it, c);

      if (m == 0 or m == 1 or m == 3 or m == 5)
        for (const Line& l : it->polygon().lines())
          draw_line(res, l, Color::white, 1);

      for (const Tessellation::Link& nid : it.links())
      {
        if (links_ref.find(nid.first) != links_ref.end())
        {
          Line l(center, links_ref[nid.first]);

          switch (m)
          {
            // case 0:
            // {
            //   draw_line(res, l, Color::white);
            //   break;
            // }

            case 1:
            {
              draw_line(res, l, next_color(nid.second + type), 1);
              break;
            }

            case 5:
            {
              draw_line(res, l, next_color(l.delta().length()), 1);
              break;
            }

            case 2:
            {
              double d = l.length();
              double k = std::abs(d - nid.second) / d;
              float coeff = mml::clamp<float>(k, 0, 1.f);

              if (k >= 0.01 and dbs.find(k) == dbs.end())
              {
                std::cout << "  " << int(k * 10000 + 0.5) / 100. << "%" << std::endl;
                dbs.insert(k);
              }

              draw_line(res, l, Color::grayf(coeff), 2, true);
              break;
            }

            default:
              break;
          }
        }
      }
    }

    switch (m)
    {
      case 3:
      case 4:
        break;

      default:
        // for (const Point& p : draw.polygon().points_data())
        //   draw_point(res, p, Color::white);
        // draw_point(res, REF.center(), Color::white);
        break;
    }

    return res;
  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

static const  mml::TilingType tts[] =
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


void render(unsigned t, int a, int x, int m)
{
  Bitmap res = populate(tts[t], a, x, m);
  std::string ofn = out(t, a, x, m);
  std::ofstream res_file(ofn.c_str());
  if (not res_file.is_open())
    std::exit(1);

  res_file << tools::tga(scale(res));
  res_file.close();

  std::cout << ">>> " << ofn << std::endl;
}


int main()
{
  for (unsigned t = 0; t < (sizeof (tts) / sizeof (mml::TilingType)); ++t)
    for (int x = 50; x <= 400; x *= 2)
    {
      render(t, 0, x, 0);
      render(t, 0, x, 1);
    }
}

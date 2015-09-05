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

#include <cmath>
#include "img/color.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  inline float max3(float r, float g, float b)
  {
    return g > b
      ? (r > g ? r : g)
      : (r > b ? r : b);
  }

  inline float min3(float r, float g, float b)
  {
    return g < b
      ? (r < g ? r : g)
      : (r < b ? r : b);
  }

  inline void hmod(float& h)
  {
    while (h <   0.f) h += 360.f;
    while (h > 360.f) h -= 360.f;
  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace tools
{


  const Color Color::black       = Color::rgb(  0,   0,   0, 255);
  const Color Color::blue        = Color::rgb(  0,   0, 255, 255);
  const Color Color::green       = Color::rgb(  0, 255,   0, 255);
  const Color Color::cyan        = Color::rgb(  0, 255, 255, 255);
  const Color Color::red         = Color::rgb(255,   0,   0, 255);
  const Color Color::magenta     = Color::rgb(255,   0, 255, 255);
  const Color Color::yellow      = Color::rgb(255, 255,   0, 255);
  const Color Color::white       = Color::rgb(255, 255, 255, 255);
  const Color Color::transparent = Color::rgb(255, 255, 255,   0);


  Color::Color()
  {
  }

  Color::Color(const Data& d)
    : p_(d)
  {
  }


  Color Color::rgbf(float r, float g, float b, float a)
  {
    Data res = {{ r, g, b, 0, 0, 0, a }};
    float tmp;
    float min;

    tmp = max3(r, g, b);
    if (tmp == 0)
      return res;
    res[V] = tmp;

    r /= tmp;
    g /= tmp;
    b /= tmp;
    min = min3(r, g, b);
    tmp = max3(r, g, b) - min;
    if (tmp == 0)
      return res;
    res[S] = tmp;

    r = (r - min) / tmp;
    g = (g - min) / tmp;
    b = (b - min) / tmp;
    tmp = max3(r, g, b);

    if (tmp == b)
      res[H] = 240.f + 60.f * (r - g);
    else if (tmp == g)
      res[H] = 120.f + 60.f * (b - r);
    else
      res[H] = (g < b ? 360.f : 0.f) + 60.f * (g - b);

    hmod(res[H]);

    return res;
  }

  Color Color::hsvf(float h, float s, float v, float a)
  {
    hmod(h);

    Data res = {{0, 0, 0, h, s, v, a }};
    float c = s * v;
    float m = v - c;
    float k = h / 60.f;
    int   i = int(k) % 6;
    float x = c * (1 - std::abs(std::fmod(k, 2.f) - 1));

    c += m;
    x += m;

    switch (i)
    {
      case 0: res[R] = c; res[G] = x; res[B] = m; break;
      case 1: res[R] = x; res[G] = c; res[B] = m; break;
      case 2: res[R] = m; res[G] = c; res[B] = x; break;
      case 3: res[R] = m; res[G] = x; res[B] = c; break;
      case 4: res[R] = x; res[G] = m; res[B] = c; break;
      case 5: res[R] = c; res[G] = m; res[B] = x; break;
    }

    return res;
  }



  Color mix_hsv(const Color& c1, const Color& c2, float k)
  {
    if (c1.hf() > c2.hf())
      return mix_hsv(c2, c1, 1.f - k);

    float c1dhfpp = (c2.hf() - c1.hf() > 180.f ? 360.f : 0) + c1.hf();
    return Color::hsvf(c1dhfpp * (1.f - k) + c2.hf() * k,
                       c1.sf() * (1.f - k) + c2.sf() * k,
                       c1.vf() * (1.f - k) + c2.vf() * k,
                       c1.af() * (1.f - k) + c2.af() * k);
  }


}

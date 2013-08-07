//
// color.hxx for tools
// Made by nicuveo <crucuny@gmail.com>
//


#ifndef TOOLS_COLOR_HXX_
# define TOOLS_COLOR_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "img/color.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace tools
{


  inline Color Color::rgb(byte r, byte g, byte b, byte a)
  {
    return rgbf(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
  }

  inline Color Color::hsv(short h, byte s, byte v, byte a)
  {
    return hsvf(float(h), s / 255.f, v / 255.f, a / 255.f);
  }


  inline Color Color::gray(byte g, byte a)
  {
    return rgb(g, g, g, a);
  }

  inline Color Color::grayf(float g, float a)
  {
    return rgbf(g, g, g, a);
  }


  inline float
  Color::operator[](unsigned i) const
  {
    assert(i < SIZE);
    return p_[i];
  }

  inline float&
  Color::operator[](unsigned i)
  {
    assert(i < SIZE);
    return p_[i];
  }

  inline float
  Color::getf(unsigned i) const
  {
    return (*this)[i];
  }

  inline byte
  Color::get(unsigned i) const
  {
    return static_cast<byte>(std::floor(0.5f + (getf(i) * 255)));
  }


  inline bool
  Color::operator==(const Color& c) const
  {
    return p_ == c.p_;
  }

  inline bool
  Color::operator!=(const Color& c) const
  {
    return not (*this == c);
  }


  inline byte  Color::r()  const { return get (R); }
  inline byte  Color::g()  const { return get (G); }
  inline byte  Color::b()  const { return get (B); }
  inline byte  Color::s()  const { return get (S); }
  inline byte  Color::v()  const { return get (V); }
  inline byte  Color::a()  const { return get (A); }
  inline float Color::rf() const { return getf(R); }
  inline float Color::gf() const { return getf(G); }
  inline float Color::bf() const { return getf(B); }
  inline float Color::hf() const { return getf(H); }
  inline float Color::sf() const { return getf(S); }
  inline float Color::vf() const { return getf(V); }
  inline float Color::af() const { return getf(A); }

  inline short Color::h()  const { return short(getf(H) + 0.5); }

  inline byte  Color::gray()  const { return byte(short(gf() * 255));    }
  inline float Color::grayf() const { return (rf() + gf() + bf()) / 3.f; }


  inline void Color::set_r(byte   i) { *this = rgb (   i,  g(),  b(),  a()); }
  inline void Color::set_g(byte   i) { *this = rgb ( r(),    i,  b(),  a()); }
  inline void Color::set_b(byte   i) { *this = rgb ( r(),  g(),    i,  a()); }
  inline void Color::set_h(short  i) { *this = hsv (   i,  s(),  v(),  a()); }
  inline void Color::set_s(byte   i) { *this = hsv ( h(),    i,  v(),  a()); }
  inline void Color::set_v(byte   i) { *this = hsv ( h(),  s(),    i,  a()); }
  inline void Color::set_rf(float f) { *this = rgbf(   f, gf(), bf(), af()); }
  inline void Color::set_gf(float f) { *this = rgbf(rf(),    f, bf(), af()); }
  inline void Color::set_bf(float f) { *this = rgbf(rf(), gf(),    f, af()); }
  inline void Color::set_hf(float f) { *this = hsvf(   f, sf(), vf(), af()); }
  inline void Color::set_sf(float f) { *this = hsvf(hf(),    f, vf(), af()); }
  inline void Color::set_vf(float f) { *this = hsvf(hf(), sf(),    f, af()); }

  inline void Color::set_a(byte b)   { p_[A] = b / 255.f; }
  inline void Color::set_af(float f) { p_[A] = f;         }

  inline void Color::set_gray(byte g)   { *this = rgb (g, g, g,  a()); }
  inline void Color::set_grayf(float g) { *this = rgbf(g, g, g, af()); }



  inline Color mix_rgb(const Color& c1, const Color& c2, float k)
  {
    return Color::rgbf(c1.rf() * (1.f - k) + c2.rf() * k,
                       c1.gf() * (1.f - k) + c2.gf() * k,
                       c1.bf() * (1.f - k) + c2.bf() * k,
                       c1.af() * (1.f - k) + c2.af() * k);
  }


}



#endif /* !TOOLS_COLOR_HXX_ */

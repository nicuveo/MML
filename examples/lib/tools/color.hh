//
// color.hh for tools
// Made by nicuveo <crucuny@gmail.com>
//


#ifndef TOOLS_COLOR_HH_
# define TOOLS_COLOR_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Include

# include <cmath>
# include <cassert>
# include <boost/array.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  typedef unsigned char byte;

  class Color
  {
    public:
      enum Key
      {
        R, G, B,
        H, S, V,
        A,

        SIZE
      };

      Color();

      static Color rgb(byte r, byte g, byte b, byte a = 255);
      static Color hsv(byte h, byte s, byte v, byte a = 255);
      static Color rgbf(float r, float g, float b, float a = 1.f);
      static Color hsvf(float h, float s, float v, float a = 1.f);

      float operator[](unsigned i) const;
      float getf(unsigned i) const;
      byte get(unsigned i) const;

      bool operator==(const Color& c) const;
      bool operator!=(const Color& c) const;

      byte r() const;
      byte g() const;
      byte b() const;
      byte h() const;
      byte s() const;
      byte v() const;
      byte a() const;
      float rf() const;
      float gf() const;
      float bf() const;
      float hf() const;
      float sf() const;
      float vf() const;
      float af() const;

      void set_r(byte b);
      void set_g(byte b);
      void set_b(byte b);
      void set_h(byte b);
      void set_s(byte b);
      void set_v(byte b);
      void set_a(byte b);
      void set_rf(float f);
      void set_gf(float f);
      void set_bf(float f);
      void set_hf(float f);
      void set_sf(float f);
      void set_vf(float f);
      void set_af(float f);

      static const Color red;
      static const Color cyan;
      static const Color blue;
      static const Color green;
      static const Color black;
      static const Color white;
      static const Color yellow;
      static const Color magenta;
      static const Color transparent;

    private:
      typedef boost::array<float, SIZE> Data;

      Color(const Data& d);

      float& operator[](unsigned i);

      Data p_;
  };


  Color mix_rgb(const Color& c1, const Color& c2, float balance = 0.5f);
  Color mix_hsv(const Color& c1, const Color& c2, float balance = 0.5f);


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "color.hxx"



#endif // !TOOLS_COLOR_HH_

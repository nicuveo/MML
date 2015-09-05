//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef TOOLS_BITMAP_HH_
# define TOOLS_BITMAP_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include "img/color.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  class Bitmap
  {
    public:
      typedef std::vector<Color> Data;
      typedef Data::size_type size_type;

      Bitmap();
      Bitmap(size_type w, size_type h, const Data& data);
      Bitmap(size_type w, size_type h, const Color& c = Color::transparent);

      bool empty() const;

            Color& operator()(size_type x, size_type y);
      const Color& operator()(size_type x, size_type y) const;
            Color& at(size_type x, size_type y);
      const Color& at(size_type x, size_type y) const;

      size_type width() const;
      size_type height() const;
      const Data& data() const;

      Bitmap& scale_to_width(size_type w);
      Bitmap  scaled_to_width(size_type w) const;
      Bitmap& scale_to_height(size_type h);
      Bitmap  scaled_to_height(size_type h) const;
      Bitmap& scale(size_type w, size_type h, bool ratio = false);
      Bitmap  scaled(size_type w, size_type h, bool ratio = false) const;

      Bitmap& grayscale();
      Bitmap  grayscaled() const;
      Bitmap& multiply(const Color& c);
      Bitmap  multiplied(const Color& c) const;

    protected:
      size_type width_;
      size_type height_;
      Data data_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "img/bitmap.hxx"



#endif /* !TOOLS_BITMAP_HH_ */

//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include "img/bitmap.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace tools
{


  Bitmap::Bitmap()
    : width_(0), height_(0)
  {
  }

  Bitmap::Bitmap(size_type w, size_type h, const Data& data)
    : width_(w), height_(h), data_(data)
  {
    assert(data.size() == w * h);
  }

  Bitmap::Bitmap(size_type w, size_type h, const Color& c)
    : width_(w), height_(h), data_(w * h, c)
  {
  }


  Bitmap
  Bitmap::scaled_to_width(size_type) const
  {
    return *this;
  }

  Bitmap
  Bitmap::scaled_to_height(size_type) const
  {
    return *this;
  }

  Bitmap
  Bitmap::scaled(size_type, size_type, bool) const
  {
    return *this;
  }


  Bitmap
  Bitmap::grayscaled() const
  {
    return *this;
  }

  Bitmap
  Bitmap::multiplied(const Color&) const
  {
    return *this;
  }


}

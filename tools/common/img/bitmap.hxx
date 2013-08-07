//
// bitmap.hxx for tools
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef TOOLS_BITMAP_HXX_
# define TOOLS_BITMAP_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "img/bitmap.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace tools
{


  inline bool
  Bitmap::empty() const
  {
    return data_.empty();
  }


  inline Color&
  Bitmap::operator()(size_type x, size_type y)
  {
    return data_[y * width_ + x];
  }

  inline const Color&
  Bitmap::operator()(size_type x, size_type y) const
  {
    return data_[y * width_ + x];
  }

  inline Color&
  Bitmap::at(size_type x, size_type y)
  {
    return data_.at(y * width_ + x);
  }

  inline const Color&
  Bitmap::at(size_type x, size_type y) const
  {
    return data_.at(y * width_ + x);
  }


  inline Bitmap::size_type
  Bitmap::width() const
  {
    return width_;
  }

  inline Bitmap::size_type
  Bitmap::height() const
  {
    return height_;
  }

  inline const Bitmap::Data&
  Bitmap::data() const
  {
    return data_;
  }


  inline Bitmap&
  Bitmap::scale_to_width(size_type w)
  {
    *this = scaled_to_width(w);
    return *this;
  }

  inline Bitmap&
  Bitmap::scale_to_height(size_type h)
  {
    *this = scaled_to_height(h);
    return *this;
  }

  inline Bitmap&
  Bitmap::scale(size_type w, size_type h, bool ratio)
  {
    *this = scaled(w, h, ratio);
    return *this;
  }


}



#endif /* !TOOLS_BITMAP_HXX_ */

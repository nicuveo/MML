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

# include <stdexcept>
# include "img/io/tga.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace tools
{

  namespace img
  {


    template <typename T>
    void
    Tga<T>::read(std::istream&)
    {
      throw std::logic_error("not implemented yet");
    }

    template <typename T>
    void
    Tga<T>::write(std::ostream& ostr) const
    {
      const Bitmap& img = this->img_;

      ostr
        .put(byte(0))                  // size of ID field that follows 18 byte header (byte(0 usually))
        .put(byte(0))                  // type of colour map 0=none, 1=has palette
        .put(byte(2))                  // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
        .put(byte(0))                  // .
        .put(byte(0))                  // first colour map entry in palette
        .put(byte(0))                  // .
        .put(byte(0))                  // number of colours in palette
        .put(byte(32))                 // number of bits per palette entry 15,16,24,32
        .put(byte(0))                  // .
        .put(byte(0))                  // image x origin
        .put(byte(0))                  // .
        .put(byte(0))                  // image y origin
        .put(byte(img.width()  % 256)) // .
        .put(byte(img.width()  / 256)) // image width in pixels
        .put(byte(img.height() % 256)) // .
        .put(byte(img.height() / 256)) // image width in pixels
        .put(byte(32))                 // image bits per pixel 8,16,24,32
        .put(byte(0));                 // image descriptor bits (byte(vh flip bits))

      for (Bitmap::size_type y = 0; y < img.height(); ++y)
        for (Bitmap::size_type x = 0; x < img.width(); ++x)
        {
          const Color& c = img.at(x, y);
          ostr.put(c.b()).put(c.g()).put(c.r()).put(c.a());
        }
    }

  }


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Instantiation

template class tools::img::Tga<tools::Bitmap&>;
template class tools::img::Tga<tools::Bitmap const&>;

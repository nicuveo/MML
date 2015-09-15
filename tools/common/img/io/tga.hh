//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef TOOLS_TGA_HH_
# define TOOLS_TGA_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "img/io/img_io.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  template <typename T>
  class Tga : public ImgIO<T>
  {
    public:
      Tga(T b)
        : ImgIO<T>(b)
      {
      }

      void read(std::istream&);
      void write(std::ostream&) const;
  };

  inline Tga<Bitmap&>       tga(Bitmap& b)       { return Tga<Bitmap&>(b);       }
  inline Tga<Bitmap const&> tga(Bitmap const& b) { return Tga<Bitmap const&>(b); }

}



#endif /* !TOOLS_TGA_HH_ */

//
// tga.hh for tools
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef TOOLS_TGA_HH_
# define TOOLS_TGA_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "img_io.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  namespace img
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

  }

  inline img::Tga<Bitmap&>       tga(Bitmap& b)       { return img::Tga<Bitmap&>(b);       }
  inline img::Tga<Bitmap const&> tga(Bitmap const& b) { return img::Tga<Bitmap const&>(b); }

}



#endif /* !TOOLS_TGA_HH_ */

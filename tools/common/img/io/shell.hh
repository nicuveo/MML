//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef TOOLS_SHELL_HH_
# define TOOLS_SHELL_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "img/io/img_io.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  namespace img
  {

    template <typename T>
    class Shell : public ImgIO<T>
    {
      public:
        Shell(T b)
          : ImgIO<T>(b)
        {
        }

        void read(std::istream&);
        void write(std::ostream&) const;
    };

  }

  inline img::Shell<Bitmap&>       shell(Bitmap& b)       { return img::Shell<Bitmap&>(b);       }
  inline img::Shell<Bitmap const&> shell(Bitmap const& b) { return img::Shell<Bitmap const&>(b); }

}



#endif /* !TOOLS_SHELL_HH_ */

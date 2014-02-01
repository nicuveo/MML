//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef TOOLS_IMG_IO_HH_
# define TOOLS_IMG_IO_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "img/io/rwops.hh"
# include "img/bitmap.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{


  template <typename T>
  class ImgIO : public Reader, public Writer
  {
    public:
      ImgIO(T b)
        : img_(b)
      {
      }

    protected:
      T img_;
  };

}



#endif /* !TOOLS_IMG_IO_HH_ */

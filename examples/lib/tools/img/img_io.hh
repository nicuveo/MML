//
// img_io.hh for tools
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef TOOLS_IMG_IO_HH_
# define TOOLS_IMG_IO_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "rwops.hh"
# include "bitmap.hh"



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

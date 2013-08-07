//
// shell.hxx for tools
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <stdexcept>
# include "img/io/shell.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  const char* cnul = "\033[m \033[m";
  const char* c000 = "\033[40m \033[m";
  const char* c100 = "\033[41m \033[m";
  const char* c010 = "\033[42m \033[m";
  const char* c110 = "\033[43m \033[m";
  const char* c001 = "\033[44m \033[m";
  const char* c101 = "\033[45m \033[m";
  const char* c011 = "\033[46m \033[m";
  const char* c111 = "\033[47m \033[m";


  inline const char* c(const tools::Color& c)
  {
    return (c.a() < 128
            ? cnul
            : (c.r()       < 128
               ? (c.g()    < 128
                  ? (c.b() < 128
                     ? c000
                     : c001)
                  : (c.b() < 128
                     ? c010
                     : c011))
               : (c.g()    < 128
                  ? (c.b() < 128
                     ? c100
                     : c101)
                  : (c.b() < 128
                     ? c110
                     : c111))));
  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace tools
{

  namespace img
  {


    template <typename T>
    void
    Shell<T>::read(std::istream&)
    {
      throw std::logic_error("not implemented yet");
    }

    template <typename T>
    void
    Shell<T>::write(std::ostream& ostr) const
    {
      const Bitmap& img = this->img_;

      for (Bitmap::size_type y = 0; y < img.height(); ++y)
      {
        for (Bitmap::size_type x = 0; x < img.width(); ++x)
          ostr << c(img.at(x, y));
        ostr << std::endl;
      }
    }

  }


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Instantiation

template class tools::img::Shell<tools::img::Bitmap&>;
template class tools::img::Shell<tools::img::Bitmap const&>;

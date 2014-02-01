//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef TOOLS_RWOPS_HH_
# define TOOLS_RWOPS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/typeof/typeof.hpp>
# include <boost/type_traits.hpp>
# include <iostream>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  // base class (static checking)

  class Reader
  {
    public:
      virtual void read(std::istream&) = 0;
  };

  class Writer
  {
    public:
      virtual void write(std::ostream&) const = 0;
  };


  // operators

  template <typename T>
  inline typename boost::enable_if<boost::is_base_of<Reader, T>, std::istream&>::type
  operator>>(std::istream& istr, T r)
  {
    r.read(istr);
    return istr;
  }

  template <typename T>
  inline typename boost::enable_if<boost::is_base_of<Writer, T>, std::ostream&>::type
  operator<<(std::ostream& ostr, T w)
  {
    w.write(ostr);
    return ostr;
  }

}



#endif /* !TOOLS_RWOPS_HH_ */

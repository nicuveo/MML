//
// real.hh for tools
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef TOOLS_REAL_HH_
# define TOOLS_REAL_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/call_traits.hpp>
# include <iostream>
# include <iomanip>
# include <limits>
# include <cmath>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  template <typename T, int P>
  class Real
  {
    public:
      typedef T ValueType;

      template <typename U>
      Real(U const& r) : data_(r) {}
      Real(T r = T())  : data_(r) {}

      template <typename U>
      Real& operator=(U const& r) { data_ = r; return *this; }
      Real& operator=(T r)        { data_ = r; return *this; }

      operator T() const          { return data_; }
      operator T&()               { return data_; }

      static const T epsilon;

    private:
      T data_;
  };


  template <typename T, int P>
  const T Real<T, P>::epsilon = std::pow(T(10), P);


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Traits

namespace std
{

  template <class T, int P>
  class numeric_limits<tools::Real<T, P> > : public numeric_limits<T>
  {
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Comparison operators

template <typename T, int P>
inline bool operator<(tools::Real<T, P> const& r1, tools::Real<T, P> const& r2)
{
  return (T(r1) == T(r2) ? false : ((T(r2) - T(r1)) >= tools::Real<T, P>::epsilon));
}

template <typename T, int P>
inline bool operator<=(tools::Real<T, P> const& r1, tools::Real<T, P> const& r2)
{
  return (T(r1) == T(r2) ? true : ((T(r2) - T(r1)) > -tools::Real<T, P>::epsilon));
}

template <typename T, int P>
inline bool operator==(tools::Real<T, P> const& r1, tools::Real<T, P> const& r2)
{
  return (T(r1) == T(r2) ? true : (std::abs(T(r2) - T(r1)) < tools::Real<T, P>::epsilon));
}

template <typename T, int P>
inline bool operator>(tools::Real<T, P> const& r1, tools::Real<T, P> const& r2)
{
  return (r2 < r1);
}

template <typename T, int P>
inline bool operator>=(tools::Real<T, P> const& r1, tools::Real<T, P> const& r2)
{
  return (r2 <= r1);
}

template <typename T, int P>
inline bool operator!=(tools::Real<T, P> const& r1, tools::Real<T, P> const& r2)
{
  return not (r1 == r2);
}



#endif /* !TOOLS_REAL_HH_ */

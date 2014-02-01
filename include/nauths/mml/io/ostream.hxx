//
// ostream.hxx for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_OSTREAM_HXX_
# define MML_OSTREAM_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/io/ostream.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_output(_1, ostr, S)               \
  case shape::MMLM_NAME(S):                     \
  ostr << s.MMLM_name(S)(); break;              \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace mml
{

  namespace local
  {

    template <typename T>
    inline void
    header(std::ostream& ostr, char c)
    {
      ostr << c << '<' << ((typeid (T)).name()) << '>';
    }

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {

    template <typename T>
    inline std::ostream&
    operator<<(std::ostream& ostr, const Shape<T>& s)
    {
      switch (s.type())
      {
        case shape::EMPTY: ostr << "Empty"; break;
        BOOST_PP_SEQ_FOR_EACH(MMLM_output, ostr, MMLM_SHAPES)
      }

      return ostr;
    }

    template <typename T>
    inline std::ostream&
    operator<<(std::ostream& ostr, const Point<T>& p)
    {
      local::header<T>(ostr, 'P');
      ostr << "(" << p.x() << ", " << p.y() << ")";

      return ostr;
    }

    template <typename T>
    inline std::ostream&
    operator<<(std::ostream& ostr, const Line<T>& l)
    {
      local::header<T>(ostr, 'L');
      const Point<T>& p1 = l[0];
      const Point<T>& p2 = l[1];
      ostr << "(("
           << p1.x() << ", " << p1.y()
           << ") -> ("
           << p2.x() << ", " << p2.y()
           << "))";

      return ostr;
    }

    template <typename T>
    inline std::ostream&
    operator<<(std::ostream& ostr, const Rect<T>& r)
    {
      local::header<T>(ostr, 'R');
      ostr << "(("
           << r.x_min() << ", " << r.y_min()
           << ") -> ("
           << r.x_max() << ", " << r.y_max()
           << "))";

      return ostr;
    }

    template <typename T>
    inline std::ostream&
    operator<<(std::ostream& ostr, const Circle<T>& c)
    {
      local::header<T>(ostr, 'C');
      ostr << "(("
           << c.center().x() << ", " << c.center().y()
           << "), "
           << c.radius()
           << ")";

      return ostr;
    }

    template <typename T>
    inline std::ostream&
    operator<<(std::ostream& ostr, const Polygon<T>& p)
    {
      typename Polygon<T>::SizeType i;
      typename Polygon<T>::SizeType n;

      local::header<T>(ostr, 'G');
      ostr << "(";
      for (i = 0, n = p.size(); i < n; ++i)
      {
        const Point<T>& pp = p.points_data()[i];
        if (i)
          ostr << " - ";
        ostr << "(" << pp.x() << ", " << pp.y() << ")";
      }
      ostr << ")";

      return ostr;
    }

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_output



#endif /* !MML_OSTREAM_HXX_ */

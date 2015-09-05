//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef TOOLS_DUAL_ITERATOR_HH_
# define TOOLS_DUAL_ITERATOR_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/iterator/iterator_adaptor.hpp>
# include <boost/tuple/tuple.hpp>
# include <boost/call_traits.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  namespace il
  {

    template <typename C>
    struct DualTrait
    {
      public:
        typedef C ContainerType;
        typedef typename ContainerType::value_type ValueType;
        typedef typename ContainerType::const_iterator IteratorType;
        typedef typename boost::call_traits<ValueType>::param_type RefType;
        typedef boost::tuple<RefType, RefType> DualType;
    };

    template <typename E, typename C>
    struct AdaptorTrait
    {
      public:
        typedef boost::iterator_adaptor<
        E,
        typename DualTrait<C>::IteratorType,
        typename DualTrait<C>::DualType,
        boost::use_default,
        typename DualTrait<C>::DualType> AdaptorType;
    };

  }


  template <typename C>
  class DualIterator : public il::AdaptorTrait<DualIterator<C>, C>::AdaptorType
  {
    public:
      // types

      typedef DualIterator<C> SelfType;
      typedef il::DualTrait<C> TraitType;
      typedef typename il::AdaptorTrait<SelfType, C>::AdaptorType AdaptorType;
      typedef typename TraitType::IteratorType IteratorType;
      typedef typename TraitType::DualType DualType;
      typedef typename TraitType::RefType RefType;


      // constructors

      DualIterator()
      {
      }

      template <typename I>
      DualIterator(I const& other)
      : AdaptorType(other), b_(other.b_), e_(other.e_)
      {
      }

      template <typename I>
      DualIterator(I const& b, I const& e, I const& i)
        : AdaptorType(i), b_(b), e_(e)
      {
      }

    private:
      friend class boost::iterator_core_access;


      // data

      IteratorType b_;
      IteratorType e_;


      // internal operations

      DualType dereference() const
      {
        IteratorType i1 = this->base_reference();
        IteratorType i2 = i1;

        if (++i2 == e_)
          i2 = b_;

        return boost::tie(*i1, *i2);
      }
  };


  template <typename C>
  struct DualType
  {
    public:
      typedef typename DualIterator<C>::DualType Type;
  };


  template <typename C>
  inline DualIterator<C> begin(C const& c)
  {
    return DualIterator<C>(c.begin(), c.end(), c.begin());
  }

  template <typename C>
  inline DualIterator<C> end(C const& c)
  {
    return DualIterator<C>(c.begin(), c.end(), c.end());
  }

  template <typename C>
  inline std::pair<DualIterator<C>, DualIterator<C> > range(C const& c)
  {
    return std::make_pair(begin(c), end(c));
  }


  template <typename T1, typename T2>
  inline typename boost::call_traits<T1>::const_reference
  first(boost::tuple<T1, T2> const& dt)
  {
    return dt.template get<0>();
  }

  template <typename T1, typename T2>
  inline typename boost::call_traits<T2>::const_reference
  second(boost::tuple<T1, T2> const& dt)
  {
    return dt.template get<1>();
  }


}



#endif /* !TOOLS_DUAL_ITERATOR_HH_ */

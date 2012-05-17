#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <boost/foreach.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/utility.hpp>
#include <iterator>
#include <vector>


template <typename Value, typename Iterator>
struct AnyTrait
{
  public:
    typedef typename std::iterator_traits<Iterator>::value_type Parameter;
    typedef typename std::iterator_traits<Iterator>::reference Reference;
    typedef boost::function1<bool,  Reference> filter_function;
    typedef boost::function1<Value, Reference> transform_function;

    typedef boost::transform_iterator<transform_function, boost::filter_iterator<filter_function, Iterator> > iterator;
    typedef std::pair<iterator, iterator> iterator_pair;

    static inline iterator range(Iterator b, Iterator e)
    {
      return boost::make_transform_iterator(boost::make_filter_iterator(filter_function(&filter), b, e), transform_function(&transform));
    }

    static inline iterator begin(Iterator b, Iterator e)
    {
      return range(b, e);
    }

    static inline iterator end(Iterator, Iterator e)
    {
      return range(e, e);
    }

    static inline iterator_pair any(Iterator b, Iterator e)
    {
      return std::make_pair(begin(b, e), end(b, e));
    }

  private:
    static inline bool  filter   (Reference a) { return a.type() == typeid(Value); }
    static inline Value transform(Reference a) { return boost::any_cast<Value>(a); }
};


template <typename Value, typename Container>
inline typename AnyTrait<Value, typename Container::const_iterator>::iterator_pair all(Container const& c)
{
  return AnyTrait<Value, typename Container::const_iterator>::any(c.begin(), c.end());
}

template <typename Value, typename Container>
inline typename AnyTrait<Value, typename Container::iterator>::iterator_pair all(Container & c)
{
  return AnyTrait<Value, typename Container::iterator>::any(c.begin(), c.end());
}



int main()
{
  std::vector<boost::any> test;

  test.push_back(1);
  test.push_back(1.5);
  test.push_back(2);
  test.push_back(2.5);
  test.push_back(3);

  BOOST_FOREACH (const int& i, all<const int&>(test))
    std::cout << i << std::endl;
}

//
// range.hh for tools
// Made by nicuveo <nicuveo@altribe.org>
//

#ifndef TOOLS_RANGE_HH_
# define TOOLS_RANGE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Include

# include <algorithm>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  template <typename Iterator>
  struct Range
  {
    public:
      typedef std::pair<Iterator, Iterator> Type;
  };

}



#endif /* !TOOLS_RANGE_HH_ */

//
// Copyright Antoine Leblanc 2010 - 2014
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_EMPTY_HH_
# define MML_EMPTY_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape_base.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    // FIXME debug::empty raise errors on calls to Empty methods?

    template <typename T>
    class Empty : public TypedShapeBase<Empty<T>, T, shape::EMPTY>
    {
      public:
        // types

        typedef ShapeBase<Empty<T>, T> ExactShapeBase;
        typedef typename ExactShapeBase::ExactVector ExactVector;
        typedef typename ExactShapeBase::ExactPoint  ExactPoint;
        typedef typename ExactShapeBase::ExactRect   ExactRect;


        // state

        bool valid() const                 { return false;        }


        // geometry

        ExactRect bounding_rect() const    { return ExactRect();  }
        ExactPoint center() const          { return ExactPoint(); }
        Real perimeter() const             { return Real();       }
        Real area() const                  { return Real();       }

        void move_of(const ExactVector&)   {                      }
        void move_to(const ExactPoint&)    {                      }
        void scale(PrmReal)                {                      }

      private:
        friend class Shape<T>;

        Empty() throw()                    {                      }
    };

  }

}



#endif /* !MML_EMPTY_HH_ */

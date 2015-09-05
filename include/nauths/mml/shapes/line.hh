//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_LINE_HH_
# define MML_LINE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/array.hpp>
# include "nauths/mml/shapes/point.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    /// A 2D line. Being a shape, it is wrappable in a Shape
    /// instance.
    template <typename T>
    class Line : public TypedShapeBase<Line<T>, T, shape::LINE>
    {
      public:
        // types

        typedef ShapeBase<Line<T>, T> ExactShapeBase;
        typedef typename ExactShapeBase::ValueType    ValueType;
        typedef typename ExactShapeBase::PrmValueType PrmValueType;
        typedef typename ExactShapeBase::RefValueType RefValueType;
        typedef typename ExactShapeBase::ExactPoint   ExactPoint;
        typedef typename ExactShapeBase::ExactVector  ExactVector;
        typedef typename ExactShapeBase::ExactRect    ExactRect;

        /// Internal coordinate array type.
        typedef boost::array<ExactPoint, 2> DataType;


        // constructors

        Line() throw();
        Line(const ExactPoint& p0, const ExactPoint& p1) throw();
        Line(PrmValueType x0, PrmValueType y0, PrmValueType x1, PrmValueType y1) throw();

        template <typename T2>
        Line(const Line<T2>&);


        // accessors

        DataType const& data() const;

        ExactPoint const& p0() const;
        ExactPoint const& p1() const;
        ExactPoint& p0();
        ExactPoint& p1();

        PrmValueType x0() const;
        PrmValueType y0() const;
        PrmValueType x1() const;
        PrmValueType y1() const;
        RefValueType x0();
        RefValueType y0();
        RefValueType x1();
        RefValueType y1();


        // access operators

        operator const DataType& () const;
        operator DataType& ();

        ExactPoint const& operator[](std::size_t i) const;
        ExactPoint& operator[](std::size_t i);


        // state

        bool valid() const;


        // geometry

        ValueType dx() const;
        ValueType dy() const;
        ExactVector delta() const;

        Real length() const;
        ValueType sqr_length() const;

        ExactRect bounding_rect() const;
        ExactPoint center() const;
        Real perimeter() const;
        Real area() const;


        // modification operators

        Line operator-() const;


        // in-place modifiers

        using ExactShapeBase::move_of;
        using ExactShapeBase::move_to;
        void move_of(const ExactVector&);
        void move_to(const ExactPoint&);

        void scale(PrmReal);


        // in-place modification operators

        template <typename S>
        Line& operator*=(S const& s);
        template <typename S>
        Line& operator/=(S const& s);
        template <typename S>
        Line& operator%=(S const& s);


      private:
        // data

        DataType c_;
    };


    // comparison operators

    template <typename T1, typename T2>
    bool operator==(const Line<T1>& p1, const Line<T2>& p2);
    template <typename T1, typename T2>
    bool operator!=(const Line<T1>& p1, const Line<T2>& p2);


    // basic operations

    template <typename T, typename S>
    MML_ENABLE_IF(MML_ISNT_SHAPE(S), Line<MML_RESULT(MML_MUL, T, S)>)
    operator*(const Line<T>& p, S const& s);
    template <typename T, typename S>
    MML_ENABLE_IF(MML_ISNT_SHAPE(S), Line<MML_RESULT(MML_MUL, T, S)>)
    operator*(S const& s, const Line<T>& p);
    template <typename T, typename S>
    MML_ENABLE_IF(MML_ISNT_SHAPE(S), Line<MML_RESULT(MML_DIV, T, S)>)
    operator/(const Line<T>& p, S const& s);
    template <typename T, typename S>
    MML_ENABLE_IF(MML_ISNT_SHAPE(S), Line<MML_RESULT(MML_MOD, T, S)>)
    operator%(const Line<T>& p, S const& s);

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/line.hxx"



#endif /* !MML_LINE_HH_ */

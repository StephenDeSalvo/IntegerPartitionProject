////////////////////////////////////////////////////////////////////////
/// \file BGT.hpp
/// Implement the basic geometric transformations of [1].
////////////////////////////////////////////////////////////////////////

#ifndef INTEGER_PARTITIONS_COMBINATORICS_BASIC_GEOMETRIC_TRANSFORMATIONS_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_BASIC_GEOMETRIC_TRANSFORMATIONS_HPP

#include <utility>
#include <cassert>

#include "Utility.hpp"
#include "UniquePoint.hpp"
#include "UPVector.hpp"

namespace IPC
{
    namespace BGT
    {
        ////////////////////////////////////////////////////////////////////////
        /// \brief Apply the shift transformation of [1] to a set of integer points.
        /// \tparam Z is the integer type of the operand objects.
        /// \param upv is the UPVector whose points are to be shifted.
        /// \param slm is the SLMatrix2x2 determining the shift.
        /// \return the UPVector post-shift.
        ///
        /// Please refer to [1], p. 6, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// Input objects are not altered;
        /// the UPVector is passed by value and the SLMatrix2x2 is passed by
        /// constant reference.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> shift(UPVector<Z> upv, const SLMatrix2x2<Z>& slm)
        {
            for (auto& elnt : upv)
                elnt *= slm;
            return upv;
        }

        ////////////////////////////////////////////////////////////////////////
        /// \brief Apply the move transformation of [1] to a set of integer points.
        /// \tparam Z is the integer type of the operand objects.
        /// \param upv is the UPVector whose points are to be moved.
        /// \param a is the amount by which to translate the x-value of the input points.
        /// \param b is the amount by which to translate the y-value of the input points.
        /// \return the UPVector post-move.
        ///
        /// Please refer to [1], p. 6, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// NOTE: Pak defines the translation as mapping (i,j) to (i + a, j + b).
        /// Here, the translation maps (x,y) to (x + a, y + b).
        /// Input objects are not altered;
        /// the UPVector is passed by value and the two integers are passed by
        /// constant reference.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> move(UPVector<Z> upv, const Z& a, const Z& b)
        {
            for (auto& elnt : upv)
            {
                elnt.x += a;
                elnt.y += b;
            }

            return upv;
        }

        ////////////////////////////////////////////////////////////////////////
        /// \brief Apply the cut transformation of [1] to a set of integer points.
        /// \tparam Z is the integer type of the operand objects.
        /// \param upv is the UPVector whose points are to be cut.
        /// \param a is a value used to define the line along which the points are to be divided.
        /// \param b is a value used to define the line along which the points are to be divided.
        /// \param c is a value used to define the line along which the points are to be divided.
        /// \return the UPVector post-cut as a pair of UPVectors.
        ///
        /// Please refer to [1], p. 6, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// NOTE: Pak defines the transformation as dividing the set along the line
        /// a*i + b*j = c.
        /// Here, the transformation divides the set along the line
        /// a*x + b*y = c.
        /// The first element of the returned object is the UPVector of the points
        /// "above" the line; the second is the UPVector of the points "below" it.
        /// Input objects are not altered;
        /// the UPVector is passed by value and the integer arguments are passed by
        /// constant reference.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        std::pair<UPVector<Z>,UPVector<Z>> cut(
                UPVector<Z> upv, const Z& a, const Z& b, const Z& c)
        {
            UPVector<Z> upvBottom;
            /* NOTE:
             * upv will be returned as the "top" element of the cut, i.e.
             * UPVector<Z> upvTop = upv;
             */

            auto i = std::begin(upv);
            while (i != std::end(upv))
            {
                if ((a*(i->x) + b*(i->y)) > c)
                {
                    upvBottom.push_back(*i);
                    i = upv.erase(i);
                }
                else
                    ++i;
            }

            return std::make_pair(upv,upvBottom);
        }


        ////////////////////////////////////////////////////////////////////////
        /// \brief Apply the paste transformation of [1] to two sets of integer points.
        /// \tparam Z is the integer type of the operand objects.
        /// \param upvFirst is the first set of integer points.
        /// \param upvSecond is the second set of integer points
        /// \param validate determines if the upvFirst and upvSecond contain points at the same location.
        /// \return the two input sets of integer points, post-paste.
        ///
        /// Please refer to [1], p. 6, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// By setting validate to true, the function asserts that there is no point
        /// in upvFirst that occupies the same position as a point in upvSecond.
        /// Input objects are not altered;
        /// the first UPVector and the boolean are passed by value and the second
        /// UPVector is passed by constant reference.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> paste(
                UPVector<Z> upvFirst, const UPVector<Z> upvSecond, bool validate = false)
        {
            /* NOTE:
             * upvFirst will be return as the paste of the two input vectors.
             */

            if(validate)
            {
                for (auto elntF : upvFirst)
                {
                    for (auto elntS : upvSecond)
                        assert(elntF.x != elntS.x || elntF.y != elntS.y);
                }
            }

            for (auto elnt : upvSecond)
                upvFirst.push_back(elnt);

            return upvFirst;
        }

        ////////////////////////////////////////////////////////////////////////
        /// \brief Apply the paste transformation of [1] to two sets of integer points.
        /// \tparam Z is the integer type of the operand objects.
        /// \param upvPair is the pair of integer point sets.
        /// \param validate determines if the first and second pair elements contain points at the same location.
        /// \return the two input sets of integer points, post-paste.
        ///
        /// Please refer to [1], p. 6, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// By setting validate to true, the function asserts that there is no point
        /// in first pair element that occupies the same position as a point in
        /// the second pair element.
        /// Input objects are not altered;
        /// the UPVector pair is passed by constant reference and the boolean is
        /// passed by value.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> paste(
                const std::pair<UPVector<Z>,UPVector<Z>>& upvPair, bool validate = false)
        {
            return paste(upvPair.first, upvPair.second, validate);
        }

        ////////////////////////////////////////////////////////////////////////
        /// \brief Apply a constrained shred transformation of [1] to a set of integer points.
        /// \tparam Z is the integer type of the operand objects.
        /// \param upv is the UPVector whose points are to be shredded.
        /// \param horizontal determines if the UPVector is shredded horizontally or vertically.
        /// \return the UPVector post-shred as a pair of UPVectors.
        ///
        /// Please refer to [1], p. 6, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// NOTE: Pak defines the shred transformation very generally.
        /// Here, it is defined by two very specific sublattices with a volume of 2:
        /// The first one (if horizontal = true) outputs two sets, the first of
        /// which contains all of the odd columns and second contains all of the even columns.
        /// The second one (if horizontal = false) outputs two sets, the first of
        /// which contains all of the odd rows and second contains all of the even rows.
        /// Input objects are not altered;
        /// the UPVector and the boolean are passed by value.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        std::pair<UPVector<Z>,UPVector<Z>> shred2(
                UPVector<Z> upv, bool horizontal = true)
        {
            UPVector<Z> upvSecond;
            /* NOTE:
             * upv will be returned as the "first" of element of the shred, i.e.
             * UPVector<Z> upvFirst = upv;
             */

            auto i = std::begin(upv);
            if (horizontal)
            {
                while (i != std::end(upv))
                {
                    if (i->x%2)
                    {
                        upvSecond.push_back(*i);
                        i = upv.erase(i);
                    }
                    else
                        ++i;
                }
            }
            else
            {
                while (i != std::end(upv))
                {
                    if (i->y%2)
                    {
                        upvSecond.push_back(*i);
                        i = upv.erase(i);
                    }
                    else
                        ++i;
                }
            }

            return std::make_pair(upv,upvSecond);
        }

        ////////////////////////////////////////////////////////////////////////
        /// \brief Apply the stretch transformation of [1] to a set of integer points.
        /// \tparam Z is the integer type of the operand objects.
        /// \param upv is the UPVector whose points are to be stretched.
        /// \param k is a value used to define the stretch.
        /// \param l is a value used to define the stretch.
        /// \return the UPVector post-stretch.
        ///
        /// Please refer to [1], p. 6, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// NOTE: Pak defines the transformation as mapping
        /// (i,j) to (k*i, j/l).
        /// Here, it is defined by the mapping
        /// (x,y) to (x/k, l*y).
        /// Be sure that the input k,l result in a one-to-one mapping.
        /// Input objects are not altered;
        /// the UPVector is passed by value and the input integers are passed by
        /// constant reference.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> stretch(UPVector<Z> upv, const Z& k, const Z& l)
        {
            for (auto& elnt : upv)
            {
                elnt.x /= k;
                elnt.y *= l;
            }
            return upv;
        }
    }
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_BASIC_GEOMETRIC_TRANSFORMATIONS_HPP

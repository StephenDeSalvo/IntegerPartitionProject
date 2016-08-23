////////////////////////////////////////////////////////////////////////
/// \file BGT.hpp
/// \brief Implements the basic geometric transformations of [2]
////////////////////////////////////////////////////////////////////////

#ifndef IPC_BGT_HPP
#define IPC_BGT_HPP

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
		/// \brief Apply the shift transformation of [2] to a set of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upv is the UPVector whose points are to be shifted
		/// \param shear is the Matrix2x2 determining the shift
		/// \return the UPVector post-shift
        ///
		/// Please refer to [2] for the full detailing of the transformation
		/// that this function aims to mimic.
		///
		/// Before proceeding, the function asserts that the input matrix is a
		/// shear matrix.
		////////////////////////////////////////////////////////////////////////
        template <typename Z>
		UPVector<Z> shift(UPVector<Z> upv, const Matrix2x2<Z>& shear)
        {
			assert(shear.isShear());

            for (auto& elnt : upv)
				elnt = shear * elnt;
            return upv;
        }

        ////////////////////////////////////////////////////////////////////////
		/// \brief Apply the move transformation of [2] to a set of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upv is the UPVector whose points are to be moved
		/// \param a is the amount by which to translate the x-value of the input points
		/// \param b is the amount by which to translate the y-value of the input points
		/// \return the UPVector post-move
        ///
		/// Please refer to [2] for the full detailing of the transformation
        /// that this function aims to mimic.
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
		/// \brief Apply the cut transformation of [2] to a set of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upv is the UPVector whose points are to be cut
		/// \param a is a value used to define the line along which the points are to be divided
		/// \param b is a value used to define the line along which the points are to be divided
		/// \param c is a value used to define the line along which the points are to be divided
		/// \return the UPVector post-cut as a pair of UPVectors
        ///
		/// Please refer to [2] for the full detailing of the transformation
        /// that this function aims to mimic.
		///
		/// Suppose we are viewing a Ferrers diagram with the line y = c/a - b/ax
		/// drawn over it.
		/// Generally, then the first element of the returned object containes all those points
		/// in the diagram visually below or on the line,
		/// and the second element contains all those points in the diagram which are
		/// strictly above it, visually.
		///
		/// To have a return object whose first element contains all those points
		/// in the diagram visually above or on the line,
		/// figure out the equation of the line and multiply a, b, and c by -1 for the input.
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

			auto it = std::begin(upv);
			while (it != std::end(upv))
            {
				auto up = *it;
				if ((a*(up.y) + b*(up.x)) < c)
                {
					upvBottom.push_back(up);
					it = upv.erase(it);
                }
                else
                    ++it;
            }

            return std::make_pair(upv,upvBottom);
        }


        ////////////////////////////////////////////////////////////////////////
		/// \brief Apply the paste transformation of [2] to two sets of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upvFirst is the first set of integer points
        /// \param upvSecond is the second set of integer points
		/// \param validate is used to determine if two points occupy the same position
		/// \return the two input sets of integer points, post-paste
        ///
		/// Please refer to [2] for the full detailing of the transformation
		/// that this function aims to mimic.
		///
		/// By setting validate to true, the
		/// function asserts that there is no point in upvFirst that occupies
		/// the same position as a point in upvSecond.
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
		/// \brief Apply the paste transformation of [2] to two sets of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upvPair is the pair of integer point sets
		/// \param validate determines if the first and second pair elements contain points at the same location
		/// \return the two input sets of integer points, post-paste
        ///
		/// Please refer to [2] for the full detailing of the transformation
        /// that this function aims to mimic.
		///
		/// By setting validate to true, the
		/// function asserts that there is no point in upvFirst that occupies
		/// the same position as a point in upvSecond.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> paste(
                const std::pair<UPVector<Z>,UPVector<Z>>& upvPair, bool validate = false)
        {
            return paste(upvPair.first, upvPair.second, validate);
        }

        ////////////////////////////////////////////////////////////////////////
		/// \brief Apply the shred transformation of [2] to a set of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upv is the UPVector whose points are to be shredded
		/// \return the UPVector post-shred as a pair of UPVectors
        ///
		/// Please refer to [2] for the full detailing of the transformation
        /// that this function aims to mimic.
		///
		/// The first element of the returned object contains all those points
		/// whose x-coordinate is even,
		/// and the second contains all those whose x-coordinate is odd.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
		std::pair<UPVector<Z>,UPVector<Z>> shred(
				UPVector<Z> upv)
        {
            UPVector<Z> upvSecond;
            /* NOTE:
             * upv will be returned as the "first" of element of the shred, i.e.
             * UPVector<Z> upvFirst = upv;
             */

			auto it = std::begin(upv);
			while (it != std::end(upv))
			{
				auto up = *it;
				if (up.x%2)
				{
					upvSecond.push_back(*it);
					it = upv.erase(it);
				}
				else
					++it;
			}

            return std::make_pair(upv,upvSecond);
        }

        ////////////////////////////////////////////////////////////////////////
		/// \brief Apply the stretch transformation of [2] to a set of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upv is the UPVector whose points are to be stretched
		/// \param k is the factor by which to stretch the points along the y-axis
		/// \param l is the factor by which to compress the points along the x-axis
		/// \return the UPVector post-stretch
        ///
		/// Please refer to [2] for the full detailing of the transformation
        /// that this function aims to mimic.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> stretch(UPVector<Z> upv, const Z& k, const Z& l)
        {
            for (auto& elnt : upv)
            {
				elnt.x /= l;
				elnt.y *= k;
            }
            return upv;
        }

		////////////////////////////////////////////////////////////////////////
		/// \brief Apply the conjugate transformation of [2] to a set of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upv is the UPVector whose points are to be reflected
		/// \return the UPVector post-reflection
		///
		/// Please refer to [2] for the full detailing of the transformation
		/// that this function aims to mimic.
		////////////////////////////////////////////////////////////////////////
		template <typename Z>
		UPVector<Z> conjugate(UPVector<Z> upv)
		{
			for (auto& elnt : upv)
			{
				auto temp = elnt.x;
				elnt.x = elnt.y;
				elnt.y = temp;
			}
			return upv;
		}
    }
}

#endif // IPC_BGT_HPP

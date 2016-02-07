////////////////////////////////////////////////////////////////////////
/// \file UniquePoint.hpp
/// Implementation of a unique point in the integer plane.
////////////////////////////////////////////////////////////////////////

#ifndef INTEGER_PARTITIONS_COMBINATORICS_UNIQUE_POINT_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_UNIQUE_POINT_HPP

#include <cassert>
#include <fstream>
#include <cstdint>
#include <limits>

#include "Utility.hpp"

namespace IPC
{
    ////////////////////////////////////////////////////////////////////////
    /// \brief A point in the integer plane with an ID.
    /// \tparam Z is the integer type used to assign the x and y coordinate values.
    ///
    /// Note that [1] defines points in the plane as (i,j), where i takes on
    /// a y-value and j takes on an x-value.
    ////////////////////////////////////////////////////////////////////////
    template <typename Z>
    struct UniquePoint
    {
        ////////////////////////////////////////////////////////////////////////
        /// \brief The default constructor.
        /// \param x is the x-value of the point in the plane.
        /// \param y is the y-value of the point in the plane.
        /// \param id is the identifying value of the point in the plane.
        ///
        /// This function asserts that the point's coordinate values are signed.
        /// It is up to the client to ensure that every point has a unique id.
        /// Once an id is assigned, it should not be altered.
        ////////////////////////////////////////////////////////////////////////
        UniquePoint(Z x = NULL, Z y = NULL, std::uint64_t id = 0)
            : x(x), y(y), id(id)
        {
            assert(std::numeric_limits<Z>::is_signed);
        }

        Z x,y;
        std::uint64_t id;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Define compound assignment for SLMatrix2x2 multiplication.
        /// \param slm is the SLMatrix2x2 by which to multiply this point.
        /// \return this point, post matrix multiplication.
        ////////////////////////////////////////////////////////////////////////
        UniquePoint& operator*=(const SLMatrix2x2<Z>& slm)
        {
            x = x*slm.a11 + y*slm.a21;
            y = x*slm.a12 + y*slm.a22;

            return *this;
        }
    };
}

////////////////////////////////////////////////////////////////////////
/// \brief Outputs a UniquePoint as "x y id".
/// \param os is the stream to which the UniquePoint is output.
/// \param up is the UniquePoint to be output.
/// \return the input stream with the UniquePoint output to it.
////////////////////////////////////////////////////////////////////////
template <typename Z>
std::ostream& operator<<(std::ostream& os, const IPC::UniquePoint<Z>& ps)
{
    os << ps.x << ' ' << ps.y << ' ' << ps.id;
    return os;
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_UNIQUE_POINT_HPP

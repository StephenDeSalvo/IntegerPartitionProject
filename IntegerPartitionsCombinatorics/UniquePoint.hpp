////////////////////////////////////////////////////////////////////////
/// \file UniquePoint.hpp
/// \brief Defines and implements the UniquePoint class
////////////////////////////////////////////////////////////////////////

#ifndef IPC_UNIQUEPOINT_HPP
#define IPC_UNIQUEPOINT_HPP

#include <fstream>
#include <cstdint>
#include <limits>

#include "Utility.hpp"

namespace IPC
{
    ////////////////////////////////////////////////////////////////////////
	/// \brief A point in the integer plane with an ID
	/// \tparam Z is the integer type used to assign the x and y coordinate values
    ///
	/// IDs are not shared between points, hence they are "unique".
	///
	/// The compiler will check that Z is of integral type.
    ////////////////////////////////////////////////////////////////////////
    template <typename Z>
    struct UniquePoint
    {
		static_assert(	std::is_integral<Z>::value,
						"Matrix2x2 entries must be of integral type");

        ////////////////////////////////////////////////////////////////////////
		/// \brief Constructs a UniquePoint object
		/// \param x is the x-value of the point in the plane
		/// \param y is the y-value of the point in the plane
		/// \param id is the identifying value of the point in the plane
        ///
        /// This function asserts that the point's coordinate values are signed.
        /// It is up to the client to ensure that every point has a unique id.
        /// Once an id is assigned, it should not be altered.
        ////////////////////////////////////////////////////////////////////////
        UniquePoint(Z x = NULL, Z y = NULL, std::uint64_t id = 0)
            : x(x), y(y), id(id)
		{ }

        Z x,y;
        std::uint64_t id;
    };
}

////////////////////////////////////////////////////////////////////////
/// \brief Compound assigns for LHS Matrix2x2 multiplication
/// \param mat is the LHS matrix
/// \param up is the RHS unique point
/// \return the matrix multiplied by the vector
////////////////////////////////////////////////////////////////////////
template <typename Z>
IPC::UniquePoint<Z> operator*(const IPC::Matrix2x2<Z>& mat, const IPC::UniquePoint<Z>& up)
{
	auto res = up;

	res.x = up.x*mat.a11 + up.y*mat.a12;
	res.y = up.x*mat.a21 + up.y*mat.a22;

	return res;
}

////////////////////////////////////////////////////////////////////////
/// \brief Outputs a UniquePoint as "x,y,id"
/// \param os is the stream to which the UniquePoint is output
/// \param up is the UniquePoint to be output
/// \return the input stream with the UniquePoint output to it
////////////////////////////////////////////////////////////////////////
template <typename Z>
std::ostream& operator<<(std::ostream& os, const IPC::UniquePoint<Z>& up)
{
	os << up.x << ',' << up.y << ',' << up.id;
    return os;
}

#endif // IPC_UNIQUEPOINT_HPP

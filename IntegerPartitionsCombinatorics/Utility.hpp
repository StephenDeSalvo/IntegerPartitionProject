////////////////////////////////////////////////////////////////////////
/// \file Utility.hpp
/// Implement useful mathematical objects.
////////////////////////////////////////////////////////////////////////

#ifndef INTEGER_PARTITIONS_COMBINATORICS_UTILITY_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_UTILITY_HPP

#include <cassert>
#include <limits>

namespace IPC
{
    ////////////////////////////////////////////////////////////////////////
    /// \brief A 2x2 special linear matrix of elements in the integer plane.
    /// \tparam Z is the integer type used to assign the matrix element values.
    ///
    /// A special linear matrix is one whose determinant is zero.
    /// Due to the very specific use of matrices in this project,
    /// matrix element values cannot be altered.
    ////////////////////////////////////////////////////////////////////////
    template <typename Z>
    struct SLMatrix2x2
    {
        ////////////////////////////////////////////////////////////////////////
        /// \brief The default constructor.
        /// \param a11 is the top-left element of the matrix.
        /// \param a12 is the top-right element of the matrix.
        /// \param a21 is the bottom-left element of the matrix.
        /// \param a22 is the bottom-right element of the matrix.
        ///
        /// This function asserts that the matrix element values are signed.
        /// This function asserts that the matrix is special linear,
        /// i.e. that its determinant is 1.
        ////////////////////////////////////////////////////////////////////////
        SLMatrix2x2(Z a11 = NULL, Z a12 = NULL,
                    Z a21 = NULL, Z a22 = NULL)
            : a11(a11), a12(a12), a21(a21), a22(a22)
        {
            assert(std::numeric_limits<Z>::is_signed);
            assert(a11*a22 == a12*a21 + 1);
        }

        const Z a11; const Z a12;
        const Z a21; const Z a22;
    };
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_UTILITY_HPP

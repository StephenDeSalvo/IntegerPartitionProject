////////////////////////////////////////////////////////////////////////
/// \file Utility.hpp
/// \brief Defines and implements the Matrix2x2 class
////////////////////////////////////////////////////////////////////////

#ifndef IPC_UTILITY_HPP
#define IPC_UTILITY_HPP

#include <type_traits>

namespace IPC
{
    ////////////////////////////////////////////////////////////////////////
	/// \brief A 2x2 matrix of elements in the integer plane
	/// \tparam Z is the integer type used to assign the matrix element values
	///
	/// The compiler will check that Z is of integral type.
	////////////////////////////////////////////////////////////////////////
    template <typename Z>
	struct Matrix2x2
    {
		static_assert(	std::is_integral<Z>::value,
						"Matrix2x2 entries must be of integral type");

        ////////////////////////////////////////////////////////////////////////
		/// \brief The default constructor
		/// \param a11 is the top-left element of the matrix
		/// \param a12 is the top-right element of the matrix
		/// \param a21 is the bottom-left element of the matrix
		/// \param a22 is the bottom-right element of the matrix
        ////////////////////////////////////////////////////////////////////////
		Matrix2x2(Z a11 = NULL, Z a12 = NULL,
                    Z a21 = NULL, Z a22 = NULL)
            : a11(a11), a12(a12), a21(a21), a22(a22)
        {

        }

        const Z a11; const Z a12;
        const Z a21; const Z a22;

		bool isShear() const
		{
			return	(a11 == 1 && a22 == 1) && (
						(a21 == 0 && a12 != 0) ||
						(a21 != 0 && a12 == 0)
					);
		}
    };
}

#endif // IPC_UTILITY_HPP

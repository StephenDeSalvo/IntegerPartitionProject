////////////////////////////////////////////////////////////////////////
/// \file BAT.hpp
/// \brief Implements the basic arithmetic transformations of [2]
////////////////////////////////////////////////////////////////////////

#ifndef IPC_BAT_HPP
#define IPC_BAT_HPP

#include <utility>
#include <map>
#include <vector>
#include <algorithm>

#include "UPVector.hpp"

namespace IPC
{
    namespace BAT
	{
        ////////////////////////////////////////////////////////////////////////
		/// \brief Apply the sum or union transformation of [2] to two sets of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param first is the first set of integer points to sum/unite
		/// \param second is the second set of integer points to sum/unite
		/// \param horizontal determines if the points are summed row-wise or column-wise
		/// \returns the two sets of integer points post-sum/union
        ///
		/// Please refer to [2] for the full detailing of the transformations
        /// that this function aims to mimic.
		/// To mimic "union", set the horizontal argument to false.
		/// To mimic "sum", set the horizontal argument to true.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> sum(const UPVector<Z>& first, const UPVector<Z>& second, bool horizontal = true)
        {
            UPVector<Z> output;

            std::map<Z,UPVector<Z>> firstColOrRow;
            std::map<Z,UPVector<Z>> secondColOrRow;
			if (horizontal) // count the elements on each column of the result
            {
                for (auto elnt : first)
                    firstColOrRow[elnt.x].push_back(elnt);
                for (auto elnt : second)
                    secondColOrRow[elnt.x].push_back(elnt);
            }
			else // count the elements on each row of the result
            {
                for (auto elnt : first)
                    firstColOrRow[elnt.y].push_back(elnt);
                for (auto elnt : second)
                    secondColOrRow[elnt.y].push_back(elnt);
            }

            std::vector<UPVector<Z>> allColOrRow;

			// put all columns/rows into the same map
            for (auto elnt : firstColOrRow)
                allColOrRow.push_back(elnt.second);
            for (auto elnt : secondColOrRow)
                allColOrRow.push_back(elnt.second);

			// sort the rows by size
            std::sort(allColOrRow.begin(), allColOrRow.end(),
                      [](const UPVector<Z>& one, const UPVector<Z>& two)
                        {
                            return one.size() > two.size();
                        });

			// correct the UniquePoint coordinates
            if (horizontal)
            {
                for (std::size_t i = 0, n = allColOrRow.size(); i < n; ++i)
                {
                    for (auto ielnt : allColOrRow[i])
                    {
                            ielnt.x = (i + 1);
                            output.push_back(ielnt);
                    }
                }
            }
            else
            {
                for (std::size_t i = 0, n = allColOrRow.size(); i < n; ++i)
                {
                    for (auto ielnt : allColOrRow[i])
                    {
                            ielnt.y = (i + 1);
                            output.push_back(ielnt);
                    }
                }
            }

            return output;
        }

        ////////////////////////////////////////////////////////////////////////
		/// \brief Apply the sum or union transformation of [2] to two sets of integer points
		/// \tparam Z is the integer type of the operand objects
		/// \param upvPair is the pair of integer point sets
		/// \param horizontal determines if the points are summed row-wise or column-wise
		/// \returns the two sets of integer points post-sum/union
        ///
		/// Please refer to [2] for the full detailing of the transformations
		/// that this function aims to mimic.
		/// To mimic "union", set the horizontal argument to false.
		/// To mimic "sum", set the horizontal argument to true.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> sum(
                const std::pair<UPVector<Z>,UPVector<Z>>& upvPair, bool horizontal = true)
        {
            sum(upvPair.first, upvPair.second, horizontal);
        }
    }
}

#endif // IPC_BAT_HPP

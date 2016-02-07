////////////////////////////////////////////////////////////////////////
/// \file BAT.hpp
/// Implement some basic arithmetic transformations of [1].
////////////////////////////////////////////////////////////////////////

#ifndef INTEGER_PARTITIONS_COMBINATORICS_BASIC_ARITHMETIC_TRANSFORMATIONS_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_BASIC_ARITHMETIC_TRANSFORMATIONS_HPP

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
        /// \brief Apply the sum or union transformation of [1] to two sets of integer points.
        /// \tparam is the integer type of the operand objects.
        /// \param first is the first set of integer points to sum/unite.
        /// \param second is the second set of integer points to sum/unite.
        /// \param horizontal determines if the points are summed row-wise or column-wise.
        /// \returns the two sets of integer points post-sum/union.
        ///
        /// Please refer to [1], p. 9, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// NOTE: Pak defines sum as an ordered merging of the columns of two
        /// sets of points. Similarly, he defines union as an ordered merging of
        /// the rows of two sets of points.
        /// Here, both transformations are called sum, where horizontal is true
        /// when one wishes to perform a Pak sum, and false when one wishes to
        /// perform a Pak union.
        /// Input objects are not altered;
        /// the UPVectors are passed by constant reference and the bool is passed
        /// by value.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> sum(const UPVector<Z>& first, const UPVector<Z>& second, bool horizontal = true)
        {
            UPVector<Z> output;

            std::map<Z,UPVector<Z>> firstColOrRow;
            std::map<Z,UPVector<Z>> secondColOrRow;
            if (horizontal)
            {
                for (auto elnt : first)
                    firstColOrRow[elnt.x].push_back(elnt);
                for (auto elnt : second)
                    secondColOrRow[elnt.x].push_back(elnt);
            }
            else
            {
                for (auto elnt : first)
                    firstColOrRow[elnt.y].push_back(elnt);
                for (auto elnt : second)
                    secondColOrRow[elnt.y].push_back(elnt);
            }

            std::vector<UPVector<Z>> allColOrRow;
            for (auto elnt : firstColOrRow)
                allColOrRow.push_back(elnt.second);
            for (auto elnt : secondColOrRow)
                allColOrRow.push_back(elnt.second);

            std::sort(allColOrRow.begin(), allColOrRow.end(),
                      [](const UPVector<Z>& one, const UPVector<Z>& two)
                        {
                            return one.size() > two.size();
                        });

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
        /// \brief Apply the sum or union transformation of [1] to two sets of integer points.
        /// \tparam is the integer type of the operand objects.
        /// \param upvPair is the pair of integer point sets.
        /// \param horizontal determines if the points are summed row-wise or column-wise.
        /// \returns the two sets of integer points post-sum/union.
        ///
        /// Please refer to [1], p. 9, for the full detailing of the transformation
        /// that this function aims to mimic.
        /// NOTE: Pak defines sum as an ordered merging of the columns of two
        /// sets of points. Similarly, he defines union as an ordered merging of
        /// the rows of two sets of points.
        /// Here, both transformations are called sum, where horizontal is true
        /// when one wishes to perform a Pak sum, and false when one wishes to
        /// perform a Pak union.
        /// Input objects are not altered;
        /// the UPVector pair is passed by constant reference and the bool is passed
        /// by value.
        ////////////////////////////////////////////////////////////////////////
        template <typename Z>
        UPVector<Z> sum(
                const std::pair<UPVector<Z>,UPVector<Z>>& upvPair, bool horizontal = true)
        {
            sum(upvPair.first, upvPair.second, horizontal);
        }
    }
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_BASIC_ARITHMETIC_TRANSFORMATIONS_HPP

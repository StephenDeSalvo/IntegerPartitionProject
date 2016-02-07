#ifndef INTEGER_PARTITIONS_COMBINATORICS_IPS_FUNCTIONS_H
#define INTEGER_PARTITIONS_COMBINATORICS_IPS_FUNCTIONS_H

#include <array>
#include <map>
#include <cassert>
#include <iostream>

#include "PartitionTypes.hpp"

////////////////////////////////////////////////////////////////////////
/// \brief The IntegerPartitionsCombinatorics namespace.
////////////////////////////////////////////////////////////////////////
namespace IPC
{
    ////////////////////////////////////////////////////////////////////////
    /// \brief A point in Z+^2, the positive integer lattice.
    ///
    /// The first element corresponds to the x-coordinate, whereas
    /// the second element corresponds to the y-coordinate.
    /// Neither coordinate is allowed to be zero.
    ////////////////////////////////////////////////////////////////////////
    class Dot
    {
    public:
        Dot(size_t x = 1, size_t y = 1)
            : data{x,y}
        {
            assert(x != 0 && y != 0);
        }

        std::size_t& operator[](std::size_t idx) { return data[idx]; }
        const std::size_t& operator[](std::size_t idx) const { return data[idx]; }

    private:
        std::array<std::size_t,2> data;
    };

    bool operator<(const Dot& lhs, const Dot& rhs)
    {
        if (lhs[0]*lhs[0] + lhs[1]*lhs[1] != rhs[0]*rhs[0] + rhs[1]*rhs[1])
            return lhs[0]*lhs[0] + lhs[1]*lhs[1] < rhs[0]*rhs[0] + rhs[1]*rhs[1];
        else
            return lhs[0] < rhs[0];
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief The "dot-to-dot" namespace.
    ///
    /// Consider each integer partition as a Ferrer's diagram, where each
    /// dot represents a point in Z+^2, the positive integer lattice.
    /// Suppose we have two integer partitions of the same integer.
    /// This namespace defines methods to track the position of a each dot
    /// under some arbitrary bijection.
    ////////////////////////////////////////////////////////////////////////
    namespace DTD
    {
        ////////////////////////////////////////////////////////////////////////
        /// \brief Map the dots in one partition to the dots in another partition.
        /// \param start is the first partition.
        /// \param end is the second partition.
        /// \return the dot in the second partition.
        ///
        /// This map is naive in that it is generated according to how the dots
        /// are ordered, rather than as a composition of geometric transformations.
        /// NOTE: Partitions must be of the same integer.
        /// This is not currently checked.
        ////////////////////////////////////////////////////////////////////////
        std::map<Dot,Dot> naiveMap(const PSize& start, const PSize& end)
        {
            size_t dispose;

            std::map<Dot,Dot> map;
            size_t x=1,y=1;
            for (auto elnt : start)
            {
                while (elnt > 0)
                {
                    map[Dot(x,y)]= Dot(1,1);
                    --elnt;
                    ++x;
                }
                x = 1;
                ++y;

            }
            x=1,y=1;

            auto itb = map.begin();
            for (auto elnt : end)
            {
                while (elnt > 0)
                {
                    itb->second = Dot(x,y);
                    ++itb;
                    --elnt;
                    ++x;
                }
                x = 1;
                ++y;
            }

            return map;
        }
    }
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_IPS_FUNCTIONS_H

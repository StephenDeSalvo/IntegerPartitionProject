#ifndef INTEGER_PARTITIONS_COMBINATORICS_BASIC_GEOMETRIC_TRANSFORMATIONS_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_BASIC_GEOMETRIC_TRANSFORMATIONS_HPP

#include <vector>
#include <utility>
#include <cassert>
#include <map>
#include <algorithm>
#include <fstream>

namespace IPC
{
    /// @todo Put the following two structs in their own header, perhaps Utility.hpp.
    /// @todo Tracking points is easy! Add another (unchanging variable) to the Point
    /// struct, and watch where it goes after transformations.
    template <typename Z>
    struct Point
    {
        Point(Z x = NULL, Z y = NULL, Z id = NULL) : x(x), y(y), id(id) {}
        Z x, y;
        Z id;
    };

    /* WARNING
     * Pak's paper defines points (i,j) where i runs along the y-axis
     * and j runs along the x-axis.
     * These points are printed as (x,y) (equivalently, (j,i)), however.
     */
    template <typename Z>
    std::ostream& operator<<(std::ostream& os, const std::vector<Point<Z>>& ps)
    {
        for (auto elnt : ps)
            os << elnt.x << ' ' << elnt.y << ' ' << elnt.id << '\n';

        os.flush();

        return os;
    }

    template <typename Z>
    struct Matrix2x2
    {
        Matrix2x2(Z a11 = NULL, Z a12 = NULL,
                  Z a21 = NULL, Z a22 = NULL)
            : a11(a11), a12(a12), a21(a21), a22(a22)
        {}
        Z a11, a12, a21, a22;
    };

    namespace BGT
    {
        template <typename Z>
        std::vector<Point<Z>> shift(std::vector<Point<Z>> input, Matrix2x2<Z> slMatrix)
        {
            // Check that the matrix is an element of SL(2,Z).
            // Given that ad - bc == 1 is equivalent to ad == bc + 1,
            // I make use of the fact that while "1" may not be defined in
            // terms of Z, surely operator++ is.
            assert(slMatrix.a11*slMatrix.a22 == ++(slMatrix.a12*slMatrix.a21));

            for (auto& elnt : input)
            {
                Z x1 = elnt.x * slMatrix.a11;
                Z x2 = elnt.x * slMatrix.a12;
                Z y1 = elnt.y * slMatrix.a21;
                Z y2 = elnt.y * slMatrix.a22;
                elnt.x = x1 + y1;
                elnt.y = x2 + y2;
            }

            return input;
        }

        template <typename Z>
        std::vector<Point<Z>> move(std::vector<Point<Z>> input, Z a, Z b)
        {
            for (auto& elnt : input)
            {
                elnt.x += a;
                elnt.y += b;
            }

            return input;
        }

        /* WARNING
         * If a,b, or c are negative, make sure that Z supports negative types.
         */
        template <typename Z>
        std::pair<std::vector<Point<Z>>,std::vector<Point<Z>>> cut(
                std::vector<Point<Z>> input,
                Z a, Z b, Z c)
        {
            // std::vector<Point<Z>> top = input;
            std::vector<Point<Z>> bottom;

            auto i = std::begin(input);
            while (i != std::end(input))
            {
                if ((a*(i->x) + b*(i->y)) < c)
                {
                    bottom.push_back(*i);
                    input.erase(i);
                }
                else
                    ++i;
            }

            return std::make_pair(input,bottom);
        }

        /* WARNING
         * No overlap is assumed.
         */
        template <typename Z>
        std::vector<Point<Z>> paste(
                std::vector<Point<Z>> inputTop,
                const std::vector<Point<Z>>& inputBottom)
        {
            for (auto elnt : inputBottom)
                inputTop.push_back(elnt);

            return inputTop;
        }

        /* WARNING
         * No overlap is assumed.
         */
        template <typename Z>
        std::vector<Point<Z>> paste(
                const std::pair<
                    std::vector<Point<Z>>,
                    std::vector<Point<Z>>>& input_pair)
        {
            return paste<Z>(input_pair.first, input_pair.second);
        }

        /* WARNING
         * This function is defined only for when the sublattice giving rise to the
         * shred has a volume of 2.
         * Generalizing (a bit) isn't difficult, but probably isn't useful.
         */
        template <typename Z>
        std::pair<std::vector<Point<Z>>,std::vector<Point<Z>>> shred2(
                std::vector<Point<Z>> input,
                bool horizontal = true) // By default, shred along the x-axis.
        {
            // std::vector<Point<Z>> top = input;
            std::vector<Point<Z>> bottom;

            auto i = std::begin(input);
            if (horizontal)
            {
                while (i != std::end(input))
                {
                    if (i->x%2)
                    {
                        bottom.push_back(*i);
                        input.erase(i);
                    }
                    else
                        ++i;
                }
            }
            else
            {
                while (i != std::end(input))
                {
                    if (i->y%2)
                    {
                        bottom.push_back(*i);
                        input.erase(i);
                    }
                    else
                        ++i;
                }
            }

            return std::make_pair(input,bottom);
        }

        /* WARNING
         * This is only useful if it results in a one-to-one map.
         */
        template <typename Z>
        std::vector<Point<Z>> stretch(std::vector<Point<Z>> input, Z k, Z l)
        {
            for (auto& elnt : input)
            {
                elnt.x /= l;
                elnt.y *= k;
            }
            return input;
        }
    }
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_BASIC_GEOMETRIC_TRANSFORMATIONS_HPP

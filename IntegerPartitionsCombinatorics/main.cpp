////////////////////////////////////////////////////////////////////////
/// \file main.cpp
////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \date February 6, 2016
/// \author Brenden Case and Ryan McNicol
/// \version 4.0
///
/// NOTE: A reflection function has been added, but it is not clear
/// that it is a composition of the  basic geometric transformations
/// as defined in [1].
/// Moreover, it seems that Figure 14 of [1] employs the use of some
/// unknown transformation which resembles a horizontal stretch.
/// Code has been merged and cleaned.
///
/// References:
///     [1] I. Pak, The Nature of Integer Partition Bijections II.
///         Asymptotic Stability.
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdint>
#include <string>

#include "Utility.hpp"
#include "UniquePoint.hpp"
#include "UPVector.hpp"
#include "BGT.hpp"
#include "BAT.hpp"
#include "ForwardGraph.hpp"
#include "Bijections.hpp"

typedef std::int64_t int64;

using namespace IPC;

const int64 DSR = 30; // Durfee Square Rank

int main()
{
    int64 counter = 1;
    int64 max = 10*DSR;
    UPVector<int64> upvConj;
    for (int64 l = 1; l < DSR; ++l)
    {
        if (max!=0) max = rand()%max;
        upvConj.push_back(UniquePoint<int64>(l,l,counter));
        ++counter;
        for (int64 d = 1; d < max + (DSR-l); ++d)
        {
            upvConj.push_back(UniquePoint<int64>(l,l + d,counter));
            ++counter;
            upvConj.push_back(UniquePoint<int64>(l + d,l,counter));
            ++counter;
        }
        std::cout << max << " + " << DSR << " = " << (max+DSR) << "\n";
    }

    /* Compare with Figure 14, [1]. */
//    UPVector<int64> upvConj =
//    {
//        UniquePoint<int64>(1,1,1),UniquePoint<int64>(2,1,2),UniquePoint<int64>(3,1,3),UniquePoint<int64>(4,1,4),UniquePoint<int64>(5,1,5),UniquePoint<int64>(6,1,6),UniquePoint<int64>(7,1,7),
//        UniquePoint<int64>(1,2,8),UniquePoint<int64>(2,2,9),UniquePoint<int64>(3,2,10),UniquePoint<int64>(4,2,11),UniquePoint<int64>(5,2,12),UniquePoint<int64>(6,2,13),UniquePoint<int64>(7,2,14),
//        UniquePoint<int64>(1,3,15),UniquePoint<int64>(2,3,16),UniquePoint<int64>(3,3,17),UniquePoint<int64>(4,3,18),UniquePoint<int64>(5,3,19),UniquePoint<int64>(6,3,20),
//        UniquePoint<int64>(1,4,21),UniquePoint<int64>(2,4,22),UniquePoint<int64>(3,4,23),UniquePoint<int64>(4,4,24),UniquePoint<int64>(5,4,25),
//        UniquePoint<int64>(1,5,26),UniquePoint<int64>(2,5,27),UniquePoint<int64>(3,5,28),UniquePoint<int64>(4,5,29),UniquePoint<int64>(5,5,30),
//        UniquePoint<int64>(1,6,31),UniquePoint<int64>(2,6,32),UniquePoint<int64>(3,6,33),
//        UniquePoint<int64>(1,7,34),UniquePoint<int64>(2,7,35)
//    };

    std::cout << "Conjugate created! Now applying bijection...\n";

    sylvester(upvConj,true);

    std::cout << "Bijection applied!\n";

    return 0;
}

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

const int64 DSR = 300; // Durfee Square Rank

int main()
{
    int64 counter = 1;
    int64 max = 100*DSR;
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

    std::cout << "Conjugate created! Now applying bijection...\n";

    sylvester(upvConj,true);

    std::cout << "Bijection applied!\n";

    return 0;
}

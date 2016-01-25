////////////////////////////////////////////////////////////////////////
/// \file main.cpp
////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \date January 18, 2016
/// \author Brenden Case
///
/// Here I demonstrate a partition type converter and a naive bijection
/// map from one partition to another.
////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "PartitionTypes.hpp"
#include "IPsFunctions.hpp"
#include "IntegerPartitions.hpp"

using namespace IPC;

PSize multToSize(const PMult& p);



int main()
{
    IntegerPartitions ip(9);

    for (auto partition : ip)
    {
        for (auto elnt : partition)
            std::cout << elnt;
        std::cout << "     ";
        PSize ps = multToSize(partition);
        for (auto elnt : ps)
            std::cout << elnt;

        std::cout << std::endl;
    }
    auto it1 = ++++++ip.begin();
    auto v1 = multToSize(*it1);
    auto it2 = ++++++++++++++++ip.begin();
    auto v2 = multToSize(*it2);
    std::map<Dot,Dot> mymap = DTD::naiveMap(v1,v2);

    for (auto elnt : mymap)
    {
        std::cout << "(" << elnt.first[0] << "," << elnt.first[1] << ") to ";
        std::cout << "(" << elnt.second[0] << "," << elnt.second[1] << ")" << std::endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////
/// \brief Converts a vector of multiplicities to a vector of sizes.
/// \param p is the integer partition to convert.
/// \return the vector of sizes.
////////////////////////////////////////////////////////////////////////
PSize multToSize(const PMult& p)
{
    PSize pSize;

    for (size_t i = p.size()-1; i+1 > 0; --i)
    {
        size_t val = p.at(i);
        while (val != 0)
        {
            pSize.emplace_back(i+1);
            --val;
        }
    }

    return pSize;
}

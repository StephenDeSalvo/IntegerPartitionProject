////////////////////////////////////////////////////////////////////////
/// \file UPVector.hpp
/// Type-define the UPVector object, a vector of UniquePoints.
////////////////////////////////////////////////////////////////////////

#ifndef INTEGER_PARTITIONS_COMBINATORICS_UNIQUE_POINT_VECTOR_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_UNIQUE_POINT_VECTOR_HPP

#include <vector>
#include <fstream>
#include <string>
#include "UniquePoint.hpp"

namespace IPC
{
    template <typename Z>
    using UPVector = std::vector<UniquePoint<Z>>;

    template <typename Z>
    void ouputToFile(const UPVector<Z>& upv, std::string filename)
    {
        std::ofstream outfile;
        outfile.open(filename);
        if (outfile.fail())
        {
            #include <iostream>
            std::cerr << "FAILED TO OPEN FILE " << filename << std::endl;
        }
        outfile << upv;
        outfile.close();
    }
}

////////////////////////////////////////////////////////////////////////
/// \brief Outputs a UPVector by outputting each of its elements.
/// \param os is the stream to which the UPVector is output.
/// \param up is the UPVector to be output.
/// \return the input stream with the UPVector output to it.
////////////////////////////////////////////////////////////////////////
template <typename Z>
std::ostream& operator<<(std::ostream& os, const IPC::UPVector<Z>& ps)
{
    for (auto elnt : ps)
        os << elnt << '\n';

    return os;
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_UNIQUE_POINT_VECTOR_HPP

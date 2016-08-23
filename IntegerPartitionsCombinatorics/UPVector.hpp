////////////////////////////////////////////////////////////////////////
/// \file UPVector.hpp
/// \brief Defines the UPVector type and methods for filling it
////////////////////////////////////////////////////////////////////////

#ifndef IPC_UPVECTOR_HPP
#define IPC_UPVECTOR_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "UniquePoint.hpp"

namespace IPC
{
    template <typename Z>
    using UPVector = std::vector<UniquePoint<Z>>;

    template <typename Z>
    void outputToFile(const UPVector<Z>& upv, const std::string& filename)
    {
        std::ofstream outfile;
        outfile.open(filename);
        if (outfile.fail())
            std::cerr << "FAILED TO OPEN FILE " << filename << std::endl;
        outfile << upv;
        outfile.close();
    }

    template <typename Z>
    std::vector<UPVector<Z>> readInMultiplicities(const std::string& filename, const Z lineLength, const Z lineCount)
    {
        std::vector<UPVector<Z>> upvv(lineCount);
        for (auto& elnt : upvv)
            elnt.reserve(lineLength);

        std::vector<Z> mv(lineLength);

        std::ifstream ifs(filename);

        Z counter = 0;
        while (counter < lineCount)
        {
            Z index = 0;
            char sep;
            while (index < lineLength)
            {
                ifs >> mv[index] >> sep;
                ++index;
            }
            ifs.ignore(100000,'\n');
            --index;
            Z y = 1;
            Z id = 1;
            while (index >= 0)
            {
                while (mv[index] > 0)
                {
                    --mv[index];
                    for (Z x = 1; x <= index + 1; ++x,++id)
                        upvv[counter].push_back(UniquePoint<Z>(x,y,id));
                    ++y;
                }
                --index;
            }
            ++counter;
        }

        ifs.close();

        return upvv;
    }
}

////////////////////////////////////////////////////////////////////////
/// \brief Outputs a UPVector by outputting each of its elements
/// \param os is the stream to which the UPVector is output
/// \param upv is the UPVector to be output
/// \return the input stream with the UPVector output to it
////////////////////////////////////////////////////////////////////////
template <typename Z>
std::ostream& operator<<(std::ostream& os, const IPC::UPVector<Z>& upv)
{
	for (const auto& elnt : upv)
        os << elnt << '\n';

    return os;
}

#endif // IPC_UPVECTOR_HPP

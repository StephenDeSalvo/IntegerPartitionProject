////////////////////////////////////////////////////////////////////////
/// \file main.cpp
////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \date March 6, 2016
/// \author Brenden Case and Ryan McNicol
/// \version 5.0
///
/// Incorporated Ryan's implementation of the AG-bijection.
/// Added an input parameter for the bijections for specifying to which
/// folder the files are output.
/// Added a file condenser and a multiplicity reader.
/// If you would like to test this main routine for yourself, make sure
/// that the directories you input exist in you folder.
///
/// References:
///     [1] I. Pak, The Nature of Integer Partition Bijections II.
///         Asymptotic Stability.
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdint>
#include <string>
#include <limits>

#include "Utility.hpp"
#include "UniquePoint.hpp"
#include "UPVector.hpp"
#include "BGT.hpp"
#include "BAT.hpp"
#include "ForwardGraph.hpp"
#include "Bijections.hpp"

typedef std::int64_t int64;

using namespace IPC;

template <typename Z>
struct Pair
{
    Z start = std::numeric_limits<Z>::max();
    Z end = std::numeric_limits<Z>::min();
};

template <typename Z>
void condenseFile(const std::string& filename, const Z size)
{
    std::vector<Pair<Z>> lines(size);

    std::ifstream ifs(filename);
    Z x,y;
    char sep;
    while (!ifs.eof())
    {
        ifs >> x >> sep
            >> y;
        ifs.ignore(100000,'\n');

        if (lines[y-1].start > x)
            lines[y-1].start = x;
        if (lines[y-1].end < x)
            lines[y-1].end = x;
    }
    ifs.close();

    std::ofstream ofs(filename);
    for (std::size_t i = 0, n = lines.size(); i < n; ++i)
    {
        if (lines[i].start != std::numeric_limits<Z>::max())
        {
            ofs << lines[i].start << ',' << i + 1 << ",0\n"
                << lines[i].end << ',' << i + 1 << ",0\n";
        }
    }
    ofs.close();
}

enum class BijType
{
    AG,
    Syl
};

template <typename Z>
void condenseDirectory(const std::string& directory, BijType bt, Z size)
{
    std::vector<std::string> files = {
        directory + "/fileA.txt",
        directory + "/fileB.txt",
        directory + "/fileC.txt",
        directory + "/fileD.txt",
        directory + "/fileE.txt",
        directory + "/fileF.txt",
        directory + "/fileG.txt",
        directory + "/fileH.txt",
        directory + "/fileI.txt"
    };
    if (bt == BijType::AG)
    {
        files.push_back(directory + "/fileJ.txt");
        files.push_back(directory + "/fileK.txt");
        files.push_back(directory + "/fileL.txt");
        files.push_back(directory + "/fileM.txt");
        files.push_back(directory + "/fileN.txt");
        files.push_back(directory + "/fileO.txt");
        files.push_back(directory + "/fileP.txt");
        files.push_back(directory + "/fileQ.txt");
        files.push_back(directory + "/fileR.txt");
        files.push_back(directory + "/fileS.txt");
        files.push_back(directory + "/fileT.txt");
        files.push_back(directory + "/fileU.txt");
    }

    for (auto& file : files)
        condenseFile<Z>(file,size);
}

int main()
{
//    /* Compare with Figure 14, [1]. */
//    UPVector<int64> upv14;
//    int64 counter = 1;
//    for (int64 x = 1; x <= 7; ++x, ++counter)
//        upv14.push_back(UniquePoint<int64>(x,1,counter));
//    for (int64 x = 1; x <= 7; ++x, ++counter)
//        upv14.push_back(UniquePoint<int64>(x,2,counter));
//    for (int64 x = 1; x <= 6; ++x, ++counter)
//        upv14.push_back(UniquePoint<int64>(x,3,counter));
//    for (int64 x = 1; x <= 5; ++x, ++counter)
//        upv14.push_back(UniquePoint<int64>(x,4,counter));
//    for (int64 x = 1; x <= 5; ++x, ++counter)
//        upv14.push_back(UniquePoint<int64>(x,5,counter));
//    for (int64 x = 1; x <= 3; ++x, ++counter)
//        upv14.push_back(UniquePoint<int64>(x,6,counter));
//    for (int64 x = 1; x <= 2; ++x, ++counter)
//        upv14.push_back(UniquePoint<int64>(x,7,counter));

//    std::cout << "Self-conjugate partition created!\n"
//                 "Now applying Sylvester's bijection...\n";

//    auto upv14_REVERSE = sylvesterForward(upv14,"_Figure-14",true);

//    std::cout << "Bijection applied!\n"
//                 "Going in reverse...\n";

//    sylvesterBackward(upv14_REVERSE,"_Figure-14-REVERSE",true);

//    std::cout << "Bijection applied!\n\n";

//    /* Compare with Figure 16, [1]. */
//    UPVector<int64> upv16;
//    counter = 1;
//    for (int64 x = 1; x <= 11; ++x, ++counter)
//        upv16.push_back(UniquePoint<int64>(x,1,counter));
//    for (int64 x = 1; x <= 11; ++x, ++counter)
//        upv16.push_back(UniquePoint<int64>(x,2,counter));
//    for (int64 x = 1; x <= 9; ++x, ++counter)
//        upv16.push_back(UniquePoint<int64>(x,3,counter));
//    for (int64 x = 1; x <= 7; ++x, ++counter)
//        upv16.push_back(UniquePoint<int64>(x,4,counter));
//    for (int64 x = 1; x <= 3; ++x, ++counter)
//        upv16.push_back(UniquePoint<int64>(x,5,counter));
//    for (int64 x = 1; x <= 3; ++x, ++counter)
//        upv16.push_back(UniquePoint<int64>(x,6,counter));
//    upv16.push_back(UniquePoint<int64>(1,7,counter));

//    std::cout << "Odd partition created! Now applying AG-bijection...\n";

//    AG(upv16,"_Figure-16",true);

//    std::cout << "Bijection applied!\n";

//    /* Output verbose AG bijection on size 20 partitions. */
//    auto upvv = readInMultiplicities("_odd part sizes/odd_parts_size_20.txt",20,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "AG-20-" + num;
//        AG(upvv[i],directory,true);
//    }

//    /* Output verbose AG bijection on size 100 partitions. */
//    auto upvv = readInMultiplicities("_odd part sizes/odd_parts_size_100.txt",100,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "AG-100-" + num;
//        AG(upvv[i],directory,true);
//    }

//    /* Output verbose AG bijection on size 1000 partitions. */
//    /* Then condense. */
//    auto upvv = readInMultiplicities("_odd part sizes/odd_parts_size_1,000.txt",1000,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "AG-1000-" + num;
//        AG(upvv[i],directory,true);
//        condenseDirectory(directory,BijType::AG,1000);
//    }

//    /* Output verbose AG bijection on size 10000 partitions. */
//    /* Then condense. */
//    auto upvv = readInMultiplicities("_odd part sizes/odd_parts_size_10,000.txt",10000,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "AG-10000-" + num;
//        AG(upvv[i],directory,true);
//        condenseDirectory(directory,BijType::AG,10000);
//    }

//    /* Output verbose AG bijection on size 100000 partitions. */
//    /* Then condense. */
//    auto upvv = readInMultiplicities("_odd part sizes/odd_parts_size_100,000.txt",100000,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "AG-100000-" + num;
//        AG(upvv[i],directory,true);
//        condenseDirectory(directory,BijType::AG,100000);
//    }

//    /* Output verbose Sylvester bijection on size 20 partitions. */
//    auto upvv = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_20.txt",20,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "Sylvester-20-" + num;
//        sylvesterBackward(upvv[i],directory,true);
//    }

//    /* Output verbose Sylvester bijection on size 100 partitions. */
//    auto upvv = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_100.txt",100,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "Sylvester-100-" + num;
//        sylvesterBackward(upvv[i],directory,true);
//    }

//    /* Output verbose Sylvester bijection on size 1000 partitions. */
//    /* Then condense. */
//    auto upvv = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_1,000.txt",1000,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "Sylvester-1000-" + num;
//        sylvesterBackward(upvv[i],directory,true);
//        condenseDirectory(directory,BijType::Syl,1000);
//    }

//    /* Output verbose Sylvester bijection on size 10000 partitions. */
//    /* Then condense. */
//    auto upvv = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_10,000.txt",10000,100);
//    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//    {
//        std::string num = std::to_string(i + 1);
//        std::string directory = "Sylvester-10000-" + num;
//        sylvesterBackward(upvv[i],directory,true);
//        condenseDirectory(directory,BijType::Syl,10000);
//    }

    /* Output verbose Sylvester bijection on size 100000 partitions. */
    /* Then condense. */
    auto upvv = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_100,000.txt",100000,10);
    for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
    {
        std::string num = std::to_string(i + 1);
        std::string directory = "Sylvester-100000-" + num;
        sylvesterBackward(upvv[i],directory,true);
        condenseDirectory(directory,BijType::Syl,100000);
    }

    return 0;
}

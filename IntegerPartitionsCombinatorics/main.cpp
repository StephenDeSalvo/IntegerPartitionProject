////////////////////////////////////////////////////////////////////////
/// \file main.cpp
////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \date February 6, 2016
/// \author Brenden Case
/// \version 3.0
///
/// Commenting has been added to all methods.
/// Code has been (re)organized file-wise.
/// Again, it is up to the client to initialize the id of each point.
/// Fixed an iterator invalidation bug.
/// Consolidated the sum and union2 function into one to reduce code duplication.
/// Demonstrations of methods have been updated to reflect updated code.
/// Demonstration of the ForwardGraph object has been added.
/// Functions for ease of file output have been added.
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

typedef std::int64_t int64;

using namespace IPC;

int main()
{
    /*
     * Basic Geometric Transformation Demo
     * Follow along with [1], p. 7!
     */
    std::cout << "BASIC GEOMETRIC TRANSFORMATION DEMO\n";

    UPVector<int64> upv = {
        UniquePoint<int64>(1,1,1), UniquePoint<int64>(2,1,2), UniquePoint<int64>(3,1,3), UniquePoint<int64>(4,1,4), UniquePoint<int64>(5,1,5), UniquePoint<int64>(6,1,6),
        UniquePoint<int64>(1,2,7), UniquePoint<int64>(2,2,8), UniquePoint<int64>(3,2,9), UniquePoint<int64>(4,2,10), UniquePoint<int64>(5,2,11),
        UniquePoint<int64>(1,3,12), UniquePoint<int64>(2,3,13), UniquePoint<int64>(3,3,14), UniquePoint<int64>(4,3,15), UniquePoint<int64>(5,3,16),
        UniquePoint<int64>(1,4,17), UniquePoint<int64>(2,4,18), UniquePoint<int64>(3,4,19)
    };

    SLMatrix2x2<int64> slm(1,0,1,1);
    // SLMatrix2x2<int64> slm(1,0,1,2);  // Uncomment to test assert.

    std::cout << "The original set of points \"x y id \":\n"
              << upv
              << std::endl;

    std::cout << "Post-shift:\n"
              << IPC::BGT::shift(upv, slm)
              << std::endl;

    int64 move_a = -1;
    int64 move_b = 1;
    std::cout << "Post-move:\n"
              << IPC::BGT::move(upv, move_a, move_b)
              << std::endl;

    int64 cut_a = -1;
    int64 cut_b = 1;
    int64 cut_c = 0;
    std::cout << "Post-cut, first:\n"
              << IPC::BGT::cut(upv, cut_a, cut_b, cut_c).first
              << "Post-cut, second:\n"
              << IPC::BGT::cut(upv, cut_a, cut_b, cut_c).second
              << std::endl;

    /* Compare results with [1], Figure 4. */
    int64 move_null = 0;
    std::cout << "Post-paste (see Figure 4):\n"
              << IPC::BGT::paste(
                     IPC::BGT::move(
                         IPC::BGT::cut(upv, cut_a, cut_b, cut_c).first, move_a, move_null),
                     IPC::BGT::move(
                         IPC::BGT::cut(upv, cut_a, cut_b, cut_c).second, move_null, move_b),
                     true)
              << std::endl;
    // IPC::BGT::paste(upv,upv,true);  // Uncomment to test assert.

    std::cout << "Post-shred2, first:\n"
              << IPC::BGT::shred2(upv,true).first
              << "Post-shred2, second:\n"
              << IPC::BGT::shred2(upv,true).second
              << std::endl;

    int64 stretch_k = 2;
    int64 stretch_l = 2;
    std::cout << "Post-stretch, after shred (first element):\n"
              << IPC::BGT::stretch(IPC::BGT::shred2(upv,true).first,stretch_k, stretch_l)
              << std::endl;

    /*
     * Basic Arithmetic Transformation Demo
     */
    std::cout << "BASIC GEOMETRIC TRANSFORMATION DEMO\n";

    UPVector<int64> upv2 = {
        UniquePoint<int64>(1,1,1), UniquePoint<int64>(2,1,2), UniquePoint<int64>(3,1,3), UniquePoint<int64>(4,1,4), UniquePoint<int64>(5,1,5), UniquePoint<int64>(6,1,6),
        UniquePoint<int64>(1,2,7), UniquePoint<int64>(2,2,8), UniquePoint<int64>(3,2,9), UniquePoint<int64>(4,2,10), UniquePoint<int64>(5,2,11),
        UniquePoint<int64>(1,3,12), UniquePoint<int64>(2,3,13), UniquePoint<int64>(3,3,14), UniquePoint<int64>(4,3,15), UniquePoint<int64>(5,3,16),
        UniquePoint<int64>(1,4,17), UniquePoint<int64>(2,4,18), UniquePoint<int64>(3,4,19)
    };
    UPVector<int64> upv3 = {
        UniquePoint<int64>(1,1,20), UniquePoint<int64>(2,1,21), UniquePoint<int64>(3,1,22), UniquePoint<int64>(4,1,23), UniquePoint<int64>(5,1,24), UniquePoint<int64>(6,1,25),
        UniquePoint<int64>(1,2,26), UniquePoint<int64>(2,2,27), UniquePoint<int64>(3,2,28), UniquePoint<int64>(4,2,29), UniquePoint<int64>(5,2,30), UniquePoint<int64>(6,2,31),
        UniquePoint<int64>(1,3,31), UniquePoint<int64>(2,3,32), UniquePoint<int64>(3,3,33), UniquePoint<int64>(4,3,34), UniquePoint<int64>(5,3,35),
        UniquePoint<int64>(1,4,36), UniquePoint<int64>(2,4,37), UniquePoint<int64>(3,4,38),
        UniquePoint<int64>(1,5,39)
    };

    std::cout << "The first original set of points \"x y id \":\n"
              << upv2
              << std::endl;

    std::cout << "The second original set of points:\n"
              << upv3
              << std::endl;

    std::cout << "The column-wise(horizontal) sum:\n"
              << IPC::BAT::sum(upv2,upv3,true)
              << std::endl;

    std::cout << "The row-wise(vertical) sum, i.e. the union:\n"
              << IPC::BAT::sum(upv2,upv3,false)
              << std::endl;

    /*
     * Forward Graph Demo
     */
    std::cout << "FORWARD GRAPH DEMO\n";

    IPC::ForwardGraph<std::string,int64> fg;

    fg.addVertex("file1.txt", 1);
    fg.addVertex("file2.txt", 2);
    fg.addVertex("file3.txt", 2);
    fg.addVertex("file4.txt", 3);
    fg.addVertex("file5.txt", 3);
    fg.addVertex("file6.txt", 4);
    fg.addVertex("file7.txt", 5);

    fg.addEdge("file1.txt","file2.txt");
    fg.addEdge("file1.txt","file3.txt");
    fg.addEdge("file2.txt","file4.txt");
    fg.addEdge("file2.txt","file5.txt");
    fg.addEdge("file4.txt","file6.txt");
    fg.addEdge("file5.txt","file6.txt");
    fg.addEdge("file6.txt","file7.txt");
    fg.addEdge("file3.txt","file7.txt");

    std::cout << "The forward graph:\n"
              << fg
              << std::endl;

    fg.ouputToFile(false);
    IPC::ouputToFile(upv,"points1.txt");
    return 0;
}

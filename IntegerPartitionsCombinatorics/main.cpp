////////////////////////////////////////////////////////////////////////
/// \file main.cpp
////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \date February 1, 2016
/// \author Brenden Case
/// \version 2.0
///
/// Demonstrates the "basic geometric transformations" from Pak's paper.
/// Version 2.0 also demonstrates "basic arithmetic transformations from
/// Pak's paper.
/// Also added an id element for the Points class.
/// IF YOU WISH TO USE THIS, YOU MUST INITIALIZE EACH POINT WITH ITS OWN
/// UNIQUE ID YOURSELF.
////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdint>
#include <vector>
#include <fstream>

#include "BGT.hpp"
#include "BAT.hpp"

typedef std::int64_t int64;

using namespace IPC;

/* WARNING
 * Pak's paper defines points (i,j) where i runs along the y-axis
 * and j runs along the x-axis.
 * These points are printed as (x,y) (equivalently, (j,i)), however.
 */
std::ostream& operator<<(std::ostream& os, const std::vector<Point<int64>>& ps)
{
    for (auto elnt : ps)
        os << "(" << elnt.x << "," << elnt.y << "), ID: " << elnt.id << "\n";

    os.flush();

    return os;
}

// Compare examples with figures 4 through 6 in Pak's paper.
// Feel free to uncomment all of them - there should be no conflicts!
int main()
{
    /*
     * Basic Geometric Transform Demo
     */
//    Matrix2x2<int64> slMatrix(1,0,1,1);

    std::vector<Point<int64>> points;

    points.push_back(Point<int64>(1,1,1));
    points.push_back(Point<int64>(2,1,2));
    points.push_back(Point<int64>(3,1,3));
    points.push_back(Point<int64>(4,1,4));
    points.push_back(Point<int64>(5,1,5));
    points.push_back(Point<int64>(6,1,6));
    points.push_back(Point<int64>(1,2,7));
    points.push_back(Point<int64>(2,2,8));
    points.push_back(Point<int64>(3,2,9));
    points.push_back(Point<int64>(4,2,10));
    points.push_back(Point<int64>(5,2,11));
    points.push_back(Point<int64>(1,3,12));
    points.push_back(Point<int64>(2,3,13));
    points.push_back(Point<int64>(3,3,14));
    points.push_back(Point<int64>(4,3,15));
    points.push_back(Point<int64>(5,3,16));
    points.push_back(Point<int64>(1,4,17));
    points.push_back(Point<int64>(2,4,18));
    points.push_back(Point<int64>(3,4,19));

//    // Demo the shift BGT.
//    auto new_pointsShift = BGT::shift<int64>(points, slMatrix);
//    std::cout << "Ponts pre-shift:\n" << points;
//    std::cout << "Points post-shift:\n" << new_pointsShift;
//    std::cout << std::endl;

//    // Demo the move BGT.
//    auto new_pointsMove = BGT::move<int64>(points, 2, 2);
//    std::cout << "Ponts pre-move:\n" << points;
//    std::cout << "Points post-move:\n" << new_pointsMove;
//    std::cout << std::endl;

    // Demo the cut BGT.
    auto new_points_pair_cut = BGT::cut<int64>(points,-1,1,0);
    std::cout << "Ponts pre-cut:\n" << points;
    std::cout << "Points post-cut, top:\n" << new_points_pair_cut.first;
    std::cout << "Points post-cut, bottom:\n" << new_points_pair_cut.second;
    std::cout << std::endl;

//    // Demo the paste BGT.
//    auto new_pointsPaste = BGT::paste<int64>(BGT::cut<int64>(points,1,-1,1));
//    std::cout << "Poinst pre-paste:\n" << points;
//    std::cout << "Points post-paste:\n" << new_pointsPaste;
//    std::cout << std::endl;

//    // Demo the shred BGT.
//    auto new_points_pair_shred = BGT::shred2<int64>(points,true);
//    std::cout << "Points pre-shred:\n" << points;
//    std::cout << "Points post-shred, top:\n" << new_points_pair_shred.first;
//    std::cout << "Points post-shred, bottom:\n" << new_points_pair_shred.second;
//    std::cout << std::endl;

//    // Demo the stretch BGT.
//    auto points2 = BGT::shred2<int64>(points,true).first;
//    auto new_pointsStretch = BGT::stretch<int64>(points2, 2, 2);
//    std::cout << "Points pre-stretch:\n" << points2;
//    std::cout << "Points post-stretch:\n" << new_pointsStretch;
//    std::cout << std::endl;

    /*
     * Basic Aritmetic Transform Demo
     */
//    std::vector<Point<int64>> more_points1;
//    more_points1.push_back(Point<int64>(1,1,1));
//    more_points1.push_back(Point<int64>(2,1,2));
//    more_points1.push_back(Point<int64>(3,1,3));
//    more_points1.push_back(Point<int64>(4,1,4));
//    more_points1.push_back(Point<int64>(5,1,5));
//    more_points1.push_back(Point<int64>(1,2,6));
//    more_points1.push_back(Point<int64>(2,2,7));
//    more_points1.push_back(Point<int64>(3,2,8));
//    more_points1.push_back(Point<int64>(4,2,9));
//    more_points1.push_back(Point<int64>(5,2,10));
//    more_points1.push_back(Point<int64>(1,3,11));
//    more_points1.push_back(Point<int64>(2,3,12));
//    more_points1.push_back(Point<int64>(3,3,13));
//    more_points1.push_back(Point<int64>(4,3,14));
//    more_points1.push_back(Point<int64>(1,4,15));
//    more_points1.push_back(Point<int64>(2,4,16));
//    more_points1.push_back(Point<int64>(3,4,17));
//    more_points1.push_back(Point<int64>(4,4,18));
//    more_points1.push_back(Point<int64>(1,5,19));
//    more_points1.push_back(Point<int64>(2,5,20));
//    more_points1.push_back(Point<int64>(1,6,21));
//    more_points1.push_back(Point<int64>(2,6,22));

//    std::vector<Point<int64>> more_points2;
//    more_points2.push_back(Point<int64>(1,1,23));
//    more_points2.push_back(Point<int64>(2,1,24));
//    more_points2.push_back(Point<int64>(3,1,25));
//    more_points2.push_back(Point<int64>(4,1,26));
//    more_points2.push_back(Point<int64>(5,1,27));
//    more_points2.push_back(Point<int64>(6,1,28));
//    more_points2.push_back(Point<int64>(7,1,29));
//    more_points2.push_back(Point<int64>(1,2,30));
//    more_points2.push_back(Point<int64>(2,2,31));
//    more_points2.push_back(Point<int64>(3,2,32));
//    more_points2.push_back(Point<int64>(4,2,33));
//    more_points2.push_back(Point<int64>(5,2,34));
//    more_points2.push_back(Point<int64>(1,3,35));
//    more_points2.push_back(Point<int64>(2,3,36));
//    more_points2.push_back(Point<int64>(3,3,37));
//    more_points2.push_back(Point<int64>(4,3,38));
//    more_points2.push_back(Point<int64>(5,3,39));
//    more_points2.push_back(Point<int64>(1,4,40));
//    more_points2.push_back(Point<int64>(2,4,41));
//    more_points2.push_back(Point<int64>(1,5,42));
//    more_points2.push_back(Point<int64>(2,5,43));
//    more_points2.push_back(Point<int64>(1,6,44));
//    more_points2.push_back(Point<int64>(1,7,45));

//    // Demo the sum BAT.
//    auto sumpoints = IPC::BAT::sum(more_points1,more_points2);
//    std::cout << "Points pre-sum, lhs:\n" << more_points1;
//    std::cout << "Points pre-sum, rhs:\n" << more_points2;
//    std::cout << "Points post-sum:\n" << sumpoints;
//    std::cout << std::endl;

//    // Demo the sum BAT.
//    auto union2points = IPC::BAT::union2(more_points1,more_points2);
//    std::cout << "Points pre-union, lhs:\n" << more_points1;
//    std::cout << "Points pre-union, rhs:\n" << more_points2;
//    std::cout << "Points post-union:\n" << union2points;
//    std::cout << std::endl;

    return 0;
}

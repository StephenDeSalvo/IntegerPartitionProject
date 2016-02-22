////////////////////////////////////////////////////////////////////////
/// \file Bijections.hpp
/// \author Ryan McNicol w/ edits by Brenden Case.
/// Defines several bijections on integer partitions, as seen in [1].
////////////////////////////////////////////////////////////////////////

#ifndef INTEGER_PARTITIONS_COMBINATORICS_BIJECTIONS_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_BIJECTIONS_HPP

#include <string>

#include "UPVector.hpp"
#include "BGT.hpp"
#include "BAT.hpp"
#include "ForwardGraph.hpp"

namespace IPC
{
    ////////////////////////////////////////////////////////////////////////
    /// \brief Reflect a set of integer points across the line x = y.
    /// \tparam Z is the integer type of the operand objects.
    /// \param upv is the UPVector whose points are to be reflected.
    /// \return the UPVector post-reflection.
    ////////////////////////////////////////////////////////////////////////
    template <typename Z>
    UPVector<Z> reflect(UPVector<Z> upv)
    {
        for (auto elnt : upv)
        {
            auto temp = elnt.x;
            elnt.x = elnt.y;
            elnt.y = temp;
        }
        return upv;
    }

    template<typename Z>
    UPVector<Z> sylvester(UPVector<Z> upv, bool verbose = false)
    {
        ForwardGraph<std::string,Z> fg;

        ouputToFile(upv,"fileA.txt");
        fg.addVertex("fileA.txt",1);

        auto upvPair = BGT::cut<Z>(upv,-1,1,0);

        if(verbose)
        {
            ouputToFile(upvPair.first,"fileB.txt");
            ouputToFile(upvPair.second,"fileC.txt");
            fg.addVertex("fileB.txt",2);
            fg.addVertex("fileC.txt",2);
            fg.addEdge("fileA.txt","fileB.txt");
            fg.addEdge("fileA.txt","fileC.txt");
        }

        upvPair.first = BGT::move<Z>(upvPair.first,1,0);

        if(verbose)
        {
            ouputToFile(upvPair.first,"fileD.txt");
            fg.addVertex("fileD.txt",3);
            fg.addEdge("fileB.txt","fileD.txt");
        }

        upvPair.first = BGT::shift<Z>(upvPair.first,SLMatrix2x2<Z>(1,0,-1,1));

        if(verbose)
        {
            ouputToFile(upvPair.first,"fileE.txt");
            fg.addVertex("fileE.txt",4);
            fg.addEdge("fileD.txt","fileE.txt");
        }

        upvPair.first = reflect(upvPair.first);

        if(verbose)
        {
            ouputToFile(upvPair.first,"fileF.txt");
            fg.addVertex("fileF.txt",5);
            fg.addEdge("fileE.txt","fileF.txt");
        }

        upvPair.first = BGT::stretch<Z>(upvPair.first,1,2);

        if(verbose)
        {
            ouputToFile(upvPair.first,"fileG.txt");
            fg.addVertex("fileG.txt",6);
            fg.addEdge("fileF.txt","fileG.txt");
        }

        upvPair.first = BGT::move<Z>(upvPair.first,0,-1);

        if(verbose)
        {
            ouputToFile(upvPair.first,"fileH.txt");
            fg.addVertex("fileH.txt",7);
            fg.addEdge("fileG.txt","fileH.txt");
        }

        upvPair.first = reflect(upvPair.first);

        if(verbose)
        {
            ouputToFile(upvPair.first,"fileI.txt");
            fg.addVertex("fileI.txt",8);
            fg.addEdge("fileH.txt","fileI.txt");
        }

        upvPair.second = BGT::shift<Z>(upvPair.second,SLMatrix2x2<Z>(1,-1,0,1));

        if(verbose)
        {
            ouputToFile(upvPair.second,"fileJ.txt");
            fg.addVertex("fileJ.txt",3);
            fg.addEdge("fileC.txt","fileJ.txt");
        }

        upvPair.second = BGT::stretch<Z>(upvPair.second,1,2);

        if(verbose)
        {
            ouputToFile(upvPair.second,"fileK.txt");
            fg.addVertex("fileK.txt",4);
            fg.addEdge("fileJ.txt","fileK.txt");
        }

        upvPair.second = reflect(upvPair.second);

        if(verbose)
        {
            ouputToFile(upvPair.second,"fileL.txt");
            fg.addVertex("fileL.txt",5);
            fg.addEdge("fileK.txt","fileL.txt");
        }

        upv = BGT::paste(upvPair);

        if(verbose)
        {
            ouputToFile(upv,"fileM.txt");
            fg.addVertex("fileM.txt",9);
            fg.addEdge("fileI.txt","fileM.txt");
            fg.addEdge("fileL.txt","fileM.txt");
        }
        else
        {
            ouputToFile(upv,"fileB.txt");
            fg.addVertex("fileB.txt",2);
            fg.addEdge("fileA.txt","fileB.txt");
        }

        fg.ouputToFile();

        return upv;
    }
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_BIJECTIONS_HPP

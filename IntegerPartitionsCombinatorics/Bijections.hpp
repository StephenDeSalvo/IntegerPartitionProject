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
        for (auto& elnt : upv)
        {
            auto temp = elnt.x;
            elnt.x = elnt.y;
            elnt.y = temp;
        }
        return upv;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Apply Sylvester's bijection to a self-conjugate integer
    /// partition.
    /// \tparam Z is the integer type of the operand objects.
    /// \param upv is the UPVector which represents a self-conjugate
    /// integer partition.
    /// \param directory is the folder directory in which to save the
    /// verbose output.
    /// \param verbose determines if the bijection outputs a set of integer
    /// points to a file at each step of the bijection.
    /// \return a UPVector representing an odd-distinct integer partition.
    ///
    /// See [1] p.16-18 for more details.
    /// By forward, I mean it operates on a self-conjugate partition
    /// and maps it to a partition of odd-distinct parts.
    ////////////////////////////////////////////////////////////////////////
    template<typename Z>
    UPVector<Z> sylvesterForward(UPVector<Z> upv,
                                 const std::string& directory = "",
                                 const bool verbose = false)
    {
        ForwardGraph<std::string,Z> fg;
        std::string A = directory + "/fileA.txt";
        std::string B = directory + "/fileB.txt";
        std::string C = directory + "/fileC.txt";
        std::string D = directory + "/fileD.txt";
        std::string E = directory + "/fileE.txt";
        std::string F = directory + "/fileF.txt";
        std::string G = directory + "/fileG.txt";
        std::string H = directory + "/fileH.txt";
        std::string I = directory + "/fileI.txt";
        if (verbose)
        {
            fg.addVertex(A,1);
            outputToFile(upv,A);
        }

        auto upvPair = BGT::cut<Z>(upv,-1,1,0);
        if (verbose)
        {
            fg.addVertex(B,2);
            fg.addEdge(A,B);
            outputToFile(upvPair.second,B);
            fg.addVertex(C,2);
            fg.addEdge(A,C);
            outputToFile(upvPair.first,C);
        }

        upvPair.first = BGT::move<Z>(upvPair.first,1,0);
        upvPair.first = BGT::shift<Z>(upvPair.first,SLMatrix2x2<Z>(1,0,-1,1));
        if (verbose)
        {
            fg.addVertex(E,3);
            fg.addEdge(C,E);
            outputToFile(upvPair.first,E);
        }

        upvPair.second = BGT::shift<Z>(upvPair.second,SLMatrix2x2<Z>(1,-1,0,1));
        if( verbose)
        {
            fg.addVertex(D,3);
            fg.addEdge(B,D);
            outputToFile(upvPair.second,D);
        }


        upvPair.first = reflect(upvPair.first);
        upvPair.first = BGT::stretch<Z>(upvPair.first,1,2);
        upvPair.first = BGT::move<Z>(upvPair.first,0,-1);
        upvPair.first = reflect(upvPair.first);
        if (verbose)
        {
            fg.addVertex(H,4);
            fg.addEdge(E,H);
            outputToFile(upvPair.first,H);
        }

        upvPair.second = reflect(upvPair.second);
        if (verbose)
        {
            fg.addVertex(F,4);
            fg.addEdge(D,F);
            outputToFile(upvPair.second,F);
        }

        upvPair.second = reflect(upvPair.second);
        upvPair.second = BGT::stretch<Z>(upvPair.second,1,2);
        upvPair.second = reflect(upvPair.second);
        if (verbose)
        {
            fg.addVertex(G,5);
            fg.addEdge(F,G);
            outputToFile(upvPair.second,G);
        }

        upv = BGT::paste(upvPair);
        if (verbose)
        {
            fg.addVertex(I,6);
            fg.addEdge(G,I);
            fg.addEdge(H,I);
            outputToFile(upv,I);
            fg.ouputToFile(directory);
        }

        return upv;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Apply Sylvester's bijection to an odd-distinct integer
    /// partition.
    /// \tparam Z is the integer type of the operand objects.
    /// \param upv is the UPVector which represents an odd-distinct
    /// integer partition.
    /// \param directory is the folder directory in which to save the
    /// verbose output.
    /// \param verbose determines if the bijection outputs a set of integer
    /// points to a file at each step of the bijection.
    /// \return a UPVector representing a self-conjugate integer partition.
    ///
    /// See [1] p.16-18 for more details.
    /// By backward, I mean it operates on an odd-distinct partition
    /// and maps it to a self-conjugate partition.
    ////////////////////////////////////////////////////////////////////////
    template<typename Z>
    UPVector<Z> sylvesterBackward(UPVector<Z> upv,
                                  const std::string& directory = "",
                                  const bool verbose = false)
    {
        ForwardGraph<std::string,Z> fg;
        std::string A = directory + "/fileA.txt";
        std::string B = directory + "/fileB.txt";
        std::string C = directory + "/fileC.txt";
        std::string D = directory + "/fileD.txt";
        std::string E = directory + "/fileE.txt";
        std::string F = directory + "/fileF.txt";
        std::string G = directory + "/fileG.txt";
        std::string H = directory + "/fileH.txt";
        std::string I = directory + "/fileI.txt";
        if (verbose)
        {
            fg.addVertex(A,1);
            outputToFile(upv,A);
        }

        auto upvPair = BGT::shred2<Z>(upv,true);
        if (verbose)
        {
            fg.addVertex(C,2);
            fg.addEdge(A,C);
            outputToFile(upvPair.second,C);
            fg.addVertex(B,2);
            fg.addEdge(A,B);
            outputToFile(upvPair.first,B);
        }

        upvPair.first = BGT::stretch<Z>(upvPair.first,2,1);
        if (verbose)
        {
            fg.addVertex(D,3);
            fg.addEdge(B,D);
            outputToFile(upvPair.first,D);
        }

        upvPair.second = BGT::stretch<Z>(upvPair.second,2,1);
        upvPair.second = BGT::move<Z>(upvPair.second,1,0);
        if (verbose)
        {
            fg.addVertex(E,3);
            fg.addEdge(C,E);
            outputToFile(upvPair.second,E);
        }

        upvPair.first = reflect(upvPair.first);
        if (verbose)
        {
            fg.addVertex(F,4);
            fg.addEdge(D,F);
            outputToFile(upvPair.first,F);
        }

        upvPair.second = BGT::shift<Z>(upvPair.second,SLMatrix2x2<Z>(1,0,1,1));
        upvPair.second = BGT::move<Z>(upvPair.second,-1,0);
        if (verbose)
        {
            fg.addVertex(H,4);
            fg.addEdge(E,H);
            outputToFile(upvPair.second,H);
        }

        upvPair.first = BGT::shift<Z>(upvPair.first,SLMatrix2x2<Z>(1,1,0,1));
        if (verbose)
        {
            fg.addVertex(G,5);
            fg.addEdge(F,G);
            outputToFile(upvPair.first,G);
        }

        upv = BGT::paste<Z>(upvPair,true);
        if (verbose)
        {
            fg.addVertex(I,6);
            fg.addEdge(G,I);
            fg.addEdge(H,I);
            outputToFile(upv,I);
            fg.ouputToFile(directory);
        }

        return upv;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Apply the AG bijection to an integer partition of odd parts.
    /// \tparam Z is the integer type of the operand objects.
    /// \param upv is the UPVector which represents an integer partition of
    /// odd parts.
    /// \param directory is the folder directory in which to save the
    /// verbose output.
    /// \param verbose determines if the bijection outputs a set of integer
    /// points to a file at each step of the bijection.
    /// \return a UPVector representing an distinct-part integer partition.
    ///
    /// See [1] p.18-20 for more details.
    ////////////////////////////////////////////////////////////////////////
    template<typename Z>
    UPVector<Z> AG(UPVector<Z> upv,
                   const std::string& directory = "",
                   const bool verbose = false)
    {
        ForwardGraph<std::string,Z> fg;
        std::string A = directory + "/fileA.txt";
        std::string B = directory + "/fileB.txt";
        std::string C = directory + "/fileC.txt";
        std::string D = directory + "/fileD.txt";
        std::string E = directory + "/fileE.txt";
        std::string F = directory + "/fileF.txt";
        std::string G = directory + "/fileG.txt";
        std::string H = directory + "/fileH.txt";
        std::string I = directory + "/fileI.txt";
        std::string J = directory + "/fileJ.txt";
        std::string K = directory + "/fileK.txt";
        std::string L = directory + "/fileL.txt";
        std::string M = directory + "/fileM.txt";
        std::string N = directory + "/fileN.txt";
        std::string O = directory + "/fileO.txt";
        std::string P = directory + "/fileP.txt";
        std::string Q = directory + "/fileQ.txt";
        std::string R = directory + "/fileR.txt";
        std::string S = directory + "/fileS.txt";
        std::string T = directory + "/fileT.txt";
        std::string U = directory + "/fileU.txt";
        if(verbose)
        {
            fg.addVertex(A,1);
            outputToFile(upv,A);
        }

        auto upvPair = BGT::cut<Z>(upv,-2,4,1);
        if (verbose)
        {
            fg.addVertex(B,2);
            fg.addEdge(A,B);
            outputToFile(upvPair.second,B);
            fg.addVertex(C,2);
            fg.addEdge(A,C);
            outputToFile(upvPair.first,C);
        }

        /* Begin top maps */

        upvPair.first = BGT::move<Z>(upvPair.first,1,0);
        upvPair.first = BGT::shift<Z>(upvPair.first,SLMatrix2x2<Z>(1,0,-2,1));
        if (verbose)
        {
            fg.addVertex(F,3);
            fg.addEdge(C,F);
            outputToFile(upvPair.first,F);
        }

        auto topPair = BGT::shred2<Z>(upvPair.first,true);
        if (verbose)
        {
            fg.addVertex(I,4);
            fg.addEdge(F,I);
            outputToFile(topPair.first,I);
            fg.addVertex(J,4);
            fg.addEdge(F,J);
            outputToFile(topPair.second,J);
        }

        topPair.first = BGT::stretch<Z>(topPair.first,2,2);
        if (verbose)
        {
            fg.addVertex(M,5);
            fg.addEdge(I,M);
            outputToFile(topPair.first,M);
        }

        topPair.second = BGT::stretch<Z>(topPair.second,2,2);
        topPair.second = BGT::move<Z>(topPair.second,1,-1);
        if (verbose)
        {
            fg.addVertex(N,5);
            fg.addEdge(J,N);
            outputToFile(topPair.second,N);
        }

        auto lhs = BGT::paste<Z>(topPair);
        if (verbose)
        {
            fg.addVertex(Q,6);
            fg.addEdge(M,Q);
            fg.addEdge(N,Q);
            outputToFile(lhs,Q);
        }

        /* Begin bottom maps. */

        auto bottomPair = BGT::shred2<Z>(upvPair.second,true);
        if (verbose)
        {
            fg.addVertex(D,3);
            fg.addEdge(B,D);
            outputToFile(bottomPair.first,D);
            fg.addVertex(E,3);
            fg.addEdge(B,E);
            outputToFile(bottomPair.second,E);
        }

        bottomPair.second = BGT::stretch<Z>(bottomPair.second,2,1);
        bottomPair.second = BGT::move<Z>(bottomPair.second,1,0);
        if (verbose)
        {
            fg.addVertex(H,4);
            fg.addEdge(E,H);
            outputToFile(bottomPair.second,H);
        }

        bottomPair.first = BGT::stretch<Z>(bottomPair.first,2,1);
        if (verbose)
        {
            fg.addVertex(G,4);
            fg.addEdge(D,G);
            outputToFile(bottomPair.first,G);
        }

        bottomPair.second = BGT::move<Z>(bottomPair.second,0,1);
        bottomPair.second = BGT::shift<Z>(bottomPair.second,SLMatrix2x2<Z>(1,-1,0,1));
        if (verbose)
        {
            fg.addVertex(L,5);
            fg.addEdge(H,L);
            outputToFile(bottomPair.second,L);
        }

        bottomPair.first = BGT::shift<Z>(bottomPair.first,SLMatrix2x2<Z>(1,-1,0,1));
        if (verbose)
        {
            fg.addVertex(K,5);
            fg.addEdge(G,K);
            outputToFile(bottomPair.first,K);
        }

        bottomPair.second = reflect<Z>(bottomPair.second);
        if (verbose)
        {
            fg.addVertex(P,6);
            fg.addEdge(L,P);
            outputToFile(bottomPair.second,P);
        }

        bottomPair.first = reflect<Z>(bottomPair.first);
        if (verbose)
        {
            fg.addVertex(O,6);
            fg.addEdge(K,O);
            outputToFile(bottomPair.first,O);
        }

        bottomPair.second = BGT::stretch<Z>(bottomPair.second,1,2);
        bottomPair.second = BGT::move<Z>(bottomPair.second,0,-1);
        if (verbose)
        {
            fg.addVertex(S,7);
            fg.addEdge(P,S);
            outputToFile(bottomPair.second,S);
        }

        bottomPair.first = BGT::stretch<Z>(bottomPair.first,1,2);
        if (verbose)
        {
            fg.addVertex(R,7);
            fg.addEdge(O,R);
            outputToFile(bottomPair.first,R);
        }

        auto rhs = BGT::paste<Z>(bottomPair,true);
        if (verbose)
        {
            fg.addVertex(T,8);
            fg.addEdge(R,T);
            fg.addEdge(S,T);
            outputToFile(rhs,T);
        }

        /* Sum both sides */

        upv = BAT::sum<Z>(lhs,rhs,true);
        if (verbose)
        {
            fg.addVertex(U,9);
            fg.addEdge(T,U);
            fg.addEdge(Q,U);
            outputToFile(upv,U);
            fg.ouputToFile(directory);
        }

        return upv;
    }
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_BIJECTIONS_HPP

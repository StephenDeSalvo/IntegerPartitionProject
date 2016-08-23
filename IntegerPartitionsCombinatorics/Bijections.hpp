////////////////////////////////////////////////////////////////////////
/// \file Bijections.hpp
/// \brief Implements the bijections discussed in [2]
////////////////////////////////////////////////////////////////////////

#ifndef IPC_BIJECTIONS_HPP
#define IPC_BIJECTIONS_HPP

#include <string>

#include "UPVector.hpp"
#include "BGT.hpp"
#include "BAT.hpp"
#include "ForwardGraph.hpp"

namespace IPC
{
	////////////////////////////////////////////////////////////////////////
	/// \brief Applies the "self-conjugate to distinct, odd" bijection of [2]
	/// \tparam Z is the integral type of the operands
	/// \param upv is the self-conjugate Ferrers diagram to undergo the bijection
	/// \param directory is the location to save the verbose output
	/// \param verbose determines if snapshots are taken of the bijection as it happens
	/// \return a distinct, odd-part Ferrers diagram
	///
	/// Please see [2] for more details.
	////////////////////////////////////////////////////////////////////////
	template <typename Z>
	UPVector<Z> scdo(UPVector<Z> upv,
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
			outputToFile(upvPair.first,B);
			fg.addVertex(C,2);
			fg.addEdge(A,C);
			outputToFile(upvPair.second,C);
		}

		upvPair.first = BGT::move<Z>(upvPair.first,1,0);
		upvPair.first = BGT::shift<Z>(upvPair.first,Matrix2x2<Z>(1,-1,0,1));
		if (verbose)
		{
			fg.addVertex(D,3);
			fg.addEdge(B,D);
			outputToFile(upvPair.first,D);
		}
		upvPair.first = BGT::conjugate<Z>(upvPair.first);
		if (verbose)
		{
			fg.addVertex(E,4);
			fg.addEdge(D,E);
			outputToFile(upvPair.first,E);
		}
		upvPair.first = BGT::stretch<Z>(upvPair.first,2,1);
		if (verbose)
		{
			fg.addVertex(F,5);
			fg.addEdge(E,F);
			outputToFile(upvPair.first,F);
		}
		upvPair.first = BGT::move<Z>(upvPair.first,0,-1);
		upvPair.first = BGT::conjugate<Z>(upvPair.first);
		if (verbose)
		{
			fg.addVertex(G,6);
			fg.addEdge(F,G);
			outputToFile(upvPair.first,G);
		}

		upvPair.second = BGT::shift<Z>(upvPair.second,Matrix2x2<Z>(1,0,-1,1));
		if (verbose)
		{
			fg.addVertex(H,3);
			fg.addEdge(C,H);
			outputToFile(upvPair.second,H);
		}
		upvPair.second = BGT::stretch<Z>(upvPair.second,2,1);
		if (verbose)
		{
			fg.addVertex(I,4);
			fg.addEdge(H,I);
			outputToFile(upvPair.second,I);
		}
		upvPair.second = BGT::conjugate<Z>(upvPair.second);
		if (verbose)
		{
			fg.addVertex(J,5);
			fg.addEdge(I,J);
			outputToFile(upvPair.second,J);
		}

		upv = BGT::paste<Z>(upvPair);
		if (verbose)
		{
			fg.addVertex(K,7);
			fg.addEdge(J,K);
			fg.addEdge(G,K);
			outputToFile(upv,K);
			fg.outputToFile(directory);
		}
		return upv;
	}

	////////////////////////////////////////////////////////////////////////
	/// \brief Applies the "self-conjugate to distinct, odd" bijection of [2], backwards
	/// \tparam Z is the integral type of the operands
	/// \param upv is the distinct, odd-part Ferrers diagram to undergo the bijection
	/// \param directory is the location to save the verbose output
	/// \param verbose determines if snapshots are taken of the bijection as it happens
	/// \return a self-conjugate Ferrers diagram
	///
	/// Please see [2] for more details.
	////////////////////////////////////////////////////////////////////////
	template <typename Z>
	UPVector<Z> scdoBackwards(UPVector<Z> upv,
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

		if (verbose)
		{
			fg.addVertex(A,1);
			outputToFile(upv,A);
		}

		auto upvPair = BGT::shred<Z>(upv);
		if (verbose)
		{
			fg.addVertex(B,2);
			fg.addEdge(A,B);
			outputToFile(upvPair.first,B);
			fg.addVertex(C,2);
			fg.addEdge(A,C);
			outputToFile(upvPair.second,C);
		}

		upvPair.first = BGT::stretch<Z>(upvPair.first,1,2);
		if (verbose)
		{
			fg.addVertex(D,3);
			fg.addEdge(B,D);
			outputToFile(upvPair.first,D);
		}
		upvPair.first = BGT::conjugate<Z>(upvPair.first);
		if (verbose)
		{
			fg.addVertex(E,4);
			fg.addEdge(D,E);
			outputToFile(upvPair.first,E);
		}
		upvPair.first = BGT::shift<Z>(upvPair.first,Matrix2x2<Z>(1,0,1,1));
		if (verbose)
		{
			fg.addVertex(F,5);
			fg.addEdge(E,F);
			outputToFile(upvPair.first,F);
		}

		upvPair.second = BGT::stretch<Z>(upvPair.second,1,2);
		upvPair.second = BGT::move<Z>(upvPair.second,1,0);
		if (verbose)
		{
			fg.addVertex(G,3);
			fg.addEdge(C,G);
			outputToFile(upvPair.second,G);
		}
		upvPair.second = BGT::shift<Z>(upvPair.second,Matrix2x2<Z>(1,1,0,1));
		upvPair.second = BGT::move<Z>(upvPair.second,-1,0);
		if (verbose)
		{
			fg.addVertex(H,4);
			fg.addEdge(G,H);
			outputToFile(upvPair.second,H);
		}

		upv = BGT::paste<Z>(upvPair);
		if (verbose)
		{
			fg.addVertex(I,6);
			fg.addEdge(F,I);
			fg.addEdge(H,I);
			outputToFile(upv,I);
			fg.outputToFile(directory);
		}

		return upv;
	}

	////////////////////////////////////////////////////////////////////////
	/// \brief Apply Sylvester's bijection as defined in [2]
	/// \tparam Z is the integer type of the operand objects.
	/// \param upv is the UPVector which represents an integer partition of odd parts
	/// \param directory is the location to save the verbose output
	/// \param verbose determines if snapshots are taken of the bijection as it happens
	/// \return a distinct-part Ferrers diagram
	///
	/// See [1] p.18-20 for more details.
	////////////////////////////////////////////////////////////////////////
	template <typename Z>
	UPVector<Z> sylvester(UPVector<Z> upv,
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

		if (verbose)
		{
			fg.addVertex(A,1);
			outputToFile(upv,A);
		}

		auto upvPairMain = BGT::cut<Z>(upv,-4,2,-1);
		if (verbose)
		{
			fg.addVertex(B,2);
			fg.addEdge(A,B);
			outputToFile(upvPairMain.first,B);
			fg.addVertex(C,2);
			fg.addEdge(A,C);
			outputToFile(upvPairMain.second,C);
		}

		upvPairMain.first = BGT::move<Z>(upvPairMain.first,1,0);
		upvPairMain.first = BGT::shift<Z>(upvPairMain.first,Matrix2x2<Z>(1,-2,0,1));
		if (verbose)
		{
			fg.addVertex(D,3);
			fg.addEdge(B,D);
			outputToFile(upvPairMain.first,D);
		}

		auto upvPairSub1 = BGT::shred<Z>(upvPairMain.first);
		if (verbose)
		{
			fg.addVertex(E,4);
			fg.addEdge(D,E);
			outputToFile(upvPairSub1.first,E);
			fg.addVertex(F,4);
			fg.addEdge(D,F);
			outputToFile(upvPairSub1.second,F);
		}

		upvPairSub1.first = BGT::stretch<Z>(upvPairSub1.first,2,2);
		if (verbose)
		{
			fg.addVertex(G,5);
			fg.addEdge(E,G);
			outputToFile(upvPairSub1.first,G);
		}

		upvPairSub1.second = BGT::stretch<Z>(upvPairSub1.second,2,2);
		upvPairSub1.second = BGT::move<Z>(upvPairSub1.second,1,-1);
		if (verbose)
		{
			fg.addVertex(H,5);
			fg.addEdge(F,H);
			outputToFile(upvPairSub1.second,H);
		}

		auto lhs = BGT::paste<Z>(upvPairSub1);
		if (verbose)
		{
			fg.addVertex(I,6);
			fg.addEdge(G,I);
			fg.addEdge(H,I);
			outputToFile(lhs,I);
		}

		auto upvPairSub2 = BGT::shred<Z>(upvPairMain.second);
		if (verbose)
		{
			fg.addVertex(J,3);
			fg.addEdge(C,J);
			outputToFile(upvPairSub2.first,J);
			fg.addVertex(K,3);
			fg.addEdge(C,K);
			outputToFile(upvPairSub2.second,K);
		}

		upvPairSub2.first = BGT::stretch<Z>(upvPairSub2.first,1,2);
		if (verbose)
		{
			fg.addVertex(L,4);
			fg.addEdge(J,L);
			outputToFile(upvPairSub2.first,L);
		}
		upvPairSub2.first = BGT::shift<Z>(upvPairSub2.first,Matrix2x2<Z>(1,0,-1,1));
		if (verbose)
		{
			fg.addVertex(M,5);
			fg.addEdge(L,M);
			outputToFile(upvPairSub2.first,M);
		}
		upvPairSub2.first = BGT::conjugate<Z>(upvPairSub2.first);
		if (verbose)
		{
			fg.addVertex(N,6);
			fg.addEdge(M,N);
			outputToFile(upvPairSub2.first,N);
		}
		upvPairSub2.first = BGT::stretch<Z>(upvPairSub2.first,2,1);
		if (verbose)
		{
			fg.addVertex(O,7);
			fg.addEdge(N,O);
			outputToFile(upvPairSub2.first,O);
		}

		upvPairSub2.second = BGT::stretch<Z>(upvPairSub2.second,1,2);
		upvPairSub2.second = BGT::move<Z>(upvPairSub2.second,1,1);
		if (verbose)
		{
			fg.addVertex(P,4);
			fg.addEdge(K,P);
			outputToFile(upvPairSub2.second,P);
		}
		upvPairSub2.second = BGT::shift<Z>(upvPairSub2.second,Matrix2x2<Z>(1,0,-1,1));
		if (verbose)
		{
			fg.addVertex(Q,5);
			fg.addEdge(P,Q);
			outputToFile(upvPairSub2.second,Q);
		}
		upvPairSub2.second = BGT::conjugate<Z>(upvPairSub2.second);
		if (verbose)
		{
			fg.addVertex(R,6);
			fg.addEdge(Q,R);
			outputToFile(upvPairSub2.second,R);
		}
		upvPairSub2.second = BGT::stretch<Z>(upvPairSub2.second,2,1);
		upvPairSub2.second = BGT::move<Z>(upvPairSub2.second,0,-1);
		if (verbose)
		{
			fg.addVertex(S,7);
			fg.addEdge(R,S);
			outputToFile(upvPairSub2.second,S);
		}

		auto rhs = BGT::paste<Z>(upvPairSub2);
		if (verbose)
		{
			fg.addVertex(T,8);
			fg.addEdge(O,T);
			fg.addEdge(S,T);
			outputToFile(rhs,T);
		}

		upv = BAT::sum<Z>(lhs,rhs,true);
		if (verbose)
		{
			fg.addVertex(U,9);
			fg.addEdge(T,U);
			outputToFile(upv,U);
			fg.outputToFile(directory);
		}

		return upv;
	}
}

#endif // IPC_BIJECTIONS_HPP

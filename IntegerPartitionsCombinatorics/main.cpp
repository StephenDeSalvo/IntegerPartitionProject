////////////////////////////////////////////////////////////////////////
/// \file main.cpp
/// \brief Contains the main routine
////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \date August 22, 2016
/// \author Brenden Case and Ryan McNicol
/// \version 6.0
///
/// Corrected the code - some functions were misnamed.
///
/// References:
///     [1] I. Pak, The Nature of Integer Partition Bijections II.
///         Asymptotic Stability.
///		[2] B. Case, Programming Partition Bijections
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

using namespace IPC;

typedef std::int64_t int64;

typedef UniquePoint<int64> UPI;

int main()
{
	// Test the "self-conjugate to disinct, odd parts" bijection
	// //////////////////////////////////////////////////////////////////////
	int64 id = 0;
	UPVector<int64> upv_scdo = {
		UPI(1,1,++id), UPI(2,1,++id), UPI(3,1,++id), UPI(4,1,++id), UPI(5,1,++id), UPI(6,1,++id), UPI(7,1,++id),
		UPI(1,2,++id), UPI(2,2,++id), UPI(3,2,++id), UPI(4,2,++id), UPI(5,2,++id), UPI(6,2,++id), UPI(7,2,++id),
		UPI(1,3,++id), UPI(2,3,++id), UPI(3,3,++id), UPI(4,3,++id), UPI(5,3,++id), UPI(6,3,++id),
		UPI(1,4,++id), UPI(2,4,++id), UPI(3,4,++id), UPI(4,4,++id), UPI(5,4,++id),
		UPI(1,5,++id), UPI(2,5,++id), UPI(3,5,++id), UPI(4,5,++id), UPI(5,5,++id),
		UPI(1,6,++id), UPI(2,6,++id), UPI(3,6,++id),
		UPI(1,7,++id), UPI(2,7,++id)
	};
	std::cout << "Pre scdo bijection:\n" << upv_scdo << std::endl;
	std::cout << "Post scdo bijection:\n" << scdo(upv_scdo,"Test1",true) << std::endl;

	// Test the sylvester bijection
	// //////////////////////////////////////////////////////////////////////
	int64 id2 = 0;
	UPVector<int64> upv_sylvester = {
		UPI(1,1,++id2), UPI(2,1,++id2), UPI(3,1,++id2), UPI(4,1,++id2), UPI(5,1,++id2), UPI(6,1,++id2), UPI(7,1,++id2), UPI(8,1,++id2), UPI(9,1,++id2), UPI(10,1,++id2), UPI(11,1,++id2),
		UPI(1,2,++id2), UPI(2,2,++id2), UPI(3,2,++id2), UPI(4,2,++id2), UPI(5,2,++id2), UPI(6,2,++id2), UPI(7,2,++id2), UPI(8,2,++id2), UPI(9,2,++id2), UPI(10,2,++id2), UPI(11,2,++id2),
		UPI(1,3,++id2), UPI(2,3,++id2), UPI(3,3,++id2), UPI(4,3,++id2), UPI(5,3,++id2), UPI(6,3,++id2), UPI(7,3,++id2), UPI(8,3,++id2), UPI(9,3,++id2),
		UPI(1,4,++id2), UPI(2,4,++id2), UPI(3,4,++id2), UPI(4,4,++id2), UPI(5,4,++id2), UPI(6,4,++id2), UPI(7,4,++id2),
		UPI(1,5,++id2), UPI(2,5,++id2), UPI(3,5,++id2),
		UPI(1,6,++id2), UPI(2,6,++id2), UPI(3,6,++id2),
		UPI(1,7,++id2)
	};
	std::cout << "Pre sylvester bijection:\n" << upv_sylvester << std::endl;
	std::cout << "Post sylvester bijection:\n" << sylvester(upv_sylvester,"Test2",true) << std::endl;

	// Test the reversed "self-conjugate to disinct, odd parts" bijection
	// //////////////////////////////////////////////////////////////////////
	int64 id3 = 0;
	UPVector<int64> upv_scdoBackwards = {
		UPI(1,1,++id3), UPI(2,1,++id3), UPI(3,1,++id3), UPI(4,1,++id3), UPI(5,1,++id3), UPI(6,1,++id3), UPI(7,1,++id3), UPI(8,1,++id3), UPI(9,1,++id3), UPI(10,1,++id3), UPI(11,1,++id3), UPI(12,1,++id3), UPI(13,1,++id3),
		UPI(1,2,++id3), UPI(2,2,++id3), UPI(3,2,++id3), UPI(4,2,++id3), UPI(5,2,++id3), UPI(6,2,++id3), UPI(7,2,++id3), UPI(8,2,++id3), UPI(9,2,++id3), UPI(10,2,++id3), UPI(11,2,++id3),
		UPI(1,3,++id3), UPI(2,3,++id3), UPI(3,3,++id3), UPI(4,3,++id3), UPI(5,3,++id3), UPI(6,3,++id3), UPI(7,3,++id3),
		UPI(1,4,++id3), UPI(2,4,++id3), UPI(3,4,++id3),
		UPI(1,5,++id3)
	};
	std::cout << "Pre scdo (backwards) bijection:\n" << upv_scdoBackwards << std::endl;
	std::cout << "Post scdo (backwards) bijection:\n" << scdoBackwards(upv_scdoBackwards,"Test3",true) << std::endl;

	std::size_t counter = 0;
	std::cout << ++counter << std::endl;
//	/* Output verbose sylvester bijection on size 20 partitions. */
//	auto upvv = readInMultiplicities("_odd part sizes/odd_parts_size_20.txt",20,100);
//	for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//	{
//		std::string num = std::to_string(i + 1);
//		std::string directory = "sylvester-20-" + num;
//		sylvester(upvv[i],directory,true);
//	}
//	std::cout << ++counter << std::endl;
//	/* Output verbose sylvester bijection on size 100 partitions. */
//	upvv = readInMultiplicities("_odd part sizes/odd_parts_size_100.txt",100,100);
//	for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//	{
//		std::string num = std::to_string(i + 1);
//		std::string directory = "sylvester-100-" + num;
//		sylvester(upvv[i],directory,true);
//	}
//	std::cout << ++counter << std::endl;
//	/* Output verbose sylvester bijection on size 1000 partitions. */
//	upvv = readInMultiplicities("_odd part sizes/odd_parts_size_1,000.txt",1000,100);
//	for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//	{
//		std::string num = std::to_string(i + 1);
//		std::string directory = "sylvester-1000-" + num;
//		sylvester(upvv[i],directory,true);
//	}
//	std::cout << ++counter << std::endl;
//	/* Output verbose sylvester bijection on size 10000 partitions. */
//	upvv = readInMultiplicities("_odd part sizes/odd_parts_size_10,000.txt",10000,100);
//	for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//	{
//		std::string num = std::to_string(i + 1);
//		std::string directory = "sylvester-10000-" + num;
//		sylvester(upvv[i],directory,true);
//		std::cout << counter << ' ' << i << std::endl;
//	}
//	std::cout << ++counter << std::endl;
//	/* Output verbose sylvester bijection on size 100000 partitions. */
//	upvv = readInMultiplicities("_odd part sizes/odd_parts_size_100,000.txt",100000,100);
//	for (std::size_t i = 0, n = upvv.size(); i < n; ++i)
//	{
//		std::string num = std::to_string(i + 1);
//		std::string directory = "sylvester-100000-" + num;
//		sylvester(upvv[i],directory,true);
//		std::cout << counter << ' ' << i << std::endl;
//	}

	/* Output verbose scdo (backwards) bijection on size 20 partitions. */
	auto upvv2 = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_20.txt",20,100);
	for (std::size_t i = 0, n = upvv2.size(); i < n; ++i)
	{
		std::string num = std::to_string(i + 1);
		std::string directory = "scdo-20-" + num;
		scdoBackwards(upvv2[i],directory,true);
	}
	std::cout << ++counter << std::endl;
	/* Output verbose scdo (backwards) bijection on size 100 partitions. */
	upvv2 = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_100.txt",100,100);
	for (std::size_t i = 0, n = upvv2.size(); i < n; ++i)
	{
		std::string num = std::to_string(i + 1);
		std::string directory = "scdo-100-" + num;
		scdoBackwards(upvv2[i],directory,true);
	}
	std::cout << ++counter << std::endl;
	/* Output verbose scdo (backwards) bijection on size 1000 partitions. */
	upvv2 = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_1,000.txt",1000,100);
	for (std::size_t i = 0, n = upvv2.size(); i < n; ++i)
	{
		std::string num = std::to_string(i + 1);
		std::string directory = "scdo-1000-" + num;
		scdoBackwards(upvv2[i],directory,true);
	}
	std::cout << ++counter << std::endl;
	/* Output verbose scdo (backwards) bijection on size 10000 partitions. */
	upvv2 = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_10,000.txt",10000,100);
	for (std::size_t i = 0, n = upvv2.size(); i < n; ++i)
	{
		std::string num = std::to_string(i + 1);
		std::string directory = "scdo-10000-" + num;
		scdoBackwards(upvv2[i],directory,true);
		std::cout << counter << ' ' << i << std::endl;
	}
	std::cout << ++counter << std::endl;
	/* Output verbose scdo (backwards) bijection on size 100000 partitions. */
	upvv2 = readInMultiplicities("_unique odd part sizes/unique_odd_parts_size_100,000.txt",100000,10);
	for (std::size_t i = 0, n = upvv2.size(); i < n; ++i)
	{
		std::string num = std::to_string(i + 1);
		std::string directory = "scdo-100000-" + num;
		scdoBackwards(upvv2[i],directory,true);
		std::cout << counter << ' ' << i << std::endl;
	}

	return 0;
}

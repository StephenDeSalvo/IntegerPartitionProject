//
//
//  PartitionCreator.hpp
//  ProbabilisticRejection
//
//  Created by Taylor Hamermesh on 1/5/16.
//  Copyright © 2016 Taylor Hamermesh. All rights reserved.
//

#ifndef PartitionCreator_h
#define PartitionCreator_h

#include <stdio.h>
#include <vector>

/**
 A class representing a specific, randomized integer partition. A random partition represents a series of multiplicities, which is the count of pieces of a certain size in an integer partition.
 
 For example, if a partition is size 10, the following are valid multiplicity sets:
 
 - 10,0,0,0,0,0,0,0,0,0 (10 pieces of size 1)
 - 1,0,0,1,1,0,0,0,0,0 (1 piece of size 1, 1 piece of size 4, 1 piece of size five)
 - 8,2,0,0,0,0,0,0,0,0 (8 pieces of size 1, 1 piece of size 2)
 - 0,0,0,0,0,0,0,0,0,1 (1 piece of size 10).
 
 */
class RandomPartition {
public:
    
    /** Stores an integer partition as a series of increasingly large multiplicities. Index zero is garbage.
     Indexes represent the number of pieces of that index's size in the partition.
     */
    std::vector<int>partition_sizes;
    /** Prints out partition multiplicities. Prints to cout each multiplicity in partition_sizes, ignoring the zero index. */
    void printPartition();
    /** Sums all partition multiplicities. Ignores the zero index and returns the total size of all combined pieces. */
    int sumPartition();
};

/** A class which creates partitions of a desired size and with desired restrictions.*/
class PartitionCreator {
public:
    /** Constructor. Initializes the partition creator to have no active restrictions.*/
    PartitionCreator();
    /** Valid partition creation algorithms. self_similar_div_conquer is presently nonfunctional and should not be used.*/
    enum sampleAlgorithms {rejection_sample, div_conquer_deterministic, self_similar_div_conquer};
    /** Valid restrictions. None is default. even_parts is presently nonfunctional and should not be used*/
    enum activeRestrictions {none, even_parts, odd_parts};
    
    /** Generates a random partition of a given size. One may choose the algorithm to use for this generation.
     Rejection sample is effective within till around 10^5 in size at which point it will likely no longer terminate, and Divide and conquer with deterministic second half will work until around 10^8 in size, after which it should still work, albeit slowly.
     
     Nondefault restrictions desired should be made active before running this using the setRestriction function, as this effects how the partition is generated.
     
     If one wants odd distinct partition generation, generate using generateOddDistinct instead.
     @param size The desired partition size.
     @param sampleAlgorithms The desired algorithm to run.
     @see setRestriction()
     @see generateOddDistinct()
     */
    RandomPartition* generateRandomPartition(int size, enum PartitionCreator::sampleAlgorithms = div_conquer_deterministic);
    
    /** Sets restrictions to be used in generateRandomPartition().
     @param activeRestrictions Makes this parameter the active restriction, none being default. 
     @see generateRandomPartition()*/
    void setRestriction(enum PartitionCreator::activeRestrictions);
    
    /** Generates odd distinct partitions. Odd distinct partitions have only either 1's or 0's in odd indexed slots. Restrictions do not affect this function.
     @param goal_size The desired partition size.*/
    RandomPartition* generateOddDistinct(int goal_size);
    
    /** Defunct poisson generation attempted implementation. A non-class updated attempt which works despite asymptotic overshoot in partitionCreator.cpp exists
     @param size Desired partition size.*/
    void poissonGeneration(int size);
private:
    /** 
     Rejection sample algorithm for partition generation.
     @param goal_size Size of partition to generate
     */
    RandomPartition* rejectionSample(int goal_size);
    /**
     Divide and conquer with deterministic second half algorithm for partition generation.
     @param goal_size Size of partition to generate
     */
    RandomPartition* divConquerDeterministic(int goal_size);
    /**
     In progress non-functional self similar divide and conquer algorithm for partition generation.
     @param goal_size Size of partition to generate
     */
    RandomPartition* selfSimilarDivConquer(int goal_size);
    /**
     Generates multiplicities values for a partition. These values are not guaranteed to sum to the desired size, though they will statistically be rather close
     Restrictions affect the way that this function operates.
     @param size Aimed for generation size
     @param start_pos Dictates multiplicity where generation of multiplicities begins. 
     @see setRestriction()
     */
    RandomPartition* createPartitionGroups(int size, int start_pos);
    /**
     Uses bernoulli generation and modified rejection sample in order to produce distinct odd parts multiplicities. Unaffected by restrictions. Not guaranteed to be equal to the target size.
     @param size Aimed for generation size
     */
    RandomPartition* createPartitionGroupsWithBernoulli(int size);

    /**Geometric random variable. */
    double U;
    /**Currently active restriction on generateRandomPartition(), default None.
      @see generateRandomPartition()*/
    activeRestrictions current_restriction;
};

#endif /* PartitionCreator_h */

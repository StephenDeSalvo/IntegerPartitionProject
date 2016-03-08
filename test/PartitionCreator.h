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


class integer_partition {
public:
    //std::vector<int>* getFerrersIndexes();
    std::vector<int>partition_sizes;
    void printPartition();
};





//To be edited later as updates needed
class RandomPartition {
public:
    //std::vector<int>* getFerrersIndexes();
    std::vector<int>partition_sizes;
    void printPartition();
    int sumPartition();
};



class PartitionCreator {
public:
    PartitionCreator();
    enum sampleAlgorithms {rejection_sample, div_conquer_deterministic, self_similar_div_conquer};
    enum activeRestrictions {none, even_parts, odd_parts};
    
    RandomPartition* generateRandomPartition(int size, enum PartitionCreator::sampleAlgorithms = div_conquer_deterministic);
    void setRestriction(enum PartitionCreator::activeRestrictions);
    
    RandomPartition* generateOddDistinct(int goal_size);
    
    //debug
    void poissonGeneration(int size);
private:
    RandomPartition* rejectionSample(int goal_size);
    RandomPartition* divConquerDeterministic(int goal_size);
    RandomPartition* selfSimilarDivConquer(int goal_size);
    
    
    RandomPartition* selfSimilarDivConquerDEFUNCT(int goal_size);
    RandomPartition* createPartitionGroups(int size, int start_pos);
    RandomPartition* createPartitionGroupsWithBernoulli(int size);

    double U;
    activeRestrictions current_restriction;
};

#endif /* PartitionCreator_h */

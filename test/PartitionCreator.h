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

//To be edited later as updates needed
class RandomPartition {
public:
    //std::vector<int>* getFerrersIndexes();
    std::vector<int>partition_sizes;
};

class PartitionCreator {
public:
    enum sampleAlgorithms {rejection_sample, div_conquer_deterministic, self_similar_div_conquer};
    RandomPartition* generateRandomPartition(int size, enum PartitionCreator::sampleAlgorithms = div_conquer_deterministic);
private:
    RandomPartition* rejectionSample(int goal_size);
    RandomPartition* divConquerDeterministic(int goal_size);
    RandomPartition* selfSimilarDivConquer(int goal_size);
    
    
    RandomPartition* selfSimilarDivConquerDEFUNCT(int goal_size);
    
    
    RandomPartition* DEBUG_createRejSamplePartGroups(int size,int start_pos);
    RandomPartition* createPartitionGroups(int size, int start_pos);

    double U;
};

#endif /* PartitionCreator_h */

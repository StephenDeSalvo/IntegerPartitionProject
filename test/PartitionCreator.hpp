//
//  PartitionCreator.hpp
//  ProbabilisticRejection
//
//  Created by Taylor Hamermesh on 1/5/16.
//  Copyright © 2016 Taylor Hamermesh. All rights reserved.
//

#ifndef PartitionCreator_hpp
#define PartitionCreator_hpp

#include <stdio.h>
#include <vector>

//To be edited later as updates needed
class RandomPartition {
public:
    std::vector<int>partition_sizes;
};

class PartitionCreator {
public:
    RandomPartition* generateRandomPartition(int size);
private:
    RandomPartition* RejectionSample(int goal_size);
    RandomPartition* createPartitionGroups(int size);
    int sumOverPartition(const RandomPartition& part);
};

#endif /* PartitionCreator_hpp */

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
    std::vector<int>* getFerrersIndexes();
    std::vector<int>partition_sizes;
};

class PartitionCreator {
public:
    RandomPartition* generateRandomPartition(int size);
private:
    RandomPartition* RejectionSample(int goal_size);
    RandomPartition* PDC_DSH_IP(int goal_size);
    RandomPartition* SS_PDC_IP(int goal_size);
    RandomPartition* createPartitionGroups(int size, int start_pos);

    double U;
};

#endif /* PartitionCreator_h */

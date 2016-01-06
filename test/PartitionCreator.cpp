//
//  PartitionCreator.cpp
//  ProbabilisticRejection
//
//  Created by Taylor Hamermesh on 1/5/16.
//  Copyright © 2016 Taylor Hamermesh. All rights reserved.
//

#include "PartitionCreator.hpp"

RandomPartition* PartitionCreator::generateRandomPartition(int size) {
    return nullptr;
}

void PartitionCreator::RejectionSample(int goal_size) {
    int counter = 0;
    for (;;) {
        RandomPartition* test_partition = createPartitionGroups();
        
        //loop through the partition and count all entries
        counter = 0;
        for (int i = 0; i<goal_size; i++)
        {
            //to be coded
            continue;
        }
    }
}

RandomPartition* PartitionCreator::createPartitionGroups() {
    return nullptr;
}

//
//  PartitionCreator.cpp
//  ProbabilisticRejection
//
//  Created by Taylor Hamermesh on 1/5/16.
//  Copyright © 2016 Taylor Hamermesh. All rights reserved.
//

#include "PartitionCreator.hpp"
#include "math.h"


RandomPartition* PartitionCreator::generateRandomPartition(int size) {
    RandomPartition* partition = new RandomPartition();
    
    //presently runs rejection sample. Could run other functions here or allow options later.
    RejectionSample(size);
    return nullptr;
}

RandomPartition* PartitionCreator::RejectionSample(int goal_size) {
    //keep a counter to compare the number of partitions with the result
    int counter = 0;
    
    RandomPartition* test_partition = nullptr;
    
    for (;;) {
        //use uniform distributions to generate numbers for partition groups
        test_partition = createPartitionGroups(goal_size);
        
        //delete this below and in the loop and replace it with either <= goal_size or <goal_size,
        //based on the indexing metric we agree on
        
        int DEBUG_VALID_STOP_POINT = 10000000;
        
        //loop through the partition we generate and count all entries to see if we generated valid partitions
        counter = 0;
        
        for (int i = 0; i<DEBUG_VALID_STOP_POINT; i++)
        {
            /*Two ideas for partition indexing.
             
             
             First: zero index value of vector is meaningless or some utility value we may need,
             and arbitrary index I would 1 to 1 correspond with the number of parts of size I.
             
             Second: index from zero like normal, deal with the mental size decrease in all instances
             
             To be determined which is preferable.
             */
            
            //sum partition counts here using whichever indexing method we agree is better.
            
            
            
            
            
            
            
            
            
            
        }
        
        //conclude if we hit the goal size
        if (counter==goal_size) {
            return test_partition;
        }
    }
}

RandomPartition* PartitionCreator::createPartitionGroups(int size) {
    double c = 3.14159/sqrt(6);
    double x = 1 - (c / (sqrt(size)));
    
    //use uniform distributions to generate numbers for partition groups here
    
    
    
    
    
    return nullptr;
}

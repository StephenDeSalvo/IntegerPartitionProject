//
//  PartitionCreator.cpp
//  ProbabilisticRejection
//
//  Created by Taylor Hamermesh on 1/5/16.
//  Copyright © 2016 Taylor Hamermesh. All rights reserved.
//

#include "PartitionCreator.hpp"
#include "math.h"
#include <random>
#include <chrono>


std::vector<int>* RandomPartition::getFerrersIndexes() {
    //loop through partitions in reverse order to give ferrer's diagram sizes in a vector:
    //largest size stored at index 1, smallest at n
    
    //no ferrers diagram if there are no partition sizes
    int size = partition_sizes.size();
    if (size==0)
        return nullptr;
    
    std::vector<int>* ferrersIndexes = new std::vector<int>;
    
    //loop through all multiplicities
    for (int i = size; i>1; i--) {
        int multQuantity = partition_sizes[i];
        
        if (multQuantity == 0)
            continue;
        
        //push back the size of the value however many times it is present
        for (int j=0; j<multQuantity; j++) {
            ferrersIndexes->push_back(i);
        }
            
    }
    
    return ferrersIndexes;
}







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
    

        //use uniform distributions to generate numbers for partition groups
        test_partition = createPartitionGroups(goal_size);
        
        //delete this below and in the loop and replace it with either <= goal_size or <goal_size,
        //based on the indexing metric we agree on
        
        //int DEBUG_VALID_STOP_POINT = 10000000;
        
        //loop through the partition we generate and count all entries to see if we generated valid partitions
        counter = sumOverPartition(*test_partition);
        

        
        //conclude if we hit the goal size
        if (counter==goal_size) {
            return test_partition;
        }
        else return nullptr;
    
}



RandomPartition* PartitionCreator::createPartitionGroups(int size) {
    //double c = 3.14159/sqrt(6);
    //double x = 1 - (c / (sqrt(size)));
    
    //use geometric distributions to generate numbers for partition groups here
    
    RandomPartition* a = new RandomPartition();
    
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    
    std::geometric_distribution<int> distribution (0.5);
    
    for(int i = 1; i <= size; i++){
        int number = distribution(generator);
        a->partition_sizes[i] = number;
    }
    
    
    return a;
}

int PartitionCreator::sumOverPartition(const RandomPartition& part){
    int sum;
    /*Two ideas for partition indexing.
     
     
     First: zero index value of vector is meaningless or some utility value we may need,
     and arbitrary index I would 1 to 1 correspond with the number of parts of size I.
     
     Second: index from zero like normal, deal with the mental size decrease in all instances
     
     To be determined which is preferable.
     */
    
    //sum partition counts here using whichever indexing method we agree is better.
    for(int i = 1; i <= part.partition_sizes.size(); ++i){
        sum += i * part.partition_sizes[i];
    }
    return sum;
}

int main(void) {
    return 0;
}
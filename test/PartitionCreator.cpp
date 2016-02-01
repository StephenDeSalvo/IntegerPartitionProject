//
//  PartitionCreator.cpp
//  ProbabilisticRejection
//
//  Created by Taylor Hamermesh on 1/5/16.
//  Copyright © 2016 Taylor Hamermesh. All rights reserved.
//

#include "PartitionCreator.h"
#include "math.h"
#include <random>
#include <chrono>
#include <iostream>


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

RandomPartition* PartitionCreator::generateRandomPartition(int size, enum PartitionCreator::sampleAlgorithms algo) {

    //error handling: do not generate partitions of size zero or less
    if (size<=0)
        return nullptr;
    
    RandomPartition* partition = nullptr;
    
    //use the algorithm passed by the user. Has a default value in the header, check if interested.
    switch (algo) {
        case rejection_sample:
            partition = RejectionSample(size);
            break;
        case div_conquer_deterministic:
            partition = PDC_DSH_IP(size);
            break;
        case self_similar_div_conquer:
            partition = selfSimilarDivConquer(size);
            break;
    }
    
    return partition;
}


RandomPartition* PartitionCreator::RejectionSample(int goal_size) {
    //keep a counter to compare the number of partitions with the result
    int counter = 0;
    
    RandomPartition* test_partition = nullptr;

    //use uniform distributions to generate numbers for partition groups.
    //partition_size[i] is the number of "i" sized partition groups.
    //Note that we index from 1 to goal_size.
    
    test_partition = createPartitionGroups(goal_size,1);

    //count if we generated a partition of the correct size.
    for(int i = 1; i <= test_partition->partition_sizes.size(); ++i){
        counter += i * test_partition->partition_sizes[i];
    }

    //conclude if we hit the goal size
    if (counter==goal_size) {
        return test_partition;
    }
    else return nullptr;
    
}

RandomPartition* PartitionCreator::PDC_DSH_IP(int goal_size){
    RandomPartition* test_partition = nullptr;
    
    test_partition = createPartitionGroups(goal_size,2);
    //test_partition->partition_sizes.erase(test_partition->partition_sizes.begin()+1);
    
    int k = goal_size;
    for(int i = 2; i <= goal_size; ++i){
        k -= i*test_partition->partition_sizes[i];
    }
    
    if(k >= 0 && U < exp(-k*3.14159/sqrt(6*goal_size))) {
        //test_partition->partition_sizes.insert(test_partition->partition_sizes.begin()+1, k);
        test_partition->partition_sizes[1] = k;
        return test_partition;
    }
    else return nullptr;
}



RandomPartition* PartitionCreator::selfSimilarDivConquer(int goal_size) {
    //DEBUG
    return nullptr;
    
    
    /*
    const double c = 3.14159/sqrt(6);
    const double x = 1 - (c / (sqrt(goal_size)));
    int k;
    
    time_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator ((unsigned int)seed);
    
    std::uniform_real_distribution<double> uni_distribution(0.0,1.0);
    U = uni_distribution(generator);
    
    RandomPartition* test_partition = nullptr;
    if(goal_size == 1){
        test_partition->partition_sizes.push_back(1);
        return test_partition;
    }
    else{
        test_partition->partition_sizes.resize(goal_size+1);
        test_partition->partition_sizes[0] = 0;
        if(goal_size/2 == 0){
            for(int i = 1; i <= goal_size/2; i++){
                std::geometric_distribution<unsigned int> geo_distribution (1-pow(x,1+2*(i-1)));
                test_partition->partition_sizes[2*i-1] = geo_distribution(generator);
                test_partition->partition_sizes[2*i] = 0;
            }
            k = goal_size;
            for (int i = 1; i <= goal_size/2; i++){
                k -= (2*i-1)*test_partition->partition_sizes[2*i-1];
            }
        }
        else if(goal_size/2 == 1){
            for(int i = 1; i <= goal_size/2; i++){
                std::geometric_distribution<unsigned int> geo_distribution (1-pow(x,1+2*(i-1)));
                test_partition->partition_sizes[2*i-1] = geo_distribution(generator);
                test_partition->partition_sizes[2*i] = 0;
            }
            std::geometric_distribution<unsigned int> geo_distribution (1-pow(x,goal_size));
            test_partition->partition_sizes[goal_size] = geo_distribution(generator);
            k = goal_size;
            for(int i = 1; i <= goal_size/2+1; i++){
                k -= (2*i-1)*test_partition->partition_sizes[2*i-1];
            }

        }
        
        if(k<0 || k/2 == 1)
            return nullptr;
        
        else if(*******){
            RandomPartition* a = selfSimilarDivConquer(k/2);
            for (int i = 1; i <= goal_size/2; i++){
                test_partition->partition_sizes[2*i] = a->partition_sizes[2*i-1];
                return test_partition;
            }
        }
        else return nullptr;

    }
  */
}



RandomPartition* PartitionCreator::DEBUG_createRejSamplePartGroups(int size,int start_pos) {
    return nullptr;
}





//See function DEBUG_createRejSamplePartGroups
//It's possible based on the paper that the math here is incorrect
RandomPartition* PartitionCreator::createPartitionGroups(int size,int start_pos) {
    double c = 3.14159/sqrt(6);
    double x = 1 - (c / (sqrt(size)));
    
    //use geometric distributions to generate numbers for partition groups here
    
    RandomPartition* a = new RandomPartition();
    
    time_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator ((unsigned int)seed);
    
    a->partition_sizes.resize(size+1);
    for(int i = 0; i < start_pos; i++){
        a->partition_sizes[i] = 0;
        
    }
    
    std::uniform_real_distribution<double> uni_distribution(0.0,1.0);
    U = uni_distribution(generator);
    
    if(start_pos == 2)
        x = x*x;
    for(int i = start_pos; i <= size; i++){
    
        std::geometric_distribution<unsigned int> geo_distribution (1-x);
        
        a->partition_sizes[i] = geo_distribution(generator);
        
        x = x*x; // add another factor to x.  I.e., x^i --> x^i+1)
        
    }
    
    return a;
}


int main(){
    int size = 9;
    RandomPartition* test;
    PartitionCreator* PC = new PartitionCreator();
    
    test = PC->PartitionCreator::generateRandomPartition(size);
    for(int i = 1; i<=size; ++i){
        std::cout << test->partition_sizes[i] << "  ";
    }
    std::cout << std::endl;
}


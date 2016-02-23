//
//  PartitionCreator.cpp
//  ProbabilisticRejection
//
//  Created by Taylor Hamermesh on 1/5/16.
//  Copyright © 2016 Taylor Hamermesh. All rights reserved.
//

#include "PartitionCreator.h"
#include <cmath>
#include <cfloat>
#include <random>
#include <chrono>
#include <iostream>


PartitionCreator::PartitionCreator() {
    current_restriction = none;
}


void PartitionCreator::setRestriction(enum PartitionCreator::activeRestrictions restriction) {
    current_restriction = restriction;
}

RandomPartition* PartitionCreator::generateRandomPartition(int size, enum PartitionCreator::sampleAlgorithms algo) {

    //error handling: do not generate partitions of size zero or less
    if (size<=0)
        return nullptr;
    
    RandomPartition* partition = nullptr;
    
    //use the algorithm passed by the user. Has a default value in the header, check if interested.
    switch (algo) {
        case rejection_sample:
        {
            partition = rejectionSample(size);
            break;
        }
        case div_conquer_deterministic:
        {
            partition = divConquerDeterministic(size);
            break;
        }
        case self_similar_div_conquer:
        {
            //partition = selfSimilarDivConquer(size);
            break;
        }
        default:
        {
            std::cout << "Generate Random Partition ran without a valid function enum";
            exit(5);
        }
    }
    return partition;
}


RandomPartition* PartitionCreator::rejectionSample(int goal_size) {
    RandomPartition* test_partition = nullptr;
    
    //rerun the algorithm until it works.
    for (;;)
    {
        //keep a counter to compare the number of partitions with the result
        int counter = 0;
        
        //delete the last partition allocation if one exists
        if (test_partition!=nullptr)
            delete test_partition;
        
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
    }
} 

RandomPartition* PartitionCreator::divConquerDeterministic(int goal_size){
    RandomPartition* test_partition = nullptr;
    
    //rerun the algorithm until it works.
    for (;;)
    {
        //delete the last partition allocation if one exists
        if (test_partition != nullptr)
            delete test_partition;
    
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
    }
}

RandomPartition* PartitionCreator::selfSimilarDivConquer(int goal_size)
{
    //In progress
    return nullptr;
}


RandomPartition* PartitionCreator::selfSimilarDivConquerDEFUNCT(int goal_size) {
    //Returns nullptr if called, only still here for prior code until new version implemented
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
            RandomPartition* a = SS_PDC_IP(k/2);
            for (int i = 1; i <= goal_size/2; i++){
                test_partition->partition_sizes[2*i] = a->partition_sizes[2*i-1];
                return test_partition;
            }
        }
        else return nullptr;

    }
    
}
*/
    
}


//DEBUG



void PartitionCreator::poissonGeneration(int size)
{
    double c = 3.14159/sqrt(6);
    double pi = 3.14159;
    
    double x = exp(-(c / (sqrt(size))));
    double s=0.0; //get an interval length s
    
    std::vector<double> poissonPositions;
    
    time_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator ((unsigned int)seed);
    std::uniform_real_distribution<double> uni_distribution(0.0,1.0);
    
    double a=uni_distribution(generator); //random variable
    std::exponential_distribution<double> exp_distribution(1);
    
    
    RandomPartition* part = new RandomPartition;
    part->partition_sizes.push_back(0);
    
    

    /*
    //repeat until double precision breaks down but this is too slow so we do not use this
    double j=1.0;
    while (1/(j*j)!=0.0) {
        s+=(1/(j*j))*((j*pow(x,j))/(1-pow(x,j))); //see formula 34
        j++;
    }*/
    
    
    
    //supposedly tight bound:
    s = ((pi*pi)/6)*(x/(1-x));
    
    
    
    
    double time = 0.0;
    int arrivals = 0;
    
    double current_target = x/(1-x);
    int index = 1;
    
    //keep track of whether we're done
    bool flag = true;
    while (flag)
    {
        double val = exp_distribution(generator);
        time += val;
        if (time > s) // if outside boundary stop
            flag = false;
        if (time > current_target) //once we complete the interval we were in
        {
            part->partition_sizes.push_back(arrivals);              //store the number of arrivals
            arrivals = 0;                                           //reset arrivals
           
            index++;
            double next_interval = pow(x,index)/(1-pow(x,index));   //calculate the next interval
            current_target+=next_interval;
            
            while (current_target < time)                           //run till we are in an interval
            {
                part->partition_sizes.push_back(0);
                index++;
                double next_interval = pow(x,index)/(1-pow(x,index));   //calculate the next interval
                current_target+=next_interval;
            }
        }
        poissonPositions.push_back(time);
        arrivals++;                                                 //increment arrivals each time we're in the interval
    
    }
    
    std::cout << "Printing Poisson values, s is " << s<< " and N(t) is " << arrivals <<  std::endl;
    for (int i=0;i<poissonPositions.size(); i++)
        std::cout << poissonPositions[i] << std::endl;
    
    part->printPartition();
    
}
//END DEBUG




RandomPartition* PartitionCreator::createPartitionGroups(int size,int start_pos) {
    double c = 3.14159/sqrt(6);
    double x = 1 - (c / (sqrt(size)));
    
    int iter_size = 1; //go one sized steps unless restrictions active
    
    if (current_restriction == activeRestrictions::even_parts)
    {
        //it's an error if size is odd
        if (size % 2 == 0)
        {
            std::cout << "Odd size was given to an even restricted partition's generation, this will never terminate. "
            << std::endl << "Returning a size n partition" << std::endl;
            
            RandomPartition* a = new RandomPartition();
            a->partition_sizes.resize(size+1);
            for (int i = 1; i<=size-1;i++)
                a->partition_sizes[i] = 0;
            a->partition_sizes[size]=1;
            return a;
        }
        
        //start from one higher position if we don't have an even start
        if ((start_pos % 2)!=0)
            start_pos++;
        iter_size = 2;
    }
    else if (current_restriction == activeRestrictions::odd_parts)
    {
        //start from one higher position if we begin at two
        if (start_pos == 2)
            start_pos++;
        iter_size = 2;
    }
    
    
    
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
    
    double y = x;
    
    //if(start_pos == 2)
    //    y = x*x;
    
    for(int i = start_pos; i <= size; i+=iter_size) { //changing to iter size allows odd sampling
    
        //std::geometric_distribution<unsigned int> geo_distribution (1-y);
        
        
        a->partition_sizes[i] = floor(log(uni_distribution(generator))/(log(y)*i));
        
        //y *= x; // add another factor to x.  I.e., x^i --> x^i+1)
        
    }
    
    return a;
}

/*
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
*/

void RandomPartition::printPartition(){
    for(int i = 1; i<=partition_sizes.size()-1; ++i){
        std::cout << partition_sizes[i] << "  ";
    }
    std::cout << std::endl;
}


int main() {
    /*
    int size = 17;
    RandomPartition* test;
    RandomPartition* test_2;
    RandomPartition* test_odd_part;
    RandomPartition* test_even_part;
    PartitionCreator* PC = new PartitionCreator();
    PartitionCreator* PC_restricted = new PartitionCreator();
    
    
    PC->poissonGeneration(100);
    PC_restricted->setRestriction(PartitionCreator::activeRestrictions::odd_parts);
    
    test = PC->generateRandomPartition(size, PartitionCreator::rejection_sample);
    test_2 = PC->generateRandomPartition(size, PartitionCreator::div_conquer_deterministic);
    test_odd_part = PC_restricted->generateRandomPartition(size, PartitionCreator::rejection_sample);
    
    PC_restricted->setRestriction(PartitionCreator::activeRestrictions::even_parts);
    test_even_part = PC_restricted->generateRandomPartition(size, PartitionCreator::rejection_sample);
    
    
    
    test->printPartition();
    test_2->printPartition();
    test_odd_part->printPartition();
    if (test_even_part!=nullptr)
        test_even_part->printPartition();
    
    
    std::cout << std::endl;
     */

    PartitionCreator* PC = new PartitionCreator();
    PC->poissonGeneration(20);
}


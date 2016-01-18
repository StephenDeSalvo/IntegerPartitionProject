////////////////////////////////////////////////////////////////////////
/// \file main.cpp
////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \date January 17, 2016
/// \author Brenden Case
///
/// Here I demonstrate an IntegerPartitions class with a forward iterator.
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include "IntegerPartitions.hpp"

////////////////////////////////////////////////////////////////////////
/// \brief Outputs an integer partition as a vector of multiplicities to a stream.
/// \param os is the stream to which the integer partition is output.
/// \param partition is the integer partition to output.
/// \return the stream, now containing the integer partition.
////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const IPC::IntegerPartitions::Partition& partition)
{
    for (auto elnt : partition)
    {
        os << elnt << " ";
    }
    os.put('\n');
    os.flush();

    return os;
}

////////////////////////////////////////////////////////////////////////
/// \brief The main routine.
/// \return 0 if the program exits successfully.
///
/// Demonstrates the IntegerPartition class and its forward iterator.
/// The user has an option to view an integer's partitions as vectors
///  of multiplicities or as Ferrers diagrams in the console.
/// For large integers, this isn't useful.
///////////////////////////////////////////////////////////////////////////
int main()
{
    size_t N = 0;
    do
    {
        std::cout << "Enter a positive integer, or 0 to exit: ";
        std::cin >> N;

        if (N != 0)
        {
            IPC::IntegerPartitions ip(N);
            size_t choice = 0;

            std::cout << "1) Vector of multiplicities.\n"
                         "2) Ferrers diagram.\n"
                         "Please enter the number corresponding to how you would like to\n"
                         "display the partitions: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                size_t counter = 0;
                for (auto part : ip)
                {
                    std::cout << part;
                    ++counter;
                }
                std::cout << "There are " << counter << " partitions of " << N << "." << std::endl;
            }
                break;
            case 2:
            {
                size_t counter = 0;
                size_t mult = 0;
                for (auto part : ip)
                {
                    for (size_t i = 1; i <= part.size(); ++i)
                    {
                        mult = part.at(i-1);
                        while (mult > 0)
                        {
                            for (size_t j = i; j > 0; --j)
                                std::cout << '*';
                            --mult;
                            std::cout << std::endl;
                        }
                    }
                    std::cout << std::endl;
                    ++counter;
                }
                std::cout << "There are " << counter << " partitions of " << N << "." << std::endl;
            }
                break;
            default:
            {
                std::cout << "Invalid input.\n\n";
            }
                break;
            }
        }
    } while (N != 0);

    std::cout << "Goodbye!\n";

    return 0;
}

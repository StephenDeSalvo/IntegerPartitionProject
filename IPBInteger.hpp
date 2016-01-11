#ifndef IPB_INTEGER_HPP
#define IPB_INTEGER_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <algorithm>
#include <functional>
namespace IPB
{
    typedef std::vector<size_t> Partition;

    class Integer
    {
    public:
        Integer(size_t N)
            : N(N)
        {
            assert(N > 0);
            size_t data[N];
            generatePartitions(N,N,0,data);
        }

        void printPartitions() const
        {
            for (auto part : partitions)
            {
                for (size_t i = 0, n = part.size(); i < n && part.at(i) != 0; ++i)
                {
                    for (size_t length = part.at(i); length > 0; --length)
                        std::cout << '*';
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
        }
        size_t getSize() const
        {
            return N;
        }
        void printEulerBijection() const
        {
            for (auto part : partitions)
            {
                bool unique = true;
                std::list<size_t> seen;
                for (auto it = std::begin(part); it != std::end(part) && unique; ++it)
                {
                    if (std::find(std::begin(seen),std::end(seen),*it) == std::end(seen))
                        seen.push_back(*it);
                    else
                        unique = false;
                }
                if (!unique)
                    continue;

                // Repeated code, compare with printPartitions() above.
                for (size_t i = 0, n = part.size(); i < n && part.at(i) != 0; ++i)
                {
                    for (size_t length = part.at(i); length > 0; --length)
                        std::cout << '*';
                    std::cout << std::endl;
                }
                std::cout << "GOES TO\n";

                Partition part2;
                for (size_t i = 0, n = part.size(); i < n && part.at(i) != 0; ++i)
                {
                    size_t num = part.at(i);
                    if (num%2 == 1)
                        part2.emplace_back(num);
                    else
                    {
                        size_t counter = 1;
                        while (num%2 == 0)
                        {
                            num /= 2;
                            ++counter;
                        }
                        for (size_t i = 0; i < counter; ++i)
                            part2.emplace_back(num);
                    }
                }
                std::sort(std::begin(part2),std::end(part2),std::greater<size_t>());
                for (size_t i = 0, n = part2.size(); i < n && part2.at(i) != 0; ++i)
                {
                    for (size_t length = part2.at(i); length > 0; --length)
                        std::cout << '*';
                    std::cout << std::endl;
                }
                std::cout << "\n";
            }
        }
    private:
        size_t N;
        std::list<Partition> partitions;

        void generatePartitions(size_t N, size_t M, size_t in, size_t* data)
        {
            if (N == 0)
            {
                Partition p;
                for (size_t i = 0; i < in; ++i)
                    p.emplace_back(data[i]);
                partitions.emplace_back(p);
            }
            else
            {
                for (size_t i = M; i > 0; --i)
                {
                    if (i <= N)
                    {
                        data[in] = i;
                        generatePartitions(N-i,i,in+1,data);
                    }
                }
            }
        }
    };
}


#endif // IPB_INTEGER_HPP

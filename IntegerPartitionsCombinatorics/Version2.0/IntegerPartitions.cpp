#include "IntegerPartitions.hpp"

namespace IPC
{
    ////////////////////////////////////////////////////////////////////////
    /// \brief Creates a set of integer partitions.
    /// \param integer is the integer which is to be partitioned.
    ////////////////////////////////////////////////////////////////////////
    IntegerPartitions::IntegerPartitions(const std::size_t& integer)
        : integer(integer)
    {

    }

    ////////////////////////////////////////////////////////////////////////
    /// \return the integer which has been partitioned.
    ////////////////////////////////////////////////////////////////////////
    std::size_t IntegerPartitions::getInteger() const
    {
        return integer;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \return an iterator containing the first integer partition.
    ///
    /// The first integer partition is always (N,0,...,0) where N is the
    /// actual integer and 0 occurs N-1 times.
    ////////////////////////////////////////////////////////////////////////
    IntegerPartitions::Iterator IntegerPartitions::begin() const
    {
        Iterator iterator(this);
        return iterator;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \return the iterator after the last iterator containing a partition.
    ///
    /// The end iterator is defined uniquely by its container and a nonexistent
    /// partition - that is, a partition of size 0.
    /// The last integer partition is always (0,...,0,1) where 0 occurs N-1
    /// times, where N is the actual integer.
    ////////////////////////////////////////////////////////////////////////
    IntegerPartitions::Iterator IntegerPartitions::end() const
    {
        Iterator iterator(this);
        iterator.partition.clear();
        return iterator;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Advances the iterator by one step.
    /// \return the iterator post-increment.
    ///
    /// This method contains the actual logic for generating successive integer
    /// partitions.
    ////////////////////////////////////////////////////////////////////////
    IntegerPartitions::Iterator& IntegerPartitions::Iterator::operator++()
    {
        const std::size_t N = container->getInteger();

        // Useful for tracking the algorithm's current position in the integer partition.
        std::size_t idx = 0;

        // Useful for tracking the number and position of succesive ones which have been passed.
        // Will not exceed a size of two.
        std::vector<std::size_t> one_count;

        while (idx < N && partition.at(idx) < 2 && one_count.size() < 2)
        {
            if (partition.at(idx) == 1)
                one_count.emplace_back(idx);
            ++idx;
        }
        // If two successive ones (with no greater value between them) exist
        //  at the "beginning" of the partition...
        if (one_count.size() == 2)
        {
            // ...increment the element after the last one...
            ++partition.at(idx);
            // ...set both of the ones to be zero...
            partition.at(one_count.at(0)) = 0;
            partition.at(one_count.at(1)) = 0;
            // ...set the first element to be the remaining value.
            partition.at(0) = one_count.at(0);
            /* Note: This is equivalent to
             *  partition.at(0) = (one_count.at(0) + 1)*1 + (one_count.at(1) + 1)*1 - (one_cout.at(1) + 2)*1
             * The above statement should make more clear what is happening here.
             */
        }
        // If the index has not exceeded the allowable max index,
        //  and if the size of the element at the index is greater than 2...
        else if (idx < N && partition.at(idx) >= 2)
        {
            // ...increment the next element...
            ++partition.at(idx + 1);
            // ...in (possible) anticipation for the coming loop,
            //  remove the some value from the first element...
            /* Note: (0 - 1) is well-defined. */
            partition.at(0) -= (idx + 2);
            // ...and add all remaining value between the first element
            //  and the indexed element to the first element.
            for (std::size_t i = 1; i <= idx; ++i)
            {
                partition.at(0) += partition.at(i)*(i + 1);
                partition.at(i) = 0;
            }
            /* Note: The above loop is expected to (maybe) run faster
             *  once a hashmap becomes the partition container->
             */
        }
        // Otherwise, make this iterator the end iterator.
        else
            partition.clear();

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Advances the iterator by one step.
    /// \return the iterator pre-increment.
    ///////////////////////////////////////////////////////////////////////////
    IntegerPartitions::Iterator IntegerPartitions::Iterator::operator++(int)
    {
        Iterator tmp(*this);
        operator++();
        return tmp;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Dereferences the iterator.
    /// \return the integer partition that this iterator contains.
    ///////////////////////////////////////////////////////////////////////////
    const PMult IntegerPartitions::Iterator::operator*() const
    {
        return partition;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief The (private) constructor.
    /// \param container is the parent object that this iterator belongs to.
    ///////////////////////////////////////////////////////////////////////////
    IntegerPartitions::Iterator::Iterator(const IntegerPartitions * const container)
        : container(container)
    {
        partition.resize(container->getInteger(),0);
        partition.at(0) = container->getInteger();
    }
}
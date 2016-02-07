#ifndef INTEGER_PARTITIONS_COMBINATORICS_INTEGER_PARTITIONS_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_INTEGER_PARTITIONS_HPP

#include "PartitionTypes.hpp"

////////////////////////////////////////////////////////////////////////
/// \brief The IntegerPartitionsCombinatorics namespace.
////////////////////////////////////////////////////////////////////////
namespace IPC
{
    ////////////////////////////////////////////////////////////////////////
    /// \brief Stores an integer and, abstractly, its partitions.
    ///
    /// The partitions of this class's integer are obtainable only via
    /// a forward iterator.
    /// To obtain the forward iterator, use the begin method.
    /// From there, use the operator++ method to advance to the "next"
    /// partition.
    /// Each partition is a vector of multiplicities.
    ////////////////////////////////////////////////////////////////////////
    class IntegerPartitions
    {
    public:
        IntegerPartitions(const std::size_t& integer);

        std::size_t getInteger() const;

        class Iterator;

        Iterator begin() const;
        Iterator end() const;

    private:
        ////////////////////////////////////////////////////////////////////////
        /// \brief The integer from which the partitions are obtained.
        ////////////////////////////////////////////////////////////////////////
        std::size_t integer;
    };

    ////////////////////////////////////////////////////////////////////////
    /// \brief The forward iterator for the IntegerPartition class.
    ///
    /// Note that the user cannot directly construct this iterator;
    /// it can only be made via the IntegerPartition class's begin and end methods.
    ////////////////////////////////////////////////////////////////////////
    /// \todo Figure out how to make this iterator bidirectional.
    ////////////////////////////////////////////////////////////////////////
    class IntegerPartitions::Iterator
    {
        friend class IntegerPartitions;
        friend bool operator==(const Iterator& it1, const Iterator& it2);
    public:
        Iterator& operator++();
        Iterator operator++(int);
        const PMult operator*() const;

    private:
        Iterator(const IntegerPartitions * const container);

        ////////////////////////////////////////////////////////////////////////
        /// \brief The current partition this iterator contains.
        ///////////////////////////////////////////////////////////////////////////
        PMult partition;
        ////////////////////////////////////////////////////////////////////////
        /// \brief The parent object of this iterator.
        ////////////////////////////////////////////////////////////////////////
        const IntegerPartitions* container;
    };

    ////////////////////////////////////////////////////////////////////////
    /// \brief Determine if two iterators are equal.
    /// \param it1 is the LHS iterator to be compared.
    /// \param it2 is the RHS iterator to be compared.
    /// \return true if the iterators are equal, false otherwise.
    ///
    /// Iterators are equal if they contain the same integer partition,
    /// and if they belong to the same parent.
    ////////////////////////////////////////////////////////////////////////
    inline bool operator==(
            const IntegerPartitions::Iterator& it1,
            const IntegerPartitions::Iterator& it2)
    {
        return (it1.partition   == it2.partition &&
                it1.container   == it2.container);
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Determine if two iterators are not equal.
    /// \param it1 is the LHS iterator to be compared.
    /// \param it2 is the RHS iterator to be compared.
    /// \return true if the iterators are equal, false otherwise.
    ///
    /// Iterators are not equal if they contain different integer partitions,
    /// or if they belong to different parents.
    ////////////////////////////////////////////////////////////////////////
    inline bool operator!=(
            const IntegerPartitions::Iterator& it1,
            const IntegerPartitions::Iterator& it2)
    {
        return !(it1 == it2);
    }
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_INTEGER_PARTITIONS_HPP

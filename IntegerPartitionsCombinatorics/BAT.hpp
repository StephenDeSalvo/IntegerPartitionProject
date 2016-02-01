#ifndef INTEGER_PARTITIONS_COMBINATORICS_BASIC_ARITHMETIC_TRANSFORMATIONS_HPP
#define INTEGER_PARTITIONS_COMBINATORICS_BASIC_ARITHMETIC_TRANSFORMATIONS_HPP

namespace IPC
{
    // The basic arithmetic transform namespace.
    // Assume all parameters are integer partitions, not just sets.
    /// @todo Look into better ways of doing these transformation; there are many easy improvements.
    namespace BAT
    {
        template <typename Z>
        std::vector<Point<Z>> sum(const std::vector<Point<Z>>& lhs,
                                  const std::vector<Point<Z>>& rhs)
        {
            std::vector<Point<Z>> output;

            std::map<Z, std::vector<Point<Z>>> lhsColumns;
            for (auto elnt : lhs)
                lhsColumns[elnt.x].push_back(elnt);

            std::map<Z, std::vector<Point<Z>>> rhsColumns;
            for (auto elnt : rhs)
                rhsColumns[elnt.x].push_back(elnt);

            // AHHH
            std::vector<std::vector<Point<Z>>> allColumns;
            for (auto elnt : lhsColumns)
                allColumns.push_back(elnt.second);
            for (auto elnt : rhsColumns)
                allColumns.push_back(elnt.second);

            std::sort(allColumns.begin(), allColumns.end(),
                      [](const std::vector<Point<Z>>& one, const std::vector<Point<Z>>& two)
                        {
                            return one.size() > two.size();
                        });

            for (std::size_t i = 0, n = allColumns.size(); i < n; ++i)
            {
                for (auto ielnt : allColumns[i])
                {
                    ielnt.x = (i + 1);
                    output.push_back(ielnt);
                }
            }

            return output;
        }

        // Currently named union2 due to union being a reserved word.
        template <typename Z>
        std::vector<Point<Z>> union2(const std::vector<Point<Z>>& lhs,
                                  const std::vector<Point<Z>>& rhs)
        {
            std::vector<Point<Z>> output;

            std::map<Z, std::vector<Point<Z>>> lhsRows;
            for (auto elnt : lhs)
                lhsRows[elnt.y].push_back(elnt);

            std::map<Z, std::vector<Point<Z>>> rhsRows;
            for (auto elnt : rhs)
                rhsRows[elnt.y].push_back(elnt);

            // AHHH
            std::vector<std::vector<Point<Z>>> allRows;
            for (auto elnt : lhsRows)
                allRows.push_back(elnt.second);
            for (auto elnt : rhsRows)
                allRows.push_back(elnt.second);

            std::sort(allRows.begin(), allRows.end(),
                      [](const std::vector<Point<Z>>& one, const std::vector<Point<Z>>& two)
                        {
                            return one.size() > two.size();
                        });

            for (std::size_t i = 0, n = allRows.size(); i < n; ++i)
            {
                for (auto ielnt : allRows[i])
                {
                    ielnt.y = (i + 1);
                    output.push_back(ielnt);
                }
            }

            return output;
        }
    }
}

#endif // INTEGER_PARTITIONS_COMBINATORICS_BASIC_ARITHMETIC_TRANSFORMATIONS_HPP

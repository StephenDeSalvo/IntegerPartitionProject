////////////////////////////////////////////////////////////////////////
/// \file ForwardGraph.hpp
/// \brief Defines and implements the ForwardGraph class
////////////////////////////////////////////////////////////////////////

#ifndef IPC_FORWARDGRAPH_HPP
#define IPC_FORWARDGRAPH_HPP

#include <unordered_map>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>

namespace IPC
{

    ////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of a forward graph
	/// \tparam K is the key value to look-up each vertex's data
	/// \tparam H is the hash value generated for K
	/// \tparam V is the type of data stored in each vertex
    ///
    /// This is a bare-bones graph implementation, named "forward" because
    /// vertices and edges can only be added, not removed.
    /// Moreover, the graph is non-traversable in the classic sense:
    /// One can only iterate over its edges and vertices.
    /// This class does ensure that no vertices with the same key value
    /// exist, and it also ensures that there are no duplicate edges.
    ////////////////////////////////////////////////////////////////////////
    template <typename K, typename V>
    class ForwardGraph
    {
    public:
		void outputToFile(const std::string& directory)
        {
            std::string filename = directory + "/graph.txt";

            std::ofstream outfile;
            outfile.open(filename);
            if (outfile.fail())
                std::cerr << "FAILED TO OPEN FILE " << filename << std::endl;
            outfile << *this;
            outfile.close();
        }

        void addVertex(const K& v_key, const V& v_data)
        {
            assert(vertices.find(v_key) == vertices.end());
            vertices[v_key] = v_data;
        }
        void addEdge(const K& v_key1, const K& v_key2)
        {
            assert(vertices.find(v_key1) != vertices.end());
            assert(vertices.find(v_key2) != vertices.end());

            for (auto elnt : edges)
            {
                assert(elnt.first != v_key1 || elnt.second != v_key2);
                assert(elnt.first != v_key2 || elnt.second != v_key1);
            }

            edges.push_back(std::pair<K,K>(v_key1,v_key2));
        }
        const V getVertexData(const K& v_key) const
        {
            return vertices.at(v_key);
        }

        typename std::unordered_map<K,V,std::hash<K>>::const_iterator beginVertices() const
        {
            return vertices.begin();
        }

        typename std::unordered_map<K,V,std::hash<K>>::const_iterator endVertices() const
        {
            return vertices.end();
        }

        typename std::vector<std::pair<K,K>>::const_iterator beginEdges() const
        {
            return edges.begin();
        }

        typename std::vector<std::pair<K,K>>::const_iterator endEdges() const
        {
            return edges.end();
        }

    private:
        std::unordered_map<K,V,std::hash<K>> vertices;
        std::vector<std::pair<K,K>> edges;
    };
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const IPC::ForwardGraph<K,V>& fg)
{
    os << "VERTICES\n";
    for (auto i = fg.beginVertices(); i != fg.endVertices(); ++i)
        os << i->first << ' ' << i->second << '\n';

    os << "EDGES\n";
    for (auto i = fg.beginEdges(); i != fg.endEdges(); ++i)
        os << i->first << ' ' << fg.getVertexData(i->first) << ';'
           << i->second << ' ' << fg.getVertexData(i->second) << ';'
           << '\n';

    return os;
}

#endif // IPC_FORWARDGRAPH_HPP

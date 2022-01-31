#pragma once
#include <vector>
#include <iostream>

// Undirected, Cyclic, Unweighted Graph

namespace Graphs
{
    class Graph
    {
    public:
        Graph() = delete;
        Graph(int nodeCount)
        {
            m_AdjacencyList.resize(nodeCount);
        }

        void AddEdges(const int nodeOne, const int nodeTwo)
        {
            m_AdjacencyList[nodeOne].push_back(nodeTwo);
            m_AdjacencyList[nodeTwo].push_back(nodeOne);
        }

        void ShowConnections()
        {
            for (int i = 0; i < m_AdjacencyList.size(); i++)
            {
                std::cout << i << ": ";

                for (auto& connectedNode : m_AdjacencyList[i])
                {
                    std::cout << connectedNode << ", ";
                }

                std::cout << "\n";
            }
        }

    public:
        std::vector<std::vector<int>> m_AdjacencyList; // A node will hold a vector of nodes it is connected to.
    };
}
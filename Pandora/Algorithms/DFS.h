#pragma once
#include <vector>
#include <iostream>

namespace DFS
{
    void AddEdge(std::vector<std::vector<int>>& ajacencyList, int fromNode, int toNode)
    {
        ajacencyList[fromNode].push_back(toNode);
    }

    void DFS(int currentNode, std::vector<std::vector<int>>& ajacencyList, std::vector<bool>& visitedNodes)
    {
        // Mark the current node as visited and print it.
        visitedNodes[currentNode] = true;
        std::cout << currentNode << " ";

        // Recur for all vertices adjacent to this vertex.
        for (auto& neighbour : ajacencyList[currentNode])
        {
            if (!visitedNodes[neighbour])
            {
                DFS(neighbour, ajacencyList, visitedNodes);
            }
        }
    }

    void TestCase_DFS()
    {
        int nodeCount = 10;
        std::vector<std::vector<int>> ajacencyList(nodeCount);
        std::vector<bool> visitedNodes(nodeCount);

        AddEdge(ajacencyList, 0, 1);
        AddEdge(ajacencyList, 0, 9);
        AddEdge(ajacencyList, 1, 2);
        AddEdge(ajacencyList, 2, 0);
        AddEdge(ajacencyList, 2, 3);
        AddEdge(ajacencyList, 9, 3);

        DFS(0, ajacencyList, visitedNodes);
        std::cout << std::endl;
    }
}
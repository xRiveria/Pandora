#pragma once
#include <vector>
#include <queue>
#include <limits.h>
#include <iostream>

namespace BFS
{ 
    void InsertNodes(std::vector<std::vector<int>>& vector, int from, int to)
    {
        vector[from].push_back(to);
        // vector[to].push_back(from);
    }

    void TestCases_BFS()
    {
        constexpr int nodeCount = 4, edgeCount = 2;

        std::vector<std::vector<int>> ajacencyList(nodeCount);
        bool visitedNodes[nodeCount];

        for (int i = 0; i < nodeCount; i++)
        {
            visitedNodes[i] = false;
        }

        InsertNodes(ajacencyList, 0, 1);
        InsertNodes(ajacencyList, 0, 2);
        InsertNodes(ajacencyList, 1, 2);
        InsertNodes(ajacencyList, 2, 0);
        InsertNodes(ajacencyList, 2, 3);
        InsertNodes(ajacencyList, 3, 3);

        int startingNode = 2;
        // startingNode--;

        std::queue<int> queue;
        queue.push(startingNode);
        visitedNodes[startingNode] = true;
        
        while (!queue.empty())
        {
            int currentVertex = queue.front();
            std::cout << currentVertex << " ";
            queue.pop();

            for (auto& neighbour : ajacencyList[currentVertex])
            {
                if (!visitedNodes[neighbour])
                {
                    visitedNodes[neighbour] = true;
                    // finalDistances[neighbour] = finalDistances[currentVertex] + 1;
                    queue.push(neighbour);
                }
            }
        }

        std::cout << std::endl;
    }
}
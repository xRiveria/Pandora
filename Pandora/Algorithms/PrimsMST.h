#pragma once
#include <vector>
#include <utility>
#include <queue>
#include <iostream>

namespace MinimumSpanningTrees
{
    std::vector<std::vector<std::pair<int, int>>> g_AdjacencyList;

    // Note that pairs are in a { Weight, Node } order.  
    void PrimsMST(int totalNodes, int startingNode)
    {
        startingNode--;
        std::vector<bool> visitedNodes(totalNodes, false);
        std::vector<int> finalMSTNodes(totalNodes, -1); // Holds the vertex numbers with which they are connected. For example, finalMSTNodes[3] = 1, means 3 is connected to 1.
        std::vector<int> finalMSTWeights(totalNodes, INT_MAX);
        // Automatically sorted by weight. 
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> priorityQueue;

        priorityQueue.push(std::make_pair(0, startingNode));
        finalMSTWeights[startingNode] = 0; // Minimum weight for our starting node is naturally 0.

        while (!priorityQueue.empty())
        {
            int currentNode = priorityQueue.top().second;
            visitedNodes[currentNode] = true;
            priorityQueue.pop();

            for (auto neighbour : g_AdjacencyList[currentNode])
            {
                int neighbourVertex = neighbour.first;
                int neighbourWeight = neighbour.second;

                // If said neighbour has not been visited before and it happens to be of lesser weight than what we currently have, switch!
                if (!visitedNodes[neighbourVertex] && finalMSTWeights[neighbourVertex] > neighbourWeight)
                {
                    finalMSTWeights[neighbourVertex] = neighbourWeight;
                    finalMSTNodes[neighbourVertex] = currentNode;
                    priorityQueue.push(std::make_pair(finalMSTWeights[neighbourVertex], neighbourVertex));
                }
            }
        }

        int totalWeight = 0;
        for (int i = 0; i < finalMSTWeights.size(); i++)
        {
            totalWeight += finalMSTWeights[i];
        }

        std::cout << totalWeight << "\n";
    }

    void AddToGraph(int edgeFrom, int edgeTo, int edgeWeight)
    {
        // Decrement edgeFrom and edgeTo to make them 0-indexed.
        edgeFrom--, edgeTo--;
        g_AdjacencyList[edgeFrom].push_back({ edgeTo, edgeWeight });
        g_AdjacencyList[edgeTo].push_back({ edgeFrom, edgeWeight });
    }

    void TestCasesMST()
    {   
        std::cout << "==== Prims Algorithm ====" << "\n";

        int totalNodes = 5;
        g_AdjacencyList.resize(totalNodes);

        AddToGraph(1, 2, 3);
        AddToGraph(1, 3, 4);
        AddToGraph(4, 2, 6);
        AddToGraph(5, 2, 2);
        AddToGraph(2, 3, 5);
        AddToGraph(3, 5, 7);

        PrimsMST(totalNodes, 1);

        std::cout << "=========================" << "\n";
    }
}
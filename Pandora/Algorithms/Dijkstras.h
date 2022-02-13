#pragma once
#include <iostream>
#include <limits.h>
#include <utility>
#include <vector>
#include <queue>

namespace DijkstrasAlgorithmMatrix
{
#define VertexCount 9

    // A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in the shortest path tree.
    int GetMinimumDistance(int distances[], bool includedVertices[])
    {
        int minimumDistance = INT_MAX;
        int minimumIndex;

        for (int i = 0; i < VertexCount; i++)
        {
            if (includedVertices[i] == false && distances[i] <= minimumDistance)
            {
                minimumDistance = distances[i];
                minimumIndex = i;
            }
        }

        return minimumIndex;
    }

    void Dijkstras(int graph[VertexCount][VertexCount], int sourceVertex)
    {
        int distances[VertexCount];         // Output array that holds the shortest distance from Source to i. 
        bool includedVertexes[VertexCount]; // includedVertices[i] will be true if vertex i is included in the shortest path tree, or if the shortest distance from source to i is finalized.

        // Initalize all distances as infinite and includedVertexes as false.
        for (int i = 0; i < VertexCount; i++)
        {
            distances[i] = INT_MAX;
            includedVertexes[i] = false;
        }

        // Distance of source vertex from itself is always 0.
        distances[sourceVertex] = 0;

        // Find the shortest path for all vertices.
        for (int i = 0; i < VertexCount - 1; i++)
        {
            // Pick the minimum distance vertex from the set of vertices not yet processed. In the first iteration, mostMinimumVertex is alwauys equal to sourceVertex.
            int mostMinimumVertex = GetMinimumDistance(distances, includedVertexes);

            // Mark the picked vertex as processed.
            includedVertexes[mostMinimumVertex] = true;

            // Update distance value of the adjacent vertices of the picked vertex.
            for (int v = 0; v < VertexCount; v++)
            {
                // Update distances[V] only if it is not in includedVertexes, there is an edge from mostMinimumVertex to V, and total weight of the path from
                // the sourceVertex to V through mostMinimumVertex is smaller than the current value of distances[V].
                if (!includedVertexes[v] && graph[mostMinimumVertex][v] && distances[mostMinimumVertex] != INT_MAX &&
                    distances[mostMinimumVertex] + graph[mostMinimumVertex][v] < distances[v])
                {
                    distances[v] = distances[mostMinimumVertex] + graph[mostMinimumVertex][v];
                }
            }
        }

        std::cout << "Vertex \t Distance from Source" << std::endl;
        for (int i = 0; i < VertexCount; i++)
        {
            std::cout << i << " \t\t" << distances[i] << std::endl;
        }
    }

    void TestCases_Dijkstra()
    {
        int graph[VertexCount][VertexCount] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0   },
                                                { 4, 0, 8, 0, 0, 0, 0, 11, 0  },
                                                { 0, 8, 0, 7, 0, 4, 0, 0, 2   },
                                                { 0, 0, 7, 0, 9, 14, 0, 0, 0  },
                                                { 0, 0, 0, 9, 0, 10, 0, 0, 0  },
                                                { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                                                { 0, 0, 0, 0, 0, 2, 0, 1, 6   },
                                                { 8, 11, 0, 0, 0, 0, 1, 0, 7  },
                                                { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

        Dijkstras(graph, 0);
    }
}

namespace DijkstrasAlgorithmAdjacencyList
{
    void InsertIntoList(std::vector<std::vector<std::pair<int, int>>>& adjecencyList, int from, int to, int weight)
    {
        from--, to--;
        adjecencyList[from].push_back({ to, weight });
        adjecencyList[to].push_back({ from, weight });
    }

    void TestsCases_DijkstrasAdjacencyList()
    {
        constexpr int nodeCount = 4, edgeCount = 4;

        std::vector<std::vector<std::pair<int, int>>> adjacencyList(nodeCount); // Node, Weight
        int finalDistances[nodeCount];  // Stores the distances between nodes.
        bool hasVisited[nodeCount];     // Flag to avoid revisiting nodes.

        for (int i = 0; i < nodeCount; i++)
        {
            finalDistances[i] = INT_MAX;
            hasVisited[i] = false;
        }

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> priorityQueue; // Min-Heap: Items arranged in ascending order.

        InsertIntoList(adjacencyList, 1, 2, 24);
        InsertIntoList(adjacencyList, 1, 4, 20);
        InsertIntoList(adjacencyList, 3, 1, 3);
        InsertIntoList(adjacencyList, 4, 3, 12);

        int startingVertex = 1;
        startingVertex--;

        priorityQueue.push({ 0, startingVertex }); // Always push with distance first to maintain our priority queue.
        finalDistances[startingVertex] = 0; // Distance to starting vertex is always 0.

        // Stores all paths and arranges them in ascending order with the lowest cost first. 
        // Only insert our best estimates possible.
        while (!priorityQueue.empty())
        {
            int currentVertex = priorityQueue.top().second;
            priorityQueue.pop();

            if (hasVisited[currentVertex])
            {
                continue;
            }

            hasVisited[currentVertex] = true;

            // For each edge connected to our current vertex...
            for (auto& pair : adjacencyList[currentVertex])
            {
                int neighbourVertex = pair.first;
                int weight = pair.second;

                // If the current shortest path for this neighbour is longer than the path taken from our current node...
                if (finalDistances[neighbourVertex] > finalDistances[currentVertex] + weight)
                {
                    finalDistances[neighbourVertex] = finalDistances[currentVertex] + weight;
                    priorityQueue.push({ finalDistances[neighbourVertex], neighbourVertex });
                }
            }
        }

        for (int i = 0; i < nodeCount; i++)
        {
            if (i == startingVertex) continue; // Ignore first node.
            if (finalDistances[i] != INT_MAX)
            {
                std::cout << finalDistances[i] << " ";
            }
            else
            {
                std::cout << -1 << " ";
            }
        }

        std::cout << std::endl;
    }
}

namespace AnotherDijkstra
{
    class WeightedGraph
    {
    public:
        WeightedGraph()
        {
            m_AjacencyList.resize(5);
        }

        void AddEdges(int from, int to, int weight)
        {
            from--, to--; 
            m_AjacencyList[from].push_back({ to, weight });
            m_AjacencyList[to].push_back({ from, weight });
        }

        void Dijkstra()
        {

        }

    private:
        std::vector<std::vector<std::pair<int, int>>> m_AjacencyList; // Node 1: Node 2, 50
    };

    void TestCases()
    {
        // Cities will start from 1 to make things easier to comprehend textually.
        WeightedGraph weightedGraph;
        weightedGraph.AddEdges(1, 2, 5);
        weightedGraph.AddEdges(1, 3, 10);
        weightedGraph.AddEdges(2, 1, 50);
    }
}
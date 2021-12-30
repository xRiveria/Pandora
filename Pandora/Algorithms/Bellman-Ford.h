#pragma once
#include <vector>
#include <iostream>

namespace BellmanFord
{
    // A directed edge containing the start and end vertex as well as its weight.
    struct Edge
    {
        int m_StartVertex;
        int m_EndVertex;
        int m_Weight;
    };

    // A graph containing N nodes and E edges.
    struct Graph
    {
        int m_VertexCount;
        int m_EdgeCount;
        std::vector<Edge> m_Edges;
    };

    // Creates a graph with V vertices and E edges.
    Graph* CreateGraph(int vertexCount, int edgeCount)
    {
        Graph* graph = new Graph();
        graph->m_VertexCount = vertexCount;
        graph->m_EdgeCount = edgeCount;

        // Array of edges for graph.
        graph->m_Edges.resize(edgeCount);
        return graph;
    }

    void BellmanFord(Graph* graph, int startingVertex)
    {
        int vertexCount = graph->m_VertexCount;
        int edgeCount = graph->m_EdgeCount;

        // Step 1) Fill the distance array and predessor array. Distances to infinity.
        std::vector<int> finalDistances(vertexCount, INT_MAX);

        // Mark the source vertex.
        finalDistances[startingVertex] = 0;

        // Step 2: Relax Edges |V| - 1 Times
        for (int i = 0; i < vertexCount - 1; i++)
        {
            for (int j = 0; j < edgeCount; j++)
            {
                // Get edge data.
                int edgeStartVertex = graph->m_Edges[j].m_StartVertex;
                int edgeEndVertex = graph->m_Edges[j].m_EndVertex;
                int edgeWeight = graph->m_Edges[j].m_Weight;

                if (finalDistances[edgeStartVertex] != INT_MAX && finalDistances[edgeStartVertex] + edgeWeight < finalDistances[edgeEndVertex])
                {
                    finalDistances[edgeEndVertex] = finalDistances[edgeStartVertex] + edgeWeight;
                }
            }
        }

        // Step 3: Detect negative cycles. Step 2 ensures the shortest distances if the graph does not contain a negative weight cycle.
        // If we iterate through all the edges one more time and get a shorter path for any vertex, then there is a negative weight cycle.
        for (int i = 0; i < edgeCount; i++)
        {
            int edgeStartVertex = graph->m_Edges[i].m_StartVertex;
            int edgeEndVertex = graph->m_Edges[i].m_EndVertex;
            int edgeWeight = graph->m_Edges[i].m_Weight;

            if (finalDistances[edgeStartVertex] != INT_MAX && finalDistances[edgeStartVertex] + edgeWeight < finalDistances[edgeEndVertex])
            {
                std::cout << "Graph contains a negative weight cycle.\n";
                return;
            }
        }

        // No negative weight cycles found. Print solution.
        for (int i = 0; i < finalDistances.size(); i++)
        {
            std::cout << finalDistances[i] << "\n";
        }
    }

    void TestCases_BellmanFord()
    {
        int vertexCount = 4;
        int edgeCount = 8;

        Graph* graph = CreateGraph(vertexCount, edgeCount);
        graph->m_Edges[0].m_StartVertex = 0;
        graph->m_Edges[0].m_EndVertex = 1;
        graph->m_Edges[0].m_Weight = 5;

        //edge 0 --> 2
        graph->m_Edges[1].m_StartVertex = 0;
        graph->m_Edges[1].m_EndVertex = 2;
        graph->m_Edges[1].m_Weight = 4;

        //edge 1 --> 3
        graph->m_Edges[2].m_StartVertex = 1;
        graph->m_Edges[2].m_EndVertex = 3;
        graph->m_Edges[2].m_Weight = 3;

        //edge 2 --> 1
        graph->m_Edges[3].m_StartVertex = 2;
        graph->m_Edges[3].m_EndVertex = 1;
        graph->m_Edges[3].m_Weight = 6;

        //edge 3 --> 2
        graph->m_Edges[4].m_StartVertex = 3;
        graph->m_Edges[4].m_EndVertex = 2;
        graph->m_Edges[4].m_Weight = 2;

        BellmanFord(graph, 0); // Source vertex of 0.
    }
}
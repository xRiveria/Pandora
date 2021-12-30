#pragma once
#pragma once
#include <vector>
#include <utility>
#include <queue>
#include <iostream>
#include <unordered_map>

namespace MinimumSpanningTrees
{
    struct Edge
    {
        Edge() = default;
        Edge(int nodeFrom, int nodeTo, int edgeWeight) : m_NodeFrom(nodeFrom), m_NodeTo(nodeTo), m_NodeWeight(edgeWeight)
        {

        }

        int m_NodeTo;
        int m_NodeFrom;
        int m_NodeWeight;
    };

    std::vector<Edge> g_Edges;

    struct Comparison
    {
        bool operator()(const Edge& weightA, const Edge& weightB) const
        {
            return weightA.m_NodeWeight > weightB.m_NodeWeight;
        }
    };

    class DisjointSet
    {
    public:
        void MakeSet(int totalNodeCount)
        {
            // Create "N" disjoint sets, one for each vertex.
            for (int i = 0; i < totalNodeCount; i++)
            {
                m_Parent[i] = i;
            }
        }

        // Find the root of the set in which element "K" belongs.
        int Find(int k)
        {
            // If "K" is the root...
            if (m_Parent[k] == k)
            {
                return k;
            }

            // Recur for the parent until we find the root.
            return Find(m_Parent[k]);
        }

        // Perform union of the two subsets.
        void Union(int a, int b)
        {
            // Find the root of the sets in which elements "X" and "Y" belongs.
            int x = Find(a);
            int y = Find(b);

            // Combine parents.
            m_Parent[x] = y;
        }

    private:
        std::unordered_map<int, int> m_Parent;
    };

    void KruskalsMST(int totalNodes)
    {
        // Store the edges present in our MST.
        std::vector<Edge> finalMST;

        // Initialize Disjoint Sets
        DisjointSet disjointSet;
        disjointSet.MakeSet(totalNodes); // Create a set for each element of our graph.

        // Sort edges by decreasing weight, such as the least weight edge is at the back.
        std::sort(g_Edges.begin(), g_Edges.end(), Comparison());

        // MST contains exactly totalNodes - 1 edges.
        while (finalMST.size() != totalNodes - 1)
        {
            // Consider the next edge with the most minimimum weight from the graph.
            Edge nextEdge = g_Edges.back();
            g_Edges.pop_back();

            // Find the root of the sets in which the two endpoints of this edge connects to.
            int x = disjointSet.Find(nextEdge.m_NodeFrom);
            int y = disjointSet.Find(nextEdge.m_NodeTo);

            // If both have different parents, they belong to different connected components and can be included in the MST.
            if (x != y)
            {
                finalMST.push_back(nextEdge);
                disjointSet.Union(x, y); // Connect them together to have the same parent. 
            }
        }

        int totalWeight = 0;
        for (int i = 0; i < finalMST.size(); i++)
        {
            totalWeight += finalMST[i].m_NodeWeight;
        }

        std::cout << totalWeight << "\n";
    }

    void AddToGraph_Kruskals(int edgeFrom, int edgeTo, int edgeWeight)
    {
        // Decrement edgeFrom and edgeTo to make them 0-indexed.
        edgeFrom--, edgeTo--;
        g_Edges.push_back({ edgeFrom, edgeTo, edgeWeight });
    }

    void TestCasesKruskalsMST()
    {
        std::cout << "==== Kruskals Algorithm ====" << "\n";

        AddToGraph_Kruskals(1, 2, 3);
        AddToGraph_Kruskals(1, 3, 4);
        AddToGraph_Kruskals(4, 2, 6);
        AddToGraph_Kruskals(5, 2, 2);
        AddToGraph_Kruskals(2, 3, 5);
        AddToGraph_Kruskals(3, 5, 7);

        KruskalsMST(5);

        std::cout << "=========================" << "\n";
    }
}
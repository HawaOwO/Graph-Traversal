//
// Created by Deyan on 15/7/2022.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class Graph
{
private:
    double** adjMatrix;
    int numVertices;
    int visitedNum;

public:
    Graph(int);
    ~Graph();
    void addEdge(int, int, double);
    list<int> *adj; // Pointer to an array containing adjacency lists
    void removeEdge(int, int);
    bool isReachable(int, int);
    void toString();
    bool isAvailable(int, int);
    void generateRandomEdge(int[][5]);

    bool DFS();
    bool cycleDetectionDFS(int, int[]);
    void printCycle(int[]);

    bool isSC();
    void getTranspose(Graph&);
    void DFSUtil(int, bool[]);

    void dijkstraDist(int[][5], int, int);
    void printShortPath(int[], double[], int, int);

    int kruskalMST(int[][5]);

    void reset(int);
};

#endif
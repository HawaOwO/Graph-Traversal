//
// Created by Deyan on 15/7/2022.
//

#include "Graph.h"
#include <list>
#include <iomanip>

Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new double* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new double[numVertices];
        for (int j = 0; j < numVertices; j++)
            adjMatrix[i][j] = 0;

    }
    visitedNum = 0;
    adj = new list<int> [numVertices];
}


void Graph::reset(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new double* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new double[numVertices];
        for (int j = 0; j < numVertices; j++)
            adjMatrix[i][j] = 0;
    }
    visitedNum = 0;
}


void Graph::addEdge(int i, int j, double weight) {
    adjMatrix[i][j] = weight;
    adj[i].push_back(j); // Add w to vâ€™s list.
}


bool Graph::isReachable(int o, int d)
{
    int vertices = 5;
    // Base case
    if (o == d)
        return true;

    // Mark all the vertices as not visited
    bool *visited = new bool[vertices];
    for (int i = 0; i < vertices; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[o] = true;
    queue.push_back(o);

    // it will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        o = queue.front();
        queue.pop_front();

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for (i = adj[o].begin(); i != adj[o].end(); ++i)
        {
            // If this adjacent node is the destination node, then return true
            if (*i == d)
                return true;

            // Else, continue to do BFS
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }

    return false;
}


void Graph::removeEdge(int i, int j) {
    adjMatrix[i][j] = 0;
}


void Graph::toString() {
    // To print the resulting graph
    cout << setw(11) << "0" << setw(11) << "1" << setw(11) << "2" << setw(11) << "3" << setw(11) << "4" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << i << " :" << setw(8);
        for (int j = 0; j < numVertices; j++)
            cout << adjMatrix[i][j] << setw(11);
        cout << "\n";
    }
}


bool Graph::DFS() {

    int *visited = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;

    }
    // To perform DFS from different nodes
    for (int i = 0; i < numVertices; i++) {
        if (cycleDetectionDFS(i, visited)) {
            cout << "\nA cycle has been detected" << endl;
            cout << "\nThe cycle that has been found" << endl;
            printCycle(visited);
            return true;
        }
    }
    return false;
}


bool Graph::cycleDetectionDFS(int v, int visited[])
{
    if (visited[v] == 0)
    {
        visited[v] = visitedNum++;

        for (int i = 0; i < numVertices; i++)
        {
            if (adjMatrix[v][i] > 0) {
                if (!(visited[i] > 0) && cycleDetectionDFS(i, visited)) {
                    return true;
                }
                    // Part where we detect the cycle and mark the node as visited
                else if (visited[i]>0 && i != v) {
                    visited[i] = -1;
                    return true;
                }
            }
        }
    }
    // If no adjacent vertex at all or there is no adjacent vertex that have been already visited
    visited[v] = 0;
    return false;
}


bool Graph::isAvailable(int v1, int v2) {
    // Check if an edge available
    if (adjMatrix[v1][v2] > 0) {
        return true;
    }
    else {
        return false;
    }
}


Graph::~Graph() {
    for (int i = 0; i < numVertices; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
}


void Graph::printCycle(int recursionStack[]) {
    cout << "\n";
    int visitedIndex = 0;
    int lastCycleIndex = 0;

    // To get the last vertex in the cycle
    for (int i = 0; i < numVertices; i++) {
        if (recursionStack[i] > 0 || recursionStack[i] == -1) {
            lastCycleIndex = i;
        }
    }
    // To get the first vertex in the cycle
    for (int i = 0; i < numVertices; i++) {
        if (recursionStack[i] != -1) {

            continue;
        }
        else {
            // Check if we can make the first vertex in the graph as the first vertex in the cycle,
            // if the second vertex in the graph is the first vertex in the cycle
            if (i - 1 == 0 && recursionStack[i-1] > 0 && adjMatrix[lastCycleIndex][i-1] > 0) {
                visitedIndex = i -1;
            }
            else {
                visitedIndex = i;
            }
        }
    }
    // Printing the cycle
    for (int i = visitedIndex; i < numVertices; i++) {
        if (recursionStack[i] > 0 || recursionStack[i] == -1) {
            cout << i << "--> ";
        }

    }
    cout << visitedIndex << endl;
}


void Graph::generateRandomEdge(int w[][5]) {
    int v1;
    int v2;

    srand(time(0));
    v1 = rand() % numVertices;
    v2 = rand() % numVertices;

    while (v1 == v2 || isAvailable(v1, v2)) {
        v1 = rand() % numVertices;
        v2 = rand() % numVertices;
    }

    addEdge(v1, v2, w[v1][v2]);
}


void Graph::getTranspose(Graph& g)
{
    for (int v = 0; v < numVertices; v++)
    {
        for (int i = 0; i < numVertices; ++i)
        {
            if (g.adjMatrix[v][i] > 0) {
                addEdge(i, v, g.adjMatrix[v][i]);    // Add edge of the inverse graph
            }
        }
    }
}


bool Graph::isSC()
{
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false; // Declare visited

    DFSUtil(0, visited); // Call DFSUtil function

    for (int i = 0; i < numVertices; i++)
        if (visited[i] == false)
            return false;   // Return false if any of the vertices is not visited

    return true; // Return true if all vertices is visited
}


void Graph::DFSUtil(int v, bool visited[]) {

    visited[v] = true;  // Set the first vertex of the graph as visited

    for (int i = 0; i < numVertices; ++i)
    {
        if (adjMatrix[v][i] > 0) {
            if (!visited[i]) {   // If any of the vertices is not visited, call thefunction again
                DFSUtil(i, visited);
            }
        }
    }
}


void Graph::dijkstraDist(int w[][5], int s, int d)
{
    int path[5], infi = 100000000, origin = s, next_location[5], c = 0, destination = d;
    double edge[5], dist[5];
    bool visited[5], reached = false;

    for (int i = 0; i < 5; i++)
    {
        visited[i] = false; // To check whether a vertex is visited or not yet
        path[i] = -1; // To hold path of each vertex
        dist[i] = infi; // To hold distance of each vertex
        edge[i] = -1; // To hold weight of edges
        next_location[i] = -1; // Used to hold vertex that are adjacent to the current vertex
    }

    path[origin] = -1;// Origin's path and distance value
    dist[origin] = 0;

    int current = origin; // Current will become origin as path starts there

    while (reached == false) // While loop will keep looping until destincation is reached where reached becomes true.
    {
        int count = 0;
        visited[current] = true; // Current will become visited so that it will not be selected again


        while (count == 0) // Loop to find edges for a particular vertex
        {
            for (int i = 0; i < 5; i++)
            {
                if (adjMatrix[current][i] > 0 && visited[i] != true)
                {
                    edge[count] = adjMatrix[current][i];
                    next_location[count] = i;
                    count = count + 1;

                    double alt = dist[current] + adjMatrix[current][i]; // Relaxation procedure
                    if (alt < dist[i])
                    {
                        dist[i] = alt;
                        path[i] = current;
                    }
                }
            }


            if (count == 0) // If vertex have no edges create random edges
            {
                generateRandomEdge(w);
            }
            break;

        }

        double minDist = infi; // Minimum distance from current
        int index = 0; // Value to hold adjacent vertex

        for (int a = 0; a < count; a++) // Loop to find shortest edge in order to determine next vertex.
        {
            if (edge[a] < minDist && edge[a] != -1)
            {
                minDist = edge[a];
                index = next_location[a];
            }

        }

        for (int i = 0; i < 5; i++) // Loop to reset values of some array that will be used again for next loopug
        {
            edge[i] = -1;
            next_location[i] = -1;
        }

        current = index; // Current will now be index which is the next chosen vetex

        if (current == destination) // Checks whether destonation is reached
        {
            reached = true;
        }

    }
    printShortPath(path, dist, origin, destination); // Call function to print shortest path
}


void Graph::printShortPath(int path[], double dist[], int origin, int destination)
{
    int finding = destination;

    int shortest_path[5], x = 0;
    while (finding != -1) // Backtrack and find path staring from destination
    {
        shortest_path[x] = finding;
        finding = path[finding];
        x = x + 1;
    }

    if (dist[destination] > 1000 && dist[destination] < 100000000)
    {
        cout << "\nThe Shortest Path\n";
        for (int y = x - 1; y >= 0; y--) // Print shortest_path array in reverse order staring from orign to destonation
        {
            cout << shortest_path[y];

            if (y != 0)
            {
                cout << " -> ";
            }
        }
        cout << "\nTotal Distance From Origin: " << dist[destination] << endl;// Print total distance form destination
    }
    else
    {
        cout << "\nThere is no path between the destination\n";
    }
}


int Graph::kruskalMST(int w[][5])
{
    // Transferring Adjacency Matrix data into Vectors
    typedef pair<int, int> iPair;
    vector< pair<int, iPair> > edges;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (adjMatrix[i][j] != 0)
                edges.push_back({adjMatrix[i][j], {i, j}});
        }
    }

    // Disjoint Sets Data Structure
    struct DisjointSets
    {
        int *parent, *rank;
        int n;

        // Constructor for the Disjoint Set
        DisjointSets(int n)
        {
            this->n = n;
            parent = new int[n+1];
            rank = new int[n+1];

            // Initially, all vertices have rank 0 and are a parent of itself
            for (int i = 0; i <= n; i++)
            {
                rank[i] = 0;
                parent[i] = i;
            }
        }

        // Find the parent of a vertex
        int find(int x)
        {
            if (parent[x] == x)
                return x;
            return find(parent[x]);
        }

        // Union by rank
        void unite(int x, int y)
        {
            int fx = find(x);
            int fy = find(y);

            if (rank[fy] > rank[fx])
                parent[fx] = fy;
            else
                parent[fy] = fx;

            if (rank[fx] == rank[fy])
                rank[fy]++;
        }
    };

    // Start of the Kruskal MST Algorithm Implementation

    int mst_weight = 0; // Initialize result

    DisjointSets ds(numVertices); // Create disjoint sets

    sort(edges.begin(), edges.end()); // Sort the weight of edges in increasing order

    int counter = 0; // set a counter to check the number of edges in the MST
    vector< pair<int, iPair> >::iterator it;

    cout << endl << "Edges of MST are" << endl;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // Check if the current edges create a cycle or not
        if (set_u != set_v)
        {
            cout << u << " - " << v << endl; // Print the current edge
            mst_weight += it->first;
            ds.unite(set_u, set_v);
            counter++;
        }
    }

    if (counter != (numVertices - 1)) // will generate a random edge if the MST algorithm fails to generate appropriate number of edge
    {
        system("CLS");
        for (int i = 0; i < counter; i++)
            generateRandomEdge(w);

        cout << "Random edges have been generated." << endl
             << "MST Algorithm will run again."        << endl;

        system("PAUSE");

        mst_weight = kruskalMST(w);
    }
    return mst_weight;
}
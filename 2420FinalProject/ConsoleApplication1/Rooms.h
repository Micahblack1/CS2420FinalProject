#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <algorithm>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;


class Graph {
public:

    
    vector<string> nodeNames;
    vector<vector<int>> adjacencyMatrix;
    vector<int> winningPath;

    Graph(int numNodes) {
        nodeNames.resize(numNodes, "");
        adjacencyMatrix.resize(numNodes, vector<int>(numNodes, 0)); // Initialize matrix with 0s
    }

    void addNode(int id, string name) {
        if (id >= 0 && id < nodeNames.size()) {
            nodeNames[id] = name;
        }
        else {
            cout << "Invalid node ID." << endl;
        }
    }

    void addEdge(int source, int destination) {
        if (source >= 0 && source < adjacencyMatrix.size() &&
            destination >= 0 && destination < adjacencyMatrix.size()) {
            adjacencyMatrix[source][destination] = 1;
            adjacencyMatrix[destination][source] = 1; // Undirected graph
        }
        else {
            cout << "Invalid edge." << endl;
        }
    }

    void printGraph() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < adjacencyMatrix.size(); i++) {
            cout << nodeNames[i] << " (" << i << "): ";
            for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<int> getConnectedRooms(int node) {
        vector<int> connectedRooms;

        if (node >= 0 && node < adjacencyMatrix.size()) {
            for (int i = 0; i < adjacencyMatrix[node].size(); i++) {
                if (adjacencyMatrix[node][i] == 1) { // If there is a connection
                    connectedRooms.push_back(i);
                }
            }
        }
        else {
            cout << "Invalid node ID." << endl;
        }

        return connectedRooms;
    }


    bool isConnected(int node1, int node2) {
        if (node1 >= 0 && node1 < adjacencyMatrix.size() &&
            node2 >= 0 && node2 < adjacencyMatrix.size()) {
            return adjacencyMatrix[node1][node2] == 1;
        }
        return false;
    }

    vector<int> findShortestPath(int startNode, int endNode) {
        vector<int> distances(adjacencyMatrix.size(), INT_MAX);
        vector<int> parent(adjacencyMatrix.size(), -1);
        vector<bool> visited(adjacencyMatrix.size(), false);
        distances[startNode] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, startNode });

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (visited[currentNode]) continue;
            visited[currentNode] = true;

            for (int neighbor = 0; neighbor < adjacencyMatrix[currentNode].size(); neighbor++) {
                if (adjacencyMatrix[currentNode][neighbor] == 1) { // Connected node
                    int newDistance = currentDistance + 1; // Weight is 1
                    if (newDistance < distances[neighbor]) {
                        distances[neighbor] = newDistance;
                        parent[neighbor] = currentNode;
                        pq.push({ newDistance, neighbor });
                    }
                }
            }
        }

        // Reconstruct the path
        vector<int> path;
        for (int current = endNode; current != -1; current = parent[current]) {
            path.push_back(current);
        }
        reverse(path.begin(), path.end());
        if (!path.empty() && path[0] == startNode) return path; // Valid path
        return {}; // No path found
    }

    // Generates a maze-like graph with a guaranteed path
    void generateMazeGraph(int numNodes, int startNode, int endNode) {
        srand(time(0));
        // Ensure the adjacency matrix is initialized to all zeros
        adjacencyMatrix.assign(numNodes, vector<int>(numNodes, 0));

        // Generate a guaranteed path of length 5-10
        int pathLength = 5 + (rand() % 1); // Random length between 10 and 15
        vector<int> pathNodes;
        pathNodes.push_back(startNode);

        // Generate intermediate nodes in the path
        for (int i = 0; i < pathLength - 2; ++i) {
            int nextNode;
            do {
                nextNode = rand() % numNodes;
            } while (find(pathNodes.begin(), pathNodes.end(), nextNode) != pathNodes.end());
            pathNodes.push_back(nextNode);
        }
        pathNodes.push_back(endNode);

        // Debugging: Print path nodes
        for (int node : pathNodes) {
            winningPath.push_back(node);
        }
        cout << endl;

        // Connect nodes in the guaranteed path
        for (int i = 0; i < pathNodes.size() - 1; ++i) {
            addEdge(pathNodes[i], pathNodes[i + 1]);
        }

        // Add additional random connections to create maze complexity
        int extraEdges = numNodes * 2; // Adjust for desired complexity
        for (int i = 0; i < extraEdges; ++i) {
            int node1 = rand() % numNodes;
            int node2 = rand() % numNodes;

            // Avoid self-loops and duplicate edges
            if (node1 != node2 && adjacencyMatrix[node1][node2] == 0) {
                addEdge(node1, node2);
            }
        }
    }
};





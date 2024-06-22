#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the shortest path from a source vertex to all other vertices
    vector<long long> bellmanFord(int V, vector<vector<int>>& edges, int S) {
        vector<long long> dist(V, LLONG_MAX);
        dist[S] = 0;

        // Relax all edges V-1 times
        for (int i = 0; i < V - 1; ++i) {
            for (auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int weight = edge[2];
                if (dist[u] != LLONG_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // Check for negative weight cycles
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            if (dist[u] != LLONG_MAX && dist[u] + weight < dist[v]) {
                // If we can still relax an edge, then there is a negative weight cycle
                cout << "Graph contains negative weight cycle" << endl;
                return {};
            }
        }

        return dist;
    }
};

// Driver Code
int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> edges;

    cout << "Enter the edges (format: u v w, where u -> v with weight w):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int S;
    cout << "Enter the source vertex: ";
    cin >> S;

    Solution obj;
    vector<long long> dist = obj.bellmanFord(V, edges, S);

    if (!dist.empty()) {
        cout << "Shortest distances from vertex " << S << ":" << endl;
        for (int i = 0; i < V; ++i) {
            if (dist[i] == LLONG_MAX) {
                cout << "Vertex " << i << ": INF" << endl;
            } else {
                cout << "Vertex " << i << ": " << dist[i] << endl;
            }
        }
    }

    return 0;
}

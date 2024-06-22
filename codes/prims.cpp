#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Pair of (weight, vertex)
typedef pair<int, int> Pair;

class Graph {
    int V;
    vector<vector<Pair>> adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void primMST();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(w, v));
    adj[v].push_back(make_pair(w, u));
}

void Graph::primMST() {
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    int start = 0; // Starting vertex
    pq.push(make_pair(0, start));
    key[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto x : adj[u]) {
            int v = x.second;
            int weight = x.first;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    cout << "Edges in the MST:" << endl;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << " with weight " << key[i] << endl;
    }
}

// Driver code
int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter the edges (format: u v w, where u -> v with weight w):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.primMST();

    return 0;
}

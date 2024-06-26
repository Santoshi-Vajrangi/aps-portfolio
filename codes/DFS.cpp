#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfsG(vector<int> &vis, int start, vector<int> &dfs, vector<int> adj[]) {
        vis[start] = 1;
        dfs.push_back(start);
        for (auto it : adj[start]) {
            if (!vis[it]) {
                dfsG(vis, it, dfs, adj);
            }
        }
    }

     
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int> dfs;
        vector<int> vis(V, 0);   
        for (int i = 0; i < V; ++i) {
            if (!vis[i]) {
                dfsG(vis, i, dfs, adj);
            }
        }
        return dfs;
    }
};

// Driver Code
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;

        vector<int> adj[V];

        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        Solution obj;
        vector<int> ans = obj.dfsOfGraph(V, adj);
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

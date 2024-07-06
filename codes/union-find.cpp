#include <iostream>
#include <vector>

class UnionFind {
public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);

        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int p) {
        if (parent[p] != p) {
            parent[p] = find(parent[p]); // Path compression
        }
        return parent[p];
    }

    void unite(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);

        if (rootP != rootQ) {
            // Union by rank
            if (rank[rootP] < rank[rootQ]) {
                parent[rootP] = rootQ;
            } else if (rank[rootP] > rank[rootQ]) {
                parent[rootQ] = rootP;
            } else {
                parent[rootQ] = rootP;
                rank[rootP]++;
            }
        }
    }

    bool connected(int p, int q) {
        return find(p) == find(q);
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

int main() {
    int size = 10;
    UnionFind uf(size);

    // Example operations
    uf.unite(1, 2);
    uf.unite(3, 4);
    uf.unite(2, 4);

    std::cout << "Are 1 and 3 connected? " << (uf.connected(1, 3) ? "Yes" : "No") << std::endl;
    std::cout << "Are 1 and 5 connected? " << (uf.connected(1, 5) ? "Yes" : "No") << std::endl;

    return 0;
}

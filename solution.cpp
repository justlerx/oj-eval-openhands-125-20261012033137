#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int size = 0) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }
    
    void resize(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        
        if (rank[x] < rank[y]) {
            parent[x] = y;
        } else if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[y] = x;
            rank[x]++;
        }
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<pair<pair<int, int>, int>> constraints;
        constraints.reserve(n);
        
        vector<int> vars;
        vars.reserve(n * 2);
        
        for (int i = 0; i < n; i++) {
            int a, b, e;
            scanf("%d %d %d", &a, &b, &e);
            constraints.push_back({{a, b}, e});
            vars.push_back(a);
            vars.push_back(b);
        }
        
        // Coordinate compression
        sort(vars.begin(), vars.end());
        vars.erase(unique(vars.begin(), vars.end()), vars.end());
        
        unordered_map<int, int> coord;
        for (int i = 0; i < vars.size(); i++) {
            coord[vars[i]] = i;
        }
        
        UnionFind uf(vars.size());
        
        // Process all equality constraints first
        for (const auto& constraint : constraints) {
            int a = constraint.first.first;
            int b = constraint.first.second;
            int e = constraint.second;
            
            if (e == 1) {
                uf.unite(coord[a], coord[b]);
            }
        }
        
        // Check all inequality constraints
        bool possible = true;
        for (const auto& constraint : constraints) {
            int a = constraint.first.first;
            int b = constraint.first.second;
            int e = constraint.second;
            
            if (e == 0) {
                if (uf.same(coord[a], coord[b])) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}
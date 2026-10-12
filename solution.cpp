#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
public:
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
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
        
        for (int i = 0; i < n; i++) {
            int a, b, e;
            scanf("%d %d %d", &a, &b, &e);
            constraints.push_back({{a, b}, e});
        }
        
        UnionFind uf;
        
        // Process all equality constraints first
        for (const auto& constraint : constraints) {
            int a = constraint.first.first;
            int b = constraint.first.second;
            int e = constraint.second;
            
            if (e == 1) {
                uf.unite(a, b);
            }
        }
        
        // Check all inequality constraints
        bool possible = true;
        for (const auto& constraint : constraints) {
            int a = constraint.first.first;
            int b = constraint.first.second;
            int e = constraint.second;
            
            if (e == 0) {
                if (uf.same(a, b)) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind() {}
    
    void ensure_size(int x) {
        if (x >= parent.size()) {
            int old_size = parent.size();
            parent.resize(x + 1);
            rank.resize(x + 1, 0);
            for (int i = old_size; i <= x; i++) {
                parent[i] = i;
            }
        }
    }
    
    int find(int x) {
        ensure_size(x);
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        ensure_size(x);
        ensure_size(y);
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
        ensure_size(x);
        ensure_size(y);
        return find(x) == find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<pair<pair<int, int>, int>> constraints;
        constraints.reserve(n);
        
        int max_var = 0;
        for (int i = 0; i < n; i++) {
            int a, b, e;
            cin >> a >> b >> e;
            constraints.push_back({{a, b}, e});
            max_var = max(max_var, max(a, b));
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
        
        cout << (possible ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
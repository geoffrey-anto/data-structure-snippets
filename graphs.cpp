#include<bits/stdc++.h>
#include <vector>
using namespace std;

vector<vector<int>> getAdjacencyList(int n, vector<vector<int>> &edges, bool directed = false) {
    vector<vector<int>> adj(n, vector<int>());

    for(auto &edge: edges) {
        if(directed) {
            adj[edge[0]].push_back(edge[1]);
        } else {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
    }

    return adj;
}

void dfs(int n, vector<vector<int>> &g, vector<int> &vis) {
    vis[n] = 1;

    for(auto &node: g[n]) {
        if(!vis[node]) {
            dfs(node, g, vis);
        }
    }
} 

void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void dfsTopoSort(int current, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& stk) {
    visited[current] = true;

    for (int neighbor : adj[current]) {
        if (!visited[neighbor]) {
            dfsTopoSort(neighbor, adj, visited, stk);
        }
    }
    stk.push(current);
}

vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    stack<int> stk;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfsTopoSort(i, adj, visited, stk);
        }
    }

    vector<int> result;
    while (!stk.empty()) {
        result.push_back(stk.top());
        stk.pop();
    }
    return result;
}

class DSU {
    private:
    vector<int> parent, rank, size;
    int _n;

    public:
    DSU(int n) {
        this->_n = n;

        parent.resize(n);
        rank.resize(n);
        size.resize(n);

        for(int i=0; i<n; i++) {
            parent[i] = i;
            rank[i] = size[i] = 1;
        }
    }

    int findUPar(int n) {
        if(parent[n] != n) {
            parent[n] = findUPar(parent[n]);
        }

        return parent[n];
    } 

    bool unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);

        if(ulp_u == ulp_v) {
            return false;
        }

        if(rank[ulp_u] > rank[ulp_v]) {
            parent[ulp_v] = ulp_u;
        } else if(rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }

        return true;
    }

    bool unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);

        if (ulp_u == ulp_v) return false;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }

        return true;
    }

    void reset(int node) {
        parent[node] = node;
        rank[node] = 1;
    }

    int getNoOfComponents() {
        int ans = 0;
        
        for(int i=0; i<_n; i++) {
            if(parent[i] == i) {
                ans++;
            }
        }

        return ans;
    }
};

vector<int> dijkstraWithLimit(int src, int n, int lim, vector<vector<pair<int, int>>> &adj) {
    vector<int> dist(n, 1e9);

    //          sz       node d
    queue<pair<int, pair<int, int>>> q;

    dist[src] = 0;

    q.push({
        0, {
            src, 0
        }
    });

    while(!q.empty()) {
        auto top = q.front();
        q.pop();

        int sz = top.first;
        int node = top.second.first;
        int d = top.second.second;

        if(sz > lim) {
            continue;
        }

        for(auto a: adj[node]) {
            int next = a.first;
            int w = a.second;

            if(d + w < dist[next] && sz <= lim) {
                dist[next] = d + w;

                q.push({sz+1, {
                    next, d + w
                }});
            }
        }
    }

    return dist;
}

vector<int> dijkstra(int src, int n, vector<vector<pair<int, int>>> &adj) {
    vector<int> dist(n, 1e9);

    queue<pair<int, int>> q;

    dist[src] = 0;

    q.push({
        src, 0
    });

    while(!q.empty()) {
        auto top = q.front();
        q.pop();

        int node = top.first;
        int d = top.second;

        for(auto a: adj[node]) {
            int next = a.first;
            int w = a.second;

            if(d + w < dist[next]) {
                dist[next] = d + w;

                q.push({
                    next, d + w
                });
            }
        }
    }

    return dist;
}

vector<int> topo(int N, vector<int> adj[]) {
    queue<int> q;
    vector<int> in(N, 0);

    for(int i = 0;i<N;i++) {
        for(auto it: adj[i]) {
            in[it]++; 
        }
    }
    
    for(int i = 0;i<N;i++) {
        if(in[i] == 0) {
            q.push(i); 
        }
    }

    vector<int> topo;

    while(!q.empty()) {
        int node = q.front(); 
        q.pop(); 
        topo.push_back(node);
        for(auto it : adj[node]) {
            in[it]--;
            if(in[it] == 0) {
                q.push(it); 
            }
        }
    }

    return topo;
}


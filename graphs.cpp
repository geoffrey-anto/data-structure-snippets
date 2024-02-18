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
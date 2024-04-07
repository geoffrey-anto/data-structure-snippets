#include <bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(false);cin.tie(0);
#define vi vector<int>
#define pii pair<int, int>
#define vvi vector<vector<int>>
#define vpii vector<pair<int,int>>
#define loop(i,a,b) for(int i = a; i < b; i++)
#define mp unordered_map<int,int>
#define MAX INT_MAX
#define MIN INT_MIN

class Node {
    public:
    int val;
    Node* left;
    Node* right;

    Node(int v) {
        val = v;
    }
};


Node* buildTree(vector<int> v) {
    if(v.size() == 0) return NULL;

    Node* root = new Node(v[0]);
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while(!q.empty() and i < v.size()) {
        Node* temp = q.front();
        q.pop();

        if(v[i] != -1) {
            temp->left = new Node(v[i]);
            q.push(temp->left);
        }

        i++;

        if(i < v.size() and v[i] != -1) {
            temp->right = new Node(v[i]);
            q.push(temp->right);
        }

        i++;
    }

    return root;
}
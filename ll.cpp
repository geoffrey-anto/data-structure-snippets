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

template <typename T>
void print(T arr)
{
    for (auto i : arr)
    {
        cout << i << ' ';
    }
    cout << endl;
}


class Node {
    public:
    int data;
    Node* next;

    Node(int d) {
        data = d;
        next = NULL;
    }

    Node(int d, Node* n) {
        data = d;
        next = n;
    }
};

Node* buildList(vi v) {
    Node* head = new Node(v[0]);
    Node* temp = head;

    for(int i=1; i<v.size(); i++) {
        Node* n = new Node(v[i]);
        temp->next = n;
        temp = n;
    }

    return head;
}
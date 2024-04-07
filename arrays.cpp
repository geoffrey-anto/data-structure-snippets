#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> merge(vector<vector<int>>& arr) {
    sort(begin(arr), end(arr));

    vector<vector<int>> ans;

    int n = arr.size();

    for(int i=0; i<n; i++) {
        if(ans.empty() or ans.back()[1] < arr[i][0]) {
            ans.push_back(arr[i]);
        } else if(ans.back()[1] >= arr[i][0]) {
            vector<int> b = ans.back();
            ans.pop_back();

            int right = max(b[1], arr[i][1]);

            ans.push_back({b[0], right});
        } 
    }

    return ans;
}
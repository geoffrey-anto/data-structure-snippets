#include <bits/stdc++.h>
using namespace std;

int seg[4 * (int)1e5];

void build(int i, int l, int h, vector<int> &arr,
           function<int(int, int)> update) {
  if (l == h) {
    seg[i] = arr[l];
    return;
  }

  int mid = l + (h - l) / 2;

  build(2 * i + 1, l, mid, arr, update);
  build(2 * i + 2, mid + 1, h, arr, update);

  seg[i] = update(seg[2 * i + 1], seg[2 * i + 2]);
}

int query(int i, int l, int h, int ql, int qh, function<int(int, int)> update,
          int base = 0) {
  if (l > qh || h < ql) {
    return base;
  }

  if (l >= ql && h <= qh) {
    return seg[i];
  }

  int mid = l + (h - l) / 2;

  return update(query(2 * i + 1, l, mid, ql, qh, update, base),
                query(2 * i + 2, mid + 1, h, ql, qh, update, base));
}

void update(int i, int l, int h, int idx, int val, function<int(int, int)> up) {
  if (l == h) {
    seg[i] = val;
    return;
  }

  int mid = l + (h - l) / 2;

  if (idx <= mid) {
    update(2 * i + 1, l, mid, idx, val, up);
  } else {
    update(2 * i + 2, mid + 1, h, idx, val, up);
  }

  seg[i] = up(seg[2 * i + 1], seg[2 * i + 2]);
}
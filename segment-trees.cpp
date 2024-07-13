#include <bits/stdc++.h>
#include <functional>
using namespace std;

class SegTreeLazy {
public:
  vector<int> seg, lazy;
  function<int(int, int)> updateFunc;
  int n = 0;

  SegTreeLazy(function<int(int, int)> u, int n) {
    seg = vector<int>(4 * n, 0);
    lazy = vector<int>(4 * n, 0);
    this->n = n;
    this->updateFunc = u;
  }

  void build(const vector<int>& arr, int i, int l, int h) {
    if (l == h) {
      seg[i] = arr[l];
      return;
    }

    int mid = l + (h - l) / 2;

    build(arr, 2 * i + 1, l, mid);
    build(arr, 2 * i + 2, mid + 1, h);

    seg[i] = updateFunc(seg[2 * i + 1], seg[2 * i + 2]);
  }

  int query(int i, int l, int h, int ql, int qh, int base = 0) {
    if (l > qh || h < ql) {
      return base;
    }

    if (l >= ql && h <= qh) {
      return seg[i];
    }

    int mid = l + (h - l) / 2;

    return updateFunc(query(2 * i + 1, l, mid, ql, qh, base),
                      query(2 * i + 2, mid + 1, h, ql, qh, base));
  }

  void update(int i, int l, int h, int idx, int val) {
    if (l == h) {
      seg[i] = val;
      return;
    }

    int mid = l + (h - l) / 2;

    if (idx <= mid) {
      update(2 * i + 1, l, mid, idx, val);
    } else {
      update(2 * i + 2, mid + 1, h, idx, val);
    }

    seg[i] = updateFunc(seg[2 * i + 1], seg[2 * i + 2]);
  }

  void rangeUpdate(int i, int low, int high, int l, int r, int val) {
    if (lazy[i] != 0) {
      seg[i] += (high - low + 1) * lazy[i];

      if (low != high) {
        lazy[2 * i + 1] += lazy[i];
        lazy[2 * i + 2] += lazy[i];
      }

      lazy[i] = 0;
    }

    if (r < low || l > high || low > high) {
      return;
    }

    if (l <= low && r >= high) {
      seg[i] += (high - low + 1) * val;

      if (low != high) {
        lazy[2 * i + 1] += val;
        lazy[2 * i + 2] += val;
      }

      return;
    }

    int mid = low + (high - low) / 2;

    rangeUpdate(2 * i + 1, low, mid, l, r, val);
    rangeUpdate(2 * i + 2, mid + 1, high, l, r, val);
    seg[i] = updateFunc(seg[2 * i + 1], seg[2 * i + 2]);
  }

  int queryLazy(int i, int low, int high, int l, int r, int val, int base = 0) {
    if (lazy[i] != 0) {
      seg[i] += (high - low + 1) * lazy[i];

      if (low != high) {
        lazy[2 * i + 1] += lazy[i];
        lazy[2 * i + 2] += lazy[i];
      }

      lazy[i] = 0;
    }

    if (r < low || l > high || low > high) {
      return base;
    }

    if (l <= low && r >= high) {
      return seg[i];
    }

    int mid = low + (high - low) / 2;

    int lq = queryLazy(2 * i + 1, low, mid, l, r, val, base);
    int rq = queryLazy(2 * i + 2, mid + 1, high, l, r, val, base);

    return updateFunc(lq, rq);
  }
};

class SegTree {
public:
  vector<int> seg;
  function<int(int, int)> updateFunc;
  int n = 0;

  SegTree(function<int(int, int)> u, int n) {
    seg = vector<int>(4 * n, 0);
    this->n = n;
    this->updateFunc = u;
  }

  void build(const vector<int>& arr, int i, int l, int h) {
    if (l == h) {
      seg[i] = arr[l];
      return;
    }

    int mid = l + (h - l) / 2;

    build(arr, 2 * i + 1, l, mid);
    build(arr, 2 * i + 2, mid + 1, h);

    seg[i] = updateFunc(seg[2 * i + 1], seg[2 * i + 2]);
  }

  int query(int i, int l, int h, int ql, int qh, int base = 0) {
    if (l > qh || h < ql) {
      return base;
    }

    if (l >= ql && h <= qh) {
      return seg[i];
    }

    int mid = l + (h - l) / 2;

    return updateFunc(query(2 * i + 1, l, mid, ql, qh, base),
                      query(2 * i + 2, mid + 1, h, ql, qh, base));
  }

  void update(int i, int l, int h, int idx, int val) {
    if (l == h) {
      seg[i] = val;
      return;
    }

    int mid = l + (h - l) / 2;

    if (idx <= mid) {
      update(2 * i + 1, l, mid, idx, val);
    } else {
      update(2 * i + 2, mid + 1, h, idx, val);
    }

    seg[i] = updateFunc(seg[2 * i + 1], seg[2 * i + 2]);
  }
};
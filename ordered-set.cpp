#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename T>
tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>
getOrderedSet() {
  return tree<T, null_type, less<T>, rb_tree_tag,
              tree_order_statistics_node_update>();
}

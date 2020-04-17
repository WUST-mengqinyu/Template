#include <bits/extc++.h>
#pragma comment(linker, "/STACK:102400000,102400000")
using namespace __gnu_pbds; // tree, gp_hash_table, trie
using namespace __gnu_cxx; // rope
tree<TYPE, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> tr;
// 可并堆
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> q[maxn];
//q[i].join(q[j]) 将j堆并入i
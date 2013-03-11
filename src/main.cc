#include <cstdio>
#include <functional>
#include "segtree.h"

int main() {
  const int n = 8;
  SegmentTree<int> segmentTree(n, 1,
                               std::multiplies<int>());

  for (int i = 0; i < n; ++i)
    segmentTree.set(i, i + 1);

  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j) {
      int s = segmentTree.get(i, j);
      std::printf(
        "Function applied from data[%d] to data[%d] is equal to %d \n",
        i, j, s);
    }

  return 0;
}

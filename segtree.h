//============================================================================
// Name        : segtree.h
// Author      : Oleksandr
// Copyright   : Licensed with GPL2
// Description : Segment tree class in C++11
//============================================================================

#ifndef SEGTREE_H_ // NOLINT
#define SEGTREE_H_

#include <cassert>
#include <functional>
#include <vector>

template <typename T>
class SegmentTree {
 private:
  std::vector<T> tree;
  int levels;
  int el;
  std::function<T(T, T)> f;
  std::function<T(T, T)> f_inv;

 public:
  SegmentTree(const std::vector<T>& data,
      std::function<T(T, T)> f = std::plus<T>(),
      std::function<T(T, T)> f_inv = std::minus<T>()) {
    this -> f     = f;
    this -> f_inv = f_inv;

    // build tree
    levels = 1, el = 1;
    while (el < static_cast<int>(data.size())) {
      el <<= 1;
      ++levels;
    }
    tree.assign(2 * el, T());
    for (size_t i = 0; i < data.size(); ++i)
      tree[i + el - 1] = data[i];
    for (int i = el - 2; i >= 0; --i)
      tree[i] = f(tree[2 * i + 1], tree[2 * i + 2]);
  }

  SegmentTree(int n, T val = T(),
      std::function<T(T, T)> f = std::plus<T>(),
      std::function<T(T, T)> f_inv = std::minus<T>()) :
        SegmentTree(std::vector<T>(n, val), f, f_inv) {
  }

  T query(int level, int r) {
    assert(r >= 0 && level >= 0);
    if (level == levels - 1)  // last level - only one element
      return get(r);
    int seg_size = el / (1 << level);    // size of segment on current level
    int seg = r / seg_size;              // number of segment on this level
    int seg_child = r / (seg_size / 2);  // number of segment on next level
    int st  = seg_size * seg;            // start of the current segment
    int mid = st + seg_size / 2;         // first value in the left subsegment
    if (st + seg_size - 1 == r)
      return tree[(1 << level) + seg - 1];
    else if (r < mid)
      return query(level + 1, r);
    else
      return f(tree[(2 << level) + seg_child - 2], query(level + 1, r));
  }

  T get(int l, int r) {
    if (l == 0)
      return query(0, r);
    else
      return f_inv(query(0, r), query(0, l - 1));
  }

  T get(int index) {
    return tree[el - 1 + index];
  }

  void set(int index, T value) {
    int i = el - 1 + index;
    T prev_ch = tree[i], new_ch = value;
    tree[i] = value;
    do {
      i = (i - 1) / 2;
      T new_prev_ch = tree[i];
      tree[i] = f(f_inv(tree[i], prev_ch), new_ch);
      prev_ch = new_prev_ch;
      new_ch = tree[i];
    } while (i != 0);
  }
};


#endif /* SEGTREE_H_ */ // NOLINT

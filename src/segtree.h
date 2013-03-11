#ifndef SEGTREE_H_
#define SEGTREE_H_

#include <cassert>
#include <functional>
#include <vector>

template <typename T>
class SegmentTree {
public:
  SegmentTree(const std::vector<T>& data,
              std::function<T(T, T)> f = std::plus <T>()) {
    this->f = f;
    this->n = data.size();
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
              std::function<T(T, T)> f = std::plus <T>()) :
    SegmentTree(std::vector<T>(n, val), f) {
  }


  T get(int l, int r) {
    return query(l, r, 0, n);
  }

  T get(int index) {
    return tree[el - 1 + index];
  }

  void set(int index, T value) {
    int i = el - 1 + index;
    tree[i] = value;

    do {
      i = (i - 1) / 2;
      tree[i] = f(tree[i * 2 + 1], tree[i * 2 + 2]);
    } while (i > 0);
  }

private:
  std::vector<T> tree;
  int levels;
  int n;
  int el;
  std::function<T(T, T)> f;

  T query(int l, int r, int st, int fi) {
    if (l == r)
      return get(l);

    int mid = (st + fi + 1) / 2;

    if (r < mid) {
      return query(l, r, st,  mid - 1);
    } else if (l >= mid) {
      return query(l, r, mid, fi);
    } else {
      T left  = query(l,   mid - 1, st,  mid - 1);
      T right = query(mid, r,       mid, fi);
      return f(left, right);
    }
  }
};


#endif /* SEGTREE_H_ */

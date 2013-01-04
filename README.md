segtree
=======

Segment tree is a data structure which supports fast θ(logn) queries on segments [a,b] where query is F(arr[a], F(arr[a+1], ...(F(arr[b-1], arr[b])))) for [monoids][MN].

Monoid is a triple of <U,F,e>, where U - is a set of elements, F - associative function, e - neutral element such that ∀x: x+e = x.

Here is implemented segment tree class in header file and provided example of usage in source file.

Notes: 
 * used C++11
 * performed static checker using Google's cpplint.py

------
Read more about segment tree [here][ST]

[MN]: http://en.wikipedia.org/wiki/Monoid
[ST]: http://en.wikipedia.org/wiki/Segment_tree
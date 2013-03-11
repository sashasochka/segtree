segtree
=======

[Segment tree][ST] is a data structure which supports and uses:
 * fast θ(logn) queries for monoids on segments [a,b] where query is result of repetitive applied function to all elements in this segment (similar to reduce or [fold][FLD] in functional programming). 
 ```F(arr[a], F(arr[a+1], ...(F(arr[b-1], arr[b])))) ``` 
 * fast θ(logn) elements update
 * θ(n) initialization time
 * θ(n) memory

[Monoid][MN] is a triple of {U, F, ε}, where U - is a set of elements, F - associative function, e - neutral element such that ∀x ∈ U: F(x, ε) = x.

Here is implemented segment tree class in header file and provided example of usage in source file.

Notes: 
 * used C++11

[MN]: http://en.wikipedia.org/wiki/Monoid
[ST]: http://en.wikipedia.org/wiki/Segment_tree
[FLD]: http://en.wikipedia.org/wiki/Fold_%28higher-order_function%29

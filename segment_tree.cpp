#include <bits/stdc++.h>
using namespace std;

#define num long long int
#define v vector
#define vi v<num>

class SegTree {
public:
  v<num> st; // segment tree is stored as an array
  v<num> arr; num N; // arr is original array. N is its size
  v<num> lazy; // lazy values 

  num l(num p) {return 2*p;} // find left node of current parent
  num r(num p) {return 2*p + 1;} // find right node of current parent 

  void build(num p, num L, num R) { // build the segment tree from the root node
    if (L == R) st[p] = arr[L];     // leaf node
    else {
      num m = floor((L+R)/2);
      build(l(p), L, m);            // build children first
      build(r(p), m+1, R);
      st[p] = st[l(p)] + st[r(p)]; // use children to build parent 
    }
  }

  void prop(num p, num L, num R) { // update node with lazy flag
    // note: this is also called lazy propagation
    // hence the function name "prop"
    if (lazy[p] == 0) return;       // no lazy flag
    else { // update flag
      num total = R - L + 1;
      st[p] = total * lazy[p];
    }

    num m = floor((L+R)/2);
    if (L == R) {                  // leaf node- 
      lazy[p] = 0;
      return;
    }        
    // if previous updates are pending, they must be stored
    // in the child nodes
    if (lazy[l(p)]) prop(l(p), L, m);
    if (lazy[r(p)]) prop(r(p), m+1, R);
    // mark child nodes as lazy 
    lazy[l(p)] = lazy[p];
    lazy[r(p)] = lazy[p];
    lazy[p] = 0; // parent node not wrong any more
  }

  num rsq(num p, num L, num R, num i, num j) { // rsq: range sum query 
    prop(p, L, R); // propagate lazy first
    if (i > j) return 0;
    if ((L >= i) && (R <= j)) return st[p];
    num m = floor((L+R)/2);
    if (L == R) return 0;
    // return rsq of both children 
    return rsq(l(p), L, m, i, min(m,j)) + rsq(r(p), m+1, R, max(m+1,i), j);
  }

  // shorthand for rsq between range [i,j]
  num rsq(num i, num j) {return rsq(1,0,N-1,i,j);}

  // update an entire range [i,j]
  void range_update(num p, num L, num R, num i, num j) {
    prop(p, L, R);
    if (i > j) return;
    if ((L >= i) && (R <= j)) {
      lazy[p] = 1;
      prop(p, L, R);
    }
    else {
      num m = floor((L+R)/2);
      if (L == R) return;
      range_update(l(p), L, m, i, min(m,j));
      range_update(r(p), m+1, R, max(m+1,i), j);
      st[p] = st[l(p)] + st[r(p)];
    }
  }
  
  void range_update(num i, num j, num d) {range_update(1, 0, N-1, i ,j);}

  // initialise a segment tree
  SegTree(v<num> a) {
    N = a.size();
    arr.assign(N, 0);
    for (num i = 0; i < N; i++) arr[i] = a[i];
    st.assign(4*N, 0);
    lazy.assign(4*N, 2);
    build(1,0,N-1);
  }

};

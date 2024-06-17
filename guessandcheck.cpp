#include <bits/stdc++.h>
using namespace std;

int n, t[8], a[8], b[8], L;

bool possible(int pL) {
  int last = a[t[0]];
  for (int i = 1; i < n; i++) {
    last = max(last+pL, a[t[i]]);
    if (last > b[t[i]]) return false; 
  }
  return true;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i]; 
    t[i] = i;
  }
  L=0;
  do {
    int l = 0, r = 1440, pL = 0; 
    for (int i = 0; i < 11; i++) { // max tries = log(1440) < 11
      pL = (l+r)/2;
      if (possible(pL)) l=pL;
      else r = pL;
    }
    L = max(L, pL);
  } while (next_permutation(t, t+n));

  return 0;
}
